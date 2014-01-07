#include <arkanoid/model/SimpleLevelGenerator.hpp>
#include <arkanoid/model/Level.hpp>
#include <arkanoid/model/Brick.hpp>
#include <arkanoid/model/Ball.hpp>
#include <arkanoid/model/Wall.hpp>
#include <arkanoid/model/Paddle.hpp>
#include <generic/type/Vector2.hpp>


using namespace arkanoid;
using namespace generic::type;


model::Level * model::SimpleLevelGenerator::generateNewLevel( unsigned int number )
{
	model::Level * level = new model::Level;

	const Vector2i brickNum( number, number );
	const Vector2d brickWallBL( -0.8, -0.2 );
	const Vector2d brickWallTR( 0.8, 0.8 );
	const Vector2d brickWallSize( brickWallTR - brickWallBL );
	const Vector2d brickWallGridStep( brickWallSize.x/brickNum.x, brickWallSize.y/brickNum.y );
	const Vector2d brickSize( 0.9*brickWallSize.x/brickNum.x, 0.9*brickWallSize.y/brickNum.y );

	for( int y=0; y<brickNum.y; y++ )
	{
		for( int x=0; x<brickNum.x; x++ )
		{
			arkanoid::model::Brick * b = new arkanoid::model::Brick;
			b->setPosition( Vector2d( brickWallBL.x + x * brickWallGridStep.x + brickSize.x/2.0, brickWallBL.y + y * brickWallGridStep.y + brickSize.y/2.0 ) );
			b->setSize( brickSize );
			level->takeBrick( b );
		}
	}

	arkanoid::model::Wall * w;
	w = new arkanoid::model::Wall;
	w->setPosition( Vector2d(-0.95, 0.0 ) );
	w->setSize( Vector2d( 0.1, 2.0 ) );
	level->takeWall( w );
	w = new arkanoid::model::Wall;
	w->setPosition( Vector2d( 0.95, 0.0 ) );
	w->setSize( Vector2d( 0.1, 2.0 ) );
	level->takeWall( w );
	w = new arkanoid::model::Wall;
	w->setPosition( Vector2d( 0.0, 0.95 ) );
	w->setSize( Vector2d( 2.0, 0.1 ) );
	level->takeWall( w );

	arkanoid::model::Ball * b = new arkanoid::model::Ball;
	b->setPosition( Vector2d( 0.0, -0.7 ) );
	b->setVelocity( Vector2d( 0.3, 0.6) );
	b->setSize( Vector2d( 0.05, 0.05 ) );
	level->takeBall( b );

	arkanoid::model::Paddle * p = new arkanoid::model::Paddle;
	p->setPosition( Vector2d(0.0,-0.9) );
	p->setSize( Vector2d(0.5,0.1) );
	level->takePaddle( p );
	return level;
}
