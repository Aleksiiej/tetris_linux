add_executable(tetris_linux main.cpp)
target_compile_features(tetris_linux PRIVATE cxx_std_20)

target_link_libraries(tetris_linux PRIVATE tetris_lib)