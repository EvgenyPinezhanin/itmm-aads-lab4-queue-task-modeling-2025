#include "tqueue.h"
#include <gtest.h>

TEST(TQueue, DefaultConstructor)
{
    TQueue<int> queue;
    EXPECT_TRUE(queue.IsEmpty());
    EXPECT_FALSE(queue.IsFull());
    EXPECT_EQ(0, queue.size());
}

TEST(TQueue, ConstructorWithSize)
{
    TQueue<int> queue(5);
    EXPECT_TRUE(queue.IsEmpty());
    EXPECT_FALSE(queue.IsFull());
    EXPECT_EQ(0, queue.size());
}

TEST(TQueue, PushAndSize)
{
    TQueue<int> queue(3);
    queue.Push(1);
    EXPECT_FALSE(queue.IsEmpty());
    EXPECT_EQ(1, queue.size());
    
    queue.Push(2);
    queue.Push(3);
    EXPECT_TRUE(queue.IsFull());
    EXPECT_EQ(3, queue.size());
}

TEST(TQueue, PushAndPop)
{
    TQueue<int> queue(3);
    queue.Push(10);
    queue.Push(20);
    queue.Push(30);
    
    EXPECT_EQ(10, queue.Pop());
    EXPECT_EQ(20, queue.Pop());
    EXPECT_EQ(30, queue.Pop());
    EXPECT_TRUE(queue.IsEmpty());
}

TEST(TQueue, FrontMethod)
{
    TQueue<int> queue(3);
    queue.Push(42);
    EXPECT_EQ(42, queue.Front());
    
    queue.Push(24);
    queue.Pop();
    EXPECT_EQ(24, queue.Front());
}

TEST(TQueue, CircularBehavior)
{
    TQueue<int> queue(3);
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    
    EXPECT_EQ(1, queue.Pop());
    queue.Push(4);
    
    EXPECT_EQ(2, queue.Pop());
    EXPECT_EQ(3, queue.Pop());
    EXPECT_EQ(4, queue.Pop());
    EXPECT_TRUE(queue.IsEmpty());
}

TEST(TQueue, ClearMethod)
{
    TQueue<int> queue(5);
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    
    EXPECT_EQ(3, queue.size());
    queue.Clear();
    EXPECT_TRUE(queue.IsEmpty());
    EXPECT_EQ(0, queue.size());
}

TEST(TQueue, OverflowException)
{
    TQueue<int> queue(2);
    queue.Push(1);
    queue.Push(2);
    
    EXPECT_THROW(queue.Push(3), std::overflow_error);
}

TEST(TQueue, UnderflowException)
{
    TQueue<int> queue(3);
    EXPECT_THROW(queue.Pop(), std::underflow_error);
    EXPECT_THROW(queue.Front(), std::underflow_error);
    
    queue.Push(1);
    queue.Pop();
    EXPECT_THROW(queue.Pop(), std::underflow_error);
}

TEST(TQueue, CopyConstructor)
{
    TQueue<int> queue1(3);
    queue1.Push(10);
    queue1.Push(20);
    
    TQueue<int> queue2(queue1);
    
    EXPECT_EQ(queue1.size(), queue2.size());
    EXPECT_EQ(queue1.Pop(), queue2.Pop());
    EXPECT_EQ(queue1.Pop(), queue2.Pop());
}

TEST(TQueue, AssignmentOperator)
{
    TQueue<int> queue1(3);
    queue1.Push(100);
    queue1.Push(200);
    
    TQueue<int> queue2(5);
    queue2 = queue1;
    
    EXPECT_EQ(queue1.size(), queue2.size());
    EXPECT_EQ(queue1.Pop(), queue2.Pop());
    EXPECT_EQ(queue1.Pop(), queue2.Pop());
}

TEST(TQueue, DifferentDataTypes)
{
    TQueue<double> queue(3);
    queue.Push(3.14159);
    queue.Push(2.71828);
    
    EXPECT_DOUBLE_EQ(3.14159, queue.Pop());
    EXPECT_DOUBLE_EQ(2.71828, queue.Pop());
}