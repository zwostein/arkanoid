#include "arkanoid.h"

#include <set>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>


using namespace arkanoid;


bool model::Model::addUpdateable( generic::model::AUpdateable * updateable )
{
	return updateables.insert( updateable ).second;
}


bool model::Model::removeUpdateable( generic::model::AUpdateable * updateable )
{
	return updateables.erase( updateable );
}


void model::Model::update( const double & delta )
{
	for( const auto & i : updateables )
		i->update( delta );
}


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

	window = SDL_CreateWindow( "Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if( !window )
		throw std::runtime_error( std::string("SDL failed to create window: ") + std::string(SDL_GetError()) );

	glContext = SDL_GL_CreateContext( window );
	if( !glContext )
		throw std::runtime_error( std::string("SDL failed to create OpenGL context: ") + std::string(SDL_GetError()) );

	SDL_GL_SetSwapInterval( 1 );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}


view::View::~View()
{
	SDL_GL_DeleteContext( glContext );
	SDL_DestroyWindow( window );
	SDL_Quit();
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

	glClear( GL_COLOR_BUFFER_BIT );

	for( const auto & i : drawables )
		i->draw();

	SDL_GL_SwapWindow( window );
}


void model::Paddle::update( const double & delta )
{
	if( movingLeft )
		positionX -= speed * delta;
	else if( movingRight )
		positionX += speed * delta;
}


void view::Paddle::draw() const
{
	glPushMatrix();
		glTranslated( model->getPositionX(), model->getPositionY(), 0.0 );
		glColor3f( 1, 1, 1 );
		glBegin( GL_QUADS );
			glVertex2f( -model->getWidth()/2.0, -model->getHeight()/2.0 );
			glVertex2f( model->getWidth()/2.0, -model->getHeight()/2.0 );
			glVertex2f( model->getWidth()/2.0, model->getHeight()/2.0 );
			glVertex2f( -model->getWidth()/2.0, model->getHeight()/2.0 );
		glEnd();
	glPopMatrix();
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
