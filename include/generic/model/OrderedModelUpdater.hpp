#ifndef _GENERIC_MODEL_ORDEREDMODELUPDATER_INCLUDED_
#define _GENERIC_MODEL_ORDEREDMODELUPDATER_INCLUDED_

#include <generic/model/AOrderedModelUpdater.hpp>
#include <map>

namespace generic
{
	namespace model
	{
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
}

#endif
