#ifndef _ARKANOID_MODEL_BRICK_INCLUDED_
#define _ARKANOID_MODEL_BRICK_INCLUDED_

#include <generic/type/Vector2.hpp>
#include <generic/model/ACollideableBox2D.hpp>

namespace arkanoid
{
	namespace model
	{
		class Brick : public ::generic::model::ACollideableBox2D
		{
		public:
			Brick() {}
			virtual ~Brick() {}
			bool isDestroyed() const { return destroyed; }
			//Overrides ::generic::model::ACollideableBox2D:
			virtual ::generic::type::Vector2d getPosition() const override { return position; }
			virtual void setPosition( const ::generic::type::Vector2d & position ) override { this->position = position; }
			virtual ::generic::type::Vector2d getSize() const override { return size; }
			virtual void setSize( const ::generic::type::Vector2d & size ) override { this->size = size; }
			virtual bool collide( ACollideable2D & other, const ::generic::type::Vector2d & position, const ::generic::type::Vector2d & depth ) override;
			virtual bool isCollisionEnabled() const override { return !destroyed; }
		private:
			::generic::type::Vector2d position = ::generic::type::Vector2d(0.0,0.0);
			::generic::type::Vector2d size = ::generic::type::Vector2d(0.1,0.1);
			bool destroyed = false;
		};
	}
}

#endif
