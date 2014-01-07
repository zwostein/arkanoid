#ifndef _GENERIC_MODEL_COLLISIONDETECTORBOX2D_INCLUDED_
#define _GENERIC_MODEL_COLLISIONDETECTORBOX2D_INCLUDED_

#include <generic/model/ACollisionDetectorBox2D.hpp>
#include <set>

namespace generic
{
	namespace model
	{
		class ACollideableBox2D;

		class CollisionDetectorBox2D : public ACollisionDetectorBox2D
		{
		public:
			//Overrides ACollisionDetectorBox2D:
			virtual bool addCollideable( ACollideableBox2D * collideable ) override;
			virtual bool removeCollideable( ACollideableBox2D * collideable ) override;
			virtual void update( const double & delta ) override;
		private:
			std::set< ACollideableBox2D * > collideables;
		};
	}
}

#endif
