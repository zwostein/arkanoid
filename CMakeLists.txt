project( arkanoid )
cmake_minimum_required( VERSION 2.8 )

set( CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra ${CMAKE_CXX_FLAGS}")

include_directories( include )

add_executable( arkanoid
	src/main.cpp

	src/arkanoid/controller/PaddlePlayer.cpp

	src/arkanoid/model/Ball.cpp
	src/arkanoid/model/Wall.cpp
	src/arkanoid/model/Brick.cpp
	src/arkanoid/model/Level.cpp
	src/arkanoid/model/Paddle.cpp
	src/arkanoid/model/SimpleLevelGenerator.cpp
	src/arkanoid/model/LevelTextFile.cpp

	src/arkanoid/view/View.cpp
	src/arkanoid/view/BallRenderer.cpp
	src/arkanoid/view/BrickRenderer.cpp
	src/arkanoid/view/PaddleRenderer.cpp
	src/arkanoid/view/WallRenderer.cpp

	src/generic/model/OrderedModelUpdater.cpp
	src/generic/model/CollisionDetectorBox2D.cpp
)

target_link_libraries( arkanoid SDL2 GL GLU )
install( TARGETS arkanoid RUNTIME DESTINATION bin )
