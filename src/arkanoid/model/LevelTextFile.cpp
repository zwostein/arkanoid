#include <arkanoid/model/LevelTextFile.hpp>
#include <arkanoid/model/Level.hpp>
#include <arkanoid/model/Brick.hpp>
#include <arkanoid/model/Ball.hpp>
#include <arkanoid/model/Wall.hpp>
#include <arkanoid/model/Paddle.hpp>
#include <generic/type/Vector2.hpp>

#include <SDL2/SDL_rwops.h>

#include <vector>
#include <string>

#include <stdio.h>
#include <unistd.h>


using namespace arkanoid;
using namespace generic::type;


static Vector2<size_t> boxSize( const std::vector< std::string > & levelString, size_t startLine, size_t startRow, char type )
{
	if( levelString[startLine][startRow] != type )
		return Vector2<size_t>( 0, 0 );

	Vector2<size_t> size( 1, 1 );

	for( size_t row = startRow+1; row < levelString[startLine].size(); ++row )
	{
		if( levelString[startLine][row] == type )
			size.x += 1;
		else
			break;
	}

	for( size_t line = startLine+1; line < levelString.size(); ++line )
	{
		size_t lineLength = 0;
		for( size_t row = startRow; row < levelString[line].size(); ++row )
		{
			if( levelString[line][row] == type )
				lineLength += 1;
			else
				break;
		}
		if( lineLength == size.x )
			size.y += 1;
		else
			break;

	}
	return size;
}


static void clearBox( std::vector< std::string > & levelString, size_t startLine, size_t startRow, Vector2<size_t> size )
{
	for( size_t line = startLine; line < startLine+size.y; ++line )
	{
		for( size_t row = startRow; row < startRow+size.x; ++row )
		{
			levelString[line][row] = ' ';
		}
	}
}


static Vector2d toLevelPosition( const Vector2<size_t> & levelSize, const Vector2<size_t> & coord )
{
	return Vector2d( ((double)(2*coord.x)/(double)(levelSize.x))-1.0, -(((double)(2*coord.y)/(double)(levelSize.y))-1.0) );
}


static Vector2d toLevelSize( const Vector2<size_t> & levelSize, const Vector2<size_t> & coord )
{
	return Vector2d( (double)(2*coord.x)/(double)(levelSize.x), (double)(2*coord.y)/(double)(levelSize.y) );
}


static void setToLevelPositionAndSize( generic::model::ABox2D & boxObject, const Vector2<size_t> & levelSize, const Vector2<size_t> & boxPosition, const Vector2<size_t> & boxSize )
{
	boxObject.setSize( toLevelSize( levelSize, boxSize ) );
	boxObject.setPosition( toLevelPosition( levelSize, Vector2<size_t>( boxPosition.x, boxPosition.y + boxSize.y) ) + boxObject.getSize()/2.0 );
}


static void setToLevelPosition( generic::model::ABox2D & boxObject, const Vector2<size_t> & levelSize, const Vector2<size_t> & boxPosition, const Vector2<size_t> & boxSize )
{
	boxObject.setPosition( toLevelPosition( levelSize, Vector2<size_t>( boxPosition.x, boxPosition.y + boxSize.y) ) + toLevelSize( levelSize, boxSize )/2.0 );
}


model::Level * model::LevelTextFile::load( const std::string & fileName )
{
	model::Level * level = new model::Level;

	SDL_RWops * file = SDL_RWFromFile( fileName.c_str(), "r" );
	if( !file )
		return nullptr;

	std::vector< std::string > levelString;
	levelString.push_back( std::string() );
	char c;
	while( true )
	{
		size_t ret = SDL_RWread( file, &c, 1, 1 );
		if( ret == 0 )
			break;

		if( c == '\n' )
			levelString.push_back( std::string() );
		else
			levelString.back().push_back( c );
	}
	if( levelString.back().length() == 0 )
		levelString.pop_back();
/*
	for( std::string line : levelString )
	{
		printf( "\"%s\"\n", line.c_str() );
	}
*/
	Vector2<size_t> levelSize( (size_t)0, levelString.size() );
	for( std::string line : levelString )
		if( line.size() > levelSize.x )
			levelSize.x = line.size();
//	printf( "LevelSize %lux%lu\n", levelSize.x, levelSize.y );

	bool createdSomething = false;
	do
	{
		for( size_t line = 0; line < levelString.size(); ++line )
		{
			for( size_t row = 0; row < levelString[line].size(); ++row )
			{
				createdSomething = false;
				Vector2<size_t> size = boxSize( levelString, line, row, levelString[line][row] );
				switch( levelString[line][row] )
				{
					case 'w':
					{
						arkanoid::model::Wall * b = new arkanoid::model::Wall;
						setToLevelPositionAndSize( *b, levelSize, Vector2<size_t>(row,line), size );
						level->takeWall( b );
//						printf( "Wall %f %f: %fx%f\n", b->getPosition().x, b->getPosition().y, b->getSize().x, b->getSize().y );
						createdSomething = true;
						break;
					}
					case 'b':
					{
						arkanoid::model::Brick * b = new arkanoid::model::Brick;
						setToLevelPositionAndSize( *b, levelSize, Vector2<size_t>(row,line), size );
						level->takeBrick( b );
//						printf( "Brick %f %f: %fx%f\n", b->getPosition().x, b->getPosition().y, b->getSize().x, b->getSize().y );
						createdSomething = true;
						break;
					}
					case 'o':
					{
						arkanoid::model::Ball * b = new arkanoid::model::Ball;
						setToLevelPosition( *b, levelSize, Vector2<size_t>(row,line), size );
						level->takeBall( b );
//						printf( "Ball %f %f\n", b->getPosition().x, b->getPosition().y );
						createdSomething = true;
						break;
					}
					case 'p':
					{
						arkanoid::model::Paddle * b = new arkanoid::model::Paddle;
						setToLevelPositionAndSize( *b, levelSize, Vector2<size_t>(row,line), size );
						level->takePaddle( b );
//						printf( "Paddle %f %f: %fx%f\n", b->getPosition().x, b->getPosition().y, b->getSize().x, b->getSize().y );
						createdSomething = true;
						break;
					}
				}
				if( createdSomething )
				{
					clearBox( levelString, line, row, size );
/*
					printf( "--------\n" );
					for( std::string line : levelString )
					{
						printf( "\"%s\"\n", line.c_str() );
					}
*/
					//TODO: this causes a complete reparse - could be more efficient ;)
					line = 0;
					row = 0;
				}
			}
		}
	} while( createdSomething );

	SDL_RWclose( file );

	return level;
}
