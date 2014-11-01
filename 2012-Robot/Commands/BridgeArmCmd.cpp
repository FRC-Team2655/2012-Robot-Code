#include "BridgeArmCmd.h"

BridgeArmCmd::BridgeArmCmd(Button* deploy_btn) 
: CommandBase("BridgeArmCmd")
{
	Requires(CommandBase::bridgeArmSubsystem);
	_deployBtn = deploy_btn;
	
}


void BridgeArmCmd::Initialize() 
{
	
}


void BridgeArmCmd::Execute() 
{
	bool deploy = _deployBtn->Get();
	CommandBase::bridgeArmSubsystem->DeployRampLoweringDevice(deploy);
	CommandBase::bridgeArmSubsystem->DeployArmLatch(deploy);
//	if (deploy) printf("Deploying bridge arm\n");
}

// Make this return true when this Command no longer needs to run execute()
bool BridgeArmCmd::IsFinished() 
{
	return false;
}

// Called once after isFinished returns true
void BridgeArmCmd::End() 
{
	
}


void BridgeArmCmd::Interrupted() 
{
}
