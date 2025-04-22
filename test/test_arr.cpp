#include "data_structure/array.hpp"
#include <gtest/gtest.h>

// Test Array initialization
TEST(ArrayTest, ConstructorAndDestructor) {
    Array<int> arr;
    EXPECT_NO_THROW(arr.push_back(1));
    EXPECT_NO_THROW(arr.pop_back());
}

// Test push_back
TEST(ArrayTest, PushBack) {
    Array<int> arr;
    for (int i = 0; i < 10; ++i) {
        arr.push_back(i);
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// Test pop_back
TEST(ArrayTest, PopBack) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.pop_back();
    EXPECT_EQ(arr.back(), 1);
    arr.pop_back();
    EXPECT_THROW(arr.pop_back(), std::runtime_error);
}

// Test at
TEST(ArrayTest, At) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    EXPECT_EQ(arr.at(0), 10);
    EXPECT_EQ(arr.at(1), 20);
    EXPECT_THROW(arr.at(2), std::out_of_range);
}

// Test front and back
TEST(ArrayTest, FrontAndBack) {
    Array<int> arr;
    arr.push_back(5);
    arr.push_back(10);
    EXPECT_EQ(arr.front(), 5);
    EXPECT_EQ(arr.back(), 10);
    arr.pop_back();
    EXPECT_EQ(arr.back(), 5);
}

// Test operator[]
TEST(ArrayTest, OperatorSquareBrackets) {
    Array<int> arr;
    arr.push_back(100);
    arr.push_back(200);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_THROW(arr[2], std::out_of_range);
}

// Test assignment operator
TEST(ArrayTest, AssignmentOperator) {
    Array<int> arr1;
    for (int i = 0; i < 5; ++i) {
        arr1.push_back(i);
    }
    Array<int> arr2;
    arr2 = arr1;
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(arr2[i], i);
    }
}

// Test move assignment operator
TEST(ArrayTest, MoveAssignmentOperator) {
    Array<int> arr1;
    for (int i = 0; i < 5; ++i) {
        arr1.push_back(i);
    }
    Array<int> arr2 = std::move(arr1);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(arr2[i], i);
    }
    EXPECT_THROW(arr1.front(), std::runtime_error); // arr1 should be empty
}

// Test edge cases
TEST(ArrayTest, EdgeCases) {
    Array<int> arr;
    EXPECT_THROW(arr.front(), std::runtime_error);
    EXPECT_THROW(arr.back(), std::runtime_error);
    EXPECT_THROW(arr.pop_back(), std::runtime_error);
    EXPECT_THROW(arr.at(0), std::out_of_range);
}

// Parameterized test fixture
template <typename T>
class ArrayParameterizedTest : public ::testing::Test {
protected:
    Array<T> arr;
};

// Define the types to test
typedef ::testing::Types<int, double, float> TestTypes;
TYPED_TEST_SUITE(ArrayParameterizedTest, TestTypes);

// Test push_back with different types
TYPED_TEST(ArrayParameterizedTest, PushBack) {
    this->arr.push_back(TypeParam(1));
    this->arr.push_back(TypeParam(2));
    EXPECT_EQ(this->arr[0], TypeParam(1));
    EXPECT_EQ(this->arr[1], TypeParam(2));
}

// Test pop_back with different types
TYPED_TEST(ArrayParameterizedTest, PopBack) {
    this->arr.push_back(TypeParam(1));
    this->arr.push_back(TypeParam(2));
    this->arr.pop_back();
    EXPECT_EQ(this->arr.back(), TypeParam(1));
    this->arr.pop_back();
    EXPECT_THROW(this->arr.pop_back(), std::runtime_error);
}

// Test at with different types
TYPED_TEST(ArrayParameterizedTest, At) {
    this->arr.push_back(TypeParam(10));
    this->arr.push_back(TypeParam(20));
    EXPECT_EQ(this->arr.at(0), TypeParam(10));
    EXPECT_EQ(this->arr.at(1), TypeParam(20));
    EXPECT_THROW(this->arr.at(2), std::out_of_range);
}

// Test edge cases with different types
TYPED_TEST(ArrayParameterizedTest, EdgeCases) {
    EXPECT_THROW(this->arr.front(), std::runtime_error);
    EXPECT_THROW(this->arr.back(), std::runtime_error);
    EXPECT_THROW(this->arr.pop_back(), std::runtime_error);
    EXPECT_THROW(this->arr.at(0), std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}