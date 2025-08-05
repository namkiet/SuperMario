#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Spiny/Components.hpp>
#include <Gameplay/Enemy/Spiny/SpinyFlippedState.hpp>
#include <Gameplay/Enemy/Spiny/SpinyFlippedBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>

void SpinyFlippedState::onEnter(Entity* entity)
{
    entity->addComponent<PassThroughTag>();

    if (entity->hasComponent<Animation>()) 
    {
        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Spiny/spiny_flipped.png"));
        anim.frameWidth = 16;
        anim.frameHeight = 14;
        anim.frameCount = 1;
        anim.frameDuration = 0.25f;
        anim.currentFrame = 0;
        anim.timer = 0;
    }

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<SpinyFlippedBehaviour>();
    
    entity->getComponent<RigidBody>().velocity.y = -600;
    entity->getComponent<SpinyPatrol>().velocity = sf::Vector2f(0, 0);

    entity->removeComponent<BlockTag>();
    entity->removeComponent<CanHitBlockTag>();
    entity->removeComponent<DamageOnContactComponent>();
}

std::shared_ptr<EnemyState> SpinyFlippedState::getNewState(Entity* entity, float dt)
{
    return nullptr;
}