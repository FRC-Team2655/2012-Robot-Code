#ifndef TEST_FIRE_CMD_H
#define TEST_FIRE_CMD_H

#include "../CommandBase.h"
#include <Timer.h>


/**
 *
 *
 * @author ExampleAuthor
 */
class TestFireCmd: public CommandBase 
{
public:
	TestFireCmd(Button* trigger);
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
