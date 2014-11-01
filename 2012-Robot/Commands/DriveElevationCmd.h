#ifndef DRIVE_ELEVATION_COMMAND_H
#define DRIVE_ELEVATION_COMMAND_H

#include "../CommandBase.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class DriveElevationCmd: public CommandBase {
public:
	DriveElevationCmd(Joystick* joystick, Joystick::AxisType axis);
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
};

#endif
