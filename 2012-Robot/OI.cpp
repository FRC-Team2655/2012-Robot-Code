#include "OI.h"
#include "Commands/ExampleCommand.h"
#include "Robotmap.h"
OI::OI() 
	: _count(0)	
{
	// Process operator interface input here.
	leftDriveJoystick = new Joystick(LEFT_DRIVE_JOYSTICK);
	rightDriveJoystick = new Joystick(RIGHT_DRIVE_JOYSTICK);
	turretJoystick = new Joystick(TURRET_JOYSTICK);
	gamepadJoystick = new Joystick(GAME_PAD_JOYSTICK);

	kinectLeft = new KinectStick(1);
	kinectRight = new KinectStick(2);
	kinectBridgeBtn = new JoystickButton(kinectLeft, 1);
	
	fireBtn = new JoystickButton(turretJoystick, 1);
	launchMotorButton = new JoystickButton(turretJoystick, 2);
	azimuthFineTune = new JoystickButton(turretJoystick, 3);
	
	driveTrigger = new JoystickButton(leftDriveJoystick, 1);

	bridgeArmDeployBtn = new JoystickButton(rightDriveJoystick, 1);
	switchCollectorModeBtn = new JoystickButton(rightDriveJoystick, 3);
	overrideCollectorFwdBtn = new JoystickButton(rightDriveJoystick, 5);
	overrideCollectorRevBtn = new JoystickButton(rightDriveJoystick, 4);
	latchButton = new JoystickButton(leftDriveJoystick, 2);
	//button1->WhileHeld(new ExampleCommand(_count));
	//button2->WhileHeld(new DriveElevationCommand(_count));
	//DriveElevationCmd(leftJoy, kYAxis);

	
}

