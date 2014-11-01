#ifndef TEST_LAUNCHER_CMD_H
#define TEST_LAUNCHER_CMD_H

#include "../CommandBase.h"
#include <Timer.h>


/**
 *
 *
 * @author ExampleAuthor
 */
class TestLauncherCmd: public CommandBase 
{
public:
	TestLauncherCmd(Button* trigger);
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
	bool _maxSpeed;
	float _max;
	float _min;
	
private:
	bool checkDone();
};

#endif
