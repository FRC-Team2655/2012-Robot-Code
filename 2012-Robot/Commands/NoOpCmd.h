#ifndef NO_OP_CMD_H
#define NO_OP_CMD_H

#include "../CommandBase.h"



/**
 *
 *
 * @author ExampleAuthor
 */
class NoOpCmd: public CommandBase 
{
public:
	NoOpCmd();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:

};

#endif
