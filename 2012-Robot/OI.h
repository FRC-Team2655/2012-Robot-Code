#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	int _count;

public:
	OI();
	
	Joystick* leftDriveJoystick;
	Joystick* rightDriveJoystick;
	Joystick* turretJoystick;
	Joystick* gamepadJoystick;
	Button* fireBtn;
	Button* kinectBridgeBtn;
	Button* driveTrigger;
	Button* azimuthFineTune;
	Button* switchCollectorModeBtn;
	Button* overrideCollectorFwdBtn;
	Button* overrideCollectorRevBtn;
	Button* bridgeArmDeployBtn;
	Button* launchMotorButton;
	Button* latchButton;
	KinectStick* kinectLeft;
	KinectStick* kinectRight;
	
};

#endif
