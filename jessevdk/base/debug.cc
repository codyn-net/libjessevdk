#include "debug.hh"
#include <iostream>

using namespace std;
using namespace jessevdk::base;

Debug *Debug::s_instance;

Debug::Debug(int domain)
:
	d_stream(cout),
	d_nostream(new StreamBuf()),
	d_domain(domain)
{
}

Debug::Debug(ostream &stream, int domain)
:
	d_stream(stream),
	d_nostream(new StreamBuf()),
	d_domain(domain)
{
}

void
Debug::Disable(int domain)
{
	if (!s_instance)
	{
		s_instance = new Debug();
	}

	s_instance->Domain() &= ~domain;
}

void
Debug::Enable(int domain)
{
	if (!s_instance)
	{
		s_instance = new Debug();
	}

	s_instance->Domain() |= domain;
}

void
Debug::Enable(ostream &stream, int domain)
{
	if (s_instance)
	{
		delete s_instance;
	}

	s_instance = new Debug(stream, domain);
}

bool
Debug::Enabled(int domain)
{
	return s_instance ? (s_instance->Domain() & domain) : false;
}
