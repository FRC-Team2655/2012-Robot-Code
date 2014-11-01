#include "TestFireCmd.h"



TestFireCmd::TestFireCmd(Button* trigger)
: CommandBase("TestFireCmd")
, _trigger(trigger)
, _period(2.0)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::azimuthSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
	Requires(CommandBase::collectorSubsystem);
	Requires(CommandBase::launcherSubsystem);
}

void TestFireCmd::Initialize()
{
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Test Fire Mech");
	DriverStationLCD::GetInstance()->UpdateLCD();

	_done = false;
	_current = _trigger->Get();
	_last = false;
	
	_timer.Start();
	
	_goForward= true;
}

void TestFireCmd::Execute()
{
	_done = checkDone();
	if (_done)
	{
		CommandBase::launcherSubsystem->Fire(false);
		return;
	}
	
	if (_timer.HasPeriodPassed(_period))
	{
		
		_goForward = (_goForward == true ? false : true);
	
	}
	
	if (_goForward == true)
	{
		CommandBase::launcherSubsystem->Fire(true);
	}
	else
	{
		CommandBase::launcherSubsystem->Fire(false);
	}
}

bool TestFireCmd::IsFinished()
{
	return _done;
}

void TestFireCmd::End()
{
}

void TestFireCmd::Interrupted()
{
}

bool TestFireCmd::checkDone()
{
	_last = _current;
	_current = _trigger->Get();
	return ( (_last == false) && (_current == true) );
}
