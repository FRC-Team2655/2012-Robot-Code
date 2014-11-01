#ifndef LAUNCHER_SUBSYSTEM_H
#define LAUNCHER_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../OI.h"

/**
 * 
 *
 * @author ExampleAuthor
 */
class LauncherSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Jaguar _launcherMotor;
	Joystick* _throttleStick;
	Joystick::AxisType _axis;
	bool _ballLoaded;
	float _targetSpeed;
	float _speedRange;
	Relay _ballFire;
	bool _enabled;
	bool _firing;
	float _lastSpeed;
	
	
public:
	// constructor
	LauncherSubsystem(Joystick* joystick, Joystick::AxisType axis);
	
	void InitDefaultCommand();

	void Fire(bool fire);
	
	bool IsFiring();

	bool IsEnabled();
	
	void SetEnabled(bool enabled);
	
	void SetTargetSpeed(float speed);
	
	void SetTargetRange(float range);
	
	void SetSpeedWithJoystick();
	
	void SetSpeed(float speed);
	
	float GetSpeed();
	
	float GetMaxSpeed() { return _targetSpeed + (_speedRange / 2.0f); }
	
	float GetMinSpeed() { return _targetSpeed - (_speedRange / 2.0f); }

	
	
	

};

#endif
