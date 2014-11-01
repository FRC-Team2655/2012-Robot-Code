#include "TestBallBrushesCmd.h"



TestBallBrushesCmd::TestBallBrushesCmd(Button* trigger)
: CommandBase("TestBallBrushesCmd")
, _trigger(trigger)
, _period(2.0)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::azimuthSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
	Requires(CommandBase::collectorSubsystem);
	Requires(CommandBase::launcherSubsystem);
}

void TestBallBrushesCmd::Initialize()
{
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Test Ball Brushes");
	DriverStationLCD::GetInstance()->UpdateLCD();

	_done = false;
	_current = _trigger->Get();
	_last = false;
	
	_timer.Start();
	
	_goForward= true;
}

void TestBallBrushesCmd::Execute()
{
	_done = checkDone();
	if (_done)
	{
		CommandBase::collectorSubsystem->StopBallBrushMotor();
		return;
	}
	
	if (_timer.HasPeriodPassed(_period))
	{
		
		_goForward = (_goForward == true ? false : true);
	
	}
	
	if (_goForward == true)
	{
		CommandBase::collectorSubsystem->StartBallBrushMotor();
	}
	else
	{
		CommandBase::collectorSubsystem->ReverseBallBrushMotor();
	}
}

bool TestBallBrushesCmd::IsFinished()
{
	return _done;
}

void TestBallBrushesCmd::End()
{
}

void TestBallBrushesCmd::Interrupted()
{
}

bool TestBallBrushesCmd::checkDone()
{
	_last = _current;
	_current = _trigger->Get();
	return ( (_last == false) && (_current == true) );
}
