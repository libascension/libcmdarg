/*
 * cmdarg.h
 *
 * Header for libcmdarg.
 *
 * Copyright (C) 2015 The LibAscension Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SRC_CMDARG_H_
#define SRC_CMDARG_H_
#include <string>
#include <vector>
#include <map>

#define LIB_VERSION_MAJOR 0
#define LIB_VERSION_MINOR 1
#define LIB_VERSION_PATCH 0

#ifdef __unix
	#define OPTION_SHORT_PREFIX '-'
	#define OPTION_LONG_PREFIX "--"
#elif _WIN32
	#define OPTION_SHORT_PREFIX '/'
	#define OPTION_LONG_PREFIX '/'
#endif

namespace cmdarg {

	struct optionInfo {
		char shortName;
		std::string longName;
		bool argRequired;
	};
	struct option {
		optionInfo opt;
		std::string arg;
		unsigned pos;
	};
	struct baseArgument {
		std::string arg;
		unsigned pos;
	};

	enum parseMode {
		kInterpolate = 0,
		kStrict = 1
	};
	enum errMode {
		kNone,
		kUnknown,
		kUnknownFatal,
		kTooFewArguments,
		kOptMissingArgument,
		kFatalMissingArgument
	};

	unsigned getLibVersion() { return LIB_VERSION_MAJOR; }
	bool checkLibVersion(unsigned version) { return (version >= LIB_VERSION_MAJOR); }
	bool checkLibVersion(unsigned major, unsigned minor);

	class cmdline {
	public:
		cmdline(int argc, char* argv[], parseMode mode=kInterpolate);
		~cmdline();

		// GET CMDLINE INFO ****************
		std::vector<std::string> getRawCmdline() { return m_cmdLine; }
		std::vector<option> getOpts();
		std::vector<std::string> getBaseArgs();

		bool optionExists(char opt);
		bool optionExists(std::string opt);

		errMode getError() { return m_error; }

		// RUN CMDLINE OPERATIONS **********
		bool parse();

		// MODIFY CMDLINE OBJECT ***********
		bool importOptInfo(std::vector<optionInfo> optInfo);

		// CMDLINE CONFIGURATION ***********
		void config (std::string key, std::string value);
		void config (std::string key, int value);
		void config (std::string key, bool value);
	private:
		// FUNCTIONS ***********************
		bool parse_interpolate();
		bool parse_strict();

		void initConfig();

		// VARIABLES ***********************
		int m_argc;
		char** m_argv;

		errMode m_error;

		std::vector<std::string> m_cmdLine;
		std::vector<option> m_options;
		std::vector<baseArgument> m_baseArgs;

		std::vector<optionInfo> m_optInfo;

		std::map<std::string, int> m_config;
	};
}



#endif /* SRC_CMDARG_H_ */
