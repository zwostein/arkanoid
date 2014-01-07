#ifndef _ARKANOID_CONTROLLER_PADDLEPLAYER_INCLUDED_
#define _ARKANOID_CONTROLLER_PADDLEPLAYER_INCLUDED_

#include <arkanoid/model/Paddle.hpp>
#include <SDL2/SDL.h>
#include <unordered_set>

namespace arkanoid
{
	namespace controller
	{
		class PaddlePlayer
		{
		public:
			PaddlePlayer( model::Paddle * model, const SDL_Scancode & leftKey, const SDL_Scancode & rightKey )
				: model(model), leftKey(leftKey), rightKey(rightKey) {};
			void processInput();
		private:
			model::Paddle * model;
			SDL_Scancode leftKey;
			SDL_Scancode rightKey;
		};
	}
}

#endif
