#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>

class ThreadPool
{
	struct Task
	{
		std::function<void()> fn;
		unsigned int priority;
		Task() : fn(nullptr), priority(0) {}
		Task(std::function<void()> f, unsigned int p) : fn(f), priority(p) {}
		bool operator<(const Task& other) const {
			return priority < other.priority;
		}
	};

	std::vector<std::thread> workers;
	std::priority_queue<Task> tasks;
	std::mutex queue_mutex;
	std::condition_variable condition;
	std::atomic<bool> stop;
public:
	ThreadPool(unsigned int threads = std::thread::hardware_concurrency()) : stop(false) {
		for (unsigned int i = 0; i < threads; ++i)
		{
			workers.emplace_back([this]() mutable {
				while (true)
				{
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(queue_mutex);
						condition.wait(lock, [&] { return stop || !tasks.empty(); });
						if (stop && tasks.empty())
							return;
						task = tasks.top().fn;
						tasks.pop();
					}
					task();
				}
				});
		}
	}

	~ThreadPool() {
		Stop();
	}

	template<typename F, typename... Args>
	auto Submit(unsigned int priority, F&& f, Args&&... args) -> std::future<std::invoke_result<F, Args...>>
	{
		using return_type = std::invoke_result<F, Args...>;
		auto task = std::make_shared<std::packaged_task<return_type()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);
		auto fut = task->get_future();
		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			if (stop)
				throw std::runtime_error("ThreadPool is stopped");
			tasks.emplace([task]() { (*task)(); }, priority);
		}
		condition.notify_one();
		return fut;
	}

	void Stop() {
		stop = true;
		condition.notify_all();
		for (std::thread& worker : workers) {
			if (worker.joinable()) {
				worker.join();
			}
		}
	}
};