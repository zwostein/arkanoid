#ifndef _ARKANOID_MODEL_LEVELTEXTFILE_INCLUDED_
#define _ARKANOID_MODEL_LEVELTEXTFILE_INCLUDED_

#include <string>

namespace arkanoid
{
	namespace model
	{
		class Level;

		class LevelTextFile
		{
		public:
			static Level * load( const std::string & fileName );
			static bool save( const Level * level );
		};
	}
}

#endif
