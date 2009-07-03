#ifndef __BASE_BINARY_STREAM__
#define __BASE_BINARY_STREAM__

#include <fstream>
#include <base/Object/object.hh>

namespace base
{
	class BinaryStream : public Object
	{
		struct Data : public base::Object::PrivateData
		{
			std::ifstream *stream;
			
			~Data();
		};
		
		Data *d_data;
		
		public:
			typedef std::streampos Mark;

			/* Constructor/destructor */
			BinaryStream();
			BinaryStream(std::string const &filename);
			
			/* Public functions */
			operator bool() const;
			std::ifstream &stream();
			
			template <typename Type>		
			bool read(Type &result);
			
			template <typename Type>
			bool read(Type &result, size_t size);
			
			template <typename Type>
			bool read(Type &result, Mark mark, size_t size);
			
			template <typename Type>
			bool read(Type *result, size_t size);
			
			template <typename Type>
			bool read(Type *result, Mark mark, size_t size);
			
			bool skip(size_t size);
			
			Mark mark();
			void gotoMark(Mark mark);
			size_t sinceMark(Mark mark);
			void reset();
		private:
			/* Private functions */
	};
	
	inline BinaryStream::BinaryStream()
	:
		d_data(0)
	{
	}
	
	inline std::ifstream &BinaryStream::stream()
	{
		return *d_data->stream;
	}
	
	inline BinaryStream::operator bool() const
	{
		return *d_data->stream;
	}

	template <typename Type>
	inline bool BinaryStream::read(Type &result)
	{
		return read(result, sizeof(Type));
	}
	
	template <typename Type>
	inline bool BinaryStream::read(Type &result, size_t size)
	{
		return read(&result, size);
	}
	
	template <typename Type>
	inline bool BinaryStream::read(Type &result, BinaryStream::Mark mark, size_t size)
	{
		return read(&result, mark, size);
	}
	
	template <typename Type>
	bool BinaryStream::read(Type *result, size_t size)
	{
		return stream().read(reinterpret_cast<char *>(result), size);
	}
	
	template <typename Type>
	bool BinaryStream::read(Type *result, BinaryStream::Mark mark, size_t size)
	{
		BinaryStream::Mark current = this->mark();
		
		reset();
		gotoMark(mark);
		bool ret = read(result, size);
		gotoMark(current);
		
		return ret;
	}
	
	inline bool BinaryStream::skip(size_t size)
	{
		return stream().seekg(size, std::ios::cur);
	}
	
	inline BinaryStream::Mark BinaryStream::mark()
	{
		return stream().tellg();
	}
	
	inline void BinaryStream::gotoMark(BinaryStream::Mark mark)
	{
		reset();
		stream().seekg(mark, std::ios::beg);
	}
	
	inline size_t BinaryStream::sinceMark(BinaryStream::Mark mark)
	{
		return stream().tellg() - mark;
	}
}

#endif /* __BASE_BINARY_STREAM__ */
