#include "AzimuthSubsystem.h"
#include "../Robotmap.h"
#include "Encoder.h"
#include <math.h>
#include "../Commands/DriveAzimuthCmd.h"


AzimuthSubsystem::AzimuthSubsystem() 
 : PIDSubsystem("AzimuthSubsystem", 0.004, 0.0005, 0.0)
 , _azimuthMotor(MODULE_B, PWM_CHAN_AZIMUTH_MOTOR)
 , _azimuthEncoder(	MODULE_B, DIO_CHAN_AZIMUTH_ENC_A,
		 	 	 	MODULE_B, DIO_CHAN_AZIMUTH_ENC_B)
 , _limitSwitch (MODULE_B, DIO_AZIMUTH_LIMITSWITCH)
// , _LEFT_BOUND(-180.0f) // degrees !TBD
// , _RIGHT_BOUND(180.0f) // degrees !TBD
 , _LEFT_BOUND(0.0f) 
 , _RIGHT_BOUND(1200.0f) 
// , _LAZY_SUSAN_CIRCUMFERENCE(2.0f) // meters !TBD
// , _ENCODER_WHEEL_CIRCUMFERENCE(0.25f) // meters !TBD
 , _ENCODER_TICKS_PER_REVOLUTION(360.0f) // ticks !TBD
 , _GEAR_RATIO(1.0f)
 , _count(0)
 , _currentSetPoint(0)
 , _printAzimuthValues(false)
 , _sendAzimuthValues(false)
 , _sendLcdAzimuthValues(false)
 , _calibrated(false)

{
	_azimuthMotor.SetSafetyEnabled(false);
		while (_limitSwitch.Get() != 0)
		{
			_azimuthMotor.Set(-0.4f);
		}
		_azimuthMotor.Set(0.0f);
		_azimuthEncoder.Reset();
		
		SetSetpointRange(_LEFT_BOUND, _RIGHT_BOUND);
		//_azimuthEncoder.SetDistancePerPulse( (360.0f / _ENCODER_TICKS_PER_REVOLUTION) / (360.0f * _ENCODER_WHEEL_CIRCUMFERENCE) / ( _LAZY_SUSAN_CIRCUMFERENCE * 360.0f ) );
		
		_azimuthEncoder.SetDistancePerPulse(_ENCODER_TICKS_PER_REVOLUTION / 360.0f * _GEAR_RATIO);
		_azimuthEncoder.Start();
		SetSetpoint(0);
		_dsLCD = DriverStationLCD::GetInstance();
	//	_smartdash = SmartDashboard::GetInstance();
	//	_smartdash->PutData(this);
	    Enable();
	    _calibrated = true;
	
}

void AzimuthSubsystem::CalibrateAzimuth()
{

    
    //_calibrated = true;
}
    
void AzimuthSubsystem::InitDefaultCommand() 
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new DriveAzimuthCmd(CommandBase::oi->turretJoystick, Joystick::kTwistAxis, CommandBase::oi->azimuthFineTune));
}

void AzimuthSubsystem::SetAzimuth(float new_azimuth)
{
	SetSetpoint(new_azimuth);
	_currentSetPoint = new_azimuth;
	displayDebuggingInfo(new_azimuth);
	Enable();
}
void AzimuthSubsystem::AZStop()
{
	Disable();
}

void AzimuthSubsystem::DriveMotorDirectly(float speed)
{
	Disable();
	_azimuthMotor.Set(speed);
}

void AzimuthSubsystem::ResetEncoder()
{
	_azimuthEncoder.Reset();
}

float AzimuthSubsystem::GetAzimuth()
{
	//_dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "SetAz(%f): %f", new_azimuth,  _azimuthEncoder.GetDistance());
	return _azimuthEncoder.GetDistance();
}

//void AzimuthSubsystem::SetMotor(float value)
//{
//	_azimuthMotor.Set(value);
//	_dsLCD->PrintfLine(DriverStationLCD::kUser_Line3, "SetMotor(%d): %d", _count++, (_azimuthEncoder.Get() / 8) );
//}

double AzimuthSubsystem::ReturnPIDInput() 
{
//	_dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "(%f): %f", _currentSetPoint,  _azimuthEncoder.GetDistance());
//	_dsLCD->UpdateLCD();
	return _azimuthEncoder.GetDistance();
}

void AzimuthSubsystem::UsePIDOutput(double output) 
{
	_azimuthMotor.Set(output);
}


bool AzimuthSubsystem::AtSetpoint()
{
	return (fabs(GetPosition() - GetSetpoint()) < 0.1);
}

bool AzimuthSubsystem::IsAtLeftStop()
{
	return (_limitSwitch.Get() == 0);
}

void AzimuthSubsystem::displayDebuggingInfo(float azimuth)
{
	if (_printAzimuthValues)
	{
		printf("Azimuth: %-5.2f\n", azimuth);
	}
	
	if (_sendAzimuthValues)
	{
		SmartDashboard::GetInstance()->PutDouble("Azimuth", (double)azimuth);
	}
	if (_sendLcdAzimuthValues)
	{
		_dsLCD->PrintfLine(DriverStationLCD::kUser_Line2, "Azimuth: %f", azimuth);
		_dsLCD->UpdateLCD();
	}
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

/*
public class Wrist extends PIDSubsystem {
    public static final double UPPER_BOUND = 0.024;
    public static final double LOWER_BOUND = UPPER_BOUND + 0.92;
    public static final double UP_POSITION = UPPER_BOUND + 0.150;
    private final Jaguar motor = new Jaguar(2);
    private final AnalogChannel pot = new AnalogChannel(4);
    
    public Wrist() {
        super(2.3, 0, 0);
        setSetpointRange(LOWER_BOUND, UPPER_BOUND);
        setSetpoint(UP_POSITION);
        enable();
    } 
    
      protected double returnPIDInput() {
        return pot.getAverageVoltage() / MAX_VOLTAGE;
    }
    protected void usePIDOutput(double output) {
        motor.set(output);
    }
    
 */

