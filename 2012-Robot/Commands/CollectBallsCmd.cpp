#include "CollectBallsCmd.h"





CollectBallsCmd::CollectBallsCmd(Button* switch_btn, Button* override_fwd_btn, Button* override_rev_btn)
: CommandBase("CollectBallsCmd")
, _switchBtn(switch_btn)
, _overrideFwdBtn(override_fwd_btn)
, _overrideRevBtn(override_rev_btn)
, _lastSwitchBtnState(false)
, _currentSwitchBtnState(false)
, _state(0)
, _lastState(false)
, _newState(false)
, _BallFeedState(0)
, _GateState(0)
, _InfeedRollerState(0)
, _newReadLowSensor(false)
, _newReadMidSensor(false)
, _newReadHighSensor(false)
, _newReadHopperSensor(false)
, _lastReadLowSensor(false)
, _lastReadMidSensor(false)
, _lastReadHighSensor(false)
, _lastReadHopperSensor(false)
, _mode(0)
{
	Requires(CommandBase::collectorSubsystem);
}

void CollectBallsCmd::Initialize()
{
	_lastSwitchBtnState = false;
	_currentSwitchBtnState = false;
	_mode = 0;
}

void CollectBallsCmd::Execute()
{
	_lastSwitchBtnState = _currentSwitchBtnState;
	_currentSwitchBtnState = _switchBtn->Get();
	bool switchedPressed = (_lastSwitchBtnState == false) && (_currentSwitchBtnState == true);
	if (switchedPressed)
	{
		_mode++;
		if (_mode > 1) _mode = 0;
	}
	
	if (_overrideFwdBtn->Get() == true)
	{
		allMotorsForward();
		return;
	}
	if (_overrideRevBtn->Get() == true)
	{
		allMotorsReverse();
		return;
	}
	
	switch (_mode)
	{
	case 0: // use our logic
		BallBrushLogic();
		BallFeedLogic();
		BallGateLogic();
		InfeedRollerLogic();
		break;
	case 1: // force off
		allMotorsOff();
		break;
	}
}

bool CollectBallsCmd::IsFinished()
{
	return false;
}

void CollectBallsCmd::End()
{
}

void CollectBallsCmd::Interrupted()
{
}


void CollectBallsCmd::BallFeedLogic()
{
	CollectorSubsystem* cs = CommandBase::collectorSubsystem;
	
	if ( (cs->IsBallLoaded() == false) && (CommandBase::launcherSubsystem->IsFiring() == false) )
	{
		cs->StartBallFeedMotor();
		return;
	}

// JBS: The following if case removed since we found one ball can trigger two sensors simultaneously, so we don't want to reverse, just stop 	
//	if (cs->IsBallInLowPosition() && cs->IsBallInMidPosition() && cs->IsBallInUpperPosition())
//	{
//		cs->ReverseBallFeedMotor();
//		return;
//	}
	
	if (    ( ( cs->IsBallInLowPosition() == true)  && (cs->IsBallInMidPosition() == false) && (cs->IsBallInUpperPosition() == false) )
		 || ( ( cs->IsBallInLowPosition() == true)  && (cs->IsBallInMidPosition() == true)  && (cs->IsBallInUpperPosition() == false) )
		 || ( ( cs->IsBallInLowPosition() == false) && (cs->IsBallInMidPosition() == false) && (cs->IsBallInUpperPosition() == false) )	)
	{
		cs->StartBallFeedMotor();
		return;
	}
	
	cs->StopBallFeedMotor();
}

//void CollectBallsCmd::OldBallFeed()
//{
//	int ballsInCollector = CommandBase::collectorSubsystem->NumBallsInCollector();
//
//	_lastReadLowSensor = _newReadLowSensor;
//	_newReadLowSensor = CommandBase::collectorSubsystem->IsBallInLowPosition();
//	bool lowPositionEdge = (_lastReadLowSensor == false) && (_newReadLowSensor == true);
//
//	_lastReadMidSensor = _newReadMidSensor;
//	_newReadMidSensor = CommandBase::collectorSubsystem->IsBallInMidPosition();
//	bool midPositionEdge = (_lastReadMidSensor == false) && (_newReadMidSensor == true);
//
//	_lastReadHighSensor = _newReadHighSensor;
//	_newReadHighSensor = CommandBase::collectorSubsystem->IsBallInUpperPosition();
//	bool highPositionEdge = (_lastReadHighSensor == false) && (_newReadHighSensor == true);
//
//	_lastReadHopperSensor = _newReadHopperSensor;
//	_newReadHopperSensor = CommandBase::collectorSubsystem->IsBallLoaded();
//	bool justLoaded = (_lastReadHopperSensor == false) && (_newReadHopperSensor == true);
//	//bool justFired = (_lastReadHopperSensor == true) && (_newReadHopperSensor == false);
//
////	S0: motor running (0 balls)
////	if one in hopper and LSM rising edge 
////	S1: motor off (1 ball in launcher, one in collector) : if fire goto S0
////	if LSL rising edge
////	S2: motor running (1 in hopper, 2 in collector); if fire goto S
////	if LSM rising edge 
////	S3: motor off (1 in hopper, 2 in collector)
//	
//
//	switch(_BallFeedState)
//	{
//	case 0:			
//		//The Ball Feed is stopped
//		CommandBase::collectorSubsystem->StopBallFeedMotor();
//		bool fire = (ballsInCollector > 0) && !CommandBase::collectorSubsystem->IsBallLoaded();
//		if(lowPositionEdge||fire){
//			_GateState = 1;
//		}
//		break;
//
//	case 1:
//		//The ball feed is going
//		CommandBase::collectorSubsystem->StartBallFeedMotor();
//		
//		bool trip2 = midPositionEdge&&CommandBase::collectorSubsystem->IsBallLoaded()&&CommandBase::collectorSubsystem->IsBallInUpperPosition();
//		bool trip3 = highPositionEdge&&CommandBase::collectorSubsystem->IsBallLoaded();
//		bool tripHopper = justLoaded && (CommandBase::collectorSubsystem->NumBallsInCollector() == 1);
//
//		if(trip2||trip3||tripHopper){
//			_GateState = 0;
//		}
//
//		break;
//
//	default:
//		break;
//	}
//}

void CollectBallsCmd::BallBrushLogic()
{
	CollectorSubsystem* cs = CommandBase::collectorSubsystem;
	
	if ( (cs->IsBallLoaded() == false) && (CommandBase::launcherSubsystem->IsFiring() == false) )
	{
		cs->StartBallBrushMotor();
		return;
	}

	if ( ( cs->IsBallInLowPosition() == true) && (cs->IsBallInUpperPosition() == true) )
	{
		cs->StopBallBrushMotor();
		return;
	}
	
	cs->StartBallBrushMotor();
}

//void CollectBallsCmd::BallBrushLogic()
//{
//	int ballsInCollector = CommandBase::collectorSubsystem->NumBallsInCollector();
//
//	if (ballsInCollector < 3)
//	{
//		CommandBase::collectorSubsystem->StartBallBrushMotor();
//		return;
//	}
//	
//	if (ballsInCollector > 3)
//	{
//		CommandBase::collectorSubsystem->ReverseBallBrushMotor();
//	}
//	
//	CommandBase::collectorSubsystem->StopBallBrushMotor();
//}

void CollectBallsCmd::InfeedRollerLogic()
{
	int ballsInCollector = CommandBase::collectorSubsystem->NumBallsInCollector();
	int incomingBalls = CommandBase::collectorSubsystem->NumBallsUnderInfeed();

	switch(_InfeedRollerState)
			{
				case 0:			
					//This is the InfeedRoller going forward
					CommandBase::collectorSubsystem->StartInfeed();
					if( (ballsInCollector > 2) || ( (ballsInCollector == 2) && (incomingBalls >= 2) ) )
					{
						_InfeedRollerState = 1;
					}
					break;
			
				case 1:
					//This is the InfeedRoller reversing
					CommandBase::collectorSubsystem->ReverseInfeed();
					if( (ballsInCollector <= 1) || ( ( ballsInCollector == 2) && ( incomingBalls < 2) )  )
					{
						_InfeedRollerState = 0;
					}
						
					break;
			
				default:
					break;
			}
}

void CollectBallsCmd::BallGateLogic()
{
	if ( (CommandBase::collectorSubsystem->IsBallLoaded() == true) && ((CommandBase::launcherSubsystem->IsFiring() == false)) )
	{
		CommandBase::collectorSubsystem->CloseGate();
	}
	else
	{
		CommandBase::collectorSubsystem->OpenGate();
	}
}


void CollectBallsCmd::allMotorsForward()
{
	CollectorSubsystem* cs = CommandBase::collectorSubsystem;

	cs->StartInfeed();
	cs->StartBallBrushMotor();
	cs->StartBallFeedMotor();
	cs->OpenGate();
}

void CollectBallsCmd::allMotorsReverse()
{
	CollectorSubsystem* cs = CommandBase::collectorSubsystem;

	cs->ReverseInfeed();
	cs->ReverseBallBrushMotor();
	cs->ReverseBallFeedMotor();
	cs->CloseGate();
}


void CollectBallsCmd::allMotorsOff()
{
	CollectorSubsystem* cs = CommandBase::collectorSubsystem;

	cs->StopInfeed();
	cs->StopBallBrushMotor();
	cs->StopBallFeedMotor();
	cs->CloseGate();
}

