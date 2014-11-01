#include "DriveInSquareCmd.h"
#include "DriveCmd.h"

DriveInSquareCmd::DriveInSquareCmd()
: CommandGroup("DriveInSquareCmd")
, _isDone(false)
{
	Requires(CommandBase::driveTrainSubsystem);

	AddSequential(new DriveCmd(4.0, 0.5, 0.5));
	AddSequential(new DriveCmd(2.0, -0.5, 0.5));
	AddSequential(new DriveCmd(4.0, 0.5, 0.5));
	AddSequential(new DriveCmd(2.0, -0.5, 0.5));
	AddSequential(new DriveCmd(4.0, 0.5, 0.5));
	AddSequential(new DriveCmd(2.0, -0.5, 0.5));				
	AddSequential(new DriveCmd(4.0, 0.5, 0.5));
	AddSequential(new DriveCmd(2.0, -0.5, 0.5));
}

//void DriveInSquareCmd::Initialize()
//{
//	_isDone = false;
//}
//
//
//void DriveInSquareCmd::Execute()
//{
//	_isDone = true;
//}
//
//
//bool DriveInSquareCmd::IsFinished()
//{
//	return _isDone;
//}
//
//
//void DriveInSquareCmd::End()
//{
//	
//}
//
//
//void DriveInSquareCmd::Interrupted()
//{
//	
//}

