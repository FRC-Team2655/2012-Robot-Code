#include "TestLauncherCmd.h"



TestLauncherCmd::TestLauncherCmd(Button* trigger)
: CommandBase("TestLauncherCmd")
, _trigger(trigger)
, _period(2.0)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::azimuthSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
	Requires(CommandBase::collectorSubsystem);
	Requires(CommandBase::launcherSubsystem);
}

void TestLauncherCmd::Initialize()
{
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Test Launcher Motor");
	DriverStationLCD::GetInstance()->UpdateLCD();

	_done = false;
	_current = _trigger->Get();
	_last = false;
	
	_timer.Start();
	
	_maxSpeed= false;
	_min = CommandBase::launcherSubsystem->GetMinSpeed();
	_max = CommandBase::launcherSubsystem->GetMaxSpeed();

}

void TestLauncherCmd::Execute()
{
	_done = checkDone();
	if (_done)
	{
		CommandBase::launcherSubsystem->SetSpeed(0.0);
		return;
	}
	
	if (_timer.HasPeriodPassed(_period))
	{
		
		_maxSpeed = (_maxSpeed == true ? false : true);
	
	}
	
	if (_maxSpeed == true)
	{
		CommandBase::launcherSubsystem->SetSpeed(_max);
	}
	else
	{
		CommandBase::launcherSubsystem->SetSpeed(_min);
	}
}

bool TestLauncherCmd::IsFinished()
{
	return _done;
}

void TestLauncherCmd::End()
{
}

void TestLauncherCmd::Interrupted()
{
}

bool TestLauncherCmd::checkDone()
{
	_last = _current;
	_current = _trigger->Get();
	return ( (_last == false) && (_current == true) );
}
