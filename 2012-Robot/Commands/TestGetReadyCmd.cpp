#include "TestGetReadyCmd.h"



TestGetReadyCmd::TestGetReadyCmd(Button* trigger)
: CommandBase("TestGetReadyCmd")
, _trigger(trigger)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::azimuthSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
	Requires(CommandBase::collectorSubsystem);
	Requires(CommandBase::launcherSubsystem);
}

void TestGetReadyCmd::Initialize()
{
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1,"CLEAR A SPACE OR PUT THE ROBOT ON BLOCKS!!!");
	DriverStationLCD::GetInstance()->UpdateLCD();

	_done = false;
	_current = _trigger->Get();
	_last = false;
}

void TestGetReadyCmd::Execute()
{
	_done = checkDone();
	
}

bool TestGetReadyCmd::IsFinished()
{
	return _done;
}

void TestGetReadyCmd::End()
{
}

void TestGetReadyCmd::Interrupted()
{
}

bool TestGetReadyCmd::checkDone()
{
	_last = _current;
	_current = _trigger->Get();
	return ( (_last == false) && (_current == true) );
}
