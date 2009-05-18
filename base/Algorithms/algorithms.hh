#ifndef __BASE_ALGORITHMS_H__
#define __BASE_ALGORITHMS_H__

namespace base
{
namespace algorithms
{
	template <typename InputIterator1, typename InputIterator2, typename OutputContainer>
	OutputContainer &append(InputIterator1 begin, InputIterator2 end, OutputContainer &container)
	{
		while (begin != end)
			container.push_back(*begin++);
		
		return container;
	}
}
}

#endif /* __BASE_ALGORITHMS_H__ */

