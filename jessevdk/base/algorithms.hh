#ifndef __JESSEVDK_BASE_ALGORITHMS_H__
#define __JESSEVDK_BASE_ALGORITHMS_H__

namespace jessevdk
{
namespace base
{
namespace algorithms
{
	template <typename InputIterator1, typename InputIterator2, typename OutputContainer>
	OutputContainer &Append(InputIterator1 begin, InputIterator2 end, OutputContainer &container)
	{
		while (begin != end)
		{
			container.push_back(*begin++);
		}

		return container;
	}
}
}
}

#endif /* __JESSEVDK_BASE_ALGORITHMS_H__ */

