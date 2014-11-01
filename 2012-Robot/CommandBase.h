#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Commands/Command.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Subsystems/AzimuthSubsystem.h"
#include "OI.h"
#include "Subsystems/DriveTrainSubsystem.h"
#include "Subsystems/ElevationSubsystem.h"
#include "Subsystems/CollectorSubsystem.h"
#include "Subsystems/BridgeArmSubsystem.h" 
#include "Subsystems/LauncherSubsystem.h"
#include "Subsystems/CompressorSubsystem.h"



/**
 * The base for all commands. All amtomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command 
{
public:
	CommandBase(const char *name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	static ExampleSubsystem* examplesubsystem;
	static AzimuthSubsystem* azimuthSubsystem;
	static DriveTrainSubsystem* driveTrainSubsystem;
//	static ElevationSubsystem* elevationSubsystem;
	static CollectorSubsystem* collectorSubsystem;
	static BridgeArmSubsystem* bridgeArmSubsystem;
	static LauncherSubsystem* launcherSubsystem;
	static CompressorSubsystem* compressorSubsystem;
	static OI * oi;
	
};

#endif
