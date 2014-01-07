#include <arkanoid/view/BallRenderer.hpp>
#include <generic/type/Vector2.hpp>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>


using namespace arkanoid;
using namespace generic::type;


static void drawGlCircle( double radius, int segments )
{
	glBegin( GL_POLYGON );
	for( double i=0.0; i<360.0; i+=360.0/segments )
	{
		double degInRad = i*(3.14159/180.0);
		glVertex2d( cos(degInRad)*radius, sin(degInRad)*radius );
	}
	glEnd();
}


void view::BallRenderer::draw() const
{
	for( const auto & m : getModels() )
	{
		glPushMatrix();
			glTranslated( m->getPosition().x, m->getPosition().y, 0.1 );
			glScaled( m->getSize().x/2.0, m->getSize().y/2.0, 1.0f );
			glColor3f( 1, 1, 1 );
			drawGlCircle( 1.1, 6 );
		glPopMatrix();
	}
}
