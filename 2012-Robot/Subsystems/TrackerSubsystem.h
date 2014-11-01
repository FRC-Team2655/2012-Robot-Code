#ifndef TRACKER_SUBSYSTEM_H
#define TRACKER_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class TrackerSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	TrackerSubsystem();
	void InitDefaultCommand();

	bool IsTrackingEnabled(); 

	void SetTrackingEnabled(bool enabled);

	float GetTrimX(); 

	float GetTrimY(); 

	void ResetTrim();
};

#endif
