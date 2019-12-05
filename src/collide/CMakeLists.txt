list(APPEND LAPIN_SRC
	${CMAKE_CURRENT_LIST_DIR}/circle.cpp
	${CMAKE_CURRENT_LIST_DIR}/clip.cpp
	${CMAKE_CURRENT_LIST_DIR}/collide.cpp
	${CMAKE_CURRENT_LIST_DIR}/collision.cpp
	${CMAKE_CURRENT_LIST_DIR}/configuration.cpp
	${CMAKE_CURRENT_LIST_DIR}/draw_collision_shape.cpp
	${CMAKE_CURRENT_LIST_DIR}/move_collision.cpp
	${CMAKE_CURRENT_LIST_DIR}/pixel_collision.cpp
	${CMAKE_CURRENT_LIST_DIR}/quad.cpp
	${CMAKE_CURRENT_LIST_DIR}/rectangular.cpp
	${CMAKE_CURRENT_LIST_DIR}/triangle.cpp
	${CMAKE_CURRENT_LIST_DIR}/turn_collision.cpp
)

include(${CMAKE_CURRENT_LIST_DIR}/sub/CMakeLists.txt)