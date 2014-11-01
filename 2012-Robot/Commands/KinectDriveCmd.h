#ifndef Kinect_Drive_Cmd
#define Kinect_Drive_Cmd

#include "../CommandBase.h"



/**
 *
 *
 * @author ExampleAuthor
 */
class KinectDriveCmd: public CommandBase 
{
public:
	KinectDriveCmd(KinectStick* left_stick, KinectStick* right_stick, Button* bridge_btn);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	KinectStick* _leftStick;
	KinectStick* _rightStick;
	Button* _bridgeBtn;
};

#endif
