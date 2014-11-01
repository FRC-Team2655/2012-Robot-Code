#ifndef COMPRESSOR_MONITOR_CMD_H
#define COMPRESSOR_MONITOR_CMD_H

#include "../CommandBase.h"



/**
 *
 *
 * @author ExampleAuthor
 */
class CompressorMonitorCmd: public CommandBase 
{
public:
	CompressorMonitorCmd();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:

};

#endif
