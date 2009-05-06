#include "filedescriptor.ih"

void FileDescriptor::attach()
{
	if (d_data->fd == -1)
		return;

	if (d_data->sourceConnection)
		d_data->sourceConnection.disconnect();

	d_data->sourceConnection = Glib::signal_io().connect(sigc::mem_fun(*d_data, &FileDescriptor::Data::onIOSource), d_data->fd, Glib::IO_IN | Glib::IO_PRI | Glib::IO_ERR | Glib::IO_HUP);
}
