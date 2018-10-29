#include "gtest\gtest.h"
#include "..\include\list.h"

using pkl::list;

#define TESTLIST

#ifdef  TESTLIST


class ConstructorsTest : public ::testing::Test {};

TEST_F(ConstructorsTest, DefaultConstructor) 
{
    list<int> list1;

    EXPECT_TRUE(list1.empty());
    EXPECT_EQ(list1.begin(), nullptr);
    EXPECT_EQ(list1.end(), nullptr);
    EXPECT_EQ(list1.size(), 0);
    EXPECT_EQ(list1.begin(), list1.end());
}

TEST_F(ConstructorsTest, InitializerList) 
{
    list<int> list1 = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(list1.size(), 5);
    EXPECT_EQ(list1.front(), 1);
    EXPECT_EQ(list1.back(), 5);

    list1 = { 10, 20, 30, 50 };

    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1.front(), 10);
    EXPECT_EQ(list1.back(), 50);
}

TEST_F(ConstructorsTest, FillConstructor) 
{
    list<int> list1(2, 10);

    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(list1.front(), 10);
    EXPECT_EQ(list1.back(), 10);
}

TEST_F(ConstructorsTest, CopyConstructor) 
{
    list<int> list1 = { 1, 2, 3, 4 };
    list<int> testList(list1);

    ASSERT_NE(list1.begin(), testList.begin());
    ASSERT_NE(list1.end(), testList.end());

    testList.pop_front();

    auto it = testList.begin();
    it++;

    EXPECT_EQ(testList.size(), 3);
    EXPECT_EQ(testList.front(), 2);
    EXPECT_EQ(testList.back(), 4);
    EXPECT_EQ(*it, 3);
}

TEST_F(ConstructorsTest, MoveConstructor) 
{
    list<int> list1 = { 1, 2, 3, 4 };

    list<int> testList(std::move(list1));

    ASSERT_EQ(list1.begin(), nullptr);
    ASSERT_EQ(list1.end(), nullptr);
    ASSERT_EQ(list1.size(), 0);
    ASSERT_NE(list1.begin(), testList.begin());
    //ASSERT_NE(list1.end(), testList.end());

    EXPECT_EQ(testList.size(), 4);
    EXPECT_EQ(testList.front(), 1);
    EXPECT_EQ(testList.back(), 4);

    list1 = std::move(testList);
    ASSERT_EQ(testList.begin(), nullptr);
    ASSERT_EQ(testList.end(), nullptr);
    ASSERT_EQ(testList.size(), 0);
    ASSERT_NE(testList.begin(), list1.begin());
    //ASSERT_NE(testList.end(), list1.end());

    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1.front(), 1);
    EXPECT_EQ(list1.back(), 4);
}


class AssignmentOperatorTest : public ::testing::Test {};

TEST_F(AssignmentOperatorTest, AssignmentOperator) 
{
    list<int> list1 = { 1, 2, 3, 4 };

    list<int> testList = { 5, 6, 7 };

    testList = list1;

    ASSERT_NE(list1.begin(), testList.begin());
    //ASSERT_NE(list1.end(), testList.end());

    EXPECT_EQ(testList.size(), 4);
    EXPECT_EQ(testList.front(), 1);
    EXPECT_EQ(testList.back(), 4);
}

TEST_F(AssignmentOperatorTest, MoveAssignmentOperator) 
{
    list<int> list1 = { 1, 2, 3, 4 };

    list<int> testList = { 5, 6, 7 };

    testList = std::move(list1);

    ASSERT_EQ(list1.begin(), nullptr);
    ASSERT_EQ(list1.end(), nullptr);
    ASSERT_EQ(list1.size(), 0);
    ASSERT_NE(list1.begin(), testList.begin());
    //ASSERT_NE(list1.end(), testList.end());

    EXPECT_EQ(testList.size(), 4);
    EXPECT_EQ(testList.front(), 1);
    EXPECT_EQ(testList.back(), 4);

    list1 = std::move(testList);

    ASSERT_EQ(testList.begin(), nullptr);
    ASSERT_EQ(testList.end(), nullptr);
    ASSERT_EQ(testList.size(), 0);
    ASSERT_NE(testList.begin(), list1.begin());
    //ASSERT_NE(testList.end(), list1.end());

    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1.front(), 1);
    EXPECT_EQ(list1.back(), 4);
}


class ModifiersTest : public ::testing::Test {};

TEST_F(ModifiersTest, PushFrontEmpty) 
{
    list<int> list1;

    list1.push_front(123);
    
    EXPECT_EQ(list1.size(), 1);
    EXPECT_EQ(list1.front(), 123);
}

TEST_F(ModifiersTest, PushFrontNonEmpty) 
{
    list<int> list1;

    list1.push_back(123);
    list1.push_front(456);
    list1.push_front(-123);
    list1.push_front(45);

    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1.front(), 45);
}

TEST_F(ModifiersTest, PushBackEmpty) 
{
    list<int> list1;

    list1.push_back(4);

    EXPECT_EQ(list1.size(), 1);
    EXPECT_EQ(list1.back(), 4);
    EXPECT_EQ(list1.front(), 4);
    //EXPECT_EQ(list1.begin(), list1.end());
}

TEST_F(ModifiersTest, PushBackNonEmpty) 
{
    list<int> list1;

    list1.push_front(-78);
    list1.push_back(123);
    list1.push_back(456);

    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list1.front(), -78);
    EXPECT_EQ(list1.back(), 456);
}

TEST_F(ModifiersTest, PopFront) 
{
    list<int> list1;

    list1.push_front(66);

    EXPECT_EQ(list1.front(), 66);
    EXPECT_EQ(list1.size(), 1);

    list1.pop_front();
    EXPECT_EQ(list1.size(), 0);

    list1.clear();

    list1.push_front(12);
    list1.push_front(11);
    list1.push_front(20);
    list1.push_front(-155);

    list1.pop_front();
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list1.front(), 20);

    list1.pop_front();
    list1.pop_front();

    EXPECT_EQ(list1.size(), 1);
    EXPECT_EQ(list1.front(), 12);
}

TEST_F(ModifiersTest, PopBack) 
{
    list<int> list1;

    list1.push_back(4);

    int back = list1.back();
    list1.pop_back();

    EXPECT_EQ(list1.size(), 0);
    EXPECT_EQ(back, 4);

    list1.clear();

    list1.push_back(33);
    list1.push_front(13);
    list1.push_back(-455);
    list1.push_front(0);

    back = list1.back();
    list1.pop_back();

    EXPECT_EQ(back, -455);
    EXPECT_EQ(list1.size(), 3);

    back = list1.back();
    list1.pop_back();

    EXPECT_EQ(back, 33);
    EXPECT_EQ(list1.size(), 2);
}

TEST_F(ModifiersTest, AssignFill) 
{
    list<int> list1 = { 1, 2, 3, 5 };

    list1.assign(3, 20);
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list1.front(), 20);
    EXPECT_EQ(list1.back(), 20);

    list1.assign(20, 1000);
    EXPECT_EQ(list1.size(), 20);
    EXPECT_EQ(list1.front(), 1000);
    EXPECT_EQ(list1.back(), 1000);
}

TEST_F(ModifiersTest, AssignInitList)
{
    list<int> list1 = { 1, 2, 3, 5 };

    list1.assign({ 20, 30, 40, 50 });
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1.front(), 20);
    EXPECT_EQ(list1.back(), 50);

    list1.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    EXPECT_EQ(list1.size(), 10);
    EXPECT_EQ(list1.front(), 1);
    EXPECT_EQ(list1.back(), 10);
}

TEST_F(ModifiersTest, InsertSingle)
{
    list<int> list1 = { 1, 2, 3, 4, 5 };

    auto it = list1.insert(list1.begin(), 10);
    // 10 1 2 3 4 5 
    EXPECT_EQ(list1.size(), 6);
    EXPECT_EQ(list1.front(), 10);
    EXPECT_EQ(list1.back(), 5);
    EXPECT_EQ(*it, 10);

    it++; it++;

    it = list1.insert(it, 35);
    // 10 1 35 2 3 4 5 
    EXPECT_EQ(list1.size(), 7);
    EXPECT_EQ(list1.front(), 10);
    EXPECT_EQ(list1.back(), 5);
    EXPECT_EQ(*it, 35);
    it++; it++;
    EXPECT_EQ(*it, 3);

    it = list1.insert(it, 100);
    // 10 1 35 2 100 3 4 5 
    EXPECT_EQ(list1.size(), 8);
    EXPECT_EQ(*it, 100);
    EXPECT_EQ(*(--it), 2);

    it = list1.insert(list1.end(), -10);
    // 10 1 2 35 100 3 4 -10 5  
    EXPECT_EQ(list1.size(), 9);
    EXPECT_EQ(list1.front(), 10);
    EXPECT_EQ(list1.back(), 5);
    EXPECT_EQ(*it, -10);
    it--; it--; it--;
    EXPECT_EQ(*it, 100);
}

TEST_F(ModifiersTest, InsertFill)
{
    list<int> li = { 1, 2, 3, 4, 5, 6 };

    auto it = li.insert(li.begin(), 3, 100);
    // 100 100 100 1 2 3 4 5 6 
    EXPECT_EQ(li.size(), 9);
    EXPECT_EQ(li.front(), 100);
    EXPECT_EQ(li.back(), 6);
    EXPECT_EQ(*it, 100);
    EXPECT_EQ(*(++it), 100);
    EXPECT_EQ(*(++it), 100);
    EXPECT_EQ(*(++it), 1);

    it = li.insert(it, 1000, 20);
    // 100 100 100 20 ... 1 2 3 4 5 6 
    EXPECT_EQ(li.size(), 1009);
    EXPECT_EQ(li.front(), 100);
    EXPECT_EQ(li.back(), 6);
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(*(++it), 20);
    EXPECT_EQ(*(--it), 20);

    it = li.insert(li.end(), 3, -10);
    // 100 100 100 20 ... 1 2 3 4 5 -10 -10 -10 6
    EXPECT_EQ(li.size(), 1012);
    EXPECT_EQ(li.front(), 100);
    EXPECT_EQ(li.back(), 6);
    EXPECT_EQ(*it, -10);
    EXPECT_EQ(*(++it), -10);
    EXPECT_EQ(*(++it), -10);
    EXPECT_EQ(*(++it), 6);
}

TEST_F(ModifiersTest, InsertInitList)
{
    list<int> li;

    auto it = li.insert(li.begin(), { 1, 2, 3, 4, 5, 6 });

    EXPECT_EQ(li.size(), 6);
    EXPECT_EQ(li.front(), 1);
    EXPECT_EQ(li.back(), 6);
    EXPECT_EQ(*it, 1);

    it++; it++;

    it = li.insert(it, { 20, 25, 40 });
    // 1 2 20 25 40 3 4 5 6 

    EXPECT_EQ(li.size(), 9);
    EXPECT_EQ(li.front(), 1);
    EXPECT_EQ(li.back(), 6);
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(*(++it), 25);
    EXPECT_EQ(*(++it), 40);
    EXPECT_EQ(*(++it), 3);
}

TEST_F(ModifiersTest, EraseOne)
{
    list<int> li = { 1, 2, 3, 4, 5 };

    auto it = li.erase(li.begin());
    // 2 3 4 5 
    EXPECT_EQ(li.size(), 4);
    EXPECT_EQ(li.front(), 2);
    EXPECT_EQ(li.back(), 5);
    EXPECT_EQ(*it, 2);

    it = li.erase(li.end());
    // 2 3 4 
    EXPECT_EQ(li.size(), 3);
    EXPECT_EQ(li.front(), 2);
    EXPECT_EQ(li.back(), 4);
    EXPECT_EQ(*it, 4);

    it = li.erase(--it);
    // 2  4
    EXPECT_EQ(li.size(), 2);
    EXPECT_EQ(li.front(), 2);
    EXPECT_EQ(li.back(), 4);
    EXPECT_EQ(*it, 4);
}

TEST_F(ModifiersTest, EraseRange)
{
    list<int> li = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto it = li.begin();
    ++it; ++it; ++it;

    it = li.erase(it, --li.end());
    // 1 2 3 9 10

    EXPECT_EQ(li.size(), 5);
    EXPECT_EQ(li.front(), 1);
    EXPECT_EQ(li.back(), 10);
    EXPECT_EQ(*(++li.begin()), 2);
    EXPECT_EQ(*(--li.end()), 9);
    EXPECT_EQ(*it, 9);

    it = li.erase(li.begin(), li.end());

    EXPECT_EQ(li.size(), 0);
    EXPECT_EQ(li.begin(), nullptr);
    EXPECT_EQ(li.end(), nullptr);
    EXPECT_EQ(it, nullptr);
}

TEST_F(ModifiersTest, Resize)
{
    list<int> vec = { 1, 2, 17, 8, 3, 18, 19, 123, 13 };

    vec.resize(2);

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 2);

    vec.resize(8);
    EXPECT_EQ(vec.size(), 8);
    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 0);

    vec.resize(12);
    EXPECT_EQ(vec.size(), 12);
    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 0);

    vec.resize(18, 100);
    EXPECT_EQ(vec.size(), 18);
    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 100);

    vec.resize(21, 100);
    EXPECT_EQ(vec.size(), 21);
    EXPECT_EQ(vec.back(), 100);
    EXPECT_EQ(*(--vec.end()), 100);
}

class IteratorTest : public ::testing::Test {};

TEST_F(IteratorTest, BeginTest)
{
    list<char> list1;

    ASSERT_TRUE(list1.begin() == nullptr);

    list1.push_back('a');

    ASSERT_FALSE(list1.begin() == nullptr);

    auto it       = list1.begin();
    auto const_it = list1.cbegin();

    EXPECT_EQ(*it, 'a');
    EXPECT_EQ(*const_it, 'a');

    list1.push_front('b');

    it       = list1.begin();
    const_it = list1.cbegin();

    EXPECT_EQ(*it, 'b');
    EXPECT_EQ(*const_it, 'b');
}

TEST_F(IteratorTest, EndTest)
{
    list<char> list1;

    ASSERT_TRUE(list1.end() == nullptr);

    list1.push_back('a');

    ASSERT_FALSE(list1.end() == nullptr);

    auto it       = list1.end();
    auto const_it = list1.cend();

    EXPECT_EQ(*it, 'a');
    EXPECT_EQ(*const_it, 'a');

    list1.push_front('b');

    it       = list1.end();
    const_it = list1.cend();

    EXPECT_EQ(*it, 'a');
    EXPECT_EQ(*const_it, 'a');
}

TEST_F(IteratorTest, EqualityTest)
{
    list<char> list1;
    auto begin_it = list1.begin();
    auto end_it   = list1.end();

    ASSERT_TRUE(begin_it == nullptr);
    ASSERT_TRUE(end_it == nullptr);
    ASSERT_TRUE(begin_it == end_it);

    list1.push_back(20);
    begin_it = list1.begin();
    end_it   = list1.end();

    ASSERT_TRUE(begin_it == end_it);

    list1.push_back(20);
    begin_it = list1.begin();
    end_it   = list1.end();

    ASSERT_TRUE(begin_it != end_it);
}

TEST_F(IteratorTest, IncDecTest)
{
    list<int> list1;

    list1.push_front(20);
    list1.push_front(10);
    list1.push_back(5);
    list1.push_back(-5);

    // 10 20 5 -5
    auto it = list1.begin();
    it++;
    EXPECT_EQ(*it, 20);

    it++;
    EXPECT_EQ(*it, 5);

    it--;
    EXPECT_EQ(*it, 20);

    auto it2 = it++;
    EXPECT_EQ(*it2, 20);
    EXPECT_EQ(*it, 5);

    it2 = ++it;
    EXPECT_EQ(*it2, -5);
    EXPECT_EQ(*it, -5);

    it2 = it--;
    EXPECT_EQ(*it2, -5);
    EXPECT_EQ(*it, 5);

    it2 = --it;
    EXPECT_EQ(*it2, 20);
    EXPECT_EQ(*it, 20);

    it--;
    it--;
    EXPECT_TRUE(it == nullptr);
}


#endif //  TESTLIST