#ifndef COLLECT_BALLS_CMD_H
#define COLLECT_BALLS_CMD_H

#include "../CommandBase.h"




/**
 *
 *
 * @author ExampleAuthor
 */
class CollectBallsCmd: public CommandBase 
{
public:
	CollectBallsCmd(Button* switch_btn, Button* override_fwd_btn, Button* override_rev_btn);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	Button* _switchBtn;
	Button* _overrideFwdBtn;
	Button* _overrideRevBtn;
	bool _lastSwitchBtnState;
	bool _currentSwitchBtnState;
	unsigned int _state;
	bool _lastState;
	bool _newState;
	unsigned int _BallFeedState;
	unsigned int _GateState;
	unsigned int _InfeedRollerState;
	bool _newReadLowSensor;
	bool _newReadMidSensor;
	bool _newReadHighSensor;
	bool _newReadHopperSensor;
	bool _lastReadLowSensor;
	bool _lastReadMidSensor;
	bool _lastReadHighSensor;
	bool _lastReadHopperSensor;
	int _mode;
	
private:
	void BallFeedLogic();
	void BallBrushLogic();
	void InfeedRollerLogic();
	void BallGateLogic();
	void allMotorsForward();
	void allMotorsReverse();
	void allMotorsOff();

	
};

#endif
