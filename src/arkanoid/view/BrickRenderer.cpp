#include <arkanoid/view/BrickRenderer.hpp>
#include <generic/type/Vector2.hpp>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>


using namespace arkanoid;
using namespace generic::type;


void view::BrickRenderer::draw() const
{
	for( const auto & m : getModels() )
	{
		if( m->isDestroyed() )
			continue;
		glPushMatrix();
			glTranslated( m->getPosition().x, m->getPosition().y, 0.1 );
			glColor3f( 0.75, 0.75, 0.75 );
			glBegin( GL_QUADS );
				glVertex2f( -m->getSize().x/2.0, -m->getSize().y/2.0 );
				glVertex2f( m->getSize().x/2.0, -m->getSize().y/2.0 );
				glVertex2f( m->getSize().x/2.0, m->getSize().y/2.0 );
				glVertex2f( -m->getSize().x/2.0, m->getSize().y/2.0 );
			glEnd();
		glPopMatrix();
	}
}
