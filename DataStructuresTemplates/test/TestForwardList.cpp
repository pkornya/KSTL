#include <stdio.h>

#include "gtest\gtest.h"
#include "..\include\forward_list.h"

using namespace pkl;

//#define TESTFORWARDLIST

#ifdef  TESTFORWARDLIST

class ConstructorsTest : public ::testing::Test {};

TEST_F(ConstructorsTest, DefaultConstructor) 
{
	forward_list<int> list;

	EXPECT_TRUE(list.empty());
	EXPECT_EQ(list.begin(), nullptr);
	EXPECT_EQ(list.size(), 0);
	EXPECT_EQ(list.begin(), list.end());
}

TEST_F(ConstructorsTest, InitializerList) 
{
	forward_list<int> list = { 1, 2, 3, 4, 5 };

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(list.front(), 1);
	EXPECT_EQ(list.back(), 5);

	list = { 10, 20, 30, 50 };

	EXPECT_EQ(list.size(), 4);
	EXPECT_EQ(list.front(), 10);
	EXPECT_EQ(list.back(), 50);
}

TEST_F(ConstructorsTest, FillConstructor) 
{
	forward_list<int> list(2, 10);

	EXPECT_EQ(list.size(), 2);
	EXPECT_EQ(list.front(), 10);
	EXPECT_EQ(list.back(), 10);
}

TEST_F(ConstructorsTest, CopyConstructor) 
{
	forward_list<int> list = { 1, 2, 3, 4 };

	forward_list<int> testList(list);

	ASSERT_NE(list.begin(), testList.begin());

    testList.pop_front();
	EXPECT_EQ(testList.size(), 3);
	EXPECT_EQ(testList.front(), 2);
	EXPECT_EQ(testList.back(), 4);
	EXPECT_EQ(testList[1], 3);
}

TEST_F(ConstructorsTest, MoveConstructor) 
{
	forward_list<int> list1 = { 1, 2, 3, 4 };

	forward_list<int> testList(std::move(list1));

	ASSERT_EQ(list1.begin(), nullptr);
	ASSERT_EQ(list1.size(), 0);
	ASSERT_NE(list1.begin(), testList.begin());

	EXPECT_EQ(testList.size(), 4);
	EXPECT_EQ(testList.front(), 1);
	EXPECT_EQ(testList.back(), 4);
	EXPECT_EQ(testList[1], 2);
	EXPECT_EQ(testList[2], 3);

    list1 = std::move(testList);
    ASSERT_EQ(testList.begin(), nullptr);
    ASSERT_EQ(testList.size(), 0);
    ASSERT_NE(testList.begin(), list1.begin());

    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1.front(), 1);
    EXPECT_EQ(list1.back(), 4);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
}

class AssignmentOperatorTest : public ::testing::Test {};

TEST_F(AssignmentOperatorTest, AssignmentOperator) 
{
	forward_list<int> list = { 1, 2, 3, 4 };

	forward_list<int> testList = { 5, 6, 7 };

	testList = list;

	ASSERT_NE(list.begin(), testList.begin());

	EXPECT_EQ(testList.size(), 4);
	EXPECT_EQ(testList.front(), 1);
	EXPECT_EQ(testList.back(), 4);
	EXPECT_EQ(testList[1], 2);
	EXPECT_EQ(testList[2], 3);
}

TEST_F(AssignmentOperatorTest, MoveAssignmentOperator) 
{
	forward_list<int> list = { 1, 2, 3, 4 };

	forward_list<int> testList = { 5, 6, 7 };

	testList = std::move(list);

	ASSERT_NE(list.begin(), testList.begin());
	ASSERT_EQ(list.begin(), nullptr);
	ASSERT_EQ(list.size(), 0);

	EXPECT_EQ(testList.size(), 4);
	EXPECT_EQ(testList.front(), 1);
	EXPECT_EQ(testList.back(), 4);
	EXPECT_EQ(testList[1], 2);
	EXPECT_EQ(testList[2], 3);
}

class SizeTest : public ::testing::Test {};

TEST_F(SizeTest, SizeEmpty) 
{
	forward_list<int> list;
	int size = list.size();

	EXPECT_EQ(size, 0);
}

TEST_F(SizeTest, Size1to2) 
{
	forward_list<int> list;
	list.push_front(4);

	EXPECT_EQ(list.size(), 1);

	list.push_front(9);
	EXPECT_EQ(list.size(), 2);
}

TEST_F(SizeTest, Size3) {
	forward_list<int> list;

	list.push_front(4);
	list.push_front(9);
	list.push_front(13);

	EXPECT_EQ(list.size(), 3);
}

class EmptyTest : public ::testing::Test {};

TEST_F(EmptyTest, Empty) 
{
	forward_list<std::string> list;

	EXPECT_TRUE(list.empty());
	list.push_front("word");

	EXPECT_FALSE(list.empty());
}

class PushFrontTest : public ::testing::Test {};

TEST_F(PushFrontTest, Front1) 
{
	forward_list<int> list;

	list.push_front(123);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.front(), 123);
}

TEST_F(PushFrontTest, Front2) 
{
	forward_list<int> list;

	list.push_front(123);
	list.push_front(456);
	list.push_front(-123);
	list.push_front(45);

	EXPECT_EQ(list.size(), 4);
	EXPECT_EQ(list.front(), 45);
}

class AssignTest : public ::testing::Test {};

TEST_F(AssignTest, AssignFill) 
{
    forward_list<int> list = { 1, 2, 3, 5 };

    list.assign(3, 20);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.back(), 20);
    EXPECT_EQ(list[1], 20);
}


TEST_F(AssignTest, AssignInitList) 
{
    forward_list<int> list = { 1, 2, 3, 5 };

    list.assign({ 20, 30, 40, 50 });
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.back(), 50);
    EXPECT_EQ(list[1], 30);
    EXPECT_EQ(list[2], 40);

    list.assign({ 1, 2, 3, 4 });
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 4);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

class SquareBrackets : public ::testing::Test {};

TEST_F(SquareBrackets, EmptyList) 
{
	forward_list<int> list;

	ASSERT_THROW(list[2], ListException);
}

TEST_F(SquareBrackets, NonEmptyList) 
{
	forward_list<int> list;

	ASSERT_THROW(list[2], ListException);

	list.push_front(10);
	list.push_back(20);

	ASSERT_THROW(list[-3], ListException);
	ASSERT_THROW(list[2], ListException);

	EXPECT_EQ(list[0], 10);
	EXPECT_EQ(list[1], 20);
}

class PushBackTest : public ::testing::Test {};

TEST_F(PushBackTest, PushEmpty) 
{
	forward_list<int> list;

	list.push_back(4);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.back(), 4);
}

TEST_F(PushBackTest, PushNonEmpty) 
{
	forward_list<int> list;

	list.push_front(-78);
	list.push_back(123);
	list.push_back(456);

	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(list.back(), 456);
	EXPECT_EQ(list.value_at(0), -78);
	EXPECT_EQ(list.value_at(1), 123);
}

class PopFrontTest : public ::testing::Test {};

TEST_F(PopFrontTest, PopFrontExceptions) 
{
	forward_list<int> list;

	ASSERT_THROW(list.pop_front(), ListException);
}

TEST_F(PopFrontTest, Pop1) 
{
	forward_list<int> list;

	list.push_front(66);
	int front = list.front();

	EXPECT_EQ(front, 66);
	EXPECT_EQ(list.size(), 1);

	list.pop_front();
	EXPECT_EQ(list.size(), 0);
}

TEST_F(PopFrontTest, Pop2) 
{
	forward_list<int> list;

	list.push_front(12);
	list.push_front(11);
	list.push_front(20);
	list.push_front(-155);

	list.pop_front();
	int front = list.front();
	EXPECT_EQ(front, 20);

	list.pop_front();
	list.pop_front();

	front = list.front();
	EXPECT_EQ(front, 12);
}

class PopBackTest : public ::testing::Test {};

TEST_F(PopBackTest, PopBackExceptions) 
{
	forward_list<int> list;

	ASSERT_THROW(list.pop_back(), ListException);
}

TEST_F(PopBackTest, Pop1) 
{
	forward_list<int> list;

	list.push_back(4);

	int back = list.back();
	list.pop_back();

	EXPECT_EQ(list.size(), 0);
	EXPECT_EQ(back, 4);
}

TEST_F(PopBackTest, Pop2) 
{
	forward_list<int> list;

	list.push_back(33);
	list.push_front(13);
	list.push_back(-455);
	list.push_front(0);

	int back = list.back();
	list.pop_back();

	EXPECT_EQ(back, -455);
	EXPECT_EQ(list.size(), 3);

	back = list.back();
	list.pop_back();

	EXPECT_EQ(back, 33);
	EXPECT_EQ(list.size(), 2);
}

class ValueAtTest : public ::testing::Test {};

TEST_F(ValueAtTest, Value012) 
{
	forward_list<int> list;

	list.push_front(99);
	EXPECT_EQ(list.value_at(0), 99);

	list.push_front(3);
	list.push_front(122);
	EXPECT_EQ(list.value_at(0), 122);
	EXPECT_EQ(list.value_at(1), 3);
	EXPECT_EQ(list.value_at(2), 99);
} 

class InsertTest : public ::testing::Test {};

TEST_F(InsertTest, InsertExceptions) 
{
	forward_list<int> list;

	ASSERT_THROW(list.insert(2, 12), ListException);
	ASSERT_THROW(list.insert(-1, 12), ListException);
}

TEST_F(InsertTest, InsertFrontEmpty) 
{
	forward_list<int> list;

	list.insert(0, 3);

	EXPECT_EQ(list[0], 3);
	EXPECT_EQ(list.size(), 1);
}

TEST_F(InsertTest, InsertFrontNonEmpty) 
{
	forward_list<int> list;

	list.push_front(123);
	list.insert(0, 3);

	EXPECT_EQ(list[0], 3);
	EXPECT_EQ(list[1], 123);
	EXPECT_EQ(list.size(), 2);
}

TEST_F(InsertTest, InsertBack) 
{
	forward_list<int> list{};

	list.push_back(123);
	list.insert(1, 3);

	EXPECT_EQ(list[1], 3);
	EXPECT_EQ(list.size(), 2);
}

TEST_F(InsertTest, InsertMid) 
{
	forward_list<int> list;

	list.push_back(123);
	list.push_back(456);
	list.push_back(999);
	list.insert(2, 777);

	EXPECT_EQ(list[0], 123);
	EXPECT_EQ(list[1], 456);
	EXPECT_EQ(list[2], 777);
	EXPECT_EQ(list[3], 999);
	EXPECT_EQ(list.size(), 4);
}

class RemoveAtTest : public ::testing::Test {};

TEST_F(RemoveAtTest, RemoveAtExceptions) 
{
	forward_list<int> list;
	
	ASSERT_THROW(list.remove_at(2), ListException);
	
	list.push_back(20);
	list.push_front(13);

	ASSERT_THROW(list.remove_at(-1), ListException);
	ASSERT_THROW(list.remove_at(2), ListException);
	ASSERT_THROW(list.remove_at(25), ListException);
}

TEST_F(RemoveAtTest, RemoveOnly) 
{
	forward_list<int> list;

	list.push_back(44);
	list.remove_at(0);

	EXPECT_EQ(list.size(), 0);
}

TEST_F(RemoveAtTest, RemoveFirst) 
{
	forward_list<int> list;

	list.push_back(44);
	list.push_back(55);
	list.remove_at(0);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list[0], 55);
}

TEST_F(RemoveAtTest, RemoveLast) 
{
	forward_list<int> list;

	list.push_back(44);
	list.push_back(55);
	list.remove_at(1);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list[0], 44);
}

TEST_F(RemoveAtTest, RemoveMid) 
{
	forward_list<int> list;

	list.push_back(44);
	list.push_back(55);
	list.push_back(66);
	list.remove_at(1);

	EXPECT_EQ(list.size(), 2);
	EXPECT_EQ(list[0], 44);
	EXPECT_EQ(list[1], 66);
}

class RemoveValueTest : public ::testing::Test {};

TEST_F(RemoveValueTest, RemoveNone) 
{
	forward_list<int> list;

	list.remove_value(5);

	EXPECT_EQ(list.size(), 0);
}

TEST_F(RemoveValueTest, RemoveOnly) 
{
	forward_list<int> list;

	list.push_back(5);
	list.remove_value(5);

	EXPECT_EQ(list.size(), 0);
}

TEST_F(RemoveValueTest, RemoveFirst) 
{
	forward_list<int> list;

	list.push_back(5);
	list.push_back(22);
	list.remove_value(5);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.front(), 22);
}

TEST_F(RemoveValueTest, RemoveLast) 
{
	forward_list<int> list;

	list.push_back(10);
	list.push_back(20);
	list.remove_value(20);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.back(), 10);
}

TEST_F(RemoveValueTest, RemoveMid) 
{
	forward_list<int> list;

	list.push_back(10);
	list.push_back(25);
	list.push_back(45);

	list.remove_value(25);

	EXPECT_EQ(list.size(), 2);
	EXPECT_EQ(list.front(), 10);
	EXPECT_EQ(list.back(), 45);
}

class IteratorTest : public ::testing::Test {};

TEST_F(IteratorTest, BeginTest)
{
	forward_list<char> list;

	ASSERT_TRUE(list.begin() == nullptr);

	list.push_back('a');

	ASSERT_FALSE(list.begin() == nullptr);

	auto it = list.begin();
	auto const_it = list.cbegin();

	EXPECT_EQ(*it, 'a');
	EXPECT_EQ(*const_it, 'a');
	
	list.push_front('b');

	it = list.begin();
	const_it = list.cbegin();

	EXPECT_EQ(*it, 'b');
	EXPECT_EQ(*const_it, 'b');
}

TEST_F(IteratorTest, EndTest)
{
	forward_list<char> list;

	ASSERT_TRUE(list.end() == nullptr);

	list.push_back(20);

	ASSERT_TRUE(list.end() == nullptr);

	list.push_front(23);

	ASSERT_TRUE(list.end() == nullptr);
}

TEST_F(IteratorTest, EqualityTest)
{
	forward_list<char> list;
	auto begin_it = list.begin();
	auto end_it = list.end();

	ASSERT_TRUE(begin_it == nullptr);
	ASSERT_TRUE(end_it == nullptr);
	ASSERT_TRUE(begin_it == end_it);

	list.push_back(20);

	begin_it = list.begin();
	end_it = list.end();

	ASSERT_TRUE(begin_it != end_it);
	ASSERT_FALSE(begin_it == nullptr);
	ASSERT_TRUE(end_it == nullptr);
}

TEST_F(IteratorTest, PlusOperatorTest)
{
	forward_list<int> list;

	list.push_front(20);
	list.push_front(10);
	list.insert(2, 23);
	list.push_back(5);
	list.push_back(-5);

	auto it = list.begin();
	it++;
	EXPECT_EQ(*it, 20);

	it++;
	EXPECT_EQ(*it, 23);

	auto it2 = it++;
	EXPECT_EQ(*it2, 23);
	EXPECT_EQ(*it, 5);

	it2 = ++it;
	EXPECT_EQ(*it2, -5);
	EXPECT_EQ(*it, -5);

	it++;
	EXPECT_TRUE(it == nullptr);
}

TEST_F(IteratorTest, IteratorExceptionsTest)
{
	forward_list<int> list;

	auto it = list.begin();

	ASSERT_THROW(it++, ListException);
	ASSERT_THROW(++it, ListException);
	ASSERT_THROW(*it, ListException);
}

#endif // TESTFORWARDLIST