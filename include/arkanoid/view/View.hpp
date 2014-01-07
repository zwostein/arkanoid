#ifndef _ARKANOID_VIEW_VIEW_INCLUDED_
#define _ARKANOID_VIEW_VIEW_INCLUDED_

#include <generic/view/AView.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <unordered_set>

namespace generic { namespace view { class ADrawable; } }

namespace arkanoid
{
	namespace view
	{
		class View : public ::generic::view::AView
		{
		public:
			View();
			virtual ~View();
			//Overrides ::generic::view::AView:
			virtual bool addDrawable( const ADrawable * drawable ) override;
			virtual bool removeDrawable( const ADrawable * drawable ) override;
			virtual void draw() const override;
		private:
			std::unordered_set< const ADrawable * > drawables;
			SDL_Window * window = nullptr;
			SDL_GLContext glContext = nullptr;
		};
	}
}

#endif
