#ifndef _ARKANOID_MODEL_LEVEL_INCLUDED_
#define _ARKANOID_MODEL_LEVEL_INCLUDED_

#include <arkanoid/model/ALevel.hpp>
#include <generic/type/Vector2.hpp>
#include <generic/model/OrderedModelUpdater.hpp>
#include <generic/model/CollisionDetectorBox2D.hpp>
#include <unordered_set>

namespace arkanoid
{
	namespace model
	{
		class Wall;
		class Brick;
		class Ball;
		class Paddle;

		class Level : public ALevel
		{
		public:
			Level();
			virtual ~Level();
			bool takeWall( Wall * wall );
			bool takeBrick( Brick * brick );
			bool takeBall( Ball * ball );
			bool takePaddle( Paddle * paddle );
			//Overrides ALevel:
			virtual const std::unordered_set< Wall * > & getWalls() const override { return walls; }
			virtual const std::unordered_set< Brick * > & getBricks() const override { return bricks; }
			virtual const std::unordered_set< Ball * > & getBalls() const override { return balls; }
			virtual const std::unordered_set< Paddle * > & getPaddles() const override { return paddles; }
			virtual void update( const double & delta ) override;
			virtual bool isGameOver() const override { return gameOver; }
		private:
			::generic::model::OrderedModelUpdater modelUpdater;
			::generic::model::CollisionDetectorBox2D collisionDetector;
			bool gameOver = false;
			std::unordered_set< Wall * > walls;
			std::unordered_set< Brick * > bricks;
			std::unordered_set< Ball * > balls;
			std::unordered_set< Paddle * > paddles;
		};
	}
}

#endif
