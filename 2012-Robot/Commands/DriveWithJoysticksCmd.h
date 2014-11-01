#ifndef DRIVE_WITH_JOYSTICKS_CMD_H
#define DRIVE_WITH_JOYSTICKS_CMD_H

#include "../CommandBase.h"



/**
 *
 *
 * @author ExampleAuthor
 */
class DriveWithJoysticksCmd: public CommandBase 
{
public:
	DriveWithJoysticksCmd();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:

};

#endif
