#include "signals.ih"

base::signals::Signal<> Signals::onInterrupt;

volatile sig_atomic_t Signals::s_stopping = false;
volatile sig_atomic_t Signals::s_fatalError = false;
