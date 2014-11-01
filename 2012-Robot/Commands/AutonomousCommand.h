#ifndef AUTONOMOUS_COMMAND_H
#define AUTONOMOUS_COMMAND_H

#include "../CommandBase.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class AutonomousCommand: public CommandBase {
public:
	AutonomousCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
