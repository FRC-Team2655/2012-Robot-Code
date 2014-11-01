#ifndef DRIVE_IN_SQUARE_CMD_H
#define DRIVE_IN_SQUARE_CMD_H

#include "../CommandBase.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class DriveInSquareCmd: public CommandGroup 
{
public:
	DriveInSquareCmd();
//	virtual void Initialize();
//	virtual void Execute();
//	virtual bool IsFinished();
//	virtual void End();
//	virtual void Interrupted();
	
private:
	bool _isDone;
};

#endif
