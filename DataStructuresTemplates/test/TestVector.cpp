#include "gtest\gtest.h"
#include "..\include\vector.h"

using pkl::vector;

#define TESTVECTOR

#ifdef TESTVECTOR

// Need to change the way capacity works, now it`s equal to size that is extremely inefficient, unless we use reserve();

class ConstructorsTest : public ::testing::Test {};

TEST_F(ConstructorsTest, DefaultConstructor) {
    vector<int> vec;

    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.begin(), nullptr);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.begin(), vec.end());
}

TEST_F(ConstructorsTest, InitializerList) {
    vector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), 5);
    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 5);

    vec = { 10, 20, 30, 40, 50 };

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.front(), 10);
    EXPECT_EQ(vec.back(), 50);
}

TEST_F(ConstructorsTest, FillConstructor) {
    vector<int> vec(2, 10);

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.front(), 10);
    EXPECT_EQ(vec.back(), 10);
}

TEST_F(ConstructorsTest, CopyConstructor) {
    vector<int> vec = { 1, 2, 3, 4 };

    vector<int> vecTest(vec);

    ASSERT_NE(vec.begin(), vecTest.begin());
    ASSERT_NE(vec.end(), vecTest.end());

    EXPECT_EQ(vecTest.size(), 4);
    EXPECT_EQ(vecTest.front(), 1);
    EXPECT_EQ(vecTest.back(), 4);
    EXPECT_EQ(vecTest[1], 2);
    EXPECT_EQ(vecTest[2], 3);
}

TEST_F(ConstructorsTest, MoveConstructor) {
    vector<int> vec = { 1, 2, 3, 4 };

    vector<int> testVec(std::move(vec));

    ASSERT_EQ(vec.begin(), nullptr);
    ASSERT_EQ(vec.size(), 0);
    ASSERT_NE(vec.begin(), testVec.begin());

    EXPECT_EQ(testVec.size(), 4);
    EXPECT_EQ(testVec.front(), 1);
    EXPECT_EQ(testVec.back(), 4);
    EXPECT_EQ(testVec[1], 2);
    EXPECT_EQ(testVec[2], 3);
}

class AssignmentOperatorTest : public ::testing::Test {};

TEST_F(AssignmentOperatorTest, AssignmentOperator) {
    vector<int> vec = { 1, 2, 3, 4 };

    vector<int> testVec = { 5, 6, 7 };

    testVec = vec;

    ASSERT_NE(vec.begin(), testVec.begin());

    EXPECT_EQ(testVec.size(), 4);
    EXPECT_EQ(testVec.front(), 1);
    EXPECT_EQ(testVec.back(), 4);
    EXPECT_EQ(testVec[1], 2);
    EXPECT_EQ(testVec[2], 3);
}

TEST_F(AssignmentOperatorTest, MoveAssignmentOperator) {
    vector<int> vec = { 1, 2, 3, 4 };

    vector<int> testVec = { 5, 6, 7 };

    testVec = std::move(vec);

    ASSERT_NE(vec.begin(), testVec.begin());
    ASSERT_EQ(vec.begin(), nullptr);
    ASSERT_EQ(vec.size(), 0);

    EXPECT_EQ(testVec.size(), 4);
    EXPECT_EQ(testVec.front(), 1);
    EXPECT_EQ(testVec.back(), 4);
    EXPECT_EQ(testVec[1], 2);
    EXPECT_EQ(testVec[2], 3);
}

class SquareBrackets : public ::testing::Test {};

TEST_F(SquareBrackets, NonEmptyList) {
    vector<int> vec(2, 10);

    //ASSERT_THROW(list[2], ListException);

    //list.push_front(10);
    //list.push_back(20);

    //ASSERT_THROW(list[-3], ListException);
    //ASSERT_THROW(list[2], ListException);

    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 10);
}

#endif // TESTVECTOR