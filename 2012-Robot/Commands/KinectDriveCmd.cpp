#include "KinectDriveCmd.h"



KinectDriveCmd::KinectDriveCmd(KinectStick* left_stick, KinectStick* right_stick, Button* bridge_btn)
: CommandBase("KinectDriveCmd")
 ,_leftStick(left_stick)
 ,_rightStick(right_stick)
 ,_bridgeBtn(bridge_btn)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
}

void KinectDriveCmd::Initialize()
{
}

void KinectDriveCmd::Execute()
{
	float leftValue = _leftStick->GetY();
	float rightValue = _rightStick->GetY();
	CommandBase::driveTrainSubsystem-> Drive(leftValue, rightValue);
	if (_bridgeBtn)
	{
		CommandBase::bridgeArmSubsystem->DeployRampLoweringDevice(true);
	}
//	printf("LeftStick: %-4.1f  RightStick: %-4.1f\n", leftValue, rightValue);
}

bool KinectDriveCmd::IsFinished()
{
	return false;
}

void KinectDriveCmd::End()
{
}

void KinectDriveCmd::Interrupted()
{
}
