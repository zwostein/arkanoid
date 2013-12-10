#ifndef _ARKANOID_H_
#define _ARKANOID_H_

#include "generic.h"

#include <vector>


namespace arkanoid
{
	namespace model
	{
		using namespace ::generic::model;

		class Brick : public ABox2D, public ACollideable2D
		{
		public:
			//Overrides ABox2D:
			virtual double getPositionX() const { return positionX; }
			virtual double getPositionY() const { return positionY; }
			virtual void setPositionX( const double & positionX ) { this->positionX = positionX; }
			virtual void setPositionY( const double & positionY ) { this->positionY = positionY; }
			virtual double getWidth() const { return width; }
			virtual double getHeight() const { return height; }
			virtual void setWidth( const double & width ) { this->width = width; }
			virtual void setHeight( const double & height ) { this->height = height; }
			//Overrides ACollideable2D:
			virtual bool collidePoint( const double & x, const double & y ) const;
			virtual bool collideCircle( const double & x, const double & y, const double & radius ) const;
			virtual bool collideLine( const double & fromX, const double & fromY, const double & toX, const double & toY ) const;
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
			virtual void update( const double & delta );
			virtual double getPositionX() const { return positionX; }
			virtual double getPositionY() const { return positionY; }
			virtual void setPositionX( const double & positionX ) { this->positionX = positionX; }
			virtual void setPositionY( const double & positionY ) { this->positionY = positionY; }
			virtual double getVelocityX() const { return velocityX; }
			virtual double getVelocityY() const { return velocityY; }
			virtual void setVelocityX( const double & velocityX ) { this->velocityX = velocityX; }
			virtual void setVelocityY( const double & velocityY ) { this->velocityY = velocityY; }
		private:
			double positionX;
			double positionY;
			double velocityX;
			double velocityY;
		};

		class Paddle : public APositionable2D
		{
		public:
			//Overrides APositionable2D:
			virtual double getPositionX() const { return positionX; }
			virtual double getPositionY() const { return positionY; }
			virtual void setPositionX( const double & positionX ) { this->positionX = positionX; }
			virtual void setPositionY( const double & positionY ) { this->positionY = positionY; }
		private:
			double positionX;
			double positionY;
		};

		class Field : public AUpdateable, public ACollideable2D
		{
		public:
			//Overrides AUpdateable:
			virtual void update( const double & delta );
			//Overrides ACollideable2D:
			virtual bool collidePoint( const double & x, const double & y ) const;
			virtual bool collideCircle( const double & x, const double & y, const double & radius ) const;
			virtual bool collideLine( const double & fromX, const double & fromY, const double & toX, const double & toY ) const;
		private:
			std::vector< std::vector< Brick > > bricks;
			std::vector< Ball > balls;
			Paddle paddle;
		};
	}

	namespace view
	{
		using namespace ::generic::view;

		class Brick : public ADrawable
		{
		public:
			Brick( ::arkanoid::model::Brick * brick );
			//Overrides ADrawable:
			virtual void draw() const;
		};

		class Ball : public ADrawable
		{
		public:
			Ball( ::arkanoid::model::Ball * ball );
			//Overrides ADrawable:
			virtual void draw() const;
		};

		class Paddle : public ADrawable
		{
		public:
			Paddle( ::arkanoid::model::Paddle * paddle );
			//Overrides ADrawable:
			virtual void draw() const;
		};
	}

	namespace controller
	{
		using namespace ::generic::controller;

		class PaddlePlayer
		{
		public:
			PaddlePlayer( ::arkanoid::model::Paddle * paddle );
		};

		class PaddleAI
		{
		public:
			PaddleAI( ::arkanoid::model::Paddle * paddle, ::arkanoid::model::Field * field );
		};
	}
}


#endif
