#include "TestInfeedCmd.h"



TestInfeedCmd::TestInfeedCmd(Button* trigger)
: CommandBase("TestInfeedCmd")
, _trigger(trigger)
, _period(2.0)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::azimuthSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
	Requires(CommandBase::collectorSubsystem);
	Requires(CommandBase::launcherSubsystem);
}

void TestInfeedCmd::Initialize()
{
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Test Infeed Motor");
	DriverStationLCD::GetInstance()->UpdateLCD();

	_done = false;
	_current = _trigger->Get();
	_last = false;
	
	_timer.Start();
	
	_goLeft = false;
}

void TestInfeedCmd::Execute()
{
	_done = checkDone();
	if (_done)
	{
		CommandBase::collectorSubsystem->StopInfeed();
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
		CommandBase::collectorSubsystem->StartInfeed();
	}
	else
	{
		CommandBase::collectorSubsystem->ReverseInfeed();
	}
}

bool TestInfeedCmd::IsFinished()
{
	return _done;
}

void TestInfeedCmd::End()
{
}

void TestInfeedCmd::Interrupted()
{
}

bool TestInfeedCmd::checkDone()
{
	_last = _current;
	_current = _trigger->Get();
	return ( (_last == false) && (_current == true) );
}
