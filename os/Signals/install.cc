#include "signals.ih"

static void termination_handler(int signum)
{
	if (signum != SIGPIPE)
		Signals::setStopping(true);

	switch (signum)
	{
		// fallthrough
		case SIGILL: 
		case SIGSEGV:
		case SIGFPE:
		case SIGBUS:
			Signals::setFatalError(true);
			cerr << endl << "** Fatal signal: " << signum << endl;
			exit(EXIT_FAILURE);
			break;
		case SIGINT:
			Signals::onInterrupt();

			break;
	}

}

void Signals::install() 
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
