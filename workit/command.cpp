
#include <stdio.h>
#include <stdlib.h>  
#include "command.h"

command::command() : commandText("")
{
	;
}

int command::run()
{
	int r = system(commandText.c_str());
	commandText = "";
	return r;
}

