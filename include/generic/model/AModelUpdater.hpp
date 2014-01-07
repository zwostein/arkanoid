#ifndef _GENERIC_MODEL_AMODELUPDATER_INCLUDED_
#define _GENERIC_MODEL_AMODELUPDATER_INCLUDED_

#include <generic/model/AUpdateable.hpp>

namespace generic
{
	namespace model
	{
		class AModelUpdater : public AUpdateable
		{
		public:
			virtual bool addUpdateable( AUpdateable * updateable ) = 0;
			virtual bool removeUpdateable( AUpdateable * updateable ) = 0;
		};
	}
}

#endif
