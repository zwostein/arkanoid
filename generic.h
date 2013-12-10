#ifndef _GENERIC_H_
#define _GENERIC_H_


namespace generic
{
	namespace model
	{
		class AUpdateable
		{
		public:
			virtual void update( const double & delta ) = 0;
		};

		class ACollideable2D
		{
		public:
			virtual bool collidePoint( const double & x, const double & y ) const = 0;
			virtual bool collideCircle( const double & x, const double & y, const double & radius ) const = 0;
			virtual bool collideLine( const double & fromX, const double & fromY, const double & toX, const double & toY ) const = 0;
		};

		class APositionable2D
		{
		public:
			virtual double getPositionX() const = 0;
			virtual double getPositionY() const = 0;
			virtual void setPositionX( const double & positionX ) = 0;
			virtual void setPositionY( const double & positionY ) = 0;
		};

		class AMoveable2D : public APositionable2D, public AUpdateable
		{
		public:
			virtual double getVelocityX() const = 0;
			virtual double getVelocityY() const = 0;
			virtual void setVelocityX( const double & velocityX ) = 0;
			virtual void setVelocityY( const double & velocityY ) = 0;
		};

		class ABox2D : public APositionable2D
		{
		public:
			virtual double getWidth() const = 0;
			virtual double getHeight() const = 0;
			virtual void setWidth( const double & width ) = 0;
			virtual void setHeight( const double & height ) = 0;
		};
	}

	namespace view
	{
		class ADrawable
		{
		public:
			virtual void draw() const = 0;
		};
	}

	namespace controller
	{
	}
}


#endif
