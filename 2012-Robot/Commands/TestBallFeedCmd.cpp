#include "TestBallFeedCmd.h"



TestBallFeedCmd::TestBallFeedCmd(Button* trigger)
: CommandBase("TestBallFeedCmd")
, _trigger(trigger)
, _period(2.0)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::azimuthSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
	Requires(CommandBase::collectorSubsystem);
	Requires(CommandBase::launcherSubsystem);
}

void TestBallFeedCmd::Initialize()
{
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Test Ball Feed");
	DriverStationLCD::GetInstance()->UpdateLCD();

	_done = false;
	_current = _trigger->Get();
	_last = false;
	
	_timer.Start();
	
	_goForward= true;
}

void TestBallFeedCmd::Execute()
{
	_done = checkDone();
	if (_done)
	{
		CommandBase::collectorSubsystem->StopBallFeedMotor();
		return;
	}
	
	if (_timer.HasPeriodPassed(_period))
	{
		
		_goForward = (_goForward == true ? false : true);
	
	}
	
	if (_goForward == true)
	{
		CommandBase::collectorSubsystem->StartBallFeedMotor();
	}
	else
	{
		CommandBase::collectorSubsystem->ReverseBallFeedMotor();
	}
}

bool TestBallFeedCmd::IsFinished()
{
	return _done;
}

void TestBallFeedCmd::End()
{
}

void TestBallFeedCmd::Interrupted()
{
}

bool TestBallFeedCmd::checkDone()
{
	_last = _current;
	_current = _trigger->Get();
	return ( (_last == false) && (_current == true) );
}
