#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "Commands/AutonomousCommand.h"
#include "CommandBase.h"
#include "Commands/AutonomousFireCmd.h"
#include "Commands/NoOpCmd.h"
#include "Commands/DriveWithJoysticksCmd.h"
#include "Commands/DriveInSquareCmd.h"
#include "Commands/ExerciseMotorsCmd.h"
#include "Joystick.h"
#include "Commands/KinectDriveCmd.h"
#include "Commands/MoveToAndDropBridgeCmd.h"
#include "Commands/TestRobotCmd.h"
#include "Commands/TestDrivetrainCmd.h"
#include "Commands/TestInfeedCmd.h"
#include "Commands/TestBallBrushesCmd.h"
#include "Commands/TestBallGateCmd.h"
#include "Commands/TestBallFeedCmd.h"
#include "Commands/TestFireCmd.h"
#include "Commands/TestAzimuthCmd.h"
#include "Commands/TestLauncherCmd.h"
#include "Commands/TestBridgeArmCmd.h"

class CommandBasedRobot : public IterativeRobot 
{
private:
	Command* _autonomousCommand;
	Command* _teleopCommand;
	SendableChooser* _teleopChooser ;
	SendableChooser* _autoChooser ;
	MoveToAndDropBridgeCmd* _moveToAndDropBridgeCmd;
	DriveInSquareCmd* _driveInSquareCmd;
	KinectDriveCmd* _kinectDriveCmd;
	TestRobotCmd* _testRobotCmd;
	DriveWithJoysticksCmd* _driveWithJoysticksCmd;
	AutonomousFireCmd* _autoFireCmd;
	NoOpCmd* _noOpCmd;
	int _count;
	Command* _cmd;

	void clearStatus()
	{
		SmartDashboard::GetInstance()->PutString("Status", "                                                      ");
	}
	
	void clearLCD()
	{
		clearStatus();
		DriverStationLCD::GetInstance()->Clear();
	}
	
	void printCommandToLCD(std::string cmd_name)
	{
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, cmd_name.c_str());
		DriverStationLCD::GetInstance()->UpdateLCD();
	}
	
	virtual void RobotInit() {
		CommandBase::init();
		
		DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
		dsLCD->Clear();
		dsLCD->UpdateLCD();
		
		//Wait(0.1);

		//_autonomousCommand = new AutonomousCommand();
		_autonomousCommand = NULL;
		_teleopCommand = NULL;
		
		_moveToAndDropBridgeCmd = new MoveToAndDropBridgeCmd();
		_noOpCmd = new NoOpCmd();
		_driveInSquareCmd = new DriveInSquareCmd();
		_kinectDriveCmd = new KinectDriveCmd(CommandBase::oi->kinectLeft, CommandBase::oi->kinectRight, CommandBase::oi->kinectBridgeBtn);
		_testRobotCmd = new TestRobotCmd(CommandBase::oi->driveTrigger);
		_autoFireCmd = new AutonomousFireCmd();

		//_driveWithJoysticksCmd = new DriveWithJoysticksCmd();
		
		
		_autoChooser = new SendableChooser();
		//		_autoChooser->AddDefault("Autonomous Fire", _autoFireCmd);
		_autoChooser->AddDefault("Move To And Drop Bridge", _moveToAndDropBridgeCmd);
//		_autoChooser->AddObject("Move To And Drop Bridge", _moveToAndDropBridgeCmd);
		_autoChooser->AddObject("Autonomous Fire", _autoFireCmd);
		_autoChooser->AddObject("Drive with Kinect", _kinectDriveCmd);
		_autoChooser->AddObject("Drive In Square", _driveInSquareCmd);
		SmartDashboard::GetInstance()->PutData("AutoMenu", _autoChooser);
		
		_teleopChooser = new SendableChooser();
		_teleopChooser->AddDefault("Drive With Joysticks", _noOpCmd);
		_teleopChooser->AddObject("Test Robot", _testRobotCmd);
		SmartDashboard::GetInstance()->PutData("TeleopMenu", _teleopChooser);
//		SmartDashboard::GetInstance()->PutData("SchedulerData", Scheduler::GetInstance());
//		SmartDashboard::GetInstance()->PutData("DriveTrainSubsystem", CommandBase::driveTrainSubsystem);
//		SmartDashboard::GetInstance()->PutData("AzimuthSubsystem", CommandBase::azimuthSubsystem);
	}
	
	virtual void AutonomousInit() 
	{
		if (_teleopCommand)
		{
			_teleopCommand->Cancel();
		}

		clearLCD();

		_autonomousCommand = (Command*)_autoChooser->GetSelected();
//		_autonomousCommand = (Command*) _autoFireCmd;

		printCommandToLCD(_autonomousCommand->GetName());

		_autonomousCommand->Start();
	}
	
	virtual void AutonomousPeriodic() 
	{
		Scheduler::GetInstance()->Run();
	}
	
	virtual void AutonomousContinuous()
	{

	}
	
	virtual void TeleopInit() {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (_autonomousCommand)
		{
			_autonomousCommand->Cancel();
		}
		
		clearLCD();
		
		_teleopCommand = (Command*)_teleopChooser->GetSelected();
//		_teleopCommand = (Command*)_noOpCmd;

		printCommandToLCD(_teleopCommand->GetName());
		
//		if (! CommandBase::azimuthSubsystem->IsCalibrated())
//		{
//			CommandBase::azimuthSubsystem->CalibrateAzimuth();
//		}
		_teleopCommand->Start();
//		_testRobotCmd->Start();
//		_cmd = new TestBridgeArmCmd(CommandBase::oi->driveTrigger);
//		_cmd->Start();
	}
	
	virtual void TeleopPeriodic() 
	{
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopContinuous()
	{
		
	}
	
	virtual void DisabledInit()
	{
		
	}
	
	virtual void DisabledPeriodic()
	{
		
	}
	virtual void DisabledContinuous()
	{
		
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

