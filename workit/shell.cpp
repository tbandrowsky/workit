
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "direct.h"

#include "shell.h"

bool shell::review(const char* branch)
{
	if (!g.checkout(branch))
		return false;

	g.pull();

	g.merge(g.fast_development_branch);
	g.commit(g.fast_development_branch, "merge");

	std::cout << R"([y]es, merge good, [n]o, merge bad)" << std::endl;
	std::cout << ">";

	std::string input;
	std::getline(std::cin, input);

	if (input.size() > 0 && input[0]=='y') {
		std::cout << "pushing merge..." << std::endl;
		g.push();
		g.checkout(g.fast_development_branch);
		g.diff(branch);
		reviewed[branch] = true;
	}

	return true;
}

bool shell::promote(const char* branch)
{
	if (reviewed.count(branch) == 0)
	{
		std::cout << branch << " not reviewed." << std::endl;
		return false;
	}

	if (!g.checkout(g.fast_development_branch))
		return false;

	if (g.merge(branch)) {
		if (g.commit(g.fast_development_branch, "merge")) {
			g.push();
		}
	}

	return true;
}

bool shell::release()
{
	if (!g.checkout(g.fast_development_branch))
		return false;

	if (!g.pull())
		return false;

	if (!g.merge(g.main_branch))
		return false;

	if (!g.commit(g.main_branch, "merge"))
		return false;

	if (!g.push())
		return false;

	if (!g.checkout(g.main_branch))
		return false;

	if (!g.merge(g.fast_development_branch))
		return false;

	if (!g.commit(g.fast_development_branch, "release"))
		return false;

	if (!g.push())
		return false;

	return true;
}

bool shell::directory(const char* dir)
{
	int r= chdir(dir);
	return r == 0;
}

bool shell::find(const char* ticket)
{
	int r = g.find(ticket);
	return r == 0;
}

bool shell::run()
{
	std::cout << R"([r]eview ticket, [p]romote ticket, [f]ind ticket, [a]bout, [q]uit, [d]irectory)" << std::endl;
	std::cout << ">";

	std::string input, param;
	char command;
	std::getline(std::cin, input);

	if (input.length() > 0) {
		command = input[0];
		if (input.length() > 1) {
			param = input.substr(2);
		}
		switch (command) {
		case 'R':
		case 'r':
			review(param.c_str());
			break;
		case 'P':
		case 'p':
			promote(param.c_str());
			break;
		case 'F':
		case 'f':
			find(param.c_str());
			break;
		case 'd':
			if (directory(param.c_str()))
				std::cout << "directory changed" << std::endl;
			break;
		case 'a':
			std::cout << "workit code review and time entry integration tool." << std::endl;
			return true;
		case 'q':
			return false;
		}
	}
	return true;
}
