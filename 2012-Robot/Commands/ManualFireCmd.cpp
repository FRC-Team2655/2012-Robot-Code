#include "ManualFireCmd.h"

ManualFireCmd::ManualFireCmd(Button* fire_btn, Button* motor_button) 
: CommandBase("ManualFireCmd")
, _fireBtn(fire_btn)
, _motorBtn(motor_button)
{
	Requires(CommandBase::launcherSubsystem);
}

// Called just before this Command runs the first time
void ManualFireCmd::Initialize() 
{
	CommandBase::launcherSubsystem->SetEnabled(true);
}

// Called repeatedly when this Command is scheduled to run
void ManualFireCmd::Execute() 
{
	// check fire button
	if(_fireBtn->Get() == true)
	{
		CommandBase::launcherSubsystem->Fire(true);
	}
	else
	{
		CommandBase::launcherSubsystem->Fire(false);

	}

	// check motor button
	_lastState = _newState;
	_newState = _motorBtn->Get();
	bool toggle = (_lastState == false) && (_newState == true);

	if(toggle == true)
	{
		//printf(CommandBase::launcherSubsystem->IsEnabled() ? "Turning launcher motors off\n" : "Turning launcher motors on\n");
		CommandBase::launcherSubsystem->SetEnabled( CommandBase::launcherSubsystem->IsEnabled() ? false : true);
	}

	CommandBase::launcherSubsystem->SetSpeedWithJoystick();
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line3, "Fire Speed:%7.3f", CommandBase::launcherSubsystem->GetSpeed());
	DriverStationLCD::GetInstance()->UpdateLCD();

}

// Make this return true when this Command no longer needs to run execute()
bool ManualFireCmd::IsFinished() 
{
	return false;
}

// Called once after isFinished returns true
void ManualFireCmd::End() 
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualFireCmd::Interrupted() {
}
