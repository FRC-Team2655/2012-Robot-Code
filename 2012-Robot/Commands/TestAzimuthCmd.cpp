#include "TestAzimuthCmd.h"



TestAzimuthCmd::TestAzimuthCmd(Button* trigger)
: CommandBase("TestAzimuthCmd")
, _trigger(trigger)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::azimuthSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
	Requires(CommandBase::collectorSubsystem);
	Requires(CommandBase::launcherSubsystem);
}

void TestAzimuthCmd::Initialize()
{
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Test Azimuth");
	DriverStationLCD::GetInstance()->UpdateLCD();

	_done = false;
	_current = _trigger->Get();
	_last = false;
		
	_goRight= false;
	_maxValue = CommandBase::azimuthSubsystem->MaxValue();
	_minValue = CommandBase::azimuthSubsystem->MinValue();

}

void TestAzimuthCmd::Execute()
{
	_done = checkDone();
	if (_done)
	{
		CommandBase::azimuthSubsystem->SetAzimuth(0.0);
		return;
	}
	
	if (CommandBase::azimuthSubsystem->AtSetpoint())
	{
		_goRight = (_goRight == true ? false : true);
		
		if (_goRight)
		{
			CommandBase::azimuthSubsystem->SetAzimuth(_maxValue);
		}
		else
		{
			CommandBase::azimuthSubsystem->SetAzimuth(_minValue);
		}
	}
}

bool TestAzimuthCmd::IsFinished()
{
	return _done;
}

void TestAzimuthCmd::End()
{
}

void TestAzimuthCmd::Interrupted()
{
}

bool TestAzimuthCmd::checkDone()
{
	_last = _current;
	_current = _trigger->Get();
	return ( (_last == false) && (_current == true) );
}
