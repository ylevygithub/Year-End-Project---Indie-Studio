cmake_minimum_required (VERSION 3.11)
project(bomberman)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/SFML-2.5.1/lib/cmake/SFML")
file(GLOB ALL_REQUIRED_DLL "libs/required_dlls/*.dll")
file(COPY ${ALL_REQUIRED_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)

find_package(Irrlicht REQUIRED)
find_package(SFML 2.4.2 COMPONENTS audio REQUIRED)

set(PROJECT_SOURCE
  src/main.cpp src/event/catchEvent.cpp src/event/catchEvent.hpp
  src/bombermanManager/bombermanManager.cpp src/bombermanManager/bombermanManager.hpp
  src/gameloop.cpp src/include/game.h
  src/Map/Map.cpp src/Map/Map.hpp
  src/gameObject/IGameObject.cpp src/gameObject/IGameObject.hpp
  src/gameObject/Block.cpp src/gameObject/Block.hpp
  src/gameObject/Bomb.cpp src/gameObject/Bomb.hpp
  src/gameObject/Player.cpp src/gameObject/Player.hpp
  src/gameObject/PowerUp.cpp src/gameObject/PowerUp.hpp
  src/gameObject/HUD.cpp src/gameObject/HUD.hpp
  src/menu/menu.cpp src/menu/menu.hpp
  src/music/ogg/
  src/music/wav/
  src/music/music.cpp
  src/music/sound.cpp
  src/save/save.cpp
  src/music/audio.hpp)

include_directories(lib/irrlicht-1.8.4/include src/include src/bombermanManager/ src/gameObject/ src/save src/Map/ src/event/ src/menu/ src/music)

ADD_EXECUTABLE(bomberman ${PROJECT_SOURCE})
target_link_libraries(bomberman Irrlicht sfml-audio)
