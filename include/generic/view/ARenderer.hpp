#ifndef _GENERIC_VIEW_ARENDERER_INCLUDED_
#define _GENERIC_VIEW_ARENDERER_INCLUDED_

#include <generic/view/ADrawable.hpp>
#include <unordered_set>

namespace generic
{
	namespace view
	{
		template <class T> class ARenderer : public ADrawable
		{
		public:
			virtual bool addModel( const T * model ) = 0;
			virtual bool removeModel( const T * model ) = 0;
			virtual const std::unordered_set< const T * > & getModels() const = 0;
		};
	}
}

#endif
