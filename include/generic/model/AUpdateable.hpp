#ifndef _GENERIC_MODEL_AUPDATEABLE_INCLUDED_
#define _GENERIC_MODEL_AUPDATEABLE_INCLUDED_

namespace generic
{
	namespace model
	{
		class AUpdateable
		{
		public:
			virtual void update( const double & delta ) = 0;
		};
	}
}

#endif
