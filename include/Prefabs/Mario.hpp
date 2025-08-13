#pragma once
#include <ECS/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Rendering/ZIndex.hpp>
#include <Engine/Camera/FollowByCameraTag.hpp>

#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Fire/Components.hpp>
#include <Gameplay/BreakBrick/Components.hpp>
#include <Gameplay/CaptureFlag/Components.hpp>

#include <Gameplay/Player/PlayerMovementStates/PlayerIdlingState.hpp>
#include <Gameplay/Player/PlayerSizeStates/PlayerSmallState.hpp>
#include <Gameplay/Player/PlayerPowerStates/PlayerNormalState.hpp>

#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Mario : public Entity
{
public:
    Mario(float x, float y, float width, float height, int scale, int currentLevel)
    {
        addComponent<Animation>(TextureManager::load("assets/Player/SmallPlayer/marioSmall_0.png"));
        addComponent<ZIndex>(-1);

        addComponent<FollowByCameraTag>();

        // Set the size of the collision box for the player
        addComponent<BoxCollider2D>(sf::Vector2f((width - 4) * scale, height * scale), sf::Vector2f(2 * scale, 0));

        addComponent<PlayerTag>(std::make_shared<PlayerIdlingState>(), std::make_shared<PlayerSmallState>(), std::make_shared<PlayerNormalState>());

        // Set the rigid body for the player
        addComponent<RigidBody>(sf::Vector2f(0, 0));

        // Set the transform for the player
        addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width * scale, height * scale));

        addComponent<StomperTag>();

        // Able to get damage
        addComponent<CanGetDamageTag>();

        // Able to collect items
        addComponent<CanCollectTag>();

        addComponent<InputTag>();

        addComponent<CanHitBlockTag>();

        addComponent<ScoreComponent>();

        addComponent<TimeComponent>(400);

        addComponent<CoinComponent>();

        addComponent<FireCooldown>();

        addComponent<CanCaptureFlagTag>();

        this->currentLevel = currentLevel;
    }
    static int currentLevel;
};

inline int Mario::currentLevel = 1; // Initialize currentLevel to 1