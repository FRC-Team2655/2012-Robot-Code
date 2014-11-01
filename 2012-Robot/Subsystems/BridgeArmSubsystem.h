#ifndef BRIDGEARM_SUBSYSTEM_H
#define BRIDGEARM_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class BridgeArmSubsystem: public Subsystem {
private:
	Relay _relay;
	Servo _armLatch;
	DigitalInput _armLimitSwitch;
	bool _deployed;
	int _latchVal;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	BridgeArmSubsystem();
	void InitDefaultCommand();
	
	void DeployRampLoweringDevice(bool deploy);
	
	bool GetRampState();
	
	bool IsArmDown();
	
	void DeployArmLatch(bool deploy);
	
	void IsArmLatched();
};

#endif
