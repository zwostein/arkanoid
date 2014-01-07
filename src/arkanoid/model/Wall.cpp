#include <arkanoid/model/Wall.hpp>
#include <generic/type/Vector2.hpp>


using namespace arkanoid;
using namespace generic::type;


bool model::Wall::collide( generic::model::ACollideable2D & , const Vector2d & , const Vector2d &  )
{
	return false;
}
