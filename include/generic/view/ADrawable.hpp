#ifndef _GENERIC_VIEW_ADRAWABLE_INCLUDED_
#define _GENERIC_VIEW_ADRAWABLE_INCLUDED_

namespace generic
{
	namespace view
	{
		class ADrawable
		{
		public:
			virtual void draw() const = 0;
		};
	}
}

#endif
