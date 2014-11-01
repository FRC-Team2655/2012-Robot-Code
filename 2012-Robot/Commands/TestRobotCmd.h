#ifndef TEST_ROBOT_CMD_H
#define TEST_ROBOT_CMD_H

#include "../CommandBase.h"



/**
 *
 *
 * @author ExampleAuthor
 */
class TestRobotCmd: public CommandGroup 
{
public:
	TestRobotCmd(Button* trigger);
	virtual void Initialize();
	virtual void Execute();
	virtual void End();
	virtual void Interrupted();
	
private:
}; 

#endif
