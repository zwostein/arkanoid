#ifndef _ARKANOID_VIEW_BALLRENDERER_INCLUDED_
#define _ARKANOID_VIEW_BALLRENDERER_INCLUDED_

#include <arkanoid/model/Ball.hpp>
#include <generic/view/AUnorderedRenderer.hpp>

namespace arkanoid
{
	namespace view
	{
		class BallRenderer : public ::generic::view::AUnorderedRenderer<model::Ball>
		{
		public:
			BallRenderer() {}
			virtual ~BallRenderer() {}
			//Overrides ::generic::view::AUnorderedRenderer:
			virtual void draw() const override;
		};
	}
}

#endif
