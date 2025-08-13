#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/EnemyState.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Goomba/Components.hpp>
#include <Gameplay/Enemy/Goomba/GoombaStompedState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>

void GoombaStompedState::onEnter(Entity* entity)
{
    entity->addComponent<LifeSpan>(0.3f);

    // if (entity->hasComponent<Animation>()) 
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Goomba/goomba_stomped.png"));
    //     anim.frameWidth = 16;
    //     anim.frameHeight = 16;
    //     anim.frameCount = 1;
    //     anim.frameDuration = 0.0f;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("goomba_stomped"), 16, 16, 1, 0);

    entity->getComponent<GoombaPatrol>().velocity = sf::Vector2f(0, 0);

    entity->removeComponent<StompableTag>();
    entity->removeComponent<DamageOnContactComponent>();

    // Add score tag to notify the score system
    entity->addComponent<ShouldUpdateScore>(100);
}

std::shared_ptr<EnemyState> GoombaStompedState::getNewState(Entity* entity, float dt)
{
    return nullptr;
}