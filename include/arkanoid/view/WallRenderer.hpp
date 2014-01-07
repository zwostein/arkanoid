#ifndef _ARKANOID_VIEW_WALLRENDERER_INCLUDED_
#define _ARKANOID_VIEW_WALLRENDERER_INCLUDED_

#include <arkanoid/model/Wall.hpp>
#include <generic/view/AUnorderedRenderer.hpp>

namespace arkanoid
{
	namespace view
	{
		class WallRenderer : public ::generic::view::AUnorderedRenderer<model::Wall>
		{
		public:
			WallRenderer() {}
			virtual ~WallRenderer() {}
			//Overrides ::generic::view::AUnorderedRenderer:
			virtual void draw() const override;
		};
	}
}

#endif
