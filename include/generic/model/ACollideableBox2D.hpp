#ifndef _GENERIC_MODEL_ACOLLIDEABLEBOX2D_INCLUDED_
#define _GENERIC_MODEL_ACOLLIDEABLEBOX2D_INCLUDED_

#include <generic/model/ABox2D.hpp>
#include <generic/model/ACollideable2D.hpp>

namespace generic
{
	namespace model
	{
		class ACollideableBox2D : public ABox2D, public ACollideable2D
		{
		};
	}
}

#endif
