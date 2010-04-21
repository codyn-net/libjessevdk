#include "terminator.hh"
#include "processes.hh"

#include <sys/types.h>
#include <sys/wait.h>

using namespace jessevdk::os;
using namespace std;

Terminator::Terminator()
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->d_stage = Data::Stage::None;
}

Terminator::Data::~Data()
{
	if (d_timeout)
	{
		d_timeout.disconnect();
	}
}

void
Terminator::Data::Kill(int sig)
{
	vector<GPid> kills;

	if (d_recursive)
	{
		kills = Processes::Children(d_pid, true);
	}

	kills.push_back(d_pid);

	for (vector<GPid>::iterator iter = kills.begin(); iter != kills.end(); ++iter)
	{
		cerr << "Killing: " << *iter << ", " << sig << endl;
		::kill(*iter, sig);
	}
}

bool
Terminator::Data::OnTimeout()
{
	if (d_stage == Stage::Terminate)
	{
		// Kill it harder
		d_stage = Stage::Kill;

		Kill(SIGKILL);
		return true;
	}
	else
	{
		// Totally failed
		d_timeout.disconnect();
		d_stage = Stage::None;

		int status = -1;

		OnTerminated(status);
		return false;
	}
}

Terminator::operator bool() const
{
	return d_data->d_stage != Data::Stage::None;
}

void
Terminator::Terminated(int status)
{
	if (d_data->d_stage == Data::Stage::None)
	{
		return;
	}
	
	if (d_data->d_timeout)
	{
		d_data->d_timeout.disconnect();
	}

	d_data->d_stage = Data::Stage::None;
	d_data->OnTerminated(status);
}

int
Terminator::Terminate(GPid pid, bool recursive, bool block)
{
	if (pid == 0)
	{
		return 0;
	}

	if (d_data->d_stage != Data::Stage::None)
	{
		return 0;
	}

	d_data->d_pid = pid;
	d_data->d_recursive = recursive;
	d_data->d_stage = Data::Stage::Terminate;

	if (!block)
	{
		d_data->d_timeout = Glib::signal_timeout().connect_seconds(sigc::mem_fun(*d_data, &Terminator::Data::OnTimeout), 3);
	}

	d_data->Kill(SIGTERM);

	if (block)
	{
		int status;
		waitpid(pid, &status, 0);

		d_data->d_stage = Data::Stage::None;
		d_data->OnTerminated(status);

		return status;
	}

	return -1;
}

jessevdk::base::signals::Signal<int> &
Terminator::OnTerminated()
{
	return d_data->OnTerminated;
}
