#ifndef __JESSEVDK_BASE_BINARY_STREAM__
#define __JESSEVDK_BASE_BINARY_STREAM__

#include <fstream>
#include <jessevdk/base/object.hh>
#include <jessevdk/base/flags.hh>

namespace jessevdk
{
namespace base
{
	class BinaryStream : public Object
	{
		struct Data : public jessevdk::base::Object::PrivateData
		{
			std::fstream *stream;

			~Data();
		};

		Data *d_data;

		public:
			struct Direction
			{
				enum Values
				{
					In = 1 << 0,
					Out = 1 << 1
				};
			};
			
			typedef std::streampos MarkPoint;

			/* Constructor/destructor */
			BinaryStream();
			BinaryStream(std::string const &filename, base::Flags<Direction> const &direction = Direction::In);

			/* Public functions */
			operator bool() const;
			std::fstream &Stream();

			template <typename Type>
			bool Read(Type &result);

			template <typename Type>
			bool Read(Type &result, size_t size);

			template <typename Type>
			bool Read(Type &result, MarkPoint mark, size_t size);

			template <typename Type>
			bool Read(Type *result, size_t size);

			template <typename Type>
			bool Read(Type *result, MarkPoint mark, size_t size);

			template <typename Type>
			bool Write(Type const &value);

			template<typename Type>
			bool Write(Type const *value, size_t size);

			bool Skip(size_t size);

			MarkPoint Mark();
			void GotoMark(MarkPoint mark);

			size_t SinceMark(MarkPoint mark);
			void Reset();
		private:
			/* Private functions */
	};

	inline BinaryStream::BinaryStream()
	:
		d_data(0)
	{
	}

	inline std::fstream &BinaryStream::Stream()
	{
		return *d_data->stream;
	}

	inline BinaryStream::operator bool() const
	{
		return *d_data->stream;
	}

	template <typename Type>
	inline bool BinaryStream::Read(Type &result)
	{
		return read(result, sizeof(Type));
	}

	template <typename Type>
	inline bool BinaryStream::Read(Type &result, size_t size)
	{
		return read(&result, size);
	}

	template <typename Type>
	inline bool BinaryStream::Read(Type &result, BinaryStream::MarkPoint mark, size_t size)
	{
		return read(&result, mark, size);
	}

	template <typename Type>
	bool BinaryStream::Read(Type *result, size_t size)
	{
		return Stream().read(reinterpret_cast<char *>(result), size);
	}

	template <typename Type>
	bool BinaryStream::Read(Type *result, BinaryStream::MarkPoint mark, size_t size)
	{
		BinaryStream::MarkPoint current = Mark();

		Reset();
		GotoMark(mark);

		bool ret = Read(result, size);
		GotoMark(current);

		return ret;
	}

	template <typename Type>
	bool BinaryStream::Write(Type const &value)
	{
		return Write(&value, sizeof(Type));
	}

	template <typename Type>
	bool BinaryStream::Write(Type const *value, size_t size)
	{
		return Stream().write(reinterpret_cast<char const *>(value), size);
	}

	inline bool BinaryStream::Skip(size_t size)
	{
		return Stream().seekg(size, std::ios::cur);
	}

	inline BinaryStream::MarkPoint BinaryStream::Mark()
	{
		return Stream().tellg();
	}

	inline void BinaryStream::GotoMark(BinaryStream::MarkPoint mark)
	{
		Reset();
		Stream().seekg(mark, std::ios::beg);
	}

	inline size_t BinaryStream::SinceMark(BinaryStream::MarkPoint mark)
	{
		return Stream().tellg() - mark;
	}
}
}

#endif /* __JESSEVDK_BASE_BINARY_STREAM__ */
