#include "MoveToAndDropBridgeCmd.h"



MoveToAndDropBridgeCmd::MoveToAndDropBridgeCmd()
: CommandBase("MoveToAndDropBridgeCmd")
, _atTarget (false)
, _isFinished (false)
, _driveSpeed(0.7f)
//, _leftCountsPerInch(37582.8f / 120.0f)
//, _rightCountsPerInch(37092.5f / 120.0f)
, _leftCountsPerInch(37500.0f / 120.0f)
, _rightCountsPerInch(37500.0f / 120.0f)
{
	Requires(CommandBase::driveTrainSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
}

void MoveToAndDropBridgeCmd::Initialize()
{
	SmartDashboard::GetInstance()->PutString("Status", "MoveToAndDropBridgeCmd::Initialize");
	CommandBase::driveTrainSubsystem->ResetLeftMotorEncoder();
	CommandBase::driveTrainSubsystem->ResetRightMotorEncoder();
	_atTarget = false;
//	_targetedDistance = (-120.0f); // Should be 120 inches for competition, it was origionally 60 inches
	_targetedDistance = (-160.0f); // Should be 120 inches for competition, it was origionally 60 inches
	_timer.Reset();
	_timer.Start();
}

void MoveToAndDropBridgeCmd::Execute()
{
	CommandBase::bridgeArmSubsystem->DeployRampLoweringDevice(false);
	if ( CommandBase::bridgeArmSubsystem->IsArmDown() == true)
	{
		CommandBase::bridgeArmSubsystem->DeployArmLatch(true);
	}
	if (_atTarget != true){
		float left = (CommandBase::driveTrainSubsystem->GetLeftMotorEncoderDistance() / _leftCountsPerInch);
		float right = (CommandBase::driveTrainSubsystem->GetRightMotorEncoderDistance() / _rightCountsPerInch);
		printf("LeftEnc:%5.1f, RightEnc:%5.1f, TgtDist:%5.1f\n", left, right, _targetedDistance);
		if ((left <= _targetedDistance) || (right <=_targetedDistance))
		{
			CommandBase::driveTrainSubsystem->Drive(0, 0);
			_atTarget = (true);
//			SetTimeout (2.0);
			_timer.Stop();
			_timer.Reset();
			_timer.Start();
			CommandBase::bridgeArmSubsystem->DeployRampLoweringDevice(true);
		}
		else 
		{
			CommandBase::driveTrainSubsystem->Drive(_driveSpeed, _driveSpeed);
		}
	}
	
}

bool MoveToAndDropBridgeCmd::IsFinished()
{
	if ( (_isFinished == true) && (IsTimedOut() == true))
	{
		SmartDashboard::GetInstance()->PutString("Status", "MoveToAndDropBridgeCmd::Finished");
		return false;
	}
	else
	{
		return false;
	}
}

void MoveToAndDropBridgeCmd::End()
{
	if (_isFinished == true){
		CommandBase::driveTrainSubsystem->Drive(0, 0);
		CommandBase::bridgeArmSubsystem->DeployRampLoweringDevice(false);
	}
}


void MoveToAndDropBridgeCmd::Interrupted()
{
}
