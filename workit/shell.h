

#pragma once

#include <string>
#include <map>

#include "git.h"

class shell 
{
	git g;
	std::map<std::string, bool> reviewed;

	bool review(const char* branch);
	bool promote(const char* branch);
	bool release();
	bool directory(const char* dir);
	bool find(const char* branch);

public:

	bool run();
};
