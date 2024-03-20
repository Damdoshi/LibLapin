if(WITH_OPENCV)
    list(APPEND LAPIN_SRC
        ${CMAKE_CURRENT_LIST_DIR}/capture_get_size.cpp
        ${CMAKE_CURRENT_LIST_DIR}/capture_new_picture.cpp
        ${CMAKE_CURRENT_LIST_DIR}/capture_new_pixelarray.cpp
        ${CMAKE_CURRENT_LIST_DIR}/capture_to_picture.cpp
        ${CMAKE_CURRENT_LIST_DIR}/capture_to_pixelarray.cpp
        ${CMAKE_CURRENT_LIST_DIR}/capture.cpp
        ${CMAKE_CURRENT_LIST_DIR}/delete_camera.cpp
        ${CMAKE_CURRENT_LIST_DIR}/delete_capture.cpp
        ${CMAKE_CURRENT_LIST_DIR}/headtrack.cpp
        ${CMAKE_CURRENT_LIST_DIR}/new_camera.cpp
        ${CMAKE_CURRENT_LIST_DIR}/new_capture.cpp
        ${CMAKE_CURRENT_LIST_DIR}/stabilize.cpp
    )
endif()