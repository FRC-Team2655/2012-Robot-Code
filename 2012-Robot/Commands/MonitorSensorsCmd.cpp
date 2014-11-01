#include "MonitorSensorsCmd.h"



MonitorSensorsCmd::MonitorSensorsCmd()
: CommandBase("MonitorSensorsCmd")
, _frequency(25)
{
	Requires(azimuthSubsystem);
}

void MonitorSensorsCmd::Initialize()
{
	_counter = 0;
}

//  line 1: Exercising ball brush motor
//  line 2: LeftEnc:00000 RightEnc:00000
//  line 3: US:0,0,0 LSL:0 LSM:0 LSH:0 LS:0
//  Line 4: AzEnc:000 ElEnc:000
void MonitorSensorsCmd::Execute()
{
	_counter = _counter +1;
	if (_counter > _frequency)
	{
		_counter = 0;
		
		float leftMotorEncoder = CommandBase::driveTrainSubsystem->GetLeftMotorEncoderDistance();
		float rightMotorEncoder = CommandBase::driveTrainSubsystem->GetLeftMotorEncoderDistance();
		float azimuthMotorEncoder = CommandBase::azimuthSubsystem->GetAzimuth();
		//float elevationMotorEncoder = CommandBase::elevationSubsystem->GetElevation();
		int lsl = (int)CommandBase::collectorSubsystem->IsBallInLowPosition();
		int lsm = (int)CommandBase::collectorSubsystem->IsBallInMidPosition();
		int lsh = (int)CommandBase::collectorSubsystem->IsBallInUpperPosition(); 
		int ls = (int)CommandBase::collectorSubsystem->IsBallLoaded();
		int azls = (int)CommandBase::azimuthSubsystem->IsAtLeftStop();
		int armls = (int)CommandBase::bridgeArmSubsystem->IsArmDown();
		//bool us = CommandBase::collectorSubsystem->;
		
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line2, "L:%7.1f R:%7.1f",leftMotorEncoder,rightMotorEncoder);
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line3, "LSL:%1d M:%1d H:%1d", lsl,lsm,lsh);
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line4, "LS:%1d AzLS:%1d ArmLS:%1d", ls, azls, armls);
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line5, "AzEnc:%5.1f",azimuthMotorEncoder);
		DriverStationLCD::GetInstance()->UpdateLCD();

	}
}

bool MonitorSensorsCmd::IsFinished()
{
	return false;
}

void MonitorSensorsCmd::End()
{
}

void MonitorSensorsCmd::Interrupted()
{
}

