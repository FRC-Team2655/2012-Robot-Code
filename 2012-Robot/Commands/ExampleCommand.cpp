#include "ExampleCommand.h"

ExampleCommand::ExampleCommand(int& count) 
: CommandBase("ExampleCommand")
,_done(false)
, _times(count)

{
	_dsLCD = DriverStationLCD::GetInstance();
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	
}

// Called just before this Command runs the first time
void ExampleCommand::Initialize() 
{
	
}

// Called repeatedly when this Command is scheduled to run
void ExampleCommand::Execute() 
{
	
//	count=count+1;
	_dsLCD->PrintfLine(DriverStationLCD::kUser_Line1, "ExCmd:SetAzimuth(30)-%d", _times++);
	_dsLCD->UpdateLCD();
	//Wait(0.1);

	azimuthSubsystem->SetAzimuth(10.0f*_times);
	
	
	//azimuthSubsystem->SetMotor(0.5f);
	
		
	
	
	//azimuthSubsystem->SetAzimuth(300.0f);
		
	_done = true;
}

// Make this return true when this Command no longer needs to run execute()
bool ExampleCommand::IsFinished() 
{
	return _done;
}

// Called once after isFinished returns true
void ExampleCommand::End() 
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExampleCommand::Interrupted() {
}
