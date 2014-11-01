#ifndef TEST_BRIDGE_ARM_CMD_H
#define TEST_BRIDGE_ARM_CMD_H

#include "../CommandBase.h"
#include <Timer.h>


/**
 *
 *
 * @author ExampleAuthor
 */
class TestBridgeArmCmd: public CommandBase 
{
public:
	TestBridgeArmCmd(Button* trigger);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	Button* _trigger;
	bool _done;
	bool _current;
	bool _last;
	Timer _timer;
	double _period;

private:
	bool _goForward;
	
private:
	bool checkDone();
};

#endif
