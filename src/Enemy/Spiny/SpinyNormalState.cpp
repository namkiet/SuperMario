#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Spiny/Components.hpp>
#include <Gameplay/Enemy/Spiny/SpinyNormalState.hpp>
#include <Gameplay/Enemy/Spiny/SpinyFlippedState.hpp>
#include <Gameplay/Enemy/Spiny/SpinyNormalBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>

void SpinyNormalState::onEnter(Entity* entity)
{
    // if (entity->hasComponent<Animation>()) 
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Spiny/spiny_walk.png"));
    //     anim.frameWidth = 16;
    //     anim.frameHeight = 14;
    //     anim.frameCount = 2;
    //     anim.frameDuration = 0.25f;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(Animation(TextureManager::load("assets/Enemy/Spiny/spiny_walk.png"), 16, 14, 2, 0.25f));

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<SpinyNormalBehaviour>();

    entity->getComponent<Transform>().size = sf::Vector2f(16, 14) * 3.0f;
    entity->getComponent<BoxCollider2D>().size = sf::Vector2f(16, 14) * 3.0f;
    
    auto& patrol = entity->getComponent<SpinyPatrol>();
    patrol.velocity.x = 60 * (patrol.velocity.x > 0 ? 1 : -1);
}

std::shared_ptr<EnemyState> SpinyNormalState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToSpinyFlippedTag>())
    {
        entity->removeComponent<ChangeToSpinyFlippedTag>();
        return std::make_shared<SpinyFlippedState>();
    }

    return nullptr;
}