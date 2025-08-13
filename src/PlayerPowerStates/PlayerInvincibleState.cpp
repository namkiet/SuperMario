#include <Gameplay/Player/PlayerPowerStates/PlayerInvincibleState.hpp>
#include <Gameplay/Player/PlayerPowerStates/PlayerNormalState.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerInvincibleState::getName() const
{
    return "Invincible";
}

void PlayerInvincibleState::onEnter(Entity* player)
{
    player->addComponent<CanKillEnemyTag>();
    player->removeComponent<CanGetDamageTag>();
}

void PlayerInvincibleState::onExit(Entity* player)
{
    player->removeComponent<CanKillEnemyTag>();
    player->addComponent<CanGetDamageTag>();
}

void PlayerInvincibleState::update(Entity* player, float dt)
{
    if (!player->hasComponent<InvincibleTag>()) return;

    auto& invincible = player->getComponent<InvincibleTag>();
    invincible.timer += dt;
    if (invincible.timer >= invincible.duration)
    {
        player->removeComponent<InvincibleTag>();
    }
}

std::shared_ptr<PlayerPowerState> PlayerInvincibleState::getNewState(Entity* player)
{
    if (!player->hasComponent<InvincibleTag>()) 
    {
        return std::make_shared<PlayerNormalState>();
    }

    return nullptr;
}