#include "generic.h"
#include "arkanoid.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

/*
void InitGL()
{
	glShadeModel( GL_SMOOTH );
	glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_COLOR_MATERIAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}


void reshape( int width , int height )
{
	if( height == 0 )
	{
		height = 1;
	}

	glViewport( 0, 0, width, height );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective( 45.0f, ( GLfloat )width / ( GLfloat )height, 0.1f, 100.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}


void keyboard( unsigned char key, int x, int y )
{
	switch( key )
	{
	case 27: // When Escape Is Pressed...
		exit( 0 );
		break;

	case 32: // When Space is pressed
		if( ( balls > 1 ) && ( ball_start == 1 ) )
		{
			ball2_start = 1;
		}
		ball_start = 1;
		break;

	default:
		break;
	}
}


void arrow_keys( int a_keys, int x, int y )
{
	switch( a_keys )
	{
	case GLUT_KEY_LEFT:
		left_key_pressed = 1;
		break;

	case GLUT_KEY_RIGHT:
		right_key_pressed = 1;
		break;

	default:
		break;
	}
}


void arrow_keys_up( int a_keys, int x, int y )
{
	switch( a_keys )
	{

	case GLUT_KEY_LEFT:
		left_key_pressed = 0;
		break;

	case GLUT_KEY_RIGHT:
		right_key_pressed = 0;
		break;

	default:
		break;
	}
}
*/

int main( int argc, char ** argv )
{
/*	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize( 1500, 800 );
	glutCreateWindow( "Arkanoid" );
	InitGL();
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutSpecialFunc( arrow_keys );
	glutSpecialUpFunc( arrow_keys_up );
	glutIdleFunc( display );
	glutMainLoop( );*/
	return 0;
}
