#ifndef AZIUMUTH_SUBSYSTEM_H
#define AZIUMUTH_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class AzimuthSubsystem: public PIDSubsystem 
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Jaguar _azimuthMotor;
	Encoder _azimuthEncoder;
	DriverStationLCD* _dsLCD;
	SmartDashboard* _smartdash;
	DigitalInput _limitSwitch;
	const float _LEFT_BOUND;
	const float _RIGHT_BOUND;
	const float _ENCODER_TICKS_PER_REVOLUTION; 
	const float _GEAR_RATIO;
	int _count;
	float _currentSetPoint;
	bool _printAzimuthValues;
	bool _sendAzimuthValues;
	bool _sendLcdAzimuthValues;
	bool _calibrated;

public:
	// constructor
	AzimuthSubsystem();
	
	void InitDefaultCommand();
	void SetAzimuth(float new_azimuth);
//	void SetMotor(float value);
	float GetAzimuth();
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output); 
	bool AtSetpoint();
	float MinValue() { return _LEFT_BOUND; }
	float MaxValue() { return _RIGHT_BOUND; }
	bool IsAtLeftStop();
	void AZStop();
	void DriveMotorDirectly(float speed);
	void ResetEncoder();
	void CalibrateAzimuth();
	bool IsCalibrated() { return _calibrated; }
	
	
protected:
	double returnPIDInput(); 
	void usePIDOutput(double output); 

private:
	void displayDebuggingInfo(float az);

};

#endif
