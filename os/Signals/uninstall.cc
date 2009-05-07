#include "signals.ih"

void Signals::uninstall() 
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
