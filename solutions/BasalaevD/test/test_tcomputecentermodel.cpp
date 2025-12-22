#include "tcomputecentermodel.h"
#include <gtest.h>

TEST(TComputeCenterModel, DefaultConstructor)
{
    TComputeCenterModel model;
    EXPECT_EQ(0, model.GetCountTasks());
    EXPECT_EQ(0, model.GetCountFailure());
    EXPECT_EQ(0, model.GetCountStall());
    EXPECT_EQ(0, model.GetCountAvrCycles());
}

TEST(TComputeCenterModel, ConstructorWithParameters)
{
    TComputeCenterModel model(200, 15, 0.3, 0.7);
    SUCCEED();
}

TEST(TComputeCenterModel, SetParameters)
{
    TComputeCenterModel model;
    model.SetParameters(150, 10, 0.4, 0.6);
    EXPECT_EQ(0, model.GetCountTasks());
}

TEST(TComputeCenterModel, ModelExecution)
{
    TComputeCenterModel model(100, 10, 0.5, 0.5);
    model.Model();
    EXPECT_GE(model.GetCountTasks(), 0);
}

TEST(TComputeCenterModel, NoTaskGeneration)
{
    TComputeCenterModel model(100, 10, 0.0, 0.5);
    model.Model();
    EXPECT_EQ(0, model.GetCountTasks());
    EXPECT_EQ(0, model.GetCountFailure());
    EXPECT_EQ(100, model.GetCountStall());
}

TEST(TComputeCenterModel, HighLoadSystem)
{
    TComputeCenterModel model(100, 2, 0.9, 0.1);
    model.Model();
    EXPECT_GT(model.GetCountTasks(), 0);
    EXPECT_GE(model.GetCountFailure(), 0);
}

TEST(TComputeCenterModel, ProbabilityCalculations)
{
    TComputeCenterModel model(100, 10, 0.5, 0.5);
    model.Model();
    
    double failureProb = model.GetFailureProbability();
    double stallProb = model.GetStallProbability();
    
    EXPECT_GE(failureProb, 0.0);
    EXPECT_LE(failureProb, 1.0);
    EXPECT_GE(stallProb, 0.0);
    EXPECT_LE(stallProb, 1.0);
}

TEST(TComputeCenterModel, MultipleModelCalls)
{
    TComputeCenterModel model(50, 5, 0.6, 0.4);
    model.Model();
    size_t tasks1 = model.GetCountTasks();
    model.Model();
    size_t tasks2 = model.GetCountTasks();
    EXPECT_GT(tasks1, 0);
    EXPECT_GT(tasks2, 0);
}

TEST(TComputeCenterModel, QueueSizeLimit)
{
    TComputeCenterModel model(100, 1, 0.8, 0.3);
    model.Model();
    EXPECT_GT(model.GetCountTasks(), 0);
    EXPECT_GE(model.GetCountFailure(), 0);
}