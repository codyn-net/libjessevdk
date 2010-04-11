#include "signals.hh"

#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace jessevdk::os;

jessevdk::base::signals::Signal<> Signals::OnInterrupt;

volatile sig_atomic_t Signals::s_stopping = false;
volatile sig_atomic_t Signals::s_fatalError = false;

static void
termination_handler(int signum)
{
	if (signum != SIGPIPE)
	{
		Signals::SetStopping(true);
	}

	switch (signum)
	{
		// fallthrough
		case SIGILL:
		case SIGSEGV:
		case SIGFPE:
		case SIGBUS:
			Signals::SetFatalError(true);
			cerr << endl << "** Fatal signal: " << signum << endl;
			exit(EXIT_FAILURE);
			break;
		case SIGINT:
			Signals::OnInterrupt();

			break;
	}

}

void
Signals::Install()
{
	struct sigaction term_action;

	term_action.sa_handler = termination_handler;
	sigemptyset(&term_action.sa_mask);
	term_action.sa_flags = 0;

	sigaction(SIGINT, &term_action, NULL);
	sigaction(SIGPIPE, &term_action, NULL);
	sigaction(SIGHUP, &term_action, NULL);
	sigaction(SIGILL, &term_action, NULL);
	sigaction(SIGFPE, &term_action, NULL);
	sigaction(SIGSEGV, &term_action, NULL);
	sigaction(SIGBUS, &term_action, NULL);
}

void
Signals::Uninstall()
{
	struct sigaction term_action;

	/* Reset to default */
	term_action.sa_handler = SIG_DFL;
	sigemptyset(&term_action.sa_mask);
	term_action.sa_flags = 0;

	sigaction(SIGINT, &term_action, NULL);
	sigaction(SIGPIPE, &term_action, NULL);
	sigaction(SIGHUP, &term_action, NULL);
	sigaction(SIGILL, &term_action, NULL);
	sigaction(SIGFPE, &term_action, NULL);
	sigaction(SIGSEGV, &term_action, NULL);
	sigaction(SIGBUS, &term_action, NULL);
}
