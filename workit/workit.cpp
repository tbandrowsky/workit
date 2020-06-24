// workit.cpp : Defines the entry point for the application.
//

#include "workit.h"
#include "shell.h"

using namespace std;

int main()
{
	shell s;
	while (s.run());
	return 0;
}
