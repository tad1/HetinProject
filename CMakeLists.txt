# CMakeList.txt: projekt CMake dla elementu HetinProject, do³¹cz Ÿród³o i zdefiniuj
# tutaj logikê specyficzn¹ dla projektu.
#
cmake_minimum_required (VERSION 3.8)

project ("HetinProject")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Dodaj Ÿród³o do pliku wykonywalnego tego projektu.
add_executable (HetinProject "HetinProject.cpp" "HetinProject.h" "game.h" "vector.h"  "Observer.cpp" "Observer.h" "libs/Vector2.h" "libs/MyString.h" "Object.h" "include/GameObject.h" "libs/readOnly.h" "Scene.h" "Transform.h" "FileWatch.h" "include/Component.h" "Time.h"  "Input.h" "include.h" "libs/Dictionary.h" "TextureManager.h" "SpriteRendererComponent.h" "include/ScreenHandleler.h" "include/ScreenHandleler.cpp" "libs/Copyable.h"  "tests/copyableTest.cpp" "tests/tests.h" "include/Collisions/Colliders.h" "include/Collisions/Layers.h" "include/Collisions/CollidersManager.h" "include/Collisions/ColliderComponent.h" "HotMemory.h" "Console.h"  "Settings.h"  "include/Collisions/CollidersManager.cpp" "include/CollisionSystem.h")


target_link_libraries(HetinProject ${SDL2_LIBRARIES})
# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
