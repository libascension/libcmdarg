#include "cmdarg.h"
using namespace cmdarg;

cmdline::cmdline (int argc, char* argv[], parseMode mode)
{
	m_argc = argc;
	m_argv = argv;
	m_error = kNone;

	for (int i = 0; i < argc; i++)
		m_cmdLine.push_back(std::string(argv[i]));

	m_config.insert( std::pair<std::string, int>("parse.mode", mode) );

	initConfig();

	parse();
}

cmdline::~cmdline()
{
}

/** COMMANDLINE PARSING **/
bool cmdline::parse()
{
	if (m_config.find("parse.mode") == kInterpolate)
		return parse_interpolate();
	else
		return parse_strict();
}

/** CONFIGURATION **/
void cmdline::initConfig()
{
	m_config.insert( std::pair<std::string, int>("args.min", 0));
	m_config.insert( std::pair<std::string, int>("args.minBase", 0));
	m_config.insert( std::pair<std::string, int>("error.onNoArg", 0));
}
