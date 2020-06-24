
#include <iostream>
#include <stdio.h>
#include <stdlib.h>  
#include "command.h"

command::command() : commandText("")
{
	;
}

int command::run()
{
	std::cout << commandText << std::endl;
	int r = system(commandText.c_str());
	commandText = "";
	return r;
}

