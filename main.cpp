#include "generic.h"
#include "arkanoid.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdexcept>
#include <iostream>


int main( int argc, char ** argv )
{
	SDL_Init( SDL_INIT_EVENTS | SDL_INIT_TIMER );

	// setup model
	generic::model::OrderedModelUpdater * modelUpdater = new generic::model::OrderedModelUpdater;

	generic::model::CollisionDetectorBox2D * collisionDetector = new generic::model::CollisionDetectorBox2D;
	modelUpdater->addUpdateable( collisionDetector, 1 );

	std::vector<arkanoid::model::Brick *> brickModels;
	static const Vector2i brickNum( 5, 5 );
	static const Vector2d brickWallBL( -0.8, -0.3 );
	static const Vector2d brickWallTR( 0.8, 0.8 );
	static const Vector2d brickWallSize( brickWallTR - brickWallBL );
	static const Vector2d brickWallGridStep( brickWallSize.x/brickNum.x, brickWallSize.y/brickNum.y );
	static const Vector2d brickSize( 0.9*brickWallSize.x/brickNum.x, 0.9*brickWallSize.y/brickNum.y );

	for( int y=0; y<brickNum.y; y++ )
	{
		for( int x=0; x<brickNum.x; x++ )
		{
			arkanoid::model::Brick * b = new arkanoid::model::Brick;
			b->setPosition( Vector2d( brickWallBL.x + x * brickWallGridStep.x + brickSize.x/2.0, brickWallBL.y + y * brickWallGridStep.y + brickSize.y/2.0 ) );
			b->setSize( brickSize );
			collisionDetector->addCollideable( b );
			brickModels.push_back( b );
		}
	}

	arkanoid::model::Wall * wallModels[3];
	wallModels[0] = new arkanoid::model::Wall;
	wallModels[0]->setPosition( Vector2d(-0.95, 0.0 ) );
	wallModels[0]->setSize( Vector2d( 0.1, 2.0 ) );
	collisionDetector->addCollideable( wallModels[0] );
	wallModels[1] = new arkanoid::model::Wall;
	wallModels[1]->setPosition( Vector2d( 0.95, 0.0 ) );
	wallModels[1]->setSize( Vector2d( 0.1, 2.0 ) );
	collisionDetector->addCollideable( wallModels[1] );
	wallModels[2] = new arkanoid::model::Wall;
	wallModels[2]->setPosition( Vector2d( 0.0, 0.95 ) );
	wallModels[2]->setSize( Vector2d( 2.0, 0.1 ) );
	collisionDetector->addCollideable( wallModels[2] );

	arkanoid::model::Ball * ballModel = new arkanoid::model::Ball;
	ballModel->setPosition( Vector2d( 0.0, -0.7 ) );
	ballModel->setVelocity( Vector2d( 0.3, 0.6) );
	ballModel->setSize( Vector2d( 0.05, 0.05 ) );
	collisionDetector->addCollideable( ballModel );
	modelUpdater->addUpdateable( ballModel );

	arkanoid::model::Paddle * paddleModel = new arkanoid::model::Paddle;
	paddleModel->setPosition( Vector2d(0.0,-0.9) );
	paddleModel->setSize( Vector2d(0.5,0.1) );
	collisionDetector->addCollideable( paddleModel );
	modelUpdater->addUpdateable( paddleModel );

	// setup view
	arkanoid::view::View * view = new arkanoid::view::View;

	arkanoid::view::BallRenderer * ballRenderer= new arkanoid::view::BallRenderer;
	ballRenderer->addModel( ballModel );
	view->addDrawable( ballRenderer );

	arkanoid::view::PaddleRenderer * paddleRenderer = new arkanoid::view::PaddleRenderer;
	paddleRenderer->addModel( paddleModel );
	view->addDrawable( paddleRenderer );

	arkanoid::view::WallRenderer * wallRenderer = new arkanoid::view::WallRenderer;
	wallRenderer->addModel( wallModels[0] );
	wallRenderer->addModel( wallModels[1] );
	wallRenderer->addModel( wallModels[2] );
	view->addDrawable( wallRenderer );

	arkanoid::view::BrickRenderer * brickRenderer = new arkanoid::view::BrickRenderer;
	for( const auto & b : brickModels )
		brickRenderer->addModel( b );
	view->addDrawable( brickRenderer );

	// setup controllers
	arkanoid::controller::PaddlePlayer * paddleController = new arkanoid::controller::PaddlePlayer( paddleModel, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT );

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
		paddleController->processInput();

		// update model
		Uint64 currentTime = SDL_GetPerformanceCounter();
		double delta = (double)(currentTime - lastTime) / (double)SDL_GetPerformanceFrequency();
		lastTime = currentTime;
		modelUpdater->update( delta );

		// draw the view
		view->draw();
	}

	delete wallModels[0];
	delete wallModels[1];
	delete wallModels[2];
	delete paddleModel;
	delete ballModel;
	for( const auto & b : brickModels )
		delete b;
	delete collisionDetector;
	delete modelUpdater;

	delete brickRenderer;
	delete wallRenderer;
	delete paddleRenderer;
	delete ballRenderer;
	delete view;

	delete paddleController;

	SDL_Quit();
	return 0;
}
