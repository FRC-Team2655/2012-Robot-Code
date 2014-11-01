#ifndef DRIVE_CMD_H
#define DRIVE_CMD_H

#include "../CommandBase.h"



/**
 *
 *
 * @author ExampleAuthor
 */
class DriveCmd: public CommandBase 
{
public:
	DriveCmd(float drive_duration, float left_motor, float right_motor);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	float duration;
	float leftMotor;
	float rightMotor;

};

#endif
