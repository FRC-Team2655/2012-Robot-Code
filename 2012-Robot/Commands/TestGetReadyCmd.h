#ifndef TEST_GET_READY_CMD_H
#define TEST_GET_READY_CMD_H

#include "../CommandBase.h"



/**
 *
 *
 * @author ExampleAuthor
 */
class TestGetReadyCmd: public CommandBase 
{
public:
	TestGetReadyCmd(Button* trigger);
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

private:
	bool checkDone();
};

#endif
