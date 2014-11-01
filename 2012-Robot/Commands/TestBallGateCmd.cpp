#include "TestBallGateCmd.h"



TestBallGateCmd::TestBallGateCmd(Button* trigger)
: CommandBase("TestBallGateCmd")
, _trigger(trigger)
, _period(2.0)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::azimuthSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
	Requires(CommandBase::collectorSubsystem);
	Requires(CommandBase::launcherSubsystem);
}

void TestBallGateCmd::Initialize()
{
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Test Ball Gate");
	DriverStationLCD::GetInstance()->UpdateLCD();

	_done = false;
	_current = _trigger->Get();
	_last = false;
	
	_timer.Start();
	
	_goForward= true;
}

void TestBallGateCmd::Execute()
{
	_done = checkDone();
	if (_done)
	{
		CommandBase::collectorSubsystem->CloseGate();
		return;
	}
	
	if (_timer.HasPeriodPassed(_period))
	{
		
		_goForward = (_goForward == true ? false : true);
	
	}
	
	if (_goForward == true)
	{
		CommandBase::collectorSubsystem->OpenGate();
	}
	else
	{
		CommandBase::collectorSubsystem->CloseGate();
	}
}

bool TestBallGateCmd::IsFinished()
{
	return _done;
}

void TestBallGateCmd::End()
{
}

void TestBallGateCmd::Interrupted()
{
}

bool TestBallGateCmd::checkDone()
{
	_last = _current;
	_current = _trigger->Get();
	return ( (_last == false) && (_current == true) );
}
