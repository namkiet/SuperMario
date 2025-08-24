#pragma once
#include <Entity/Entity.hpp>

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
#include <Gameplay/CaptureFlag/Components.hpp>

#include <Gameplay/Player/PlayerMovementStates/PlayerIdlingState.hpp>
#include <Gameplay/Player/PlayerSizeStates/PlayerSmallState.hpp>
#include <Gameplay/Player/PlayerPowerStates/PlayerNormalState.hpp>

#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Character : public Entity
{
public:
    Character(float x, float y, float width, float height, float scale)
    {
        addComponent<ZIndex>(-1);
        addComponent<FollowByCameraTag>();
        addComponent<BoxCollider2D>(sf::Vector2f((width - 4) * scale, height * scale), sf::Vector2f(2 * scale, 0));
        addComponent<RigidBody>(sf::Vector2f(0, 0));
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height) * scale);
        addComponent<StomperTag>();
        addComponent<CanGetDamageTag>();
        addComponent<CanCollectTag>();
        addComponent<InputTag>();
        addComponent<CanHitBlockTag>();
        addComponent<FireCooldown>();
        addComponent<CanCaptureFlagTag>();
    }
};