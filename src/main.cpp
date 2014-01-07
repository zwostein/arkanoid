#include <arkanoid/controller/PaddlePlayer.hpp>
#include <arkanoid/view/WallRenderer.hpp>
#include <arkanoid/view/BallRenderer.hpp>
#include <arkanoid/view/BrickRenderer.hpp>
#include <arkanoid/view/PaddleRenderer.hpp>
#include <arkanoid/view/View.hpp>
#include <arkanoid/model/Level.hpp>
#include <arkanoid/model/SimpleLevelGenerator.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdexcept>
#include <iostream>


int main( int , char **  )
{
	SDL_Init( SDL_INIT_EVENTS | SDL_INIT_TIMER );

	// setup model
	arkanoid::model::Level * level = arkanoid::model::SimpleLevelGenerator::generateNewLevel( 10 );

	// setup view
	arkanoid::view::View * view = new arkanoid::view::View;

	arkanoid::view::BallRenderer * ballRenderer= new arkanoid::view::BallRenderer;
	for( auto & m : level->getBalls() )
		ballRenderer->addModel( m );
	view->addDrawable( ballRenderer );

	arkanoid::view::PaddleRenderer * paddleRenderer = new arkanoid::view::PaddleRenderer;
	for( auto & m : level->getPaddles() )
		paddleRenderer->addModel( m );
	view->addDrawable( paddleRenderer );

	arkanoid::view::WallRenderer * wallRenderer = new arkanoid::view::WallRenderer;
	for( auto & m : level->getWalls() )
		wallRenderer->addModel( m );
	view->addDrawable( wallRenderer );

	arkanoid::view::BrickRenderer * brickRenderer = new arkanoid::view::BrickRenderer;
	for( auto & m : level->getBricks() )
		brickRenderer->addModel( m );
	view->addDrawable( brickRenderer );

	std::unordered_set< arkanoid::controller::PaddlePlayer * > paddleControllers;
	// setup controllers
	for( auto & m : level->getPaddles() )
		paddleControllers.insert( new arkanoid::controller::PaddlePlayer( m, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT ) );

	Uint64 lastTime = SDL_GetPerformanceCounter();
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
		for( auto & c : paddleControllers )
			c->processInput();

		// update model
		Uint64 currentTime = SDL_GetPerformanceCounter();
		double delta = (double)(currentTime - lastTime) / (double)SDL_GetPerformanceFrequency();
		lastTime = currentTime;
		level->update( delta );

		// draw the view
		view->draw();
	}

	delete brickRenderer;
	delete wallRenderer;
	delete paddleRenderer;
	delete ballRenderer;
	delete view;

	for( auto & c : paddleControllers )
		delete c;

	delete level;

	SDL_Quit();
	return 0;
}
