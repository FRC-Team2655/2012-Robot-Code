#include "DriveCmd.h"

//#include "nivision.h"
//#include "nimachinevision.h"

DriveCmd::DriveCmd(float drive_duration, float left_motor, float right_motor)
 : CommandBase("DriveCmd")
{
	Requires(CommandBase::driveTrainSubsystem);

	duration = drive_duration;
	leftMotor = left_motor;
	rightMotor = right_motor;

}

void DriveCmd::Initialize()
{
	SetTimeout(duration);
}

void DriveCmd::Execute()
{
	CommandBase::driveTrainSubsystem-> Drive(leftMotor, rightMotor);
}
bool DriveCmd::IsFinished()
{
	return IsTimedOut();
}

void DriveCmd::End()
{
}

void DriveCmd::Interrupted()
{
}

