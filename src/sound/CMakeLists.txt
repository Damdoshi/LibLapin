list(APPEND LAPIN_SRC
${CMAKE_CURRENT_LIST_DIR}/attenuation.cpp
${CMAKE_CURRENT_LIST_DIR}/compute_effect.cpp
${CMAKE_CURRENT_LIST_DIR}/delete_sound.cpp
${CMAKE_CURRENT_LIST_DIR}/get_cursor.cpp
${CMAKE_CURRENT_LIST_DIR}/get_duration.cpp
${CMAKE_CURRENT_LIST_DIR}/is_playing.cpp
${CMAKE_CURRENT_LIST_DIR}/load_effect.cpp
${CMAKE_CURRENT_LIST_DIR}/load_music.cpp
${CMAKE_CURRENT_LIST_DIR}/loop.cpp
${CMAKE_CURRENT_LIST_DIR}/make_effect_unique.cpp
${CMAKE_CURRENT_LIST_DIR}/new_effect.cpp
${CMAKE_CURRENT_LIST_DIR}/pause.cpp
${CMAKE_CURRENT_LIST_DIR}/pitch.cpp
${CMAKE_CURRENT_LIST_DIR}/play.cpp
${CMAKE_CURRENT_LIST_DIR}/position.cpp
${CMAKE_CURRENT_LIST_DIR}/read_effect.cpp
${CMAKE_CURRENT_LIST_DIR}/save_effect.cpp
${CMAKE_CURRENT_LIST_DIR}/set_cursor.cpp
${CMAKE_CURRENT_LIST_DIR}/set_sound_attribute.cpp
${CMAKE_CURRENT_LIST_DIR}/stop.cpp
${CMAKE_CURRENT_LIST_DIR}/volume.cpp
)

include(${CMAKE_CURRENT_LIST_DIR}/manager/CMakeLists.txt)