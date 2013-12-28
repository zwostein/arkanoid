#include "arkanoid.h"

#include <set>
#include <stdexcept>
#include <typeinfo>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>


using namespace arkanoid;


view::View::View()
{
	if( SDL_InitSubSystem( SDL_INIT_VIDEO ) < 0 )
		throw std::runtime_error( std::string("SDL failed to initialize video subsystem: ") + std::string(SDL_GetError()) );

	if( !SDL_WasInit( SDL_INIT_EVENTS ) )
	{
		if( SDL_InitSubSystem( SDL_INIT_EVENTS ) < 0 )
			throw std::runtime_error( std::string("SDL failed to initialize event subsystem: ") + std::string(SDL_GetError()) );
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	window = SDL_CreateWindow( "Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if( !window )
		throw std::runtime_error( std::string("SDL failed to create window: ") + std::string(SDL_GetError()) );

	glContext = SDL_GL_CreateContext( window );
	if( !glContext )
		throw std::runtime_error( std::string("SDL failed to create OpenGL context: ") + std::string(SDL_GetError()) );

	SDL_GL_SetSwapInterval( 1 );

	glClearColor( 0.0, 0.0, 0.0, 1.0 );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -1, 1, -1, 1, -1, 1 );
	glEnable( GL_DEPTH_TEST );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}


view::View::~View()
{
	SDL_GL_DeleteContext( glContext );
	SDL_DestroyWindow( window );
	SDL_QuitSubSystem( SDL_INIT_VIDEO );
}


bool view::View::addDrawable( const generic::view::ADrawable * drawable )
{
	return drawables.insert( drawable ).second;
}


bool view::View::removeDrawable( const generic::view::ADrawable * drawable )
{
	return drawables.erase( drawable );
}


void view::View::draw() const
{
	SDL_Event e;
	SDL_PumpEvents();
	while( SDL_PeepEvents( &e, 1, SDL_GETEVENT, SDL_WINDOWEVENT, SDL_WINDOWEVENT ) )
	{
		if( e.type != SDL_WINDOWEVENT )
			throw std::runtime_error("SDL returned non-window-event when asking for window-event\n");
		switch( e.window.event )
		{
		case SDL_WINDOWEVENT_RESIZED:
			glViewport( 0, 0, e.window.data1, e.window.data2 );
			break;
		}
	}

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	for( const auto & i : drawables )
		i->draw();

	SDL_GL_SwapWindow( window );
}


bool model::Brick::collide( generic::model::ACollideable2D & , const Vector2d & , const Vector2d &  )
{
	destroyed = true;
	return false;
}


bool model::Wall::collide( generic::model::ACollideable2D & , const Vector2d & , const Vector2d &  )
{
	return false;
}


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


void model::Ball::update( const double & delta )
{
	this->position += this->velocity * delta;
}


bool model::Ball::collide( generic::model::ACollideable2D & , const Vector2d & , const Vector2d & depth )
{
	this->position += depth;
	this->velocity.reflect( depth.normalized() );
/*
	generic::model::AMoveable2D * moveable = dynamic_cast<generic::model::AMoveable2D*>(&other);
	if( moveable )
	{
		this->velocity += moveable->getVelocity();
	}
*/
	return true;
}


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


static void drawGlCircle( double radius, int segments )
{
	glBegin( GL_POLYGON );
	for( double i=0.0; i<360.0; i+=360.0/segments )
	{
		double degInRad = i*(3.14159/180.0);
		glVertex2d( cos(degInRad)*radius, sin(degInRad)*radius );
	}
	glEnd();
}


void view::BallRenderer::draw() const
{
	for( const auto & m : getModels() )
	{
		glPushMatrix();
			glTranslated( m->getPosition().x, m->getPosition().y, 0.1 );
			glScaled( m->getSize().x/2.0, m->getSize().y/2.0, 1.0f );
			glColor3f( 1, 1, 1 );
			drawGlCircle( 1.1, 6 );
		glPopMatrix();
	}
}


void view::PaddleRenderer::draw() const
{
	for( const auto & m : getModels() )
	{
		glPushMatrix();
			glTranslated( m->getPosition().x, m->getPosition().y, 0.1 );
			glColor3f( 1, 1, 1 );
			glBegin( GL_QUADS );
				glVertex2f( -m->getSize().x/2.0, -m->getSize().y/2.0 );
				glVertex2f( m->getSize().x/2.0, -m->getSize().y/2.0 );
				glVertex2f( m->getSize().x/2.0, m->getSize().y/2.0 );
				glVertex2f( -m->getSize().x/2.0, m->getSize().y/2.0 );
			glEnd();
		glPopMatrix();
	}
}


void view::WallRenderer::draw() const
{
	for( const auto & m : getModels() )
	{
		glPushMatrix();
			glTranslated( m->getPosition().x, m->getPosition().y, 0.1 );
			glColor3f( 0.5, 0.5, 0.5 );
			glBegin( GL_QUADS );
				glVertex2f( -m->getSize().x/2.0, -m->getSize().y/2.0 );
				glVertex2f( m->getSize().x/2.0, -m->getSize().y/2.0 );
				glVertex2f( m->getSize().x/2.0, m->getSize().y/2.0 );
				glVertex2f( -m->getSize().x/2.0, m->getSize().y/2.0 );
			glEnd();
		glPopMatrix();
	}
}


void view::BrickRenderer::draw() const
{
	for( const auto & m : getModels() )
	{
		if( m->isDestroyed() )
			continue;
		glPushMatrix();
			glTranslated( m->getPosition().x, m->getPosition().y, 0.1 );
			glColor3f( 0.75, 0.75, 0.75 );
			glBegin( GL_QUADS );
				glVertex2f( -m->getSize().x/2.0, -m->getSize().y/2.0 );
				glVertex2f( m->getSize().x/2.0, -m->getSize().y/2.0 );
				glVertex2f( m->getSize().x/2.0, m->getSize().y/2.0 );
				glVertex2f( -m->getSize().x/2.0, m->getSize().y/2.0 );
			glEnd();
		glPopMatrix();
	}
}


void controller::PaddlePlayer::processInput()
{
	int len = 0;
	const Uint8 * state = SDL_GetKeyboardState( &len );
	if( leftKey >= len || rightKey >= len )
		throw std::runtime_error("Scancode out of range\n");

	if( state[leftKey] && !state[rightKey] )
		model->moveLeft();
	else if( !state[leftKey] && state[rightKey] )
		model->moveRight();
	else
		model->stop();
}
