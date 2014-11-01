#ifndef TEST_BALLBRUSHES_CMD_H
#define TEST_BALLBRUSHES_CMD_H

#include "../CommandBase.h"
#include <Timer.h>


/**
 *
 *
 * @author ExampleAuthor
 */
class TestBallBrushesCmd: public CommandBase 
{
public:
	TestBallBrushesCmd(Button* trigger);
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
