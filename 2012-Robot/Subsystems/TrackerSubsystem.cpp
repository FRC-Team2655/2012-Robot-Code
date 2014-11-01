#include "TrackerSubsystem.h"
#include "../Robotmap.h"

TrackerSubsystem::TrackerSubsystem() : Subsystem("TrackerSubsystem") {
	
}
    
void TrackerSubsystem::InitDefaultCommand() 
{
	// Set the default command for a subsystem here.
}

bool TrackerSubsystem::IsTrackingEnabled() 
{
	return false;
}

void TrackerSubsystem::SetTrackingEnabled(bool enabled)
{

}

float TrackerSubsystem::GetTrimX() 
{
	return 0.0f;
}

float TrackerSubsystem::GetTrimY() 
{
	return 0.0f;
}

void TrackerSubsystem::ResetTrim() {

	
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

