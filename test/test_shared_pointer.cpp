#include <gtest/gtest.h>
#include "data_structure/shared_pointer.hpp"

// Test SharedPointer initialization
TEST(SharedPointerTest, ConstructorAndDestructor) {
    SharedPointer<int> sp(new int(10));
    EXPECT_EQ(*sp, 10);
}

// Test copy constructor
TEST(SharedPointerTest, CopyConstructor) {
    SharedPointer<int> sp1(new int(20));
    SharedPointer<int> sp2(sp1);
    EXPECT_EQ(*sp1, 20);
    EXPECT_EQ(*sp2, 20);
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
}

// Test assignment operator
TEST(SharedPointerTest, AssignmentOperator) {
    SharedPointer<int> sp1(new int(30));
    SharedPointer<int> sp2;
    sp2 = sp1;
    EXPECT_EQ(*sp1, 30);
    EXPECT_EQ(*sp2, 30);
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
}

// Test move constructor
TEST(SharedPointerTest, MoveConstructor) {
    SharedPointer<int> sp1(new int(40));
    SharedPointer<int> sp2(std::move(sp1));
    EXPECT_EQ(*sp2, 40);
    EXPECT_EQ(sp2.use_count(), 1);
    EXPECT_EQ(sp1.get(), nullptr);
}

// Test move assignment operator
TEST(SharedPointerTest, MoveAssignmentOperator) {
    SharedPointer<int> sp1(new int(50));
    SharedPointer<int> sp2;
    sp2 = std::move(sp1);
    EXPECT_EQ(*sp2, 50);
    EXPECT_EQ(sp2.use_count(), 1);
    EXPECT_EQ(sp1.get(), nullptr);
}

// Test reset
TEST(SharedPointerTest, Reset) {
    SharedPointer<int> sp(new int(60));
    sp.reset(new int(70));
    EXPECT_EQ(*sp, 70);
    EXPECT_EQ(sp.use_count(), 1);
}

// Test use_count
TEST(SharedPointerTest, UseCount) {
    SharedPointer<int> sp1(new int(80));
    SharedPointer<int> sp2(sp1);
    SharedPointer<int> sp3(sp2);
    EXPECT_EQ(sp1.use_count(), 3);
    EXPECT_EQ(sp2.use_count(), 3);
    EXPECT_EQ(sp3.use_count(), 3);
    sp2.reset();
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp3.use_count(), 2);
}

// Test dereference operator
TEST(SharedPointerTest, DereferenceOperator) {
    SharedPointer<int> sp(new int(90));
    EXPECT_EQ(*sp, 90);
    *sp = 100;
    EXPECT_EQ(*sp, 100);
}

// Test get
TEST(SharedPointerTest, Get) {
    int* rawPtr = new int(110);
    SharedPointer<int> sp(rawPtr);
    EXPECT_EQ(sp.get(), rawPtr);
}

// Test null SharedPointer
TEST(SharedPointerTest, NullSharedPointer) {
    SharedPointer<int> sp;
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
}