#ifndef _GENERIC_MODEL_ABOX2D_INCLUDED_
#define _GENERIC_MODEL_ABOX2D_INCLUDED_

#include <generic/type/Vector2.hpp>
#include <generic/model/APositionable2D.hpp>

namespace generic
{
	namespace model
	{
		class ABox2D : public APositionable2D
		{
		public:
			virtual type::Vector2d getSize() const = 0;
			virtual void setSize( const type::Vector2d & size ) = 0;
		};
	}
}

#endif
