#include "ExerciseMotorsCmd.h"



ExerciseMotorsCmd::ExerciseMotorsCmd(Button* button)
: CommandBase("ExerciseMotorsCmd")
, _button(button)
,_last(false) 
,_current(false)
,_state(0)
{
	Requires(CommandBase::collectorSubsystem);
	Requires(CommandBase::azimuthSubsystem);
//	Requires(CommandBase::elevationSubsystem);
	Requires(CommandBase::launcherSubsystem);
	Requires(CommandBase::bridgeArmSubsystem);
	Requires(CommandBase::driveTrainSubsystem);
}

void ExerciseMotorsCmd::Initialize()
{
	_state = 0;
}

void ExerciseMotorsCmd::Execute()
{
	// look for a rising edge on the trigger button to change state...
	_last =_current;
	_current = _button->Get();
	bool pressed = ( (_last == false) && (_current == true));
	if (!pressed) return;

	// if we got here, then we have a rising edge, so increment the state and wrap if necessary
	_state++;
	if (_state > 16)
	{
		_state=0;
	}

	// we are at the next valid state - so switch on the state variable to run the proper code
	switch (_state)
	{
	case 0: 
		printf("Clear a space or set on blocks\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Clear a space or set on blocks");
		turnOffAllMotors();
		break;
	case 1:
		printf("Run left drive motor\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Run left drive motor");
		turnOffAllMotors();
		CommandBase::driveTrainSubsystem->Drive(0.5, 0.0);
		break;
	case 2:
		printf("Reverse left drive motor\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Reverse left drive motor");
		turnOffAllMotors();
		CommandBase::driveTrainSubsystem->Drive(-0.5, 0.0);
		break;
	case 3:
		printf("Run right drive motor\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Run right drive motor");
		turnOffAllMotors();
		CommandBase::driveTrainSubsystem->Drive(0.0, 0.5);
		break;
	case 4:
		printf("Reverse right drive motor\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Reverse right drive motor");
		turnOffAllMotors();
		CommandBase::driveTrainSubsystem->Drive(0.0, -0.5);
		break;
	case 5:
		printf("Run infeed motor\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Run infeed motor");
		turnOffAllMotors();
		CommandBase::collectorSubsystem->StartInfeed();
		break;
	case 6:
		printf("Reverse infeed motor\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Reverse infeed motor");
		turnOffAllMotors();
		CommandBase::collectorSubsystem->ReverseInfeed();
		break;
	case 7:
		printf("Run ball brush motor\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Run ball brush motor");
		turnOffAllMotors();
		CommandBase::collectorSubsystem->StartBallBrushMotor();
		break;
	case 8:
		printf("Reverse ball brush motor\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Reverse ball brush motor");
		turnOffAllMotors();
		CommandBase::collectorSubsystem->ReverseBallBrushMotor();
		break;
	case 9:
		printf("Run ball feed motor\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Run ball feed motor");
		turnOffAllMotors();
		CommandBase::collectorSubsystem->StartBallFeedMotor();
		break;
	case 10:
		printf("Reverse ball feed motor\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Reverse ball feed motor");
		turnOffAllMotors();
		CommandBase::collectorSubsystem->ReverseBallFeedMotor();
		break;
	case 11:
		printf("Exercise azimuth subsystem\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Exercise azimuth subsystem");
		turnOffAllMotors();
		testAzimuth();
		break;
	case 12:
		printf("Exercise elevation subsystem\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Exercise elevation subsystem");
		turnOffAllMotors();
		testElevation();
		break;
	case 13:
		printf("Exercise launcher subsystem\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Exercise launcher subsystem");
		turnOffAllMotors();
		testLauncher();
		break;
	case 14:
		printf("Test the ball gate\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Test the ball gate");
		turnOffAllMotors();
		testBallGate();
		break;
	case 15:
		printf("Test the firing mechanism\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Test the firing mechanism");
		turnOffAllMotors();
		testFiringMechanism();
		break;
	case 16:
		printf("Test the bridge arm mechanism\n");
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, "Test the bridge arm mechanism");
		turnOffAllMotors();
		testBridgeArm();
		break;

	}
}

bool ExerciseMotorsCmd::IsFinished()
{
	return false;
}

void ExerciseMotorsCmd::End()
{
}

void ExerciseMotorsCmd::Interrupted()
{
}
void ExerciseMotorsCmd::turnOffAllMotors()
{
	CommandBase::collectorSubsystem->StopInfeed();
	CommandBase::collectorSubsystem->StopBallBrushMotor();
	CommandBase::collectorSubsystem->StopBallFeedMotor();
	CommandBase::azimuthSubsystem->SetAzimuth(CommandBase::azimuthSubsystem->GetAzimuth());
//	CommandBase::elevationSubsystem->SetElevation(CommandBase::elevationSubsystem->GetElevation());
	CommandBase::launcherSubsystem->SetSpeed(0.0f);
	CommandBase::driveTrainSubsystem->Drive(0.0, 0.0);
	CommandBase::collectorSubsystem->CloseGate();
	CommandBase::azimuthSubsystem->AZStop();
	CommandBase::bridgeArmSubsystem->DeployRampLoweringDevice(false);
	CommandBase::launcherSubsystem->Fire(false);
}

void ExerciseMotorsCmd::testAzimuth()
{
	
}

void ExerciseMotorsCmd::testElevation()
{
	
}

void ExerciseMotorsCmd::testLauncher()
{
	
}

void ExerciseMotorsCmd::testBallGate()
{
	
}

void ExerciseMotorsCmd::testFiringMechanism()
{
	
}

void ExerciseMotorsCmd::testBridgeArm()
{
	
	
}
