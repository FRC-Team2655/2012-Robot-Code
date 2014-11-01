#ifndef DRIVE_AZIMUTH_COMMAND_H
#define DRIVE_AZIMUTH_COMMAND_H

#include "../CommandBase.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class DriveAzimuthCmd: public CommandBase {
public:
	DriveAzimuthCmd(Joystick* joystick, Joystick::AxisType axis, Button* fine_tune_btn);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool _done;
	float _angle;
	DriverStationLCD* _dsLCD;
	Joystick* _joystick;
	Joystick::AxisType _axis;
	float _maxDelta;
	bool _isZeroed;
	Button* _fineTuneBtn;
};

#endif
