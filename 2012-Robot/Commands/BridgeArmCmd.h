#ifndef BRIDGE_ARM_COMMAND_H
#define BRIDGE_ARM_COMMAND_H

#include "../CommandBase.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class BridgeArmCmd: public CommandBase {
public:
	BridgeArmCmd(Button* deploy_btn);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	

private:
	Button* _deployBtn;
	
	
};

#endif
