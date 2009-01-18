#ifndef __MATH_TYPES_H__
#define __MATH_TYPES_H__

namespace math
{
	template <typename Type, size_t Size>
	struct TypeDefine
	{
		typedef Type type;
		
		enum
		{
			size = Size
		};
	};
};

#endif /* __MATH_TYPES_H__ */
