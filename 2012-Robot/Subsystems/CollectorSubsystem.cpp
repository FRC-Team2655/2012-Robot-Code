#include "CollectorSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/CollectBallsCmd.h"

/*
 * http://www.maxbotix.com/tutorials.htm
Connect all the MaxSonar®-EZ1™ RX lines together, and connect to your 
control circuit such as a pin on a microcontroller (or even a 555 timer 
set up to strobe high for at least 20us with, a period between strobes 
of 50mS or more).  Then start all the MaxSonar®-EZ1™ sensors at the same 
time by pulling the RX lines high for 20uS (or more but less than 47 mS).  
You can repeat this every 50mS or more.  This will sync the MaxSonar®-EZ1™ 
sensors to take readings at the same time.  The MaxSonar®-EZ1™, because 
of continuously variable gain, will ignore (in most instances) adjacent 
sensors. This method is especially convenient when using the analog voltage 
(AN output), as the analog voltage can be read at any time (i.e. the user 
does not have to wait for the output). Please see question 6f for 
additional information.
*/		
		
CollectorSubsystem::CollectorSubsystem() 
 : Subsystem("CollectorSubsystem") 
 , _inFeedMotor(MODULE_A, PWM_CHAN_COLLECTOR_INFEED_MOTOR)
 , _ballBrushMotor(MODULE_A, PWM_CHAN_COLLECTOR_BRUSHES_MOTOR)
 , _relayGate(MODULE_A, RELAY_CHAN_GATE, Relay::kForwardOnly)
 , _ballFeedMotor(MODULE_A, RELAY_CHAN_COLLECTOR_BALLFEED_MOTOR, Relay::kBothDirections)
 , _lightSensorLow(MODULE_B, DIO_CHAN_LIGHTSENSOR_LOW)
 , _lightSensorMid(MODULE_B, DIO_CHAN_LIGHTSENSOR_MID)
 , _lightSensorHigh(MODULE_B, DIO_CHAN_LIGHTSENSOR_HIGH)
 , _hopperLimitSwitch(MODULE_A, DIO_CHAN_LAUNCHER_LIMITSWITCH)
 , _sonarInputA(ANALOG_CHAN_SONAR_INPUT_A)
 , _sonarInputB(ANALOG_CHAN_SONAR_INPUT_B)
 , _sonarInputC(ANALOG_CHAN_SONAR_INPUT_C)
 , _brushSpeed(0.8)
{
	
}
void CollectorSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new CollectBallsCmd(CommandBase::oi->switchCollectorModeBtn, CommandBase::oi->overrideCollectorFwdBtn, CommandBase::oi->overrideCollectorRevBtn));
	_inFeedMotor.SetSafetyEnabled(false);
	_ballBrushMotor.SetSafetyEnabled(false);
}

bool CollectorSubsystem::IsBallLoaded()
{
	//printf("limit switch: %d",_hopperLimitSwitch.Get());
	if (_hopperLimitSwitch.Get() == 1)
	{
		return true;
	}
	
	else
	{
		return false;
	}
	
}



bool CollectorSubsystem::IsBallInUpperPosition()
{
//	printf("ball is in upper position: %d",_lightSensorHigh.Get());
		if (_lightSensorHigh.Get() >  4){
			return true;
		}
		
		else{
			return false;
		}
}
bool CollectorSubsystem::IsBallInMidPosition()
{
//	printf("ball is in mid position: %d",_lightSensorMid.Get());
		if (_lightSensorMid.Get() >  4){
			return true;
		}
		
		else{
			return false;
		}
}
bool CollectorSubsystem::IsBallInLowPosition()
{
//	printf("ball is in low position: %d",_lightSensorLow.Get());
		if (_lightSensorLow.Get() >  4){
			return true;
		}
		
		else{
			return false;
		}
}

int CollectorSubsystem::NumBallsUnderInfeed()
{
	return 0;
}

int CollectorSubsystem::NumBallsInCollector() 
{
	_ballUnder = 0;
	if(_lightSensorLow.Get() >  4){
		_ballUnder = _ballUnder + 1;
	}
	if(_lightSensorMid.Get() >  4){
			_ballUnder = _ballUnder + 1;
		}
	if(_lightSensorHigh.Get() >  4){
			_ballUnder = _ballUnder + 1;
		}
	 if(_hopperLimitSwitch.Get() >  .5){
		 _ballUnder = _ballUnder + 1;
	 }
	return _ballUnder;
}
void CollectorSubsystem::sonarstrobe (){

}
float CollectorSubsystem::ballDistanceFromInfeedA()
{
float voltage = _sonarInputA.GetVoltage();
return voltage * _scale - _offset;
}
float CollectorSubsystem::ballDistanceFromInfeedB()
{
float voltage = _sonarInputB.GetVoltage();
return voltage * _scale - _offset;
}
float CollectorSubsystem::ballDistanceFromInfeedC()
{
float voltage = _sonarInputC.GetVoltage();
return voltage * _scale - _offset;
}
void CollectorSubsystem::StartInfeed()
{
	_inFeedMotor.Set(-0.5);
}
void CollectorSubsystem::ReverseInfeed()
{
	_inFeedMotor.Set(0.5);
}
void CollectorSubsystem::StopInfeed()
{
	_inFeedMotor.Set(0);
}
void CollectorSubsystem::StartBallBrushMotor()
{
	_ballBrushMotor.Set(- _brushSpeed );
}
void CollectorSubsystem::ReverseBallBrushMotor()
{
	_ballBrushMotor.Set( _brushSpeed );
}
void CollectorSubsystem::StopBallBrushMotor()
{
	_ballBrushMotor.Set(0);
}
void CollectorSubsystem::StartBallFeedMotor()
{
	_ballFeedMotor.Set(Relay::kForward); 
}
void CollectorSubsystem::ReverseBallFeedMotor()
{
	_ballFeedMotor.Set(Relay::kReverse);
}
void CollectorSubsystem::StopBallFeedMotor()
{
	_ballFeedMotor.Set(Relay::kOff);
}
void CollectorSubsystem::EmergencyReverse()
{
	_inFeedMotor.Set(-0.5);
	_ballBrushMotor.Set(0);
	_ballFeedMotor.Set(Relay::kOff);
}
void CollectorSubsystem::OpenGate()
{
	_relayGate.Set(Relay::kForward);//The gate is open
}

void CollectorSubsystem::CloseGate()
{
	_relayGate.Set(Relay::kReverse);//The gate is closed
}
