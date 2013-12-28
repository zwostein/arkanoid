#ifndef _ARKANOID_H_
#define _ARKANOID_H_

#include "generic.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <vector>
#include <unordered_set>


namespace arkanoid
{
	namespace model
	{
		using namespace ::generic::model;

		class Brick : public ACollideableBox2D
		{
		public:
			Brick() {}
			virtual ~Brick() {}
			bool isDestroyed() const { return destroyed; }
			//Overrides ACollideableBox2D:
			virtual Vector2d getPosition() const override { return position; }
			virtual void setPosition( const Vector2d & position ) override { this->position = position; }
			virtual Vector2d getSize() const override { return size; }
			virtual void setSize( const Vector2d & size ) override { this->size = size; }
			virtual bool collide( ACollideable2D & other, const Vector2d & position, const Vector2d & depth ) override;
			virtual bool isCollisionEnabled() const override { return !destroyed; }
		private:
			Vector2d position = Vector2d(0.0,0.0);
			Vector2d size = Vector2d(0.1,0.1);
			bool destroyed = false;
		};

		class Wall : public ACollideableBox2D
		{
		public:
			Wall() {}
			virtual ~Wall() {}
			//Overrides ACollideableBox2D:
			virtual Vector2d getPosition() const override { return position; }
			virtual void setPosition( const Vector2d & position ) override { this->position = position; }
			virtual Vector2d getSize() const override { return size; }
			virtual void setSize( const Vector2d & size ) override { this->size = size; }
			virtual bool collide( ACollideable2D & other, const Vector2d & position, const Vector2d & depth ) override;
		private:
			Vector2d position = Vector2d(0.0,0.0);;
			Vector2d size = Vector2d(0.2,0.2);;
		};

		class Ball : public AMoveable2D, public ACollideableBox2D
		{
		public:
			Ball() {}
			virtual ~Ball() {}
			//Overrides AMoveable2D:
			virtual void update( const double & delta ) override;
			virtual Vector2d getVelocity() const override { return velocity; };
			virtual void setVelocity( const Vector2d & velocity ) override { this->velocity = velocity; };
			//Overrides ACollideableBox2D:
			virtual Vector2d getPosition() const override { return position; }
			virtual void setPosition( const Vector2d & position ) override { this->position = position; }
			virtual Vector2d getSize() const override { return size; }
			virtual void setSize( const Vector2d & size ) override { this->size = size; }
			virtual bool collide( ACollideable2D & other, const Vector2d & position, const Vector2d & depth ) override;
		private:
			Vector2d position = Vector2d(0.0,0.0);
			Vector2d size = Vector2d(0.1,0.1);
			Vector2d velocity = Vector2d(0.3,0.6);
		};

		class Paddle : public AMoveable2D, public ACollideableBox2D
		{
		public:
			Paddle() {}
			virtual ~Paddle() {}
			//Overrides AMoveable2D:
			virtual void update( const double & delta ) override;
			virtual Vector2d getVelocity() const override;
			virtual void setVelocity( const Vector2d & ) override { /* nope we choose our own */ };
			//Overrides ACollideableBox2D:
			virtual Vector2d getPosition() const override { return position; }
			virtual void setPosition( const Vector2d & position ) override { this->position = position; }
			virtual Vector2d getSize() const override { return size; }
			virtual void setSize( const Vector2d & size ) override { this->size = size; }
			virtual bool collide( ACollideable2D & other, const Vector2d & position, const Vector2d & depth ) override;

			void moveLeft() { movingLeft = true; movingRight = false; }
			void stop() { movingLeft = false; movingRight = false; }
			void moveRight() { movingLeft = false; movingRight = true; }
			void setSpeed( double speed ) { this->speed = speed; }
		private:
			double speed = 1.0;
			Vector2d position = Vector2d( 0.0, 0.0 );
			Vector2d size = Vector2d( 0.25, 0.1 );
			bool movingLeft = false;
			bool movingRight = false;
		};

		class ALevel : public AUpdateable
		{
		public:
			virtual const std::unordered_set< Wall * > & getWalls() const = 0;
			virtual const std::unordered_set< Brick * > & getBricks() const = 0;
			virtual const std::unordered_set< Ball * > & getBalls() const = 0;
			virtual const std::unordered_set< Paddle * > & getPaddles() const = 0;
			virtual bool isGameOver() const = 0;
		};

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
			OrderedModelUpdater modelUpdater;
			CollisionDetectorBox2D collisionDetector;
			bool gameOver = false;
			std::unordered_set< Wall * > walls;
			std::unordered_set< Brick * > bricks;
			std::unordered_set< Ball * > balls;
			std::unordered_set< Paddle * > paddles;
		};

		class SimpleLevelGenerator
		{
		public:
			static Level * generateNewLevel( unsigned int level );
		};
	}

	namespace view
	{
		using namespace ::generic::view;

		class View : public AView
		{
		public:
			View();
			virtual ~View();
			//Overrides AView:
			virtual bool addDrawable( const ADrawable * drawable ) override;
			virtual bool removeDrawable( const ADrawable * drawable ) override;
			virtual void draw() const override;
		private:
			std::unordered_set< const ADrawable * > drawables;
			SDL_Window * window = nullptr;
			SDL_GLContext glContext = nullptr;
		};

		class BallRenderer : public AUnorderedRenderer<::arkanoid::model::Ball>
		{
		public:
			BallRenderer() {}
			virtual ~BallRenderer() {}
			//Overrides AUnorderedRenderer:
			virtual void draw() const override;
		};

		class PaddleRenderer : public AUnorderedRenderer<::arkanoid::model::Paddle>
		{
		public:
			PaddleRenderer() {}
			virtual ~PaddleRenderer() {}
			//Overrides AUnorderedRenderer:
			virtual void draw() const override;
		};

		class WallRenderer : public AUnorderedRenderer<::arkanoid::model::Wall>
		{
		public:
			WallRenderer() {}
			virtual ~WallRenderer() {}
			//Overrides AUnorderedRenderer:
			virtual void draw() const override;
		};

		class BrickRenderer : public AUnorderedRenderer<::arkanoid::model::Brick>
		{
		public:
			BrickRenderer() {}
			virtual ~BrickRenderer() {}
			//Overrides AUnorderedRenderer:
			virtual void draw() const override;
		};
	}

	namespace controller
	{
		using namespace ::generic::controller;

		class PaddlePlayer
		{
		public:
			PaddlePlayer( ::arkanoid::model::Paddle * model, const SDL_Scancode & leftKey, const SDL_Scancode & rightKey )
				: model(model), leftKey(leftKey), rightKey(rightKey) {};
			void processInput();
		private:
			::arkanoid::model::Paddle * model;
			SDL_Scancode leftKey;
			SDL_Scancode rightKey;
		};

		class PaddleAI
		{
		public:
			PaddleAI( ::arkanoid::model::Paddle * model, ::arkanoid::model::Level * level );
		};
	}
}


#endif
