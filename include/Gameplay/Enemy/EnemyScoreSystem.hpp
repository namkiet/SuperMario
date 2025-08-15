#pragma once
#include <World.hpp>
#include <Prefabs/Coin.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <ScoreManager.hpp>

class EnemyScoreSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *enemy : world.findAll<Transform, ShouldUpdateScore>())
        {
            auto &pos = enemy->getComponent<Transform>().position;
            auto &scoreComponent = enemy->getComponent<ShouldUpdateScore>();

            // Update the score
            ScoreManager::instance().addScore(scoreComponent.score);

            // Create a text popping at the enemy's position
            Entity *scoreTextEntity = world.createEntity();
            std::string scoreText = std::to_string(scoreComponent.score);
            scoreTextEntity->addComponent<TextComponent>(scoreText, pos.x, pos.y, pos.y - 48, 15.0f, 1);

            // Remove the score tag
            enemy->removeComponent<ShouldUpdateScore>();
        }
    }
};