#include "TestBridgeArmCmd.h"



TestBridgeArmCmd::TestBridgeArmCmd(Button* trigger)
: CommandBase("TestBridgeArmCmd")
, _trigger(trigger)
, _period(5.0)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::azimuthSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
	Requires(CommandBase::collectorSubsystem);
	Requires(CommandBase::launcherSubsystem);
}

void TestBridgeArmCmd::Initialize()
{
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"Test Bridge Arm");
	DriverStationLCD::GetInstance()->UpdateLCD();

	_done = false;
	_current = _trigger->Get();
	_last = false;
	
	_timer.Start();
	
	_goForward= true;
}

void TestBridgeArmCmd::Execute()
{
	_done = checkDone();
	if (_done)
	{
		CommandBase::bridgeArmSubsystem->DeployRampLoweringDevice(false);
		return;
	}
	
	if (_timer.HasPeriodPassed(_period))
	{
		
		_goForward = (_goForward == true ? false : true);
	
	}
	
	if (_goForward == true)
	{
		CommandBase::bridgeArmSubsystem->DeployRampLoweringDevice(true);
	}
	else
	{
		CommandBase::bridgeArmSubsystem->DeployRampLoweringDevice(false);
	}
}

bool TestBridgeArmCmd::IsFinished()
{
	return _done;
}

void TestBridgeArmCmd::End()
{
}

void TestBridgeArmCmd::Interrupted()
{
}

bool TestBridgeArmCmd::checkDone()
{
	_last = _current;
	_current = _trigger->Get();
	return ( (_last == false) && (_current == true) );
}
