#include "DriveAzimuthCmd.h"

DriveAzimuthCmd::DriveAzimuthCmd(Joystick* joystick, Joystick::AxisType axis, Button* fine_tune_btn) 
 : CommandBase("DriveAzimuthCmd")
 , _done(false)
 , _angle(0)
 , _joystick(joystick)
 , _axis(axis)
 , _maxDelta(5.0f)
 , _isZeroed(false)
 , _fineTuneBtn(fine_tune_btn)
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);

	Requires(CommandBase::azimuthSubsystem); 
	_dsLCD = DriverStationLCD::GetInstance();
	
}

// Called just before this Command runs the first time
void DriveAzimuthCmd::Initialize() 
{
	_isZeroed = false;
}

void DriveAzimuthCmd::Execute() 
{
//	if (! _isZeroed)
//	{
//		printf("\nZeroing azimuth system: Enc:%-5.1f\n", azimuthSubsystem->GetAzimuth());
//		while (! azimuthSubsystem->IsAtLeftStop())
//		{
//			azimuthSubsystem->DriveMotorDirectly(-0.75f);
//		}
//		printf("At left stop: Enc:%-5.1f\n", azimuthSubsystem->GetAzimuth());
//		azimuthSubsystem->DriveMotorDirectly(0.0f);
//		azimuthSubsystem->ResetEncoder();
//		printf("Azimuth zeroed: Enc:%-5.1f\n", azimuthSubsystem->GetAzimuth());
//		_isZeroed = true;
//		return;
//	}
//	
	float joystickValue = _joystick->GetAxis(_axis);
	float min(azimuthSubsystem->MinValue());
	float max(azimuthSubsystem->MaxValue());
	bool update = false;
	
	//printf("Elevation Joystick Value: %4.1f   ", joystickValue);
	
	float adjustment = ( _fineTuneBtn->Get() == 1 ? _maxDelta * 0.1f : _maxDelta);
	if (joystickValue > 0.1f)
	{
		_angle += (adjustment * joystickValue);
		update = true;
	}
	else if (joystickValue < -0.1f)
	{
		_angle += (adjustment * joystickValue);
		update = true;
	}
	else
	{
		//printf("\n");
		return;
	}

	if (update)
	{
		if (_angle > max) _angle = max;
		if (_angle < min) _angle = min;

		printf("Joystick:%3.1f  SetAzimuth:%5.1f\n", joystickValue, _angle);
		//count=count-1;
		//	_dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "DECmd:SetAzimuth(%d)", angle);
		//	_dsLCD->UpdateLCD();
		azimuthSubsystem->SetAzimuth(_angle);
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line2, "Azimuth:%7.3f", CommandBase::azimuthSubsystem->GetAzimuth());
		DriverStationLCD::GetInstance()->UpdateLCD();
	}
}

#ifdef OBSOLETE_CODE
// Called repeatedly when this Command is scheduled to run
void DriveAzimuthCmd::Execute() 
{
	float joystickValue = _joystick->GetAxis(_axis);
	//printf("Elevation Joystick Value: %4.1f   ", joystickValue);
	if (joystickValue > 0.2f)
	{
		_times++;
	}
	else if (joystickValue < -0.2f)
	{
		_times--;
	}
	else
	{
		//printf("\n");
		return;
	}
	
	float angle = 1.0f*_times;
	//count=count-1;
//	_dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "DECmd:SetAzimuth(%d)", angle);
//	_dsLCD->UpdateLCD();

	azimuthSubsystem->SetAzimuth(angle);
//	Wait(0.5);
	//printf("angle: %-4.1f\n", angle);
	
	
	
	
	//azimuthSubsystem->SetAzimuth(300.0f);
		
	//_done = true;
}
#endif



// Make this return true when this Command no longer needs to run execute()
bool DriveAzimuthCmd::IsFinished() 
{
	return false;
}

// Called once after isFinished returns true
void DriveAzimuthCmd::End() 
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveAzimuthCmd::Interrupted() 
{
}
