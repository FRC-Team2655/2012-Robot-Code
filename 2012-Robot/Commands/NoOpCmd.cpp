#include "NoOpCmd.h"



NoOpCmd::NoOpCmd()
: CommandBase("NoOpCmd")
{
}

void NoOpCmd::Initialize()
{
}

void NoOpCmd::Execute()
{
}

bool NoOpCmd::IsFinished()
{
	return false;
}

void NoOpCmd::End()
{
}

void NoOpCmd::Interrupted()
{
}

