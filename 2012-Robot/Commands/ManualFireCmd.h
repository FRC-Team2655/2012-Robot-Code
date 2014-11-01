#ifndef MANUAL_FIRE_COMMAND_H
#define MANUAL_FIRE_COMMAND_H

#include "../CommandBase.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class ManualFireCmd: public CommandBase {
public:
	ManualFireCmd(Button* fire_btn, Button* motor_button);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool _lastState;
	bool _newState;
	Button* _fireBtn;
	Button* _motorBtn;

};

#endif
