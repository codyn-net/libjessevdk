%module(package="jessevdk") base

#pragma SWIG nowarn=SWIGWARN_PARSE_NESTED_CLASS

namespace base
{
	class Augmentation
	{
		public:
			Augmentation(Object &object, Object::PrivateData *data = 0)
			:
				d_data(data)
			{
				object.addPrivateData(d_data);
			}
		protected:
			Object::PrivateData *d_data;
		
			template <typename DataType>
			DataType *data() const
			{
				return reinterpret_cast<DataType *>(d_data);
			}
	};
}

%{
#include <base/Object/object.hh>
%}

%ignore base::Object::PrivateData;
%ignore base::Object::Data;
%ignore base::Object::Augmentation;
%ignore base::Object::onDestroy;
%ignore base::Object::operator=;

%include <base/Object/object.hh>

%{
namespace base
{
	typedef Object::Augmentation Augmentation;
}
%}
