#ifndef _GENERIC_MODEL_AORDEREDMODELUPDATER_INCLUDED_
#define _GENERIC_MODEL_AORDEREDMODELUPDATER_INCLUDED_

#include <generic/model/AModelUpdater.hpp>

namespace generic
{
	namespace model
	{
		class AUpdateable;

		class AOrderedModelUpdater : public AModelUpdater
		{
		public:
			virtual bool addUpdateable( AUpdateable * updateable, int order ) = 0;
		};
	}
}

#endif
