#ifndef MONITOR_SENSORS_CMD_H
#define MONITOR_SENSORS_CMD_H

#include "../CommandBase.h"



/**
 *
 *
 * @author ExampleAuthor
 */
class MonitorSensorsCmd: public CommandBase 
{
public:
	MonitorSensorsCmd();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	int _frequency;
	int _counter;
}; 

#endif
