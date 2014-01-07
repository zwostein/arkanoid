#include <arkanoid/model/Brick.hpp>
#include <generic/type/Vector2.hpp>


using namespace arkanoid;
using namespace generic::type;


bool model::Brick::collide( generic::model::ACollideable2D & , const Vector2d & , const Vector2d &  )
{
	destroyed = true;
	return false;
}
