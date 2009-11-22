/*
 *	Cloneable template class protects a derived object from slicing when
 *	used with stl containers
 *
 *	Author: Jesse van den Kieboom
 */
#ifndef __JESSEVDK_BASE_CLONEABLE_H__
#define __JESSEVDK_BASE_CLONEABLE_H__

#include <exception>

namespace jessevdk
{
namespace base
{
	/** Cloneable class.
	  * This class provides the cloneable pattern which prevents slicing
	  * for derived classes. The class is implemented as a template class
	  * which provides convenient operators (conversions) to allow easy use of
	  * the encapsulated class
	  * @author Jesse van den Kieboom
	  */
	template <typename Base>
	class Cloneable
	{
		Base *d_base;

		public:
			class BadAssigned : public std::exception
			{
			};

			/** Default constructor.
			  * Creates a new empty cloneable
			  * @author Jesse van den Kieboom
			  */
			Cloneable();

			/** Custom cloneable copy constructor.
			  * This copy constructor is used to copy a cloneable of
			  * class Other derived from Base
			  * @param other the cloneable to copy from
			  * @author Jesse van den Kieboom
			  */
			template <typename Other>
			Cloneable(Cloneable<Other> const &other);

			/** Specialised custom cloneable copy constructor.
			  * This copy constructor is used to copy a cloneable of class Base.
			  * This specialisation is needed to overload the default copy
			  * constructor
			  * @param other the cloneable to copy from
			  * @author Jesse van den Kieboom
			  */
			Cloneable(Cloneable<Base> const &other);

			/** Custom family class copy constructor.
			  * This copy constructor is used to copy a class Other which is
			  * either the Base class or a class derived from Base
			  * @param other the object to copy from
			  * @author Jesse van den Kieboom
			  */
			template <typename Other>
			Cloneable(Other const &other);

			template <typename Other>
			Cloneable(Other *other);

			/** Deconstructor.
			  * @author Jesse van den Kieboom
			  */
			virtual ~Cloneable();

			/** Assignment operator.
			  * The assignment operator is overloaded to ensure correct
			  * handling of destroying the encapsulated object and to copy
			  * from an existing cloneable object
			  * @param other the cloneable object to copy from
			  * @return This object
			  * @author Jesse van den Kieboom
			  */
			template <typename Other>
			Cloneable<Base> &operator=(Cloneable<Other> const &other);

			/** Specialised assignment operator.
			  * The assignment operator is overloaded to ensure correct
			  * handling of destroying the encapsulated object and to copy
			  * from an existing cloneable object. This specialisation is
			  * needed to overload the default assignment operator
			  * @param other the cloneable object to copy from
			  * @return This object
			  * @author Jesse van den Kieboom
			  */
			Cloneable<Base> &operator=(Cloneable<Base> const &other);

			/** Assignment operator for family classes.
			  * This assignment operator is used to assign family classes
			  * of Base (either Base classes or classes derived from Base) to
			  * this cloneable.
			  * @param other the object to copy from
			  * @return This
			  * @author Jesse van den Kieboom
			  */
			template <typename Other>
			Cloneable<Base> &operator=(Other const &other);

			template <typename Other>
			Cloneable<Base> &operator=(Other *other);

			/** Dereference operator.
			  * Dereferencing a cloneable yields a reference to the
			  * encapsulated object
			  * @return A reference to the encapsulated object
			  * @author Jesse van den Kieboom
			  */
			Base &operator*();

			/** Dereference operator (const).
			  * Dereferencing a cloneable yields a reference to the
			  * encapsulated object (const)
			  * @return A reference to the encapsulated object (const)
			  * @author Jesse van den Kieboom
			  */
			Base const &operator*() const;

			/** Pointer operator.
			  * The pointer operator yields a pointer to the encapsulated
			  * object
			  * @return A pointer to the encapsulated object
			  * @author Jesse van den Kieboom
			  */
			Base *operator->();

			/** Pointer operator (const).
			  * The pointer operator yields a pointer to the encapsulated
			  * object (const)
			  * @return A pointer to the encapsulated object (const)
			  * @author Jesse van den Kieboom
			  */
			Base const *operator->() const;

			/** Conversion operator.
			  * This operator enables a cloneable to be converted to the
			  * encapsulated object
			  * @return A reference to the encapsulated object
			  * @author Jesse van den Kieboom
			  */
			operator Base&();

			/** Conversion operator (const).
			  * This operator enables a cloneable to be converted to the
			  * encapsulated object (const)
			  * @return A reference to the encapsulated object
			  * @author Jesse van den Kieboom
			  */
			operator Base const &() const;

			/** Object assigned.
			  * Returns whether or not an object was assigned to the cloneable
			  * @return True if the cloneable is assigned, false otherwise
			  * @author Jesse van den Kieboom
			  */
			bool IsAssigned() const;

			operator bool() const;

			/** Greater than operator.
			  * Proxy for wrapped object operator
			  * @param other the object to compare with
			  * @author Jesse van den Kieboom
			  */
			template <typename Other>
			bool operator>(Other const &other) const;

			/** Greater than operator.
			  * Proxy for wrapped object operator (cloneable specialization)
			  * @param other the object to compare with
			  * @author Jesse van den Kieboom
			  */
			template <typename Other>
			bool operator>(Cloneable<Other> const &other) const;

			void Clear();
		private:
			/* Private functions */
			void Destroy();

			template <typename Other>
			Cloneable<Base> &Assign(Other const &other);

			template <typename Other>
			Cloneable<Base> &Assign(Other *other);
	};

	// Constructors
	template <typename Base>
	inline Cloneable<Base>::Cloneable()
	:
		d_base(0)
	{
	}

	template <typename Base>
	template <typename Other>
	inline Cloneable<Base>::Cloneable(Other const &other)
	{
		// Clone other
		d_base = other.Clone();
	}

	template <typename Base>
	template <typename Other>
	inline Cloneable<Base>::Cloneable(Other *other)
	{
		// Take over other
		d_base = other;
	}

	template <typename Base>
	inline Cloneable<Base>::Cloneable(Cloneable<Base> const &other)
	:
		d_base(0)
	{
		// Clone other from cloneable
		if (other.IsAssigned())
		{
			d_base = other->Clone();
		}
	}

	template <typename Base>
	template <typename Other>
	inline Cloneable<Base>::Cloneable(Cloneable<Other> const &other)
	:
		d_base(0)
	{
		// Clone other from cloneable
		if (other.IsAssigned())
		{
			d_base = other->Clone();
		}
	}

	// Destructor
	template <typename Base>
	inline Cloneable<Base>::~Cloneable()
	{
		Destroy();
	}

	template <typename Base>
	template <typename Other>
	Cloneable<Base>& Cloneable<Base>::Assign(Other const &other)
	{
		// Assign other to this cloneable with self-destroy check
		if (d_base != &other)
		{
			Destroy();
			d_base = other.Clone();
		}

		return *this;
	}

	template <typename Base>
	template <typename Other>
	Cloneable<Base>& Cloneable<Base>::Assign(Other *other)
	{
		// Assign other to this cloneable with self-destroy check
		if (d_base != other)
		{
			Destroy();
			d_base = other;
		}

		return *this;
	}

	template <typename Base>
	Cloneable<Base>& Cloneable<Base>::operator=(Cloneable<Base> const &other)
	{
		if (other)
		{
			return Assign(*other);
		}
		else
		{
			return Assign(static_cast<Base *>(0));
		}
	}

	template <typename Base>
	template <typename Other>
	Cloneable<Base>& Cloneable<Base>::operator=(Cloneable<Other> const &other)
	{
		if (other)
		{
			return Assign(*other);
		}
		else
		{
			return Assign(static_cast<Other *>(0));
		}
	}

	template <typename Base>
	template <typename Other>
	Cloneable<Base>& Cloneable<Base>::operator=(Other const &other)
	{
		return Assign(other);
	}

	template <typename Base>
	template <typename Other>
	Cloneable<Base>& Cloneable<Base>::operator=(Other *other)
	{
		return Assign(other);
	}

	template <typename Base>
	inline void Cloneable<Base>::Destroy()
	{
		if (d_base)
			delete d_base;

		d_base = 0;
	}

	/* Operators */
	template <typename Base>
	inline Base &Cloneable<Base>::operator*()
	{
		if (!d_base)
			throw BadAssigned();

		return *d_base;
	}

	template <typename Base>
	inline Base *Cloneable<Base>::operator->()
	{
		return d_base;
	}

	template <typename Base>
	inline Base const &Cloneable<Base>::operator*() const
	{
		if (!d_base)
			throw BadAssigned();

		return *d_base;
	}

	template <typename Base>
	inline Base const *Cloneable<Base>::operator->() const
	{
		return d_base;
	}

	template <typename Base>
	inline Cloneable<Base>::operator Base&()
	{
		if (!d_base)
			throw BadAssigned();

		return *d_base;
	}

	template <typename Base>
	inline Cloneable<Base>::operator Base const&() const
	{
		return *d_base;
	}

	template <typename Base>
	inline bool Cloneable<Base>::IsAssigned() const
	{
		return d_base != 0;
	}

	template <typename Base>
	inline Cloneable<Base>::operator bool() const
	{
		return IsAssigned();
	}

	template <typename Base>
	template <typename Other>
	inline bool Cloneable<Base>::operator>(Other const &other) const
	{
		if (!d_base)
			throw BadAssigned();

		return *d_base > other;
	}

	template <typename Base>
	template <typename Other>
	inline bool Cloneable<Base>::operator>(Cloneable<Other> const &other) const
	{
		if (!d_base)
			throw BadAssigned();

		return *d_base > *other;
	}

	template <typename Base>
	inline void Cloneable<Base>::Clear()
	{
		Destroy();
	}
}
}

#endif /* __STLEXT_CLONEABLE_H__ */
