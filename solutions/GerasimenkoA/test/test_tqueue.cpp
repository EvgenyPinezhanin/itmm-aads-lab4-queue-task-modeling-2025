#include "tqueue.h"

#include <gtest.h>

TEST(TQueue, can_create_tqueue_with_positive_length)
{
	ASSERT_NO_THROW(TQueue<int> q(5));
}

TEST(TQueue, throws_when_create_tqueue_with_negative_length)
{
	ASSERT_ANY_THROW(TQueue<int> q(-1));
}

TEST(TQueue, throws_when_create_tqueue_with_zero_length)
{
	ASSERT_ANY_THROW(TQueue<int> q(0));
}

TEST(TQueue, isempty_work)
{
	TQueue<int> q(3);
	EXPECT_TRUE(q.IsEmpty());
	q.Push(10);
	EXPECT_FALSE(q.IsEmpty());
}

TEST(TQueue, isfull_work)
{
	TQueue<int> q(2);
	EXPECT_FALSE(q.IsFull());
	q.Push(1);
	EXPECT_FALSE(q.IsFull());
	q.Push(2);
	EXPECT_TRUE(q.IsFull());
}

TEST(TQueue, can_push)
{
	TQueue<int> q(2);
	ASSERT_NO_THROW(q.Push(100));
	EXPECT_EQ(q.size(), 1);
}

TEST(TQueue, cant_push_when_stack_overflow)
{
	TQueue<int> q(1);
	q.Push(1);
	ASSERT_TRUE(q.IsFull());
	ASSERT_ANY_THROW(q.Push(2));
}

TEST(TQueue, can_pop)
{
	TQueue<int> q(3);
	q.Push(5);
	EXPECT_EQ(q.Pop(), 5);
}

TEST(TQueue, cant_pop_when_stack_underflow)
{
	TQueue<int> q(2);
	EXPECT_TRUE(q.IsEmpty());
	ASSERT_ANY_THROW(q.Pop());
}