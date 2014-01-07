#include <generic/type/Vector2.hpp>
#include <generic/model/CollisionDetectorBox2D.hpp>
#include <generic/model/ACollideableBox2D.hpp>


using namespace ::generic;
using namespace ::generic::type;


bool model::CollisionDetectorBox2D::addCollideable( generic::model::ACollideableBox2D * collideable )
{
	return collideables.insert( collideable ).second;
}


bool model::CollisionDetectorBox2D::removeCollideable( generic::model::ACollideableBox2D * collideable )
{
	return collideables.erase( collideable );
}


template <class T> static unsigned int lowestIndexInArray( T array[], unsigned int size )
{
	unsigned int index = 0;
	for( unsigned int i = 1; i < size; i++ )
	{
		if( array[i] < array[index] )
			index = i;
	}
	return index;
}


void model::CollisionDetectorBox2D::update( const double & )
{
	for( auto a = collideables.begin(); a != collideables.end(); ++a )
	{
		if( !(*a)->isCollisionEnabled() )
			continue;
		auto atmp = a;
		for( auto b = ++atmp; b != collideables.end(); ++b )
		{
			if( !(*b)->isCollisionEnabled() )
				continue;
			// calculate bottom left and top right corners
			Vector2d aBL = (*a)->getPosition()-(*a)->getSize()/2.0;
			Vector2d aTR = (*a)->getPosition()+(*a)->getSize()/2.0;
			Vector2d bBL = (*b)->getPosition()-(*b)->getSize()/2.0;
			Vector2d bTR = (*b)->getPosition()+(*b)->getSize()/2.0;
			// calculate penetration depths
			enum Direction
			{
				LEFT   = 0,
				RIGHT  = 1,
				TOP    = 2,
				BOTTOM = 3
			};
			double aDepths[4];
			aDepths[RIGHT]  = aTR.x - bBL.x;
			aDepths[LEFT]   = aBL.x - bTR.x;
			aDepths[TOP]    = aTR.y - bBL.y;
			aDepths[BOTTOM] = aBL.y - bTR.y;
			// intersecting on any axis?
			bool ix = (aDepths[RIGHT]<0) ^ (aDepths[LEFT]<0);
			bool iy = (aDepths[TOP]<0) ^ (aDepths[BOTTOM]<0);
			// continue with next object if any axis is not intersecting
			if( !(ix && iy) )
				continue;

			aDepths[RIGHT]  = fabs(aDepths[RIGHT]);
			aDepths[LEFT]   = fabs(aDepths[LEFT]);
			aDepths[TOP]    = fabs(aDepths[TOP]);
			aDepths[BOTTOM] = fabs(aDepths[BOTTOM]);
			Direction d = (Direction)lowestIndexInArray( aDepths, 4 );
			Vector2d cpA;
			Vector2d cpB;
			Vector2d cDepth;
			switch( d )
			{
				case LEFT:
					cpA = Vector2d( aBL.x, (*a)->getPosition().y );
					cpB = Vector2d( bTR.x, (*b)->getPosition().y );
					cDepth = Vector2d( aDepths[LEFT], 0.0 );
					break;
				case RIGHT:
					cpA = Vector2d( aTR.x, (*a)->getPosition().y );
					cpB = Vector2d( bBL.x, (*b)->getPosition().y );
					cDepth = Vector2d( -aDepths[RIGHT], 0.0 );
					break;
				case TOP:
					cpA = Vector2d( (*a)->getPosition().x, aTR.y );
					cpB = Vector2d( (*b)->getPosition().x, bBL.y );
					cDepth = Vector2d( 0.0, -aDepths[TOP] );
					break;
				case BOTTOM:
					cpA = Vector2d( (*a)->getPosition().x, aBL.y );
					cpB = Vector2d( (*b)->getPosition().x, bTR.y );
					cDepth = Vector2d( 0.0, aDepths[BOTTOM] );
					break;
			}
//			std::cerr << "cpx: " << cp.x << "   cpy: " << cp.y << std::endl;
//			std::cerr << "aR: " << aR << "   aL: " << aL << "   aT: " << aT << "   aB: " << aB << std::endl;
			(*a)->collide( *(*b), cpA, cDepth );
			(*b)->collide( *(*a), cpB, -cDepth );
		}
	}
}
