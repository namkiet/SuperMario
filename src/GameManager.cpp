#include <GameManager.hpp>

#include <Engine/Camera/CameraSystem.hpp>
#include <Engine/Core/DespawnSystem.hpp>

#include <Engine/Physics/CollisionDetectionSystem.hpp>
#include <Engine/Physics/HitBlockSystem.hpp>
#include <Engine/Physics/GravitySystem.hpp>
#include <Engine/Physics/MovementSystem.hpp>
#include <Engine/Physics/RotateBoxCollider2D.hpp>

#include <Engine/Animation/AnimationSystem.hpp>
#include <Engine/Animation/BlinkSystem.hpp>
#include <Engine/Rendering/RenderSystem.hpp>
#include <Engine/Rendering/DrawBoxColliderSystem.hpp>
#include <Engine/Rendering/DrawGameComponentSystem.hpp>
#include <Engine/Rendering/DrawTextSystem.hpp>

#include <Engine/Audio/SoundSystem.hpp>

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
#include <Gameplay/Enemy/EnemyScoreSystem.hpp>
#include <Gameplay/Enemy/EnemyStateSystem.hpp>
#include <Gameplay/Enemy/EnemyBehaviourSystem.hpp>

#include <ScoreManager.hpp>
#include <TimeManager.hpp>
#include <LevelManager.hpp>

#include <Gameplay/GameProperties/PlayTimeSystem.hpp>
#include <Gameplay/GameProperties/TextPoppingSystem.hpp>

#include <Gameplay/Background/LevelCompletionSystem.hpp>
#include <Gameplay/Background/BridgeSystem.hpp>
#include <Gameplay/Background/ElevatorSystem.hpp>
#include <Gameplay/Obstacles/PodobooSystem.hpp>
#include <Gameplay/Obstacles/FireBarSystem.hpp>

#include <Engine/Audio/SoundManager.hpp>

#include <cassert>
#include <iostream>
#include <fstream>

// #include <Serialization/ComponentMeta.hpp>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

GameManager::GameManager(int level, bool hasWonLastLevel, bool shouldContinue) : levelHandler(world, level), currentLevel(level)
{
    MessageBus::subscribe("GameSaved", this, [this](const std::string &)
                          {
        json j;
        j["level"] = currentLevel;
        j["lives"] = lives;
        world.saveSceneToFile(j["entities"]);  
        std::ofstream fout("save.json");
        fout << j.dump(4); });

    MessageBus::subscribe("GamePaused", this, [this](const std::string &)
                          { std::cout << "Paused\n"; isPaused = true; });
    MessageBus::subscribe("GameResumed", this, [this](const std::string &)
                          { isPaused = false; });

    if (shouldContinue)
    {
        std::ifstream fin("save.json");
        json j;
        fin >> j;
        // currentLevel = j["level"];

        lives = j["lives"];

        world.entityManager.removeAllEntities();
        world.loadSceneFromFile(j["entities"]);
    }
    else
    {
        levelHandler.start();
        world.createEntity()->addComponent<Camera>();
    }

    world.addSystem<PlayTimeSystem>();

    world.addSystem<InputSystem>();
    world.addSystem<HandlePlayerInputSystem>();

    world.addSystem<GravitySystem>();
    world.addSystem<MovementSystem>();

    world.addSystem<BounceBlockSystem>();

    world.addSystem<RotateBoxCollider2D>();
    world.addSystem<CollisionDetectionSystem>();
    world.addSystem<HitBlockSystem>();

    world.addSystem<PlayerStateSystem>();

    world.addSystem<SoundSystem>();
    world.addSystem<CameraSystem>();

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

    world.addSystem<LevelCompletionSystem>();

    world.addSystem<TextPoppingSystem>();

    world.addSystem<DamageOnContactSystem>();

    world.addSystem<EnemyStateSystem>();
    world.addSystem<EnemyBehaviourSystem>();
    world.addSystem<EnemyScoreSystem>();

    world.addSystem<AnimationSystem>(); // Animation must be the last one to receive all animation updates
    world.addSystem<BlinkSystem>();
    world.addSystem<RenderSystem>();
    world.addSystem<DrawBoxColliderSystem>();
    world.addSystem<DrawTextSystem>();
    world.addSystem<DrawGameComponentSystem>();

    world.addSystem<DespawnSystem>();
    world.addSystem<PlayerRespawnSystem>();
    
    if (hasWonLastLevel)
    {
        auto player = world.findFirst<PlayerTag>();
        auto tf = player->getComponent<Transform>();
        world.componentRegistry.loadComponents(prevMarioData, player);
        player->getComponent<Transform>().position = tf.position;
        player->getComponent<Transform>().position.y -= (player->getComponent<Transform>().size.y - tf.size.y);
    }
    else if (level != 0)
    {
        auto player = world.findFirst<PlayerTag, Transform>();
        if (player)
        {
            // Store the original initial position of the player
            auto oriPos = player->getComponent<Transform>().position;
            auto tf = player->getComponent<Transform>();

            // Get the previous Mario position from LevelManager
            auto &pos = LevelManager::instance().getPrevMarioPosition();

            // Load checkpoints from LevelHandler
            std::vector<sf::Vector2f> checkpoints = LevelHandler::getCheckPointPos();

            sf::Vector2f nearestCheckPoint = oriPos;

            for (const auto &checkPointPos : checkpoints)
            {
                if (checkPointPos.x > nearestCheckPoint.x && checkPointPos.x <= pos.x && pos.x > 0)
                {
                    nearestCheckPoint = checkPointPos;
                }
            }

            player->getComponent<Transform>().position = nearestCheckPoint;
        }
    }
    else if (level == 0)
    {
        auto player = world.findFirst<PlayerTag, FollowByCameraTag>();
        if (player)
        {
            player->removeComponent<FollowByCameraTag>();
        }
    }
}

void GameManager::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // if (event.key.code == sf::Keyboard::S)
        // {
        //     std::ifstream fin("save.json");
        //     json j;
        //     fin >> j;
        //     currentLevel = j["level"];

        //     world.entityManager.removeAllEntities();
        //     world.loadSceneFromFile(j["entities"]);
        // }

        if (event.key.code == sf::Keyboard::N)
        {
            world.findFirst<PlayerTag>()->addComponent<InvincibleTag>(500.0f);
        }

        if (event.key.code == sf::Keyboard::T)
        {
            world.findFirst<PlayerTag, Transform>()->getComponent<Transform>().position.x = 195 * 48;
        }

        if (event.key.code == sf::Keyboard::F)
        {
            // do nothing

            auto mario = world.findFirst<PlayerTag>();
            mario->addComponent<GrowUpTag>();
            mario->addComponent<CanFireTag>();
        }

        if (event.key.code == sf::Keyboard::P)
        {
            oneFrame = !oneFrame;

            if (editor)
            {
                delete editor;
                editor = nullptr;
            }
            else
            {
                editor = new Editor(world);
            }
        }

        if (event.key.code == sf::Keyboard::O)
        {
            shouldPlay = true;
        }
    }

    if (editor)
        editor->handleEvent(event, window);
}

void GameManager::update(float dt)
{
    if (dt > 0.5f)
        return;

    if (isPaused)
        return;

    if (oneFrame && !shouldPlay)
    {
        world.getSystem<CollisionDetectionSystem>()->update(world, dt);
        world.getSystem<AnimationSystem>()->update(world, dt);
        // world.getSystem<HitBlockSystem>()->update(world, dt);
        // world.getSystem<MovementSystem>()->update(world, dt);
        return;
    }

    // std::cout << 1.0f / dt << "\n";
    world.update(dt);

    if (oneFrame)
    {
        shouldPlay = false;
    }

    // std::cout << level << "\n";
}

void GameManager::draw(sf::RenderWindow &window, int level)
{
    // Set the custom view
    world.getSystem<RenderSystem>()->draw(world, window, currentLevel);

    if (level == 0)
        return;

    if (editor)
    {
        editor->drawUI();
        editor->display(window);

        // Drawn with custom view
        world.getSystem<DrawBoxColliderSystem>()->draw(world, window);
    }

    // Drawn with custiom view
    world.getSystem<DrawTextSystem>()->draw(world, window);

    // Set the default view
    world.getSystem<DrawGameComponentSystem>()->draw(world, window);
}

int GameManager::lives = 5;

int GameManager::getLives()
{
    return lives;
}

GameManager::~GameManager()
{
    MessageBus::unsubscribe("GameSaved", this);
    MessageBus::unsubscribe("GamePaused", this);
    MessageBus::unsubscribe("GameResumed", this);
    if (auto player = world.findFirst<PlayerTag>())
    {
        world.componentRegistry.saveComponents(player, prevMarioData);
    }
    --lives;
}

void GameManager::setLives(int newLives)
{
    lives = newLives;
}

json &GameManager::getPrevMarioData()
{
    return prevMarioData;
}