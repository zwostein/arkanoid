#ifndef _ARKANOID_VIEW_PADDLERENDERER_INCLUDED_
#define _ARKANOID_VIEW_PADDLERENDERER_INCLUDED_

#include <arkanoid/model/Paddle.hpp>
#include <generic/view/AUnorderedRenderer.hpp>

namespace arkanoid
{
	namespace view
	{
		class PaddleRenderer : public ::generic::view::AUnorderedRenderer<model::Paddle>
		{
		public:
			PaddleRenderer() {}
			virtual ~PaddleRenderer() {}
			//Overrides ::generic::view::AUnorderedRenderer:
			virtual void draw() const override;
		};
	}
}

#endif
