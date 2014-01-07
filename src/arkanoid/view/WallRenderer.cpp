#include <arkanoid/view/WallRenderer.hpp>
#include <generic/type/Vector2.hpp>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>


using namespace arkanoid;
using namespace generic::type;


void view::WallRenderer::draw() const
{
	for( const auto & m : getModels() )
	{
		glPushMatrix();
			glTranslated( m->getPosition().x, m->getPosition().y, 0.1 );
			glColor3f( 0.5, 0.5, 0.5 );
			glBegin( GL_QUADS );
				glVertex2f( -m->getSize().x/2.0, -m->getSize().y/2.0 );
				glVertex2f( m->getSize().x/2.0, -m->getSize().y/2.0 );
				glVertex2f( m->getSize().x/2.0, m->getSize().y/2.0 );
				glVertex2f( -m->getSize().x/2.0, m->getSize().y/2.0 );
			glEnd();
		glPopMatrix();
	}
}
