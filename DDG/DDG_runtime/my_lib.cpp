#include<cstdio>
#include<fstream>
#include<stdint.h>
#include<string>
#include<algorithm>
#include<utility>

static std::ofstream f_path;
/********************************************
 * Initialize all requirements
 ********************************************/
extern "C" void bp_init()
{
	f_path.open("main.stats");
}

/********************************************
 * Checks and prints the basicblock taken
 ********************************************/
extern "C" void bp_checkedge(char *function, char *basicblock)
{
	std::string func(function);
	std::string bb(basicblock);
	f_path << func << "/" << bb << "\n";
}

/********************************************
 * Finish up and report stats
 ********************************************/
extern "C" void bp_fini()
{
  f_path.close();
}
