#include "tcomputecentermodel.h"

#include <gtest.h>

TEST(TComputeCenterModel, throws_when_create_with_zero_queue_length)
{
    ASSERT_ANY_THROW(TComputeCenterModel m(10, 0, 0.5, 0.5));
}

TEST(TComputeCenterModel, model_no_arrivals) //нет задач
{
    srand(1);
    // q = 0
    TComputeCenterModel m(100, 5, 0.0, 0.5);
    m.Model();
    EXPECT_EQ(m.GetCountTasks(), 0);
    EXPECT_EQ(m.GetCountFailure(), 0);
    EXPECT_EQ(m.GetCountAvrCycles(), 0);
    EXPECT_EQ(m.GetCountStall(), 100);
}

TEST(TComputeCenterModel, model_all_good) //задачи есть и 100% выполн€ютс€
{
    srand(2);
    // q1 = 1, q2 = 1
    TComputeCenterModel m(50, 10, 1.0, 1.0);
    m.Model();
    EXPECT_EQ(m.GetCountTasks(), 50);
    EXPECT_EQ(m.GetCountFailure(), 0);
    EXPECT_EQ(m.GetCountAvrCycles(), 1);
    EXPECT_EQ(m.GetCountStall(), 0);
}

TEST(TComputeCenterModel, setparameters_resets) //ожидаем обнуление счетчиков при сбросе параметров
{
    srand(3);
    TComputeCenterModel m(20, 3, 1.0, 0.0);
    m.Model();

    m.SetParameters(10, 3, 0.0, 0.0);
    m.Model();

    EXPECT_EQ(m.GetCountTasks(), 0);
    EXPECT_EQ(m.GetCountFailure(), 0);
    EXPECT_EQ(m.GetCountAvrCycles(), 0);
    EXPECT_EQ(m.GetCountStall(), 10);
}