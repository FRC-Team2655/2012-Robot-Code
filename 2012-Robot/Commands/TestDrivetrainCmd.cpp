#include "TestDrivetrainCmd.h"



TestDrivetrainCmd::TestDrivetrainCmd(Button* trigger)
: CommandBase("TestDrivetrainCmd")
, _trigger(trigger)
, _period(2.0)
, _speed(0.8f)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::azimuthSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
	Requires(CommandBase::collectorSubsystem);
	Requires(CommandBase::launcherSubsystem);
}

void TestDrivetrainCmd::Initialize()
{
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Test Drive Train");
	DriverStationLCD::GetInstance()->UpdateLCD();

	_done = false;
	_current = _trigger->Get();
	_last = _current;
	
	_timer.Start();
	
	_goLeft = false;
}

void TestDrivetrainCmd::Execute()
{
	_done = checkDone();
	if (_done)
	{
		CommandBase::driveTrainSubsystem->Drive(0.0f, 0.0f);
		return;
	}
	
	if (_timer.HasPeriodPassed(_period))
	{
		// the following line is the same as...
		_goLeft = (_goLeft == true ? false : true);
		
		// ...the following code
//		if (_goLeft == true)
//		{
//			_goLeft = false;
//		}
//		else
//		{
//			_goLeft = true;
//		}
	}
	
	if (_goLeft == true)
	{
		CommandBase::driveTrainSubsystem->Drive(0.0f, _speed);
	}
	else
	{
		CommandBase::driveTrainSubsystem->Drive(_speed, 0.0f);
	}
}

bool TestDrivetrainCmd::IsFinished()
{
	return _done;
}

void TestDrivetrainCmd::End()
{
}

void TestDrivetrainCmd::Interrupted()
{
}

bool TestDrivetrainCmd::checkDone()
{
	_last = _current;
	_current = _trigger->Get();
	return ( (_last == false) && (_current == true) );
}
