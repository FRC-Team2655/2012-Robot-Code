#include "CommandBase.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
OI* CommandBase::oi = NULL;
ExampleSubsystem* CommandBase::examplesubsystem = NULL;
AzimuthSubsystem* CommandBase::azimuthSubsystem = NULL;
//ElevationSubsystem* CommandBase::elevationSubsystem = NULL;
DriveTrainSubsystem* CommandBase::driveTrainSubsystem = NULL;
CollectorSubsystem* CommandBase::collectorSubsystem = NULL;
BridgeArmSubsystem* CommandBase::bridgeArmSubsystem = NULL;
LauncherSubsystem* CommandBase::launcherSubsystem = NULL;
CompressorSubsystem* CommandBase::compressorSubsystem = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	oi = new OI();
	examplesubsystem = new ExampleSubsystem();
	azimuthSubsystem = new AzimuthSubsystem();
	//elevationSubsystem = new ElevationSubsystem();
	driveTrainSubsystem = new DriveTrainSubsystem(oi->leftDriveJoystick, oi->rightDriveJoystick);
    collectorSubsystem = new CollectorSubsystem();
    bridgeArmSubsystem = new BridgeArmSubsystem();
    launcherSubsystem = new LauncherSubsystem(oi->turretJoystick, Joystick::kThrottleAxis);
    compressorSubsystem = new CompressorSubsystem();
}
