#ifndef MOVE_TO_AND_DROP_BRIDGE_CMD
#define MOVE_TO_AND_DROP_BRIDGE_CMD

#include "../CommandBase.h"
	


/**
 *
 *
 * @author ExampleAuthor
 */
class MoveToAndDropBridgeCmd: public CommandBase 
{
public:
	MoveToAndDropBridgeCmd();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();	
private:
	float _targetedDistance;
	bool _atTarget;
	bool _isFinished;
	float _driveSpeed;
	float _leftCountsPerInch;
	float _rightCountsPerInch;
	Timer _timer;
};

#endif
