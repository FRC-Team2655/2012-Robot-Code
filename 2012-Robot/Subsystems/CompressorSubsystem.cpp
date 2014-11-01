#include "CompressorSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/ManualFireCmd.h"

CompressorSubsystem::CompressorSubsystem() 
: Subsystem("CompressorSubsystem") 
//, _pressureSensor(MODULE_B, DIO_CHAN_PRESSURE_SWITCH)
, _isRunning(false)
, _enabled (false)
, _compressorControl (MODULE_B, DIO_CHAN_PRESSURE_SWITCH, MODULE_A, RELAY_CHAN_COMPRESSOR)
{
	_compressorControl.Start();
}

void CompressorSubsystem::InitDefaultCommand() 
{
	
}

void CompressorSubsystem::StopCompressor()
{
	_compressorControl.Stop();
}

bool CompressorSubsystem::IsEnabled()
{
	return _enabled;

}

void CompressorSubsystem::SetEnabled(bool enabled)
{
	_enabled = enabled;
	if (_enabled)
	{
		_compressorControl.Start();
	}
	else
	{
		_compressorControl.Stop();
	}
		
}



// Put methods for controlling this subsystem
// here. Call these from Commands.

//Gandalf = points:59
