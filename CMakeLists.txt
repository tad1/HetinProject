# CMakeList.txt: projekt CMake dla elementu HetinProject, do³¹cz Ÿród³o i zdefiniuj
# tutaj logikê specyficzn¹ dla projektu.
#
cmake_minimum_required (VERSION 3.8)

project ("HetinProject")

list(APPEND CMAKE_PREFIX_PATH ./libs/SDL2-2.0.18)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Dodaj Ÿród³o do pliku wykonywalnego tego projektu.
add_executable (HetinProject "src/main.cpp" "src/main.h" "src/game.h" "src/vector.h"  "src/Observer.cpp" "src/Observer.h" "src/include/Vector2.h" "src/include/MyString.h" "src/include/Object.h" "src/include/GameObject.h"  "src/Scene.h" "src/Transform.h"  "src/include/Component.h" "src/Time.h"  "src/Input.h"  "src/include/Dictionary.h" "src/TextureManager.h" "src/SpriteRendererComponent.h" "src/include/ScreenHandleler.h" "src/include/ScreenHandleler.cpp" "src/include/Copyable.h"   "tests/tests.h" "src/include/Collisions/Colliders.h" "src/include/Collisions/Layers.h" "src/include/Collisions/CollidersManager.h" "src/include/Collisions/ColliderComponent.h" "src/HotMemory.h" "src/Console.h"  "src/Settings.h"   "src/include/CollisionSystem.h" "src/TextRenderer.h" "src/ColorPalete.h" "src/Camera.h" "src/include/Math.h" "src/Clouds.h" "src/include/GenericPool.h" "src/include/Random.h" "src/include/SDL_Audio.h" "src/Player.h" "src/PhysicsComponent.h" "src/include/Physics2D.h" "src/Projectiles.h"  "src/Enemy.h" "src/Cannon.h" "src/ShootPatterns.h" "src/EnemyPlane.h" "src/ParticleSystem.h" "src/EnemySpawner.h" "src/Score.h" "src/Menu.h" "src/include/MonoBechaviour.h" "src/Camera.cpp" "components/Achivement.h" "src/AchivementSystem.h")


target_link_libraries(HetinProject ${SDL2_LIBRARIES})
