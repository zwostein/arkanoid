#include "arkanoid.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdexcept>
#include <iostream>


int main( int argc, char ** argv )
{
	SDL_Init( SDL_INIT_EVENTS | SDL_INIT_TIMER );

	// setup model
	arkanoid::model::Model * model = new arkanoid::model::Model;
	arkanoid::model::Paddle * paddleModel = new arkanoid::model::Paddle;
	paddleModel->setPositionX( 0.0 );
	paddleModel->setPositionY(-0.9 );
	paddleModel->setWidth( 0.5 );
	paddleModel->setHeight( 0.1 );
	model->addUpdateable( paddleModel );

	// setup view
	arkanoid::view::View * view = new arkanoid::view::View;
	arkanoid::view::Paddle * paddleView = new arkanoid::view::Paddle( paddleModel );
	view->addDrawable( paddleView );

	// setup controllers
	arkanoid::controller::PaddlePlayer * paddleController = new arkanoid::controller::PaddlePlayer( paddleModel, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT );

	bool run = true;
	while( run )
	{
		// check for quit event
		SDL_Event e;
		SDL_PumpEvents();
		while( SDL_PeepEvents( &e, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT ) )
		{
			if( e.type ==  SDL_QUIT )
				run = false;
			else
				throw std::runtime_error("SDL returned non-quit-event when asking for quit-event.\n");
		}

		// let controllers process their input
		paddleController->processInput();

		// update model
		static Uint64 lastTime = 0;
		static Uint64 currentTime = 0;
		currentTime = SDL_GetPerformanceCounter();
		double delta = (double)(currentTime - lastTime) / (double)SDL_GetPerformanceFrequency();
		lastTime = currentTime;
		model->update( delta );

		// draw the view
		view->draw();
	}

	delete paddleModel;

	delete paddleView;
	delete view;

	SDL_Quit();
	return 0;
}
