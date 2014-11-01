#include "LauncherSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/ManualFireCmd.h"

LauncherSubsystem::LauncherSubsystem(Joystick* joystick, Joystick::AxisType axis)  
: Subsystem("LauncherSubsystem") 
, _launcherMotor(MODULE_B, PWM_CHAN_LAUNCHER_MOTOR)
, _throttleStick(joystick)
, _axis(axis)
, _ballLoaded(false)
, _targetSpeed (0.8f)
, _speedRange (0.4f)
, _ballFire (MODULE_A, RELAY_CHAN_RELAY_FIRE, Relay::kBothDirections)
, _enabled (false)
, _firing(false)
, _lastSpeed(0.0f)
{
	_launcherMotor.SetSafetyEnabled(false);
}

void LauncherSubsystem::InitDefaultCommand() 
{
	SetDefaultCommand(new ManualFireCmd(CommandBase::oi->fireBtn, CommandBase::oi->launchMotorButton));
}

void LauncherSubsystem::Fire(bool fire)
{
//	if(_enabled == false)
//	{
//		_ballFire.Set(Relay::kOff);
//		_firing = false;
//		return;
//	}
	if (fire == true)
	{
		_ballFire.Set(Relay::kForward);
//		_ballFire.Set(Relay::kOff);
		_firing = true;
	}
	else
	{
		_ballFire.Set(Relay::kOff);
//		_ballFire.Set(Relay::kForward);
		_firing = false;
	}
}

bool LauncherSubsystem::IsFiring()
{
	return _firing;
}


bool LauncherSubsystem::IsEnabled()
{
	return _enabled;

}

void LauncherSubsystem::SetEnabled(bool enabled)
{
	_enabled = enabled;
}

void LauncherSubsystem::SetTargetSpeed(float speed)
{
	_targetSpeed = speed;
}

void LauncherSubsystem::SetTargetRange(float range)
{
	_speedRange = range;
}

void LauncherSubsystem::SetSpeedWithJoystick()
{
	if (_enabled == false){
		_launcherMotor.Set(0);
		return;
	}
	float throttleValue = 0 - _throttleStick->GetAxis(_axis);
	_lastSpeed = _targetSpeed + ( (0.5f * _speedRange) * throttleValue);
	_launcherMotor.Set(_lastSpeed);
}

void LauncherSubsystem::SetSpeed(float speed)
{
	if(_enabled == false)
	{
		_launcherMotor.Set(0);
		return;
	}
	_lastSpeed = speed;
	_launcherMotor.Set(speed);
}

float LauncherSubsystem::GetSpeed()
{
	return _lastSpeed;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

//Gandalf = points:100
