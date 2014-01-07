#ifndef _GENERIC_VIEW_AVIEW_INCLUDED_
#define _GENERIC_VIEW_AVIEW_INCLUDED_

#include <generic/view/ADrawable.hpp>

namespace generic
{
	namespace view
	{
		class AView : public ADrawable
		{
		public:
			virtual bool addDrawable( const ADrawable * drawable ) = 0;
			virtual bool removeDrawable( const ADrawable * drawable ) = 0;
		};
	}
}

#endif
