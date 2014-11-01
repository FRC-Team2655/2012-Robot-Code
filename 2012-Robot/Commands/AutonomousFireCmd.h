#ifndef AUTONOMOUS_FIRE_COMMAND_H
#define AUTONOMOUS_FIRE_COMMAND_H

#include "../CommandBase.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class AutonomousFireCmd: public CommandBase {
public:
	AutonomousFireCmd();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	Timer _timer;
	double _timeToRunCollector;
	double _timeToFireBallActuator;
	double _timeToSpinUp;
	int _mode;
};

#endif
