#include <arkanoid/model/Brick.hpp>
#include <generic/type/Vector2.hpp>
#include <typeinfo>

#include <iostream>


using namespace arkanoid;
using namespace generic::type;


bool model::Brick::collide( generic::model::ACollideable2D & other, const Vector2d & , const Vector2d &  )
{
	if( typeid(other) == typeid(model::Brick) )
		std::cerr << "oops\n";
//		return false;
	destroyed = true;
	return true;
}
