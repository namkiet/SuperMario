#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Camera/FollowByCameraTag.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/HitQuestionBlock/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Mario : public Entity
{
public:
    Mario(float x, float y)
    {
        addComponent<Animation>(TextureManager::load("assets/mario_idling.png"));
        addComponent<FollowByCameraTag>();

        addComponent<BoxCollider2D>(SIZE::MARIO);
        addComponent<RigidBody>(sf::Vector2f(0, 0));
        addComponent<Transform>(sf::Vector2f(x, y), SIZE::MARIO);

        addComponent<PlayerTag>(std::make_shared<PlayerIdlingState>());
        
        addComponent<StomperTag>();
        addComponent<CanHitQuestionBlockTag>();
        addComponent<CanGetDamageTag>();
        addComponent<InputTag>();
    }
};