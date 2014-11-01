#ifndef ELEVATION_SUBSYSTEM_H
#define ELEVATION_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

#ifdef DONT_COMPILE
/**
 *
 *
 * @author ExampleAuthor
 */
class ElevationSubsystem: public PIDSubsystem 
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
		Jaguar _elevationMotor;
		Encoder _elevationEncoder;
		DriverStationLCD* _dsLCD;
		SmartDashboard* _smartdash;
		DigitalInput _limitSwitch;
		
		const float _UP_BOUND;
		const float _DOWN_BOUND;
		const float _ENCODER_TICKS_PER_REVOLUTION; 
		const float _GEAR_RATIO;
		int _count;
		float _currentSetPoint;
		bool _printElevationValues;
		bool _sendElevationValues;
		bool _sendLcdElevationValues;

public:
	// constructor
	ElevationSubsystem();
	
	void InitDefaultCommand();

	void SetElevation(float elevation); 
	//	void SetMotor(float value);
		


	float GetElevation(); 
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output); 
	bool AtSetpoint();



protected:
	double returnPIDInput(); 
	void usePIDOutput(double output); 

private:
	void displayDebuggingInfo(float elevation);

};
#endif

#endif
