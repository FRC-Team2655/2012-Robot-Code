#include "TestRobotCmd.h"
#include "ExerciseMotorsCmd.h"
#include "MonitorSensorsCmd.h"
#include "TestGetReadyCmd.h"
#include "TestDrivetrainCmd.h"
#include "TestInfeedCmd.h"
#include "TestBallBrushesCmd.h"
#include "TestBallGateCmd.h"
#include "TestBallFeedCmd.h"
#include "TestFireCmd.h"
#include "TestAzimuthCmd.h"
#include "TestLauncherCmd.h"
#include "TestBridgeArmCmd.h"



TestRobotCmd::TestRobotCmd(Button* trigger)
: CommandGroup("TestRobotCmd")
{
//	AddParallel(new MonitorSensorsCmd());
	AddSequential(new TestGetReadyCmd(trigger));
	AddSequential(new TestDrivetrainCmd(trigger));
	AddSequential(new  TestInfeedCmd(trigger));
	AddSequential(new TestBallBrushesCmd(trigger));
	AddSequential(new TestBallFeedCmd(trigger));
	AddSequential(new TestBallGateCmd(trigger));
	AddSequential(new TestFireCmd(trigger));
//	AddSequential(new TestAzimuthCmd(trigger));
	AddSequential(new TestLauncherCmd(trigger));
	AddSequential(new TestBridgeArmCmd(trigger));
	AddSequential(new MonitorSensorsCmd());

}

void TestRobotCmd::Initialize()
{
}

void TestRobotCmd::Execute()
{
}

void TestRobotCmd::End()
{
}

void TestRobotCmd::Interrupted()
{
}

