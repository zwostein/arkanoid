#ifndef _GENERIC_MODEL_APOSITIONABLE2D_INCLUDED_
#define _GENERIC_MODEL_APOSITIONABLE2D_INCLUDED_

#include <generic/type/Vector2.hpp>

namespace generic
{
	namespace model
	{
		class APositionable2D
		{
		public:
			virtual type::Vector2d getPosition() const = 0;
			virtual void setPosition( const type::Vector2d & position ) = 0;
		};
	}
}

#endif
