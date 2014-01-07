#ifndef _ARKANOID_MODEL_PADDLE_INCLUDED_
#define _ARKANOID_MODEL_PADDLE_INCLUDED_

#include <generic/type/Vector2.hpp>
#include <generic/model/AMoveable2D.hpp>
#include <generic/model/ACollideableBox2D.hpp>

namespace arkanoid
{
	namespace model
	{
		class Paddle : public ::generic::model::AMoveable2D, public ::generic::model::ACollideableBox2D
		{
		public:
			Paddle() {}
			virtual ~Paddle() {}
			//Overrides ::generic::model::AMoveable2D:
			virtual void update( const double & delta ) override;
			virtual ::generic::type::Vector2d getVelocity() const override;
			virtual void setVelocity( const ::generic::type::Vector2d & ) override { /* nope we choose our own */ };
			//Overrides ::generic::model::ACollideableBox2D:
			virtual ::generic::type::Vector2d getPosition() const override { return position; }
			virtual void setPosition( const ::generic::type::Vector2d & position ) override { this->position = position; }
			virtual ::generic::type::Vector2d getSize() const override { return size; }
			virtual void setSize( const ::generic::type::Vector2d & size ) override { this->size = size; }
			virtual bool collide( ACollideable2D & other, const ::generic::type::Vector2d & position, const ::generic::type::Vector2d & depth ) override;

			void moveLeft() { movingLeft = true; movingRight = false; }
			void stop() { movingLeft = false; movingRight = false; }
			void moveRight() { movingLeft = false; movingRight = true; }
			void setSpeed( double speed ) { this->speed = speed; }
		private:
			double speed = 1.0;
			::generic::type::Vector2d position = ::generic::type::Vector2d( 0.0, 0.0 );
			::generic::type::Vector2d size = ::generic::type::Vector2d( 0.25, 0.1 );
			bool movingLeft = false;
			bool movingRight = false;
		};
	}
}

#endif
