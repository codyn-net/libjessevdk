#include "filedescriptor.ih"

void FileDescriptor::attach()
{
	if (d_data->fd == -1)
		return;

	d_data->source = Glib::IOSource::create(d_data->fd, Glib::IO_IN | Glib::IO_PRI | Glib::IO_ERR | Glib::IO_HUP);
	d_data->source->attach();
	
	d_data->source->connect(sigc::mem_fun(*d_data, &FileDescriptor::Data::onIO));
}
