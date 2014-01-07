#include <arkanoid/model/Paddle.hpp>
#include <arkanoid/model/Wall.hpp>
#include <generic/type/Vector2.hpp>
#include <typeinfo>


using namespace arkanoid;
using namespace generic::type;


void model::Paddle::update( const double & delta )
{
	if( movingLeft )
		position.x -= speed * delta;
	else if( movingRight )
		position.x += speed * delta;
}


bool model::Paddle::collide( ACollideable2D & other, const Vector2d & , const Vector2d & depth )
{
	if( typeid(other) == typeid(model::Wall) )
	{
		this->position.x += depth.x;
		return true;
	}
	return false;
}


Vector2d model::Paddle::getVelocity() const
{
	if( movingLeft )
		return Vector2d( -speed, 0.0 );
	if( movingRight )
		return Vector2d( speed, 0.0 );
	return Vector2d( 0.0, 0.0 );
}
