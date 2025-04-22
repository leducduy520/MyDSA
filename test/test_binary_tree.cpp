#include "data_structure/binary_tree.hpp"
#include <gtest/gtest.h>

// Test BinarySearchTree initialization
TEST(BinaryTreeTest, ConstructorAndDestructor) {
    BinarySearchTree<int> tree;
    EXPECT_NO_THROW(tree.insert(10));
    EXPECT_NO_THROW(tree.clear());
}

// Test insert
TEST(BinaryTreeTest, Insert) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    EXPECT_EQ(tree.find(10)->data, 10);
    EXPECT_EQ(tree.find(5)->data, 5);
    EXPECT_EQ(tree.find(15)->data, 15);
}

// Test is_completed
TEST(BinaryTreeTest, IsCompleted) {
    BinarySearchTree<int> tree;

    // Test an empty tree (should be completed)
    EXPECT_TRUE(tree.is_completed());

    // Test a single-node tree (should be completed)
    tree.insert(10);
    EXPECT_TRUE(tree.is_completed());

    // Test a complete binary tree
    tree.insert(5);
    tree.insert(15);
    EXPECT_TRUE(tree.is_completed());

    // Test an incomplete binary tree (missing a node)
    tree.insert(2);
    EXPECT_TRUE(tree.is_completed());
    tree.insert(20);
    EXPECT_FALSE(tree.is_completed());

    tree.insert(12);
    EXPECT_TRUE(tree.is_completed());
    tree.insert(7);
    EXPECT_TRUE(tree.is_completed());
    tree.insert(11);
    EXPECT_FALSE(tree.is_completed());

    // Test after clearing the tree
    tree.clear();
    EXPECT_TRUE(tree.is_completed());
}

// Test find
TEST(BinaryTreeTest, Find) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    EXPECT_NE(tree.find(10), nullptr);
    EXPECT_NE(tree.find(5), nullptr);
    EXPECT_NE(tree.find(15), nullptr);
    EXPECT_EQ(tree.find(20), nullptr); // Not in the tree
}

// Test find_min
TEST(BinaryTreeTest, FindMin) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    EXPECT_EQ(tree.find_min()->data, 2);
}

// Test find_max
TEST(BinaryTreeTest, FindMax) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(20);
    EXPECT_EQ(tree.find_max()->data, 20);
}

// Test erase
TEST(BinaryTreeTest, Erase) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.erase(5);
    EXPECT_EQ(tree.find(5), nullptr);
    tree.erase(10);
    EXPECT_EQ(tree.find(10), nullptr);
    tree.erase(15);
    EXPECT_EQ(tree.find(15), nullptr);
}

// Test clear
TEST(BinaryTreeTest, Clear) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.clear();
    EXPECT_EQ(tree.find(10), nullptr);
    EXPECT_EQ(tree.find(5), nullptr);
    EXPECT_EQ(tree.find(15), nullptr);
}

// Test height
TEST(BinaryTreeTest, Height) {
    BinarySearchTree<int> tree;

    // Test height of an empty tree
    EXPECT_EQ(tree.height(), -1);

    // Test height after inserting a single node
    tree.insert(10);
    EXPECT_EQ(tree.height(), 0);

    // Test height after creating a balanced tree
    tree.insert(5);
    tree.insert(15);
    EXPECT_EQ(tree.height(), 1);

    // Test height after adding nodes to one side (unbalanced tree)
    tree.insert(2);
    tree.insert(1);
    EXPECT_EQ(tree.height(), 3);

    // Test height after adding nodes to the other side
    tree.insert(20);
    tree.insert(25);
    EXPECT_EQ(tree.height(), 3);

    // Test height after clearing the tree
    tree.clear();
    EXPECT_EQ(tree.height(), -1);
}

// Test is_full
TEST(BinaryTreeTest, IsFull) {
    BinarySearchTree<int> tree;
    EXPECT_TRUE(tree.is_full()); // Empty tree is considered full
    tree.insert(10);
    EXPECT_TRUE(tree.is_full());
    tree.insert(5);
    tree.insert(15);
    EXPECT_TRUE(tree.is_full());
    tree.insert(2);
    EXPECT_FALSE(tree.is_full());
}

// Test leaves
TEST(BinaryTreeTest, Leaves) {
    BinarySearchTree<int> tree;
    EXPECT_EQ(tree.leaves(), 0);
    tree.insert(10);
    EXPECT_EQ(tree.leaves(), 1);
    tree.insert(5);
    tree.insert(15);
    EXPECT_EQ(tree.leaves(), 2);
    tree.insert(2);
    EXPECT_EQ(tree.leaves(), 2);
}

// Test duplicate insertions
TEST(BinaryTreeTest, DuplicateInsertions) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(10); // Duplicate
    EXPECT_NE(tree.find(10), nullptr);
    tree.erase(10);
    EXPECT_NE(tree.find(10), nullptr);
}

// Test print_tree (in-order traversal)
TEST(BinaryTreeTest, PrintTree) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    testing::internal::CaptureStdout();
    tree.print_in_order(tree.find_min());
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "5 ");
}

// Test edge cases
TEST(BinaryTreeTest, EdgeCases) {
    BinarySearchTree<int> tree;

    // Find in an empty tree
    EXPECT_EQ(tree.find(10), nullptr);

    // Erase from an empty tree
    EXPECT_NO_THROW(tree.erase(10));

    // Find min and max in an empty tree
    EXPECT_EQ(tree.find_min(), nullptr);
    EXPECT_EQ(tree.find_max(), nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}