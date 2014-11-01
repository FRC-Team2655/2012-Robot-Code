#include "BridgeArmSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/BridgeArmCmd.h"

BridgeArmSubsystem::BridgeArmSubsystem() : Subsystem("BridgeArmSubsystem")
,_relay(MODULE_A, RELAY_CHAN_BRIDGEARM, Relay::kBothDirections)
, _armLatch(MODULE_B, PWM_CHAN_BRIDGEARM_LATCH_SERVO)
, _armLimitSwitch(MODULE_B, DIO_BRIDGEARM_LIMITSWITCH)
,_deployed(false)
,_latchVal(0)

{
} 
    
void BridgeArmSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new BridgeArmCmd(CommandBase::oi->bridgeArmDeployBtn));
}


void BridgeArmSubsystem::DeployRampLoweringDevice(bool deploy)
{
	if(deploy == true)
	{
		_relay.Set(Relay::kForward);
		_deployed = true;
	}
	else
	{
		_relay.Set(Relay::kOff);
		_deployed = false;
	}
}


bool BridgeArmSubsystem::GetRampState()
{
	return _deployed;
}
	
bool BridgeArmSubsystem::IsArmDown()
{
	if(_armLimitSwitch.Get() == 1){
		return true;
	}
	else{
		return false;
	}
}

void BridgeArmSubsystem::DeployArmLatch(bool deploy)
{
	if (deploy == true){
		_armLatch.Set(1.0);
	}
	else{
		_armLatch.Set(0.0);
	}
}

void BridgeArmSubsystem::IsArmLatched()
{
	 _latchVal = _armLatch.Get();
	
}
	

// Put methods for controlling this subsystem
// here. Call these from Commands.

