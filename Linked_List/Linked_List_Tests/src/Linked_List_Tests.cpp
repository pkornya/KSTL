#include "gtest\gtest.h"
#include "Linked_List\src\LinkedList.h"
#include "Linked_List\src\OwnOterator.h"

class SizeTest : public ::testing::Test {};

TEST_F(SizeTest, SizeEmpty) {
	LinkedList<int> list;
	int size = list.size();

	EXPECT_EQ(size, 0);
}

TEST_F(SizeTest, Size1to2) {
	LinkedList<int> list;
	list.push_front(4);

	EXPECT_EQ(list.size(), 1);

	list.push_front(9);
	EXPECT_EQ(list.size(), 2);
}

TEST_F(SizeTest, Size3) {
	LinkedList<int> list;

	list.push_front(4);
	list.push_front(9);
	list.push_front(13);

	EXPECT_EQ(list.size(), 3);
}

class EmptyTest : public ::testing::Test {};

TEST_F(EmptyTest, Empty) {
	LinkedList<std::string> list;

	EXPECT_TRUE(list.empty());
	list.push_front("word");

	EXPECT_FALSE(list.empty());
}

class PushFrontTest : public ::testing::Test {};

TEST_F(PushFrontTest, Front1) {
	LinkedList<int> list;

	list.push_front(123);
	int front = list.front();

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(front, 123);
}

TEST_F(PushFrontTest, Front2) {
	LinkedList<int> list;

	list.push_front(123);
	list.push_front(456);
	list.push_front(-123);
	list.push_front(45);

	int front = list.front();

	EXPECT_EQ(list.size(), 4);
	EXPECT_EQ(front, 45);
}

class SquareBrackets : public ::testing::Test {};

TEST_F(SquareBrackets, EmptyList) {
	LinkedList<int> list;

	ASSERT_THROW(list[2], ListException);
}

TEST_F(SquareBrackets, NonEmptyList) {
	LinkedList<int> list;

	ASSERT_THROW(list[2], ListException);

	list.push_front(10);
	list.push_back(20);

	ASSERT_THROW(list[-3], ListException);
	ASSERT_THROW(list[2], ListException);

	EXPECT_EQ(list[0], 10);
	EXPECT_EQ(list[1], 20);
}

class PushBackTest : public ::testing::Test {};

TEST_F(PushBackTest, PushEmpty) {
	LinkedList<int> list;

	list.push_back(4);

	int back = list.back();

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(back, 4);
}

TEST_F(PushBackTest, PushNonEmpty) {
	LinkedList<int> list;

	list.push_front(-78);
	list.push_back(123);
	list.push_back(456);

	EXPECT_EQ(list.size(), 3);

	int back = list.back();

	EXPECT_EQ(back, 456);

	EXPECT_EQ(list.value_at(0), -78);
	EXPECT_EQ(list.value_at(1), 123);
}

class PopFrontTest : public ::testing::Test {};

TEST_F(PopFrontTest, PopFrontExceptions) {
	LinkedList<int> list;

	ASSERT_THROW(list.pop_front(), ListException);
}

TEST_F(PopFrontTest, Pop1) {
	LinkedList<int> list;

	list.push_front(66);
	int front = list.front();

	EXPECT_EQ(front, 66);
	EXPECT_EQ(list.size(), 1);

	list.pop_front();
	EXPECT_EQ(list.size(), 0);
}

TEST_F(PopFrontTest, Pop2) {
	LinkedList<int> list;

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

TEST_F(PopBackTest, PopBackExceptions) {
	LinkedList<int> list;

	ASSERT_THROW(list.pop_back(), ListException);
}

TEST_F(PopBackTest, Pop1) {
	LinkedList<int> list;

	list.push_back(4);

	int back = list.back();
	list.pop_back();

	EXPECT_EQ(list.size(), 0);
	EXPECT_EQ(back, 4);
}

TEST_F(PopBackTest, Pop2) {
	LinkedList<int> list;

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

TEST_F(ValueAtTest, Value012) {
	LinkedList<int> list;

	list.push_front(99);
	EXPECT_EQ(list.value_at(0), 99);

	list.push_front(3);
	list.push_front(122);
	EXPECT_EQ(list.value_at(0), 122);
	EXPECT_EQ(list.value_at(1), 3);
	EXPECT_EQ(list.value_at(2), 99);
} 

class InsertTest : public ::testing::Test {};

TEST_F(InsertTest, InsertExceptions) {
	LinkedList<int> list;

	ASSERT_THROW(list.insert(2, 12), ListException);
	ASSERT_THROW(list.insert(-1, 12), ListException);
}

TEST_F(InsertTest, InsertFrontEmpty) {
	LinkedList<int> list;

	list.insert(0, 3);

	EXPECT_EQ(list[0], 3);
	EXPECT_EQ(list.size(), 1);
}

TEST_F(InsertTest, InsertFrontNonEmpty) {
	LinkedList<int> list;

	list.push_front(123);
	list.insert(0, 3);

	EXPECT_EQ(list[0], 3);
	EXPECT_EQ(list[1], 123);
	EXPECT_EQ(list.size(), 2);
}

TEST_F(InsertTest, InsertBack) {
	LinkedList<int> list{};

	list.push_back(123);
	list.insert(1, 3);

	EXPECT_EQ(list[1], 3);
	EXPECT_EQ(list.size(), 2);
}

TEST_F(InsertTest, InsertMid) {
	LinkedList<int> list;

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

TEST_F(RemoveAtTest, RemoveAtExceptions) {
	LinkedList<int> list;
	
	ASSERT_THROW(list.remove_at(2), ListException);
	
	list.push_back(20);
	list.push_front(13);

	ASSERT_THROW(list.remove_at(-1), ListException);
	ASSERT_THROW(list.remove_at(2), ListException);
	ASSERT_THROW(list.remove_at(25), ListException);
}

TEST_F(RemoveAtTest, RemoveOnly) {
	LinkedList<int> list;

	list.push_back(44);
	list.remove_at(0);

	EXPECT_EQ(list.size(), 0);
}

TEST_F(RemoveAtTest, RemoveFirst) {
	LinkedList<int> list;

	list.push_back(44);
	list.push_back(55);
	list.remove_at(0);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list[0], 55);
}

TEST_F(RemoveAtTest, RemoveLast) {
	LinkedList<int> list;

	list.push_back(44);
	list.push_back(55);
	list.remove_at(1);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list[0], 44);
}

TEST_F(RemoveAtTest, RemoveMid) {
	LinkedList<int> list;

	list.push_back(44);
	list.push_back(55);
	list.push_back(66);
	list.remove_at(1);

	EXPECT_EQ(list.size(), 2);
	EXPECT_EQ(list[0], 44);
	EXPECT_EQ(list[1], 66);
}

class RemoveValueTest : public ::testing::Test {};

TEST_F(RemoveValueTest, RemoveNone) {
	LinkedList<int> list;

	list.remove_value(5);

	EXPECT_EQ(list.size(), 0);
}

TEST_F(RemoveValueTest, RemoveOnly) {
	LinkedList<int> list;

	list.push_back(5);
	list.remove_value(5);

	EXPECT_EQ(list.size(), 0);
}

TEST_F(RemoveValueTest, RemoveFirst) {
	LinkedList<int> list;

	list.push_back(5);
	list.push_back(22);
	list.remove_value(5);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.front(), 22);
}

TEST_F(RemoveValueTest, RemoveLast) {
	LinkedList<int> list;

	list.push_back(10);
	list.push_back(20);
	list.remove_value(20);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.back(), 10);
}

TEST_F(RemoveValueTest, RemoveMid) {
	LinkedList<int> list;

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
	LinkedList<char> list;

	ASSERT_TRUE(list.begin() == nullptr);
	//ASSERT_TRUE(list.cbegin() == nullptr);

	list.push_back('a');

	ASSERT_FALSE(list.begin() == nullptr);
	//ASSERT_FALSE(list.cbegin() == nullptr);

	auto it = list.begin();
	auto const_it = list.begin();

	EXPECT_EQ(*it, 'a');
	EXPECT_EQ(*const_it, 'a');
	
	list.push_front('b');

	it = list.begin();
	const_it = list.begin();

	EXPECT_EQ(*it, 'b');
	EXPECT_EQ(*const_it, 'b');
}

TEST_F(IteratorTest, EndTest)
{
	LinkedList<char> list;

	ASSERT_TRUE(list.end() == nullptr);

	list.push_back(20);

	ASSERT_TRUE(list.end() == nullptr);

	list.push_front(23);

	ASSERT_TRUE(list.end() == nullptr);
}

TEST_F(IteratorTest, EqualityTest)
{
	LinkedList<char> list;
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
	LinkedList<int> list;

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
	LinkedList<int> list;

	auto it = list.begin();

	ASSERT_THROW(it++, ListException);
	ASSERT_THROW(++it, ListException);
	ASSERT_THROW(*it, ListException);
}