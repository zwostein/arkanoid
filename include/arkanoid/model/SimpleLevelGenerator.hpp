#ifndef _ARKANOID_MODEL_SIMPLELEVELGENERATOR_INCLUDED_
#define _ARKANOID_MODEL_SIMPLELEVELGENERATOR_INCLUDED_

namespace arkanoid
{
	namespace model
	{
		class Level;

		class SimpleLevelGenerator
		{
		public:
			static Level * generateNewLevel( unsigned int level );
		};
	}
}

#endif
