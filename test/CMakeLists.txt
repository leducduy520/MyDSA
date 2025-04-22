# Add Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

include_directories(${PROJECT_SOURCE_DIR})

# Add test executable for linked list
add_executable(test_linked_list test_linked_list.cpp)
target_link_libraries(test_linked_list gtest gtest_main)
add_test(NAME test_linked_list COMMAND test_linked_list)

# Add test executable for array
add_executable(test_array test_arr.cpp)
target_link_libraries(test_array gtest gtest_main)
add_test(NAME test_array COMMAND test_array)

# Add test executable for deque
add_executable(test_deque test_deque.cpp)
target_link_libraries(test_deque gtest gtest_main)
add_test(NAME test_deque COMMAND test_deque)

# Add test executable for binary tree
add_executable(test_binary_tree test_binary_tree.cpp)
target_link_libraries(test_binary_tree gtest gtest_main)
add_test(NAME test_binary_tree COMMAND test_binary_tree)

# Add test executable for memory pool
add_executable(test_memory_pool test_memory_pool.cpp)
target_link_libraries(test_memory_pool gtest gtest_main)
add_test(NAME test_memory_pool COMMAND test_memory_pool)

# Add test executable for priority queue
add_executable(test_priority_queue test_priority_queue.cpp)
target_link_libraries(test_priority_queue gtest gtest_main)
add_test(NAME test_priority_queue COMMAND test_priority_queue)

# Add test executable for shared pointer
add_executable(test_shared_pointer test_shared_pointer.cpp)
target_link_libraries(test_shared_pointer gtest gtest_main)
add_test(NAME test_shared_pointer COMMAND test_shared_pointer)

#Add test excutable for quick sort
add_executable(test_quick_sort test_quick_sort.cpp)
target_link_libraries(test_quick_sort gtest gtest_main)
add_test(NAME test_quick_sort COMMAND test_quick_sort)

#Add test excutable for merge sort
add_executable(test_merge_sort test_merge_sort.cpp)
target_link_libraries(test_merge_sort gtest gtest_main)
add_test(NAME test_merge_sort COMMAND test_merge_sort)