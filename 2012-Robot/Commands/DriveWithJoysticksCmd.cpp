#include "DriveWithJoysticksCmd.h"



DriveWithJoysticksCmd::DriveWithJoysticksCmd()
: CommandBase("DriveWithJoysticksCmd")
{
	Requires(CommandBase::driveTrainSubsystem);
}

void DriveWithJoysticksCmd::Initialize()
{
	SmartDashboard::GetInstance()->PutString("Status", "DriveWithJoysticksCmd::Initialize");
}

void DriveWithJoysticksCmd::Execute()
{
	CommandBase::driveTrainSubsystem-> DriveWithJoysticks();
}
bool DriveWithJoysticksCmd::IsFinished()
{
	return false;
}

void DriveWithJoysticksCmd::End()
{
	SmartDashboard::GetInstance()->PutString("Status", "DriveWithJoysticksCmd::Interrupted");
}

void DriveWithJoysticksCmd::Interrupted()
{
	SmartDashboard::GetInstance()->PutString("Status", "DriveWithJoysticksCmd::Interrupted");
}

