#ifndef _GENERIC_H_
#define _GENERIC_H_


#include "Vector2.h"

#include <unordered_set>
#include <map>
#include <set>


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
			virtual bool isCollisionEnabled() const { return true; }
			virtual bool collide( ACollideable2D & other, const Vector2d & position, const Vector2d & depth ) = 0;
		};

		class APositionable2D
		{
		public:
			virtual Vector2d getPosition() const = 0;
			virtual void setPosition( const Vector2d & position ) = 0;
		};

		class AMoveable2D : public APositionable2D, public AUpdateable
		{
		public:
			virtual Vector2d getVelocity() const = 0;
			virtual void setVelocity( const Vector2d & velocity ) = 0;
		};

		class ABox2D : public APositionable2D
		{
		public:
			virtual Vector2d getSize() const = 0;
			virtual void setSize( const Vector2d & size ) = 0;
		};

		class ACollideableBox2D : public ABox2D, public ACollideable2D
		{
		};

		class ACollisionDetectorBox2D : public AUpdateable
		{
		public:
			virtual bool addCollideable( ACollideableBox2D * collideable ) = 0;
			virtual bool removeCollideable( ACollideableBox2D * collideable ) = 0;
		};

		class CollisionDetectorBox2D : public ACollisionDetectorBox2D
		{
		public:
			//Overrides ACollisionDetectorBox2D:
			virtual bool addCollideable( ACollideableBox2D * collideable ) override;
			virtual bool removeCollideable( ACollideableBox2D * collideable ) override;
			virtual void update( const double & delta ) override;
		private:
			std::set< ACollideableBox2D * > collideables;
		};

		class AModelUpdater : public AUpdateable
		{
		public:
			virtual bool addUpdateable( AUpdateable * updateable ) = 0;
			virtual bool removeUpdateable( AUpdateable * updateable ) = 0;
		};

		class AOrderedModelUpdater : public AModelUpdater
		{
		public:
			virtual bool addUpdateable( generic::model::AUpdateable * updateable, int order ) = 0;
		};

		class OrderedModelUpdater : public AOrderedModelUpdater
		{
		public:
			//Overrides AOrderedModelUpdater:
			virtual bool addUpdateable( generic::model::AUpdateable * updateable, int order ) override;
			virtual bool addUpdateable( AUpdateable * updateable ) override;
			virtual bool removeUpdateable( AUpdateable * updateable ) override;
			virtual void update( const double & delta ) override;
		private:
			std::multimap< int, generic::model::AUpdateable * > updateablesAsValues;
			std::map< generic::model::AUpdateable *, int > updateablesAsKeys;
		};
	}

	namespace view
	{
		class ADrawable
		{
		public:
			virtual void draw() const = 0;
		};

		template <class T> class ARenderer : public ADrawable
		{
		public:
			virtual bool addModel( const T * model ) = 0;
			virtual bool removeModel( const T * model ) = 0;
		};

		template <class T> class AUnorderedRenderer : public ARenderer<T>
		{
		public:
			virtual bool addModel( const T * model ) override final
				{ return models.insert(model).second; }
			virtual bool removeModel( const T * model ) override final
				{ return models.erase(model) != 0; }
			const std::unordered_set< const T * > & getModels() const
				{ return models; }
		private:
			std::unordered_set< const T * > models;
		};

		class AView : public ADrawable
		{
		public:
			virtual bool addDrawable( const ADrawable * drawable ) = 0;
			virtual bool removeDrawable( const ADrawable * drawable ) = 0;
		};
	}

	namespace controller
	{
	}
}


#endif
