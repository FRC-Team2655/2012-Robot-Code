#include "DriveElevationCmd.h"

DriveElevationCmd::DriveElevationCmd(Joystick* joystick, Joystick::AxisType axis) 
 : CommandBase("DriveElevationCmd")
 , _done(false)
 , _angle(0.0f)
 , _joystick(joystick)
 , _axis(axis)

{
	// TBD: Uncomment the following line when the ElevationSubstem is created and initialized in CommandBase
//	Requires(CommandBase::elevationSubsystem);
	_dsLCD = DriverStationLCD::GetInstance();
}


// Called just before this Command runs the first time
void DriveElevationCmd::Initialize() 
{
	
}

// Called repeatedly when this Command is scheduled to run
void DriveElevationCmd::Execute() 
{
	float joystickValue = _joystick->GetAxis(_axis);
	bool update = false;
	
	//printf("Elevation Joystick Value: %4.1f   ", joystickValue);
	if (joystickValue > 0.1f)
	{
		_angle += (1.0f * joystickValue);
		update = true;
	}
	else if (joystickValue < -0.1f)
	{
		_angle += (1.0f * joystickValue);
		update = true;
	}
	else
	{
		//printf("\n");
		return;
	}

	if (update)
	{
		if (_angle > 180.0f) _angle = 180.0f;
		if (_angle < -180.0f) _angle = -180.0f;

		printf("Joystick:%3.1f  SetElevation:%5.1f\n", joystickValue, _angle);
		//count=count-1;
		//	_dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "DECmd:SetAzimuth(%d)", angle);
		//	_dsLCD->UpdateLCD();
//		elevationSubsystem->SetElevation(_angle);
	}
	//	Wait(0.5);
	//printf("angle: %-4.1f\n", angle);




	//azimuthSubsystem->SetAzimuth(300.0f);

	//_done = true;
}

// Make this return true when this Command no longer needs to run execute()
bool DriveElevationCmd::IsFinished() 
{
	return false;
}

// Called once after isFinished returns true
void DriveElevationCmd::End() 
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveElevationCmd::Interrupted() 
{
}
