set(SRC_LIST
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

add_library(tetris_lib ${SRC_LIST})
target_compile_features(tetris_lib PUBLIC cxx_std_20)
target_include_directories(tetris_lib PUBLIC ../include)
