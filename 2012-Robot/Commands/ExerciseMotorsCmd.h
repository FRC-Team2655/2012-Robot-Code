#ifndef EXERCISE_MOTORS_CMD_H
#define EXERCISE_MOTORS_CMD_H

#include "../CommandBase.h"
#include <Timer.h>


/**
 *
 *
 * @author ExampleAuthor
 */
class ExerciseMotorsCmd: public CommandBase 
{
public:
	ExerciseMotorsCmd(Button* button);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	Button* _button;
	bool _last;
	bool _current;
	int _state;
	Timer _timer;

private:
	void turnOffAllMotors();
	void testAzimuth();
	void testElevation();
	void testLauncher();
	void testBallGate();
	void testFiringMechanism();
	void testBridgeArm();
	
}; 

#endif
