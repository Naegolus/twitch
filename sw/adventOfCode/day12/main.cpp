/*
  This file is part of the DSP-Crowd project
  https://www.dsp-crowd.com

  Author(s):
      - Johannes Natter, office@dsp-crowd.com

  Copyright (C) 2017-now Authors and www.dsp-crowd.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <signal.h>
#include <tclap/CmdLine.h>
#include <iostream>

#include "AdventCoding.h"
#include "TclapOutput.h"
#include "Res.h"

#include "env.h"

using namespace std;
using namespace TCLAP;

mutex envMtx;
Value env;

AdventCoding *pApp = NULL;

class AppHelpOutput : public TclapOutput {};

/*
Literature
- http://man7.org/linux/man-pages/man7/signal.7.html
  - for enums: kill -l
  - sys/signal.h
  SIGHUP  1     hangup
  SIGINT  2     interrupt
  SIGQUIT 3     quit
  SIGILL  4     illegal instruction (not reset when caught)
  SIGTRAP 5     trace trap (not reset when caught)
  SIGABRT 6     abort()
  SIGPOLL 7     pollable event ([XSR] generated, not supported)
  SIGFPE  8     floating point exception
  SIGKILL 9     kill (cannot be caught or ignored)
- https://www.usna.edu/Users/cs/aviv/classes/ic221/s16/lec/19/lec.html
- http://www.alexonlinux.com/signal-handling-in-linux
*/
void applicationCloseRequest(int signum)
{
	(void)signum;
	cout << endl;
	pApp->unusedSet();
}

int main(int argc, char *argv[]) try
{
	Value args;

	CmdLine cmd("Command description message", ' ', "Advent Of Code");

	AppHelpOutput aho;
	cmd.setOutput(&aho);

	SwitchArg argDebug("d", "debug", "Enable debugging daemon", false);
	cmd.add(argDebug);
	ValueArg<int> argVerbosity("v", "verbosity", "Verbosity: high => more output", false, 3, "int");
	cmd.add(argVerbosity);
	SwitchArg argLicenses("", "licenses", "Show dependencies", false);
	cmd.add(argLicenses);

	ValueArg<int> argPortSsh("", "port-ssh", "Used port for ssh", false, 22, "int");
	cmd.add(argPortSsh);

	ValueArg<int> argPortTelnet("", "port-telnet", "Used port for telnet", false, 23, "int");
	cmd.add(argPortTelnet);

	cmd.parse(argc, argv);

	args["debug"] = argDebug.getValue();
	args["verbosity"] = argVerbosity.getValue();
	args["portSsh"] = argPortSsh.getValue();
	args["portTelnet"] = argPortTelnet.getValue();

	env["args"] = args;

	/* https://www.gnu.org/software/libc/manual/html_node/Termination-Signals.html */
	signal(SIGINT, applicationCloseRequest);
	signal(SIGTERM, applicationCloseRequest);

	pApp = AdventCoding::create();

	size_t coreBurst;

	while (1)
	{
		for (coreBurst = 0; coreBurst < 16; ++coreBurst)
			pApp->treeTick();

		this_thread::sleep_for(chrono::milliseconds(2));

		if (pApp->progress())
			continue;

		break;
	}

	Success success = pApp->success();
	Processing::destroy(pApp);

	Processing::applicationClose();

	return !(success == Positive);

} catch (ArgException &tclapE)
{
	cerr << "tclap exception: " << tclapE.error() << " for arg " << tclapE.argId() << endl;
	return 1;
} catch (...)
{
	cerr << "Foo" << endl;
	return 1;
}

