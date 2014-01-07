#ifndef _GENERIC_MODEL_AMOVEABLE2D_INCLUDED_
#define _GENERIC_MODEL_AMOVEABLE2D_INCLUDED_

#include <generic/type/Vector2.hpp>
#include <generic/model/APositionable2D.hpp>
#include <generic/model/AUpdateable.hpp>

namespace generic
{
	namespace model
	{
		class AMoveable2D : public APositionable2D, public AUpdateable
		{
		public:
			virtual type::Vector2d getVelocity() const = 0;
			virtual void setVelocity( const type::Vector2d & velocity ) = 0;
		};
	}
}

#endif
