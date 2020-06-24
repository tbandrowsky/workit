
#pragma once

#include "command.h"

class git
{
	command com;

public:
	const char *fast_development_branch = "release";
	const char *main_branch = "master";
	const char* default_origin = "origin";

	bool update();
	bool checkout(const char* branch);
	bool merge(const char* branch);
	bool find(const char* branch);
	bool diff(const char* branch);
	bool commit(const char *branch, const char* comment);
	bool push();
	bool pull();
};
