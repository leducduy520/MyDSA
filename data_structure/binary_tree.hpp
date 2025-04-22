#include <stdexcept>
#include <queue>
template <typename T>
class BinarySearchTree
{
private:
    struct Node
    {
        T data;
        Node *left;
        Node *right;
        Node(T value) : data(value), left(nullptr), right(nullptr) {}
        Node(const Node &other) : data(other.data), left(other.left), right(other.right) {}
        Node &operator=(const Node &other)
        {
            if (this != &other)
            {
                data = other.data;
                left = other.left;
                right = other.right;
            }
            return *this;
        }
        ~Node() {}
    };
    Node *root;
    void release(Node *node)
    {
        if (node)
        {
            release(node->left);
            release(node->right);
            delete node;
        }
    }
    void deep_copy(Node *&thisNode, Node *otherNode)
    {
        if (otherNode)
        {
            if (thisNode)
            {
                thisNode->data = otherNode->data;
            }
            else
            {
                thisNode = new Node(otherNode->data);
            }
            deep_copy(thisNode->left, otherNode->left);
            deep_copy(thisNode->right, otherNode->right);
        }
        else
        {
            thisNode = nullptr;
        }
    }
    Node *find_min(Node *node) const
    {
        while (node && node->left)
        {
            node = node->left;
        }
        return node;
    }
    Node *find_max(Node *node) const
    {
        while (node && node->right)
        {
            node = node->right;
        }
        return node;
    }
    void insert(Node *&node, const T &value)
    {
        if (!node)
        {
            node = new Node(value);
            return;
        }
        if (value < node->data)
        {
            insert(node->left, value);
        }
        else
        {
            insert(node->right, value);
        }
    }
    void erase(Node *&node, const T &value)
    {
        if (!node)
        {
            return;
        }
        if (value < node->data)
        {
            erase(node->left, value);
        }
        else if (value > node->data)
        {
            erase(node->right, value);
        }
        else
        {
            if (!node->left && !node->right)
            {
                delete node;
                node = nullptr;
            }
            else if (!node->left)
            {
                Node *temp = node;
                node = node->right;
                delete temp;
            }
            else if (!node->right)
            {
                Node *temp = node;
                node = node->left;
                delete temp;
            }
            else
            {
                Node *temp = find_min(node->right);
                node->data = temp->data;
                erase(node->right, temp->data);
            }
        }
    }
    void height(Node *node, size_t &h) const
    {
        if (!node)
        {
            return;
        }
        h++;
        size_t left_height = h, right_height = h;
        height(node->left, left_height);
        height(node->right, right_height);
        h = std::max(left_height, right_height);
    }
    void count_nodes(Node *node, size_t &count) const
    {
        if (node)
        {
            count++;
            count_nodes(node->left, count);
            count_nodes(node->right, count);
        }
    }
    void count_leaves(Node *node, size_t &count) const
    {
        if (node)
        {
            if (!node->left && !node->right)
            {
                count++;
            }
            count_leaves(node->left, count);
            count_leaves(node->right, count);
        }
    }
    void is_full(Node *node, bool &full) const
    {
        if (node)
        {
            if ((node->left && !node->right) || (!node->left && node->right))
            {
                full &= false;
                return;
            }
            bool left_full = true, right_full = true;
            is_full(node->left, full);
            is_full(node->right, full);
            full &= left_full && right_full;
        }
    }

public:
    void clear()
    {
        release(root);
        root = nullptr;
    }
    BinarySearchTree() : root(nullptr) {}
    BinarySearchTree(const BinarySearchTree &other)
    {
        if (!other.root)
        {
            throw std::runtime_error("Tree is empty");
        }
        clear();
        deep_copy(root, other.root);
    }
    ~BinarySearchTree()
    {
        clear();
    }
    void insert(const T &value)
    {
        insert(root, value);
    }
    void erase(const T &value)
    {
        erase(root, value);
    }
    Node *find_min() const
    {
        return find_min(root);
    }
    Node *find_max() const
    {
        return find_max(root);
    }
    Node *find(const T &value) const
    {
        Node *current = root;
        while (current)
        {
            if (value < current->data)
            {
                current = current->left;
            }
            else if (value > current->data)
            {
                current = current->right;
            }
            else
            {
                return current;
            }
        }
        return nullptr;
    }
    size_t size() const
    {
        size_t count = 0;
        count_nodes(root, count);
        return count;
    }
    long long height() const
    {
        if (root == nullptr)
        {
            return -1;
        }
        size_t h = -1;
        height(root, h);
        return h;
    }
    size_t max_nodes() const
    {
        size_t h = height();
        return (1 << (h + 1)) - 1;
    }
    size_t leaves() const
    {
        size_t count = 0;
        count_leaves(root, count);
        return count;
    }
    bool is_empty() const
    {
        return root == nullptr;
    }
    bool is_full() const
    {
        bool full = true;
        is_full(root, full);
        return full;
    }
    bool is_completed() const
    {
        if (!root)
        {
            return true;
        }
        Node *left = nullptr;
        Node *right = nullptr;
        size_t level = 0;
        std::queue<Node *> queue;
        queue.push(root);
        while (!queue.empty())
        {   
            size_t prev_level = level;
            for (size_t i = 0; i < (1 << level); ++i)
            {
                if (queue.empty())
                {
                    break;
                }
                Node *node = queue.front();
                left = node->left;
                right = node->right;
                queue.pop();
                if (left == nullptr && right != nullptr)
                {
                    return false;
                }
                if (left != nullptr)
                {
                    queue.push(left);
                    if (i != 0 && prev_level != level + 1)
                    {
                        return false;
                    }
                    prev_level = level + 1;
                }
                else
                {
                    prev_level = level;
                }
                if (right != nullptr)
                {
                    queue.push(right);
                }
            }
            level++;
        }
        return true;
    }
    void print_in_order(Node *node) const
    {
        if (node)
        {
            print_in_order(node->left);
            std::cout << node->data << " ";
            print_in_order(node->right);
        }
    }
    void print_tree() const
    {
        print_in_order(root);
        std::cout << std::endl;
    }
};