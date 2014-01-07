#ifndef _ARKANOID_VIEW_BRICKRENDERER_INCLUDED_
#define _ARKANOID_VIEW_BRICKRENDERER_INCLUDED_

#include <arkanoid/model/Brick.hpp>
#include <generic/view/AUnorderedRenderer.hpp>

namespace arkanoid
{
	namespace view
	{
		class BrickRenderer : public ::generic::view::AUnorderedRenderer<model::Brick>
		{
		public:
			BrickRenderer() {}
			virtual ~BrickRenderer() {}
			//Overrides ::generic::view::AUnorderedRenderer:
			virtual void draw() const override;
		};
	}
}

#endif
