#ifndef TEST_AZIMUTH_CMD_H
#define TEST_AZIMUTH_CMD_H

#include "../CommandBase.h"
#include <Timer.h>


/**
 *
 *
 * @author ExampleAuthor
 */
class TestAzimuthCmd: public CommandBase 
{
public:
	TestAzimuthCmd(Button* trigger);
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
	bool _goRight;
	float _maxValue;
	float _minValue;
	
private:
	bool checkDone();
};

#endif
