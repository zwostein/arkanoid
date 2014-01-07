#ifndef _GENERIC_MODEL_ACOLLIDEABLE2D_INCLUDED_
#define _GENERIC_MODEL_ACOLLIDEABLE2D_INCLUDED_

#include <generic/type/Vector2.hpp>

namespace generic
{
	namespace model
	{
		class ACollideable2D
		{
		public:
			virtual bool isCollisionEnabled() const { return true; }
			virtual bool collide( ACollideable2D & other, const type::Vector2d & position, const type::Vector2d & depth ) = 0;
		};
	}
}

#endif
