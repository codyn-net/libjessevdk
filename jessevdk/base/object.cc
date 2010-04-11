#include "object.hh"

using namespace jessevdk::base;
using namespace std;

void
Object::AddPrivateData(PrivateData *data)
{
	d_data->managedData.push_back(data);

	data->SetData(d_data);
}

void
Object::Copy(Object const &other)
{
	if (d_data == other.d_data)
	{
		return;
	}

	d_data = other.d_data;

	/* Increase ref count */
	if (d_data)
	{
		++(d_data->refCount);
	}
}

Object::Data::Data()
:
	disposing(false),
	refCount(1)
{
}

void
Object::Data::Destroy()
{
	for (vector<PrivateData *>::reverse_iterator iter = managedData.rbegin(); iter != managedData.rend(); ++iter)
	{
		delete *iter;
	}
}

void
Object::Destroy()
{
	if (!d_data || !d_data->refCount)
	{
		return;
	}

	if (!--(d_data->refCount))
	{
		/* Notify destruction */
		d_data->onDestroy(*this);
		d_data->Destroy();

		delete d_data;
		d_data = 0;
	}
	else if (!d_data->disposing)
	{
		Dispose();
		d_data = 0;
	}
}

bool
Object::Dispose()
{
	if (!d_data)
	{
		return false;
	}

	d_data->disposing = true;
	Ref();

	for (vector<PrivateData *>::reverse_iterator iter = d_data->managedData.rbegin(); d_data && iter != d_data->managedData.rend(); ++iter)
	{
		PrivateData *data = *iter;

		if (!data)
		{
			continue;
		}

		if (!data->Dispose(*this))
		{
			Unref();

			if (d_data)
			{
				d_data->disposing = false;
			}

			return false;
		}
	}

	Unref();

	if (d_data)
	{
		d_data->disposing = false;
	}

	return true;
}

bool
Object::Disposing() const
{
	return d_data ? d_data->disposing : false;
}

void
Object::PrivateData::Ref()
{
	++d_data->refCount;
}

void
Object::PrivateData::SetData(Data *data)
{
	d_data = data;
}

void
Object::PrivateData::Unref()
{
	if (d_data->refCount > 0)
	{
		if (--d_data->refCount == 0)
		{
			Data *data = d_data;

			d_data->Destroy();
			delete data;
		}
	}
}
