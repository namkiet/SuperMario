#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Goomba/Components.hpp>
#include <Gameplay/Enemy/Goomba/GoombaFlippedState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>

void GoombaFlippedState::onEnter(Entity* entity)
{
    entity->addComponent<PassThroughTag>();
    entity->removeComponent<CanHitBlockTag>();

    if (entity->hasComponent<Animation>()) 
    {
        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Goomba/goomba_flipped.png"));
        anim.frameWidth = 16;
        anim.frameHeight = 16;
        anim.frameCount = 2;
        anim.frameDuration = 0.25f;
        anim.currentFrame = 0;
        anim.timer = 0;
    }
    
    entity->getComponent<RigidBody>().velocity.y = -300;
    entity->getComponent<GoombaPatrol>().velocity = sf::Vector2f(0, 0);

    entity->removeComponent<BlockTag>();
    entity->removeComponent<CanHitBlockTag>();
    entity->removeComponent<StompableTag>();
    entity->removeComponent<DamageOnContactComponent>();
}

std::shared_ptr<EnemyState> GoombaFlippedState::getNewState(Entity* entity, float dt)
{
    return nullptr;
}