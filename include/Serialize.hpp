#include <jsonSFML.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/DespawnTag.hpp>

DEFINE_COMPONENT(Transform, position, prevPos, size, isFacingRight)
DEFINE_COMPONENT(RigidBody, velocity, acceleration, applyGravity, onGround)
DEFINE_TAG(DespawnTag)


#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/PassThroughTag.hpp>

DEFINE_COMPONENT(BoxCollider2D, isDisabled, size, offset)
DEFINE_TAG(CanHitBlockTag)
DEFINE_TAG(BlockTag)
DEFINE_TAG(PipeTag)
DEFINE_TAG(PassThroughTag)


#include <Engine/Camera/Camera.hpp>
#include <Engine/Camera/FollowByCameraTag.hpp>

DEFINE_COMPONENT(Camera, target)
DEFINE_TAG(FollowByCameraTag)

#include <Core/TextureManager.hpp>
#include <Engine/Animation/Animation.hpp>

DEFINE_COMPONENT(Animation, frameWidth, frameHeight, frameCount, frameDuration, currentFrame, timer, loop, row, hasEnded, zIndex, textures)

#include <Gameplay/Player/Components.hpp>
#include <PlayerMovementStates/PlayerIdlingState.hpp>
#include <PlayerMovementStates/PlayerRunningState.hpp>
#include <PlayerMovementStates/PlayerJumpingState.hpp>
#include <PlayerPowerStates/PlayerBigState.hpp>
#include <PlayerPowerStates/PlayerSmallState.hpp>
#include <PlayerPowerStates/PlayerFireState.hpp>
#include <PlayerPowerStates/PlayerGrowingUpState.hpp>

REGISTER_COMPONENT(PlayerTag) // need a better way to store states

inline void to_json(json& j, const PlayerTag& tag)
{
    std::string movementState = tag.movementState ? tag.movementState->getName() : "";
    std::string powerState = tag.powerState ? tag.powerState->getName() : "";
    j["movementState"] = movementState;
    j["powerState"] = powerState;
}

inline void from_json(const json& j, PlayerTag& tag)
{
    std::string movementState = j["movementState"];
    std::string powerState = j["powerState"];

    if (movementState == "Idling")
        tag.movementState = std::make_shared<PlayerIdlingState>();
    else if (movementState == "Running")
        tag.movementState = std::make_shared<PlayerRunningState>();
    else
        tag.movementState = std::make_shared<PlayerJumpingState>();

    if (powerState == "Small")
        tag.powerState = std::make_shared<PlayerSmallState>();
    else if (powerState == "Big")
        tag.powerState = std::make_shared<PlayerBigState>();
    else if (powerState == "Fire")
        tag.powerState = std::make_shared<PlayerFireState>();
    else
        tag.powerState = std::make_shared<PlayerGrowingUpState>();
}

DEFINE_TAG(BigMarioTag)
DEFINE_TAG(FireMarioTag)
DEFINE_TAG(GrowUpTag)
DEFINE_TAG(InputTag)


#include <Gameplay/Block/Components.hpp>

DEFINE_TAG(CoinBlock)
DEFINE_TAG(GroundBlock)
DEFINE_TAG(LevelUpBlock)
DEFINE_TAG(NormalBlock)
DEFINE_TAG(StairsBlock)
DEFINE_TAG(StarBlock)
DEFINE_TAG(CoinQuestionBlock)
DEFINE_TAG(FlowerQuestionBlock)
DEFINE_TAG(MushroomQuestionBlock)
DEFINE_TAG(StarQuestionBlock)
DEFINE_TAG(FlagBlock)
DEFINE_TAG(QuestionBlockTag)
DEFINE_COMPONENT(CoinBlockComponent, waitingTime, timer, hitCount, isCollected, firstTime)
DEFINE_TAG(MushroomBlock)

#include <Gameplay/Collect/Components.hpp>

DEFINE_TAG(CollectableTag)
DEFINE_TAG(CanCollectTag)


#include <Gameplay/Item/Components.hpp>

DEFINE_TAG(Coin1Tag)
DEFINE_TAG(DebrisTag)
DEFINE_TAG(Debris1Tag)
DEFINE_TAG(Debris2Tag)
DEFINE_TAG(Debris3Tag)
DEFINE_TAG(Debris4Tag)
DEFINE_TAG(StarTag)
DEFINE_TAG(MushroomTag) // needs BUFF component
DEFINE_TAG(FlowerTag)
DEFINE_TAG(FireBulletTag)
DEFINE_TAG(SmallCoinTag)
DEFINE_TAG(Coin2Tag)
DEFINE_COMPONENT(FireworkComponent, fireworksLeft)



#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Goomba/GoombaNormalState.hpp>
#include <Gameplay/Enemy/Goomba/GoombaBehaviour.hpp>

REGISTER_COMPONENT(EnemyTag)

inline void to_json(json& j, const EnemyTag& tag)
{
    j["state"] = "GoombaNormalState";
    j["behaviour"] = "GoombaBehaviour";
}

inline void from_json(const json& j, EnemyTag& tag)
{
    std::string state = j["state"];
    std::string behaviour = j["behaviour"];

    tag.state = std::make_shared<GoombaNormalState>();
    tag.behaviour = std::make_shared<GoombaBehaviour>();
}

DEFINE_TAG(TowardPlayer) // needs direction
DEFINE_TAG(CanKillEnemyTag)
DEFINE_TAG(NotOnPatrolYet)
DEFINE_TAG(ScoreAddedTag)


#include <Gameplay/Enemy/Goomba/Components.hpp>

DEFINE_TAG(ChangeToGoombaNormalTag)
DEFINE_TAG(ChangeToGoombaFlippedTag)
DEFINE_TAG(ChangeToGoombaStompedTag)
DEFINE_COMPONENT(GoombaPatrol, velocity)