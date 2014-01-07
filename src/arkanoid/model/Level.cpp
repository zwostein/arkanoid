#include <arkanoid/model/Level.hpp>
#include <arkanoid/model/Brick.hpp>
#include <arkanoid/model/Ball.hpp>
#include <arkanoid/model/Wall.hpp>
#include <arkanoid/model/Paddle.hpp>
#include <generic/type/Vector2.hpp>


using namespace arkanoid;
using namespace generic::type;


model::Level::Level()
{
	modelUpdater.addUpdateable( &collisionDetector, 1 );
}

model::Level::~Level()
{
	for( auto & m : balls )
		delete m;
	for( auto & m : walls )
		delete m;
	for( auto & m : bricks )
		delete m;
	for( auto & m : paddles )
		delete m;
}

bool model::Level::takeWall( Wall * wall )
{
	if( !walls.insert( wall ).second )
		return false;
	return collisionDetector.addCollideable( wall );
}

bool model::Level::takeBrick( Brick * brick )
{
	if( !bricks.insert( brick ).second )
		return false;
	return collisionDetector.addCollideable( brick );
}

bool model::Level::takeBall( Ball * ball )
{
	if( !balls.insert( ball ).second )
		return false;
	if( !modelUpdater.addUpdateable( ball ) )
		return false;
	return collisionDetector.addCollideable( ball );
}

bool model::Level::takePaddle( Paddle * paddle )
{
	if( !paddles.insert( paddle ).second )
		return false;
	if( !modelUpdater.addUpdateable( paddle ) )
		return false;
	return collisionDetector.addCollideable( paddle );
}

void model::Level::update( const double & delta )
{
	for( auto & b : balls )
	{
		if( b->getPosition().y < -1.0 )
		{
			b->setPosition( Vector2d( 0.0, -0.7 ) );
			b->setVelocity( Vector2d( 0.3, 0.6) );
		}
	}
	modelUpdater.update( delta );
}
