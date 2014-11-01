#include "AutonomousFireCmd.h"

AutonomousFireCmd::AutonomousFireCmd() 
: CommandBase("AutonomousFireCmd")
, _timeToRunCollector(1.0)
, _timeToFireBallActuator(3.5)
, _timeToSpinUp(1.0)


{
	Requires(CommandBase::launcherSubsystem);
	Requires(CommandBase::collectorSubsystem);
}

// Called just before this Command runs the first time
void AutonomousFireCmd::Initialize() 
{
	_mode = 0;
	//_timer.Reset();
	_timer.Start();
	CommandBase::launcherSubsystem->SetEnabled(true);
	CommandBase::launcherSubsystem->SetSpeed(0.79);
}

// Called repeatedly when this Command is scheduled to run
void AutonomousFireCmd::Execute() 
{
	CommandBase::launcherSubsystem->SetSpeed(0.79);
	switch (_mode)
	{
	case 0:
		CommandBase::collectorSubsystem->StopBallBrushMotor();
		CommandBase::collectorSubsystem->StopBallFeedMotor();
		CommandBase::collectorSubsystem->OpenGate();
		if (_timer.HasPeriodPassed(2.0))
		{
			_mode++;
		}
		break;
	case 1:
		CommandBase::collectorSubsystem->StopBallBrushMotor();
		CommandBase::collectorSubsystem->StopBallFeedMotor();
		CommandBase::collectorSubsystem->OpenGate();
		CommandBase::launcherSubsystem->Fire(true);
		if (_timer.HasPeriodPassed(4))
		{
			_mode++;
		}
		break;
	case 2:
		CommandBase::launcherSubsystem->Fire(false);
		if (_timer.HasPeriodPassed(_timeToFireBallActuator))
		{
			_mode++;
		}
		break;
	case 3:
		CommandBase::collectorSubsystem->StartBallBrushMotor();
		CommandBase::collectorSubsystem->StartBallFeedMotor();
		CommandBase::collectorSubsystem->OpenGate();
		if (_timer.HasPeriodPassed(_timeToRunCollector))
		{
			_mode++;
		}
		break;
	case 4:
		CommandBase::collectorSubsystem->StopBallBrushMotor();
		CommandBase::collectorSubsystem->StopBallFeedMotor();
		CommandBase::collectorSubsystem->OpenGate();
		_mode++;
		break;
	case 5:
		CommandBase::launcherSubsystem->Fire(true);
		if (_timer.HasPeriodPassed(_timeToFireBallActuator))
		{
			_mode++;
		}
		break;
	case 6:
		CommandBase::launcherSubsystem->Fire(false);
		if (_timer.HasPeriodPassed(_timeToFireBallActuator))
		{
			_mode++;
		}
		break;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousFireCmd::IsFinished() 
{
	return (_mode > 6);
}

// Called once after isFinished returns true
void AutonomousFireCmd::End() 
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousFireCmd::Interrupted() {
}
