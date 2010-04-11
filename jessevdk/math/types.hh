#ifndef __JESSEVDK_MATH_TYPES_H__
#define __JESSEVDK_MATH_TYPES_H__

namespace jessevdk
{
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
}

#endif /* __JESSEVDK_MATH_TYPES_H__ */
