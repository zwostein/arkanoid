#ifndef _GENERIC_MODEL_ACOLLISIONDETECTORBOX2D_INCLUDED_
#define _GENERIC_MODEL_ACOLLISIONDETECTORBOX2D_INCLUDED_

#include <generic/model/AUpdateable.hpp>

namespace generic
{
	namespace model
	{
		class ACollideableBox2D;

		class ACollisionDetectorBox2D : public AUpdateable
		{
		public:
			virtual bool addCollideable( ACollideableBox2D * collideable ) = 0;
			virtual bool removeCollideable( ACollideableBox2D * collideable ) = 0;
		};
	}
}

#endif
