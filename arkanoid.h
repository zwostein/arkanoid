#ifndef _ARKANOID_H_
#define _ARKANOID_H_

#include "generic.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <vector>
#include <set>


namespace arkanoid
{
	namespace model
	{
		using namespace ::generic::model;

		class Model : public AModel
		{
		public:
			//Overrides AModel:
			virtual bool addUpdateable( AUpdateable * updateable ) override;
			virtual bool removeUpdateable( AUpdateable * updateable ) override;
			virtual void update( const double & delta ) override;
		private:
			std::set< AUpdateable * > updateables;
		};

		class Brick : public ABox2D, public ACollideable2D
		{
		public:
			//Overrides ABox2D:
			virtual double getPositionX() const override { return positionX; }
			virtual double getPositionY() const override { return positionY; }
			virtual void setPositionX( const double & positionX ) override { this->positionX = positionX; }
			virtual void setPositionY( const double & positionY ) override { this->positionY = positionY; }
			virtual double getWidth() const override { return width; }
			virtual double getHeight() const override { return height; }
			virtual void setWidth( const double & width ) override { this->width = width; }
			virtual void setHeight( const double & height ) override { this->height = height; }
			//Overrides ACollideable2D:
			virtual bool collidePoint( const double & x, const double & y ) const override;
			virtual bool collideCircle( const double & x, const double & y, const double & radius ) const override;
			virtual bool collideLine( const double & fromX, const double & fromY, const double & toX, const double & toY ) const override;
		private:
			double positionX;
			double positionY;
			double width;
			double height;
		};

		class Ball : public AMoveable2D
		{
		public:
			//Overrides AMoveable2D:
			virtual void update( const double & delta ) override;
			virtual double getPositionX() const override { return positionX; }
			virtual double getPositionY() const override { return positionY; }
			virtual void setPositionX( const double & positionX ) override { this->positionX = positionX; }
			virtual void setPositionY( const double & positionY ) override { this->positionY = positionY; }
			virtual double getVelocityX() const override { return velocityX; }
			virtual double getVelocityY() const override { return velocityY; }
			virtual void setVelocityX( const double & velocityX ) override { this->velocityX = velocityX; }
			virtual void setVelocityY( const double & velocityY ) override { this->velocityY = velocityY; }
		private:
			double positionX;
			double positionY;
			double velocityX;
			double velocityY;
		};

		class Paddle : public ABox2D, public AUpdateable
		{
		public:
			//Overrides AUpdateable:
			virtual void update( const double & delta ) override;
			//Overrides ABox2D:
			virtual double getPositionX() const override { return positionX; }
			virtual double getPositionY() const override { return positionY; }
			virtual void setPositionX( const double & positionX ) override { this->positionX = positionX; }
			virtual void setPositionY( const double & positionY ) override { this->positionY = positionY; }
			virtual double getWidth() const override { return width; }
			virtual double getHeight() const override { return height; }
			virtual void setWidth( const double & width ) override { this->width = width; }
			virtual void setHeight( const double & height ) override { this->height = height; }

			void moveLeft() { movingLeft = true; movingRight = false; }
			void stop() { movingLeft = false; movingRight = false; }
			void moveRight() { movingLeft = false; movingRight = true; }
			void setSpeed( double speed ) { this->speed = speed; }
		private:
			double speed = 1.0;
			double width = 0.25;
			double height = 0.1;
			double positionX = 0.0;
			double positionY = 0.0;
			bool movingLeft = false;
			bool movingRight = false;
		};

		class Field : public AUpdateable, public ACollideable2D
		{
		public:
			//Overrides AUpdateable:
			virtual void update( const double & delta ) override;
			//Overrides ACollideable2D:
			virtual bool collidePoint( const double & x, const double & y ) const override;
			virtual bool collideCircle( const double & x, const double & y, const double & radius ) const override;
			virtual bool collideLine( const double & fromX, const double & fromY, const double & toX, const double & toY ) const override;
		private:
			std::vector< std::vector< Brick > > bricks;
			std::vector< Ball > balls;
			Paddle paddle;
		};
	}

	namespace view
	{
		using namespace ::generic::view;

		class View : public AView
		{
		public:
			View();
			~View();
			//Overrides AView:
			virtual bool addDrawable( const ADrawable * drawable ) override;
			virtual bool removeDrawable( const ADrawable * drawable ) override;
			virtual void draw() const override;
		private:
			std::set< const ADrawable * > drawables;
			SDL_Window * window = nullptr;
			SDL_GLContext glContext = nullptr;
		};

		class Brick : public ADrawable
		{
		public:
			Brick( const ::arkanoid::model::Brick * model );
			//Overrides ADrawable:
			virtual void draw() const override;
		};

		class Ball : public ADrawable
		{
		public:
			Ball( const ::arkanoid::model::Ball * model );
			//Overrides ADrawable:
			virtual void draw() const override;
		};

		class Paddle : public ADrawable
		{
		public:
			Paddle( const ::arkanoid::model::Paddle * model ) : model(model) {}
			//Overrides ADrawable:
			virtual void draw() const override;
		private:
			const ::arkanoid::model::Paddle * model;
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
			PaddleAI( ::arkanoid::model::Paddle * model, ::arkanoid::model::Field * field );
		};
	}
}


#endif
