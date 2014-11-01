#ifndef COMPRESSOR_SUBSYSTEM_H
#define COMPRESSOR_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../OI.h"

/**
 *
 *
 * @author ExampleAuthor
 */

// rename to CompressorSubsystem
class CompressorSubsystem: public Subsystem {

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	//DigitalInput _pressureSensor;  
	bool _isRunning; 
	bool _enabled;
	Compressor _compressorControl;
	
	
public:

	// constructor                
	CompressorSubsystem ();

	void InitDefaultCommand();


	void StopCompressor();
	
	bool IsEnabled(); // keep
	

	void SetEnabled(bool enabled); // keep

	
	

};

#endif
