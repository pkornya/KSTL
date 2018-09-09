#include "gtest\gtest.h"
#include "Linked_List\src\LinkedList.h"

class SizeTest : public ::testing::Test {};

TEST_F(SizeTest, SizeEmpty) {
	LinkedList<int> list;
	int size = list.getSize();

	EXPECT_EQ(size, 0);
}

TEST_F(SizeTest, Size1to2) {
	LinkedList<int> list;
	list.push_front(4);

	EXPECT_EQ(list.getSize(), 1);

	list.push_front(9);
	EXPECT_EQ(list.getSize(), 2);
}

TEST_F(SizeTest, Size3) {
	LinkedList<int> list;

	list.push_front(4);
	list.push_front(9);
	list.push_front(13);

	EXPECT_EQ(list.getSize(), 3);
}

class EmptyTest : public ::testing::Test {};

TEST_F(EmptyTest, Empty) {
	LinkedList<std::string> list;

	EXPECT_TRUE(list.isEmpty());
	list.push_front("word");

	EXPECT_FALSE(list.isEmpty());
}

class PushFrontTest : public ::testing::Test {};

TEST_F(PushFrontTest, Front1) {
	LinkedList<int> list;

	list.push_front(123);
	int front = list.front();

	EXPECT_EQ(list.getSize(), 1);
	EXPECT_EQ(front, 123);
}

TEST_F(PushFrontTest, Front2) {
	LinkedList<int> list;

	list.push_front(123);
	list.push_front(456);
	list.push_front(-123);
	list.push_front(45);

	int front = list.front();

	EXPECT_EQ(list.getSize(), 4);
	EXPECT_EQ(front, 45);
}

class PushBackTest : public ::testing::Test {};

TEST_F(PushBackTest, PushEmpty) {
	LinkedList<int> list;

	list.push_back(4);

	int back = list.back();

	EXPECT_EQ(list.getSize(), 1);
	EXPECT_EQ(back, 4);
}

TEST_F(PushBackTest, PushNonEmpty) {
	LinkedList<int> list;

	list.push_front(-78);
	list.push_back(123);
	list.push_back(456);

	EXPECT_EQ(list.getSize(), 3);

	int back = list.back();

	EXPECT_EQ(back, 456);

	/*EXPECT_EQ(list.ValueAt(0), 123);
	EXPECT_EQ(list.ValueAt(1), 456);*/
}

class PopFrontTest : public ::testing::Test {};

TEST_F(PopFrontTest, Pop1) {
	LinkedList<int> list;

	list.push_front(66);
	int front = list.front();

	EXPECT_EQ(front, 66);
	EXPECT_EQ(list.getSize(), 1);

	list.pop_front();
	EXPECT_EQ(list.getSize(), 0);
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

TEST_F(PopBackTest, Pop1) {
	LinkedList<int> list;

	list.push_back(4);

	int back = list.back();
	list.pop_back();

	EXPECT_EQ(list.getSize(), 0);
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
	EXPECT_EQ(list.getSize(), 3);

	back = list.back();
	list.pop_back();

	EXPECT_EQ(back, 33);
	EXPECT_EQ(list.getSize(), 2);
}

//class ValueAtTest : public ::testing::Test {};
//
//TEST_F(ValueAtTest, Value012) {
//	LinkedList<int> list;
//
//	list.push_front(99);
//	EXPECT_EQ(list.ValueAt(0), 99);
//
//	list.PushFront(3);
//	list.PushFront(122);
//	EXPECT_EQ(list.ValueAt(0), 122);
//	EXPECT_EQ(list.ValueAt(1), 3);
//	EXPECT_EQ(list.ValueAt(2), 99);
//} 

class InsertTest : public ::testing::Test {};

TEST_F(InsertTest, InsertFrontEmpty) {
	LinkedList<int> list;

	list.insert(0, 3);

	EXPECT_EQ(list[0], 3);
	EXPECT_EQ(list.getSize(), 1);
}

TEST_F(InsertTest, InsertFrontNonEmpty) {
	LinkedList<int> list;

	list.push_front(123);
	list.insert(0, 3);

	EXPECT_EQ(list[0], 3);
	EXPECT_EQ(list[1], 123);
	EXPECT_EQ(list.getSize(), 2);
}

TEST_F(InsertTest, InsertBack) {
	LinkedList<int> list{};

	list.push_back(123);
	list.insert(1, 3);

	EXPECT_EQ(list[1], 3);
	EXPECT_EQ(list.getSize(), 2);
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
	EXPECT_EQ(list.getSize(), 4);
}

class RemoveAtTest : public ::testing::Test {};

TEST_F(RemoveAtTest, RemoveOnly) {
	LinkedList<int> list;

	list.push_back(44);
	list.removeAt(0);

	EXPECT_EQ(list.getSize(), 0);
}

TEST_F(RemoveAtTest, RemoveFirst) {
	LinkedList<int> list;

	list.push_back(44);
	list.push_back(55);
	list.removeAt(0);

	EXPECT_EQ(list.getSize(), 1);
	EXPECT_EQ(list[0], 55);
}

TEST_F(RemoveAtTest, RemoveLast) {
	LinkedList<int> list;

	list.push_back(44);
	list.push_back(55);
	list.removeAt(1);

	EXPECT_EQ(list.getSize(), 1);
	EXPECT_EQ(list[0], 44);
}

TEST_F(RemoveAtTest, RemoveMid) {
	LinkedList<int> list;

	list.push_back(44);
	list.push_back(55);
	list.push_back(66);
	list.removeAt(1);

	EXPECT_EQ(list.getSize(), 2);
	EXPECT_EQ(list[0], 44);
	EXPECT_EQ(list[1], 66);
}

//class ValueNFromEndTest : public ::testing::Test {};
//
//TEST_F(ValueNFromEndTest, Only) {
//	jw::LinkedList<int> list{};
//
//	list.PushBack(33);
//
//	EXPECT_EQ(list.ValueNFromEnd(1), 33);
//}
//
//TEST_F(ValueNFromEndTest, Last) {
//	jw::LinkedList<int> list{};
//
//	list.PushBack(44);
//	list.PushBack(55);
//	list.PushBack(66);
//
//	EXPECT_EQ(list.ValueNFromEnd(1), 66);
//	EXPECT_EQ(list.ValueNFromEnd(2), 55);
//	EXPECT_EQ(list.ValueNFromEnd(3), 44);
//}
//
//class ReverseTest : public ::testing::Test {};
//
//TEST_F(ReverseTest, ReverseOne) {
//	jw::LinkedList<int> list{};
//
//	list.PushBack(44);
//
//	list.Reverse();
//
//	EXPECT_EQ(list.Front(), 44);
//}
//
//TEST_F(ReverseTest, ReverseTwo) {
//	jw::LinkedList<int> list{};
//
//	list.PushBack(44);
//	list.PushBack(55);
//
//	list.Reverse();
//
//	EXPECT_EQ(list.Front(), 55);
//	EXPECT_EQ(list.Back(), 44);
//}
//
//TEST_F(ReverseTest, ReverseThree) {
//	jw::LinkedList<int> list{};
//
//	list.PushBack(44);
//	list.PushBack(55);
//	list.PushBack(66);
//
//	list.Reverse();
//
//	EXPECT_EQ(list.ValueAt(0), 66);
//	EXPECT_EQ(list.ValueAt(1), 55);
//	EXPECT_EQ(list.ValueAt(2), 44);
//}
//
//class RemoveValueTest : public ::testing::Test {};
//
//TEST_F(RemoveValueTest, RemoveNone) {
//	jw::LinkedList<int> list{};
//
//	list.RemoveValue(5);
//
//	EXPECT_EQ(list.Size(), 0);
//}
//
//TEST_F(RemoveValueTest, RemoveOnly) {
//	jw::LinkedList<int> list{};
//
//	list.PushBack(5);
//	list.RemoveValue(5);
//
//	EXPECT_EQ(list.Size(), 0);
//}
//
//TEST_F(RemoveValueTest, RemoveFirst) {
//	jw::LinkedList<int> list{};
//
//	list.PushBack(5);
//	list.PushBack(22);
//	list.RemoveValue(5);
//
//	EXPECT_EQ(list.Size(), 1);
//	EXPECT_EQ(list.Front(), 22);
//}
//
//TEST_F(RemoveValueTest, RemoveLast) {
//	jw::LinkedList<int> list{};
//
//	list.PushBack(10);
//	list.PushBack(20);
//	list.RemoveValue(20);
//
//	EXPECT_EQ(list.Size(), 1);
//	EXPECT_EQ(list.Back(), 10);
//}
//
//TEST_F(RemoveValueTest, RemoveMid) {
//	jw::LinkedList<int> list{};
//
//	list.PushBack(10);
//	list.PushBack(25);
//	list.PushBack(45);
//
//	list.RemoveValue(25);
//
//	EXPECT_EQ(list.Size(), 2);
//	EXPECT_EQ(list.Front(), 10);
//	EXPECT_EQ(list.Back(), 45);
//}
