#ifndef TEST_INFEED_CMD_H
#define TEST_INFEED_CMD_H

#include "../CommandBase.h"
#include <Timer.h>


/**
 *
 *
 * @author ExampleAuthor
 */
class TestInfeedCmd: public CommandBase 
{
public:
	TestInfeedCmd(Button* trigger);
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
	bool _goLeft;
	float _speed;
	
private:
	bool checkDone();
};

#endif
