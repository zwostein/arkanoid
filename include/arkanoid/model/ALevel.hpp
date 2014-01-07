#ifndef _ARKANOID_MODEL_ALEVEL_INCLUDED_
#define _ARKANOID_MODEL_ALEVEL_INCLUDED_

#include <generic/model/AUpdateable.hpp>
#include <unordered_set>

namespace arkanoid
{
	namespace model
	{
		class Wall;
		class Brick;
		class Ball;
		class Paddle;

		class ALevel : public ::generic::model::AUpdateable
		{
		public:
			virtual const std::unordered_set< Wall * > & getWalls() const = 0;
			virtual const std::unordered_set< Brick * > & getBricks() const = 0;
			virtual const std::unordered_set< Ball * > & getBalls() const = 0;
			virtual const std::unordered_set< Paddle * > & getPaddles() const = 0;
			virtual bool isGameOver() const = 0;
		};
	}
}

#endif
