#ifndef __JESSEVDK_BASE_OBJECT_H__
#define __JESSEVDK_BASE_OBJECT_H__

#include <cassert>
#include <vector>
#include <jessevdk/base/signals/signal.hh>
#include <iostream>
#include <stdint.h>

namespace jessevdk
{
namespace base
{
	class Object
	{
		struct Data;

		public:
			template <typename Base>
			class Cloned : public Base
			{
				public:
					Cloned();
					Cloned(Base const &base);

					virtual Cloned<Base> *Clone() const;
			};

			class PrivateData
			{
				Data *d_data;

				friend class Object;

				public:
					void Ref();
					void Unref();

					virtual ~PrivateData() {};
					virtual bool Dispose(Object &object) { return true; };
				private:
					void SetData(Data *data);
			};
		private:
			struct Data
			{
				std::vector<PrivateData *> managedData;
				bool disposing;
				size_t refCount;

				signals::Signal<Object> onDestroy;

				Data();
				void Destroy();
			};

			Data *d_data;

		public:
			class Augmentation
			{
				public:
					Augmentation(Object &object, Object::PrivateData *data = 0)
					:
						d_data(data)
					{
						object.AddPrivateData(d_data);
					}
				protected:
					Object::PrivateData *d_data;

					template <typename DataType>
					DataType *Data() const
					{
						return reinterpret_cast<DataType *>(d_data);
					}
			};

			friend class Augmentation;

			/** Default empty constructor.
			  * This creates an empty (no data assigned) object
			  */
			Object();

			/** Copy constructor.
			  * The copy constructor makes sure the ref counting is handled
			  * properly
			  * @param other the object to copy from
			  * @author Jesse van den Kieboom
			  */
			Object(Object const &other);

			/** Destructor.
			  * Makes sure to destroy the data if it is no longer needed
			  * @author Jesse van den Kieboom
			  */
			virtual ~Object();

			virtual Object *Clone() const;

			/** Overloaded assignment operator.
			  * Handle copy of other object data and ref counting
			  * @param other the object to copy from
			  * @author Jesse van den Kieboom
			  */
			Object &operator=(Object const &other);

			/** Get the ref count.
			  * Get the object reference count
			  * @return the reference count
			  * @author Jesse van den Kieboom
			  */
			size_t RefCount() const;

			/** Weaken the reference count.
			  * This function weakens the reference count of the object. This
			  * means that if the reference count is 1 it is decreased to 0
			  * but the data is not destroyed. So you'll end up with a floating
			  * weak reference. This can be used to hold such a weak reference
			  * in cache, but be notified when the last 'real' reference is
			  * destroyed
			  * @author Jesse van den Kieboom
			  */
			void Weaken();

			/** Increase reference count.
			  * Increase the reference count of the object. ONLY USE THIS WITH
			  * EXTREME CAUTION! You generally don't need to manually increase
			  * the reference count
			  * @author Jesse van den Kieboom
			  */
			void Ref();

			/** Decrease reference count.
			  * Decrease the reference count of the object. ONLY USE THIS WITH
			  * EXTREME CAUTION! You generally don't need to manually decrease
			  * the reference count
			  * @author Jesse van den Kieboom
			  */
			void Unref();

			/** Equal operator.
			  * Two ref objects are equal if their data points to the same
			  * data
			  * @param other the ref object to compare
			  * @return true if objects point to the same data
			  */
			bool operator==(Object const &other) const;

			bool operator!=(Object const &other) const;

			/* signals */
			signals::Signal<Object> &OnDestroy();
			bool Dispose();
			bool Disposing() const;
		protected:
			/** Copy data from other object.
			  * This method copies data from another object and increases the
			  * ref count for that data. Inherited classes should implement
			  * this if they allocate memory themselves. They should correctly
			  * take over any pointers from the other object
			  * @param other the object to copy from
			  * @author Jesse van den Kieboom
			  */
			virtual void Copy(Object const &other);

			/** Add private data to the object.
			  */
			void AddPrivateData(PrivateData *data);
		private:
			void Destroy();

			void SetData(Data *data);
	};

	template <typename Base>
	inline Object::Cloned<Base>::Cloned()
	{
	}

	template <typename Base>
	inline Object::Cloned<Base>::Cloned(Base const &base)
	:
		Base(base)
	{
	}

	template <typename Base>
	inline Object::Cloned<Base> *Object::Cloned<Base>::Clone() const
	{
		return new Object::Cloned<Base>(*this);
	}

	inline Object::Object()
	:
		d_data(new Data())
	{
	}

	inline Object::~Object()
	{
		/* Make sure to destroy */
		Destroy();
	}

	inline Object::Object(Object const &other)
	:
		d_data(0)
	{
		Copy(other);
	}

	inline Object *Object::Clone() const
	{
		return new Object(*this);
	}

	inline Object &Object::operator=(Object const &other)
	{
		if (this != &other)
		{
			Destroy();
			Copy(other);
		}

		return *this;
	}

	inline size_t Object::RefCount() const
	{
		return d_data ? d_data->refCount : 0;
	}

	inline void Object::Weaken()
	{
		if (d_data && d_data->refCount == 1)
		{
			d_data->refCount = 0;
		}
	}

	inline void Object::Ref()
	{
		if (d_data)
		{
			++(d_data->refCount);
		}
	}

	inline void Object::Unref()
	{
		Destroy();
	}

	inline bool Object::operator==(Object const &other) const
	{
		return d_data == other.d_data;
	}

	inline bool Object::operator!=(Object const &other) const
	{
		return !(*this == other);
	}

	inline signals::Signal<Object> &Object::OnDestroy()
	{
		return d_data->onDestroy;
	}
}
}

#endif /* __JESSEVDK_BASE_OBJECT_H__ */
