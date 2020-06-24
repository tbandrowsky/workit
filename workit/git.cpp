
#include "git.h"

bool git::update()
{
	int r = com.run("git fetch");
	return r == 0;
}

bool git::checkout(const char* branch)
{
	int r = com.run("git checkout ", branch);
	return r == 0;
}

bool git::merge(const char* branch)
{
	int r = com.run("git merge ", branch);
	return r == 0;
}

bool git::find(const char* text)
{
	int r = com.run("git branch -a |findstr \"", text, "\"");
	return r == 0;
}

bool git::diff(const char* branch)
{
	int r = com.run("git diff ", fast_development_branch, "...", branch);
	return r == 0;
}

bool git::commit(const char* branch, const char* comment)
{
	int r = com.run("git commit -am \"", branch, "-", comment, "\"" );
	return r == 0;
}

bool git::push()
{
	int r = com.run("git push");
	return r == 0;
}

bool git::pull()
{
	int r = com.run("git pull");
	return r == 0;
}
