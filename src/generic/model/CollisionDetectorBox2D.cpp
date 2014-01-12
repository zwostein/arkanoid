#include <generic/type/Vector2.hpp>
#include <generic/type/Direction.hpp>
#include <generic/model/CollisionDetectorBox2D.hpp>
#include <generic/model/ACollideableBox2D.hpp>


using namespace ::generic;
using namespace ::generic::type;


constexpr static const double SHRINK_FACTOR = 0.9999;


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
			// shrink the actual boxes a little so we do not trigger collisions for object exactly next to each other
			Vector2d aBL = (*a)->getPosition()-(*a)->getSize()*0.5*SHRINK_FACTOR;
			Vector2d aTR = (*a)->getPosition()+(*a)->getSize()*0.5*SHRINK_FACTOR;
			Vector2d bBL = (*b)->getPosition()-(*b)->getSize()*0.5*SHRINK_FACTOR;
			Vector2d bTR = (*b)->getPosition()+(*b)->getSize()*0.5*SHRINK_FACTOR;

			// calculate penetration depths
			double aDepths[4];
			aDepths[(int)Direction::RIGHT]  = aTR.x - bBL.x;
			aDepths[(int)Direction::LEFT]   = aBL.x - bTR.x;
			aDepths[(int)Direction::TOP]    = aTR.y - bBL.y;
			aDepths[(int)Direction::BOTTOM] = aBL.y - bTR.y;
			// intersecting on any axis?
			bool ix = (aDepths[(int)Direction::RIGHT]<0) ^ (aDepths[(int)Direction::LEFT]<0);
			bool iy = (aDepths[(int)Direction::TOP]<0) ^ (aDepths[(int)Direction::BOTTOM]<0);
			// continue with next object if any axis is not intersecting
			if( !(ix && iy) )
				continue;

			// relative penetration depths
			aDepths[(int)Direction::RIGHT]  = fabs(aDepths[(int)Direction::RIGHT]);
			aDepths[(int)Direction::LEFT]   = fabs(aDepths[(int)Direction::LEFT]);
			aDepths[(int)Direction::TOP]    = fabs(aDepths[(int)Direction::TOP]);
			aDepths[(int)Direction::BOTTOM] = fabs(aDepths[(int)Direction::BOTTOM]);
			Direction d = (Direction)lowestIndexInArray( aDepths, 4 );
			Vector2d cpA;
			Vector2d cpB;
			Vector2d cDepth;
			switch( d )
			{
				case Direction::LEFT:
					cpA = Vector2d( aBL.x, (*a)->getPosition().y );
					cpB = Vector2d( bTR.x, (*b)->getPosition().y );
					cDepth = Vector2d( aDepths[(int)Direction::LEFT], 0.0 );
					break;
				case Direction::RIGHT:
					cpA = Vector2d( aTR.x, (*a)->getPosition().y );
					cpB = Vector2d( bBL.x, (*b)->getPosition().y );
					cDepth = Vector2d( -aDepths[(int)Direction::RIGHT], 0.0 );
					break;
				case Direction::TOP:
					cpA = Vector2d( (*a)->getPosition().x, aTR.y );
					cpB = Vector2d( (*b)->getPosition().x, bBL.y );
					cDepth = Vector2d( 0.0, -aDepths[(int)Direction::TOP] );
					break;
				case Direction::BOTTOM:
					cpA = Vector2d( (*a)->getPosition().x, aBL.y );
					cpB = Vector2d( (*b)->getPosition().x, bTR.y );
					cDepth = Vector2d( 0.0, aDepths[(int)Direction::BOTTOM] );
					break;
			}
//			std::cerr << "cpx: " << cp.x << "   cpy: " << cp.y << std::endl;
//			std::cerr << "aR: " << aR << "   aL: " << aL << "   aT: " << aT << "   aB: " << aB << std::endl;
			(*a)->collide( *(*b), cpA, cDepth );
			(*b)->collide( *(*a), cpB, -cDepth );
		}
	}
}
