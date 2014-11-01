#ifndef COLLECTOR_SUBSYSTEM_H
#define COLLECTOR_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class CollectorSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities 
	Victor 			_inFeedMotor;
	Victor 			_ballBrushMotor;
	Relay           _relayGate;
	Relay 			_ballFeedMotor;
	DigitalInput 	_lightSensorLow;
	DigitalInput 	_lightSensorMid;
	DigitalInput 	_lightSensorHigh;
	DigitalInput 	_hopperLimitSwitch;
	AnalogChannel 	_sonarInputA;
	AnalogChannel 	_sonarInputB;
	AnalogChannel 	_sonarInputC;
//	DigitalOutput 	_sonarStrobe;
	float 			_brushSpeed;
	int _offset;
	int _scale;
	
	
	int 			_ballUnder;
	//Ultrasonic		_sonarA;
	//Ultrasonic		_sonarB;
	
public:
	// constructor
	CollectorSubsystem();
	
	void InitDefaultCommand();

	bool IsBallLoaded();
	bool IsBallInUpperPosition();
	bool IsBallInMidPosition();
	bool IsBallInLowPosition();
	int NumBallsUnderInfeed();
	int NumBallsInCollector();
	float ballDistanceFromInfeedA();
	float ballDistanceFromInfeedB();
	float ballDistanceFromInfeedC();
	void StartInfeed();
	void ReverseInfeed();
	void StopInfeed();
	void StartBallBrushMotor();
	void ReverseBallBrushMotor();
	void StopBallBrushMotor();
	void StartBallFeedMotor();
	void ReverseBallFeedMotor();
	void StopBallFeedMotor();
	void EmergencyReverse();
	void OpenGate();
	void CloseGate();
	void sonarstrobe();
	
};

#endif
