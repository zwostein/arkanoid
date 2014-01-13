#include <arkanoid/model/Ball.hpp>
#include <generic/type/Vector2.hpp>


using namespace arkanoid;
using namespace generic::type;


void model::Ball::update( const double & delta )
{
	this->position += this->velocity * delta;
}


bool model::Ball::collide( generic::model::ACollideable2D & other, const Vector2d & , const Vector2d & depth )
{
	this->position += depth;
	this->velocity.reflect( depth.normalized() );

	generic::model::AMoveable2D * moveable = dynamic_cast<generic::model::AMoveable2D*>(&other);
	if( moveable )
	{
		this->velocity += moveable->getVelocity() * 0.333;
	}

	return true;
}
