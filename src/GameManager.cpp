#include <GameManager.hpp>

#include <Engine/Animation/AnimationSystem.hpp>
#include <Engine/Camera/CameraSystem.hpp>
#include <Engine/Core/DespawnSystem.hpp>

#include <Engine/Physics/CollisionDetectionSystem.hpp>
#include <Engine/Physics/HitBlockSystem.hpp>
#include <Engine/Physics/GravitySystem.hpp>
#include <Engine/Physics/MovementSystem.hpp>
#include <Engine/Physics/RotateBoxCollider2D.hpp>
#include <Engine/Physics/OBBCollisionSystem.hpp>

#include <Engine/Rendering/RenderSystem.hpp>
#include <Engine/Rendering/DrawBoxColliderSystem.hpp>
#include <Engine/Rendering/DrawGameComponentSystem.hpp>

#include <Gameplay/Patrol/PatrolSystem.hpp>
#include <Gameplay/LifeSpan/LifeSpanSystem.hpp>

#include <Gameplay/Player/InputSystem.hpp>
#include <Gameplay/Player/HandlePlayerInputSystem.hpp>
#include <Gameplay/Player/PlayerRespawnSystem.hpp>
#include <Gameplay/Player/PlayerStateSystem.hpp>

#include <Gameplay/Stomp/StompSystem.hpp>
#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Gameplay/Block/BounceBlockSystem.hpp>
#include <Gameplay/DamageOnContact/DamageOnContactSystem.hpp>
#include <Gameplay/Invincible/InvincibleSystem.hpp>

#include <Gameplay/Item/ItemEmergingSystem.hpp>
#include <Gameplay/Item/CoinJumpingSystem.hpp>
#include <Gameplay/Item/DebrisSystem.hpp>
#include <Gameplay/Item/StarJumpingSystem.hpp>
#include <Gameplay/Item/FireBulletSystem.hpp>

#include <Gameplay/Collect/CollectSystem.hpp>
#include <Gameplay/Collect/CollectMushroomSystem.hpp>
#include <Gameplay/Collect/CollectFlowerSystem.hpp>
#include <Gameplay/Collect/CollectStarSystem.hpp>

#include <Gameplay/Fire/FireSystem.hpp>
#include <Gameplay/Tele/TeleSystem.hpp>

#include <Gameplay/CaptureFlag/CaptureFlagSystem.hpp>

#include <Gameplay/Enemy/EnemyStateSystem.hpp>
#include <Gameplay/Enemy/EnemyBehaviourSystem.hpp>
#include <Gameplay/Enemy/Koopa/Koopa.hpp>
#include <Gameplay/Enemy/Goomba/Goomba.hpp>
#include <Gameplay/Enemy/Koopa/KoopaJumping.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlying.hpp>
#include <Gameplay/Enemy/Piranha/Piranha.hpp>
#include <Gameplay/Enemy/Spiny/Spiny.hpp>
#include <Gameplay/Enemy/Lakitu/Lakitu.hpp>
#include <Gameplay/Enemy/Bowser/Bowser.hpp>
#include <Gameplay/Enemy/EnemyScoreSystem.hpp>

#include <Gameplay/GameProperties/PlayTimeSystem.hpp>
#include <Gameplay/GameProperties/TextPoppingSystem.hpp>

#include <Gameplay/Background/FlagPoleSystem.hpp>
#include <Gameplay/Background/LevelCompletionSystem.hpp>
#include <Gameplay/Background/BridgeSystem.hpp>
#include <Gameplay/Background/ElevatorSystem.hpp>
#include <Gameplay/Background/ElevatorCollisionSystem.hpp>
#include <Gameplay/Obstacles/PodobooSystem.hpp>
#include <Gameplay/Obstacles/FireBarSystem.hpp>

#include <cassert>
#include <iostream>
#include <fstream>

#include <Serialize.hpp>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


GameManager::GameManager(int level) : levelHandler(world, level), level(level)
{
    bool loadFromJSON = true;
    loadFromJSON = false;

    if (loadFromJSON)
    {
        // std::ifstream fin("data.json");
        // json j = json::parse(fin);

        world.loadSceneFromFile("data.json");
    }
    else
    {
        levelHandler.start();
        world.createEntity()->addComponent<Camera>();
    }


    world.addSystem<PlayTimeSystem>();
    world.addSystem<GravitySystem>();
    world.addSystem<MovementSystem>();

    world.addSystem<RotateBoxCollider2D>();
    world.addSystem<CollisionDetectionSystem>();
    // world.addSystem<OBBCollisionSystem>();
    world.addSystem<HitBlockSystem>();
    world.addSystem<ElevatorCollisionSystem>();

    world.addSystem<InputSystem>();
    world.addSystem<HandlePlayerInputSystem>();
    world.addSystem<PlayerStateSystem>();

    world.addSystem<CameraSystem>();
    world.addSystem<AnimationSystem>();
    world.addSystem<RenderSystem>();
    world.addSystem<DrawBoxColliderSystem>();
    world.addSystem<DrawGameComponentSystem>();

    world.addSystem<LifeSystem>();

    world.addSystem<PatrolSystem>();
    world.addSystem<StompSystem>();
    world.addSystem<HitSpecialBlockSystem>();

    world.addSystem<TeleSystem>();
    world.addSystem<CollectSystem>();
    world.addSystem<CollectMushroomSystem>();
    world.addSystem<CollectFlowerSystem>();
    world.addSystem<CollectStarSystem>();

    world.addSystem<CaptureFlagSystem>();
    world.addSystem<BridgeSystem>();
    world.addSystem<ElevatorSystem>();

    world.addSystem<ItemEmergingSystem>();
    world.addSystem<CoinJumpingSystem>();
    world.addSystem<DebrisSystem>();
    world.addSystem<StarJumpingSystem>();
    world.addSystem<FireSystem>();
    world.addSystem<FireBulletSystem>();
    world.addSystem<FireBarSystem>();
    world.addSystem<PodobooSystem>();
    world.addSystem<BounceBlockSystem>();

    world.addSystem<FlagPoleCollisionSystem>();
    world.addSystem<LevelCompletionSystem>();

    world.addSystem<TextPoppingSystem>();

    world.addSystem<DamageOnContactSystem>();

    world.addSystem<InvincibleSystem>();

    world.addSystem<EnemyStateSystem>();
    world.addSystem<EnemyBehaviourSystem>();
    world.addSystem<EnemyScoreSystem>();
    
    world.addSystem<DespawnSystem>();
    world.addSystem<PlayerRespawnSystem>();

}

void GameManager::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::S)
        {
            json j;
            world.saveToJSON(j);

            std::ofstream fout("save.json");
            fout << j.dump(4);
            fout.close();    
        }

        if (event.key.code == sf::Keyboard::N)
        {
            world.findFirst<PlayerTag>()->addComponent<InvincibleTag>(3.0f);
        }

        if (event.key.code == sf::Keyboard::X)
        {
            std::cout << "HELLO\n";
            auto lakitu = world.createEntity<Lakitu>(20 * 16, 3 * 16, 3);
        }

        if (event.key.code == sf::Keyboard::B)
        {
            std::cout << "HELLO\n";
            auto bowser = world.createEntity<Bowser>(10 * 16, 3 * 16, 3);
        }

        if (event.key.code == sf::Keyboard::T)
        {
            auto goomba = world.createEntity<Goomba>(7 * 16, 2 * 16, 3);
        }

        if (event.key.code == sf::Keyboard::P)
        {
            oneFrame = !oneFrame;
        }

        if (event.key.code == sf::Keyboard::O)
        {
            shouldPlay = true;
        }
    }
}

void GameManager::update(float dt)
{
    if (oneFrame && !shouldPlay)
        return;

    // std::cout << 1.0f / dt << "\n";
    world.update(dt);

    if (oneFrame)
    {
        shouldPlay = false;
    }

    world.showSceneEditor();
}

void GameManager::draw(sf::RenderWindow &window, int level) const
{
    // Set the custom view
    world.getSystem<RenderSystem>()->draw(world, window, level);

    // Drawn with custom view
    world.getSystem<DrawBoxColliderSystem>()->draw(world, window);

    // Set the default view
    world.getSystem<DrawGameComponentSystem>()->draw(world, window);
}