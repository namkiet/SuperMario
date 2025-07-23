#pragma once
#include <ECS/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Camera/FollowByCameraTag.hpp>

#include <Gameplay/Player/Components.hpp>
#include <Gameplay/HitBlock/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/Fire/Components.hpp>
#include <Gameplay/BreakBrick/Components.hpp>

#include <PlayerMovementStates/PlayerIdlingState.hpp>
#include <PlayerPowerStates/PlayerSmallState.hpp>

#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Mario : public Entity
{
public:
    Mario(float x, float y, float width, float height, int scale)
    {
// <<<<<<< HEAD
//         addComponent<Animation>(TextureManager::load("assets/Mario/mario_idling_small.png"));
// =======
        // Get the textures for the player
        addComponent<Animation>(TextureManager::load("assets/Player/SmallPlayer/marioSmall_0.png"));

        //
        addComponent<FollowByCameraTag>();

        // Set the size of the collision box for the player
        addComponent<BoxCollider2D>(sf::Vector2f(width * scale, height * scale));

        addComponent<PlayerTag>(std::make_shared<PlayerIdlingState>(), std::make_shared<PlayerSmallState>());

        // Set the rigid body for the player
        addComponent<RigidBody>(sf::Vector2f(0, 0));

        // Set the transform for the player
        addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width * scale, height * scale));

        addComponent<StomperTag>();
        addComponent<CanHitQuestionBlockTag>();
        addComponent<CanHitNormalBlockTag>();
        addComponent<CanGetDamageTag>();
// <<<<<<< HEAD
//         addComponent<CanHitBlockTag>();
// =======
        addComponent<CanCollectTag>();
        addComponent<CanHit1UpBlockTag>();
        addComponent<CanHitStarBlockTag>();
        addComponent<CanHitCoinBlockTag>();
        addComponent<InputTag>();
        addComponent<CanFireTag>();
    }
};