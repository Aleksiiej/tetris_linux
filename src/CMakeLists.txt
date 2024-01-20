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
    Game.cpp
    ScoreCounter.cpp
    StartgameText.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

find_package(SFML COMPONENTS graphics)
target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_include_directories(${PROJECT_NAME} PUBLIC ../include)
