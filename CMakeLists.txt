# CMakeList.txt: projekt CMake dla elementu HetinProject, do³¹cz Ÿród³o i zdefiniuj
# tutaj logikê specyficzn¹ dla projektu.
#
cmake_minimum_required (VERSION 3.8)

project ("HetinProject")

list(APPEND CMAKE_PREFIX_PATH ./libs/SDL2-2.0.18)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Dodaj Ÿród³o do pliku wykonywalnego tego projektu.
add_executable (HetinProject "main.cpp" "main.h" "game.h" "vector.h"  "Observer.cpp" "Observer.h" "libs/Vector2.h" "libs/MyString.h" "include/Object.h" "include/GameObject.h"  "Scene.h" "Transform.h"  "include/Component.h" "Time.h"  "Input.h"  "libs/Dictionary.h" "TextureManager.h" "SpriteRendererComponent.h" "include/ScreenHandleler.h" "include/ScreenHandleler.cpp" "libs/Copyable.h"   "tests/tests.h" "include/Collisions/Colliders.h" "include/Collisions/Layers.h" "include/Collisions/CollidersManager.h" "include/Collisions/ColliderComponent.h" "HotMemory.h" "Console.h"  "Settings.h"   "include/CollisionSystem.h" "TextRenderer.h" "ColorPalete.h" "Camera.h" "libs/Math.h" "Clouds.h" "include/GenericPool.h" "libs/Random.h" "include/SDL_Audio.h" "Player.h" "PhysicsComponent.h" "include/Physics2D.h" "Projectiles.h"  "Enemy.h" "Cannon.h" "ShootPatterns.h" "EnemyPlane.h" "ParticleSystem.h" "EnemySpawner.h" "Score.h" "Menu.h")


target_link_libraries(HetinProject ${SDL2_LIBRARIES})
# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
