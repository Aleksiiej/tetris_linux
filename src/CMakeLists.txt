set(SRC_LIST
    main.cpp
    Band.cpp
    BaseBlock.cpp
    Block1.cpp
    Block2.cpp
    Block3.cpp
    Block4.cpp
    Block5.cpp
    Block6.cpp
    Block7.cpp
    BlockBoard.cpp
    BlockCreator.cpp
    EndgameText.cpp
    ScoreCounter.cpp
)

add_executable(tetris_linux ${SRC_LIST})

find_package(SFML COMPONENTS window graphics system)
target_link_libraries(tetris_linux sfml-graphics)
target_compile_features(tetris_linux PUBLIC cxx_std_20)
target_include_directories(tetris_linux PUBLIC ../include)
