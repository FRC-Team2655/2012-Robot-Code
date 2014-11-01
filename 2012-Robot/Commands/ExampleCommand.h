#ifndef EXAMPLE_COMMAND_H
#define EXAMPLE_COMMAND_H

#include "../CommandBase.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class ExampleCommand: public CommandBase {
public:
	ExampleCommand(int& count);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool _done;
	int _times;
	DriverStationLCD* _dsLCD;
};

#endif
