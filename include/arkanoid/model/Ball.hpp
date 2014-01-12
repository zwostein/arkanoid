#ifndef _ARKANOID_MODEL_BALL_INCLUDED_
#define _ARKANOID_MODEL_BALL_INCLUDED_

#include <generic/type/Vector2.hpp>
#include <generic/model/AMoveable2D.hpp>
#include <generic/model/ACollideableBox2D.hpp>

namespace arkanoid
{
	namespace model
	{
		class Ball : public ::generic::model::AMoveable2D, public ::generic::model::ACollideableBox2D
		{
		public:
			Ball() {}
			virtual ~Ball() {}
			//Overrides ::generic::model::AMoveable2D:
			virtual void update( const double & delta ) override;
			virtual generic::type::Vector2d getVelocity() const override { return velocity; };
			virtual void setVelocity( const generic::type::Vector2d & velocity ) override { this->velocity = velocity; };
			//Overrides ::generic::model::ACollideableBox2D:
			virtual generic::type::Vector2d getPosition() const override { return position; }
			virtual void setPosition( const generic::type::Vector2d & position ) override { this->position = position; }
			virtual generic::type::Vector2d getSize() const override { return size; }
			virtual void setSize( const generic::type::Vector2d & size ) override { this->size = size; }
			virtual bool collide( ::generic::model::ACollideable2D & other, const generic::type::Vector2d & position, const generic::type::Vector2d & depth ) override;
		private:
			generic::type::Vector2d position = generic::type::Vector2d(0.0,0.0);
			generic::type::Vector2d size = generic::type::Vector2d(0.04,0.04);
			generic::type::Vector2d velocity = generic::type::Vector2d(0.3,0.6);
		};
	}
}

#endif
