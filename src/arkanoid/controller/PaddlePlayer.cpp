#include <arkanoid/controller/PaddlePlayer.hpp>
#include <SDL2/SDL.h>

using namespace arkanoid;


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
