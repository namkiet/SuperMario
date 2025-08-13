#include <jsonSFML.hpp>
#include <RegisterStates.hpp>

#include <Gameplay/Obstacles/Components.hpp>

REGISTER_COMPONENT(PodobooTag)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PodobooTag, upright, lowestY, highestY)

REGISTER_COMPONENT(FireBarComponent)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FireBarComponent, angle, isClockwise)

#include <Gameplay/Background/Components.hpp>

REGISTER_COMPONENT(Castle)
DEFINE_TAG(Castle)

REGISTER_COMPONENT(FlagPole)
DEFINE_TAG(FlagPole)

REGISTER_COMPONENT(Flag)
DEFINE_TAG(Flag)

REGISTER_COMPONENT(CastleFlag)
DEFINE_TAG(CastleFlag)

REGISTER_COMPONENT(BellTag)
DEFINE_TAG(BellTag)

REGISTER_COMPONENT(BridgeTileTag)
DEFINE_TAG(BridgeTileTag)

REGISTER_COMPONENT(ElevatorComponent)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ElevatorComponent, isHorizontal, minX, maxX, minY, maxY)

REGISTER_COMPONENT(Princess)
DEFINE_TAG(Princess)

#include <Gameplay/Collect/Components.hpp>

REGISTER_COMPONENT(CollectableTag)
DEFINE_TAG(CollectableTag)

REGISTER_COMPONENT(CanCollectTag)
DEFINE_TAG(CanCollectTag)

#include <Gameplay/Pipe/Components.hpp>

REGISTER_COMPONENT(enterablePipe)
DEFINE_TAG(enterablePipe)

REGISTER_COMPONENT(unenterablePipe)
DEFINE_TAG(unenterablePipe)

#include <Gameplay/Enemy/Spiny/Components.hpp>

REGISTER_COMPONENT(ChangeToSpinyNormalTag)
DEFINE_TAG(ChangeToSpinyNormalTag)

REGISTER_COMPONENT(ChangeToSpinyFlippedTag)
DEFINE_TAG(ChangeToSpinyFlippedTag)

REGISTER_COMPONENT(SpinyPatrol)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SpinyPatrol, velocity)

#include <Gameplay/Enemy/Lakitu/Components.hpp>

REGISTER_COMPONENT(ChangeToLakituFlippedTag)
DEFINE_TAG(ChangeToLakituFlippedTag)

REGISTER_COMPONENT(LakituPatrol)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LakituPatrol, distance, fastSpeed, accelerate, phase, velocity, lastDirection, freeTarget, limitX)

REGISTER_COMPONENT(LakituAttack)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LakituAttack, distance, delay, timer)

#include <Gameplay/Enemy/Components.hpp>

REGISTER_COMPONENT(EnemyTag)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EnemyTag, state, behaviour)

REGISTER_COMPONENT(TowardPlayer)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TowardPlayer, direction)

REGISTER_COMPONENT(CanKillEnemyTag)
DEFINE_TAG(CanKillEnemyTag)

REGISTER_COMPONENT(NotOnPatrolYet)
DEFINE_TAG(NotOnPatrolYet)

REGISTER_COMPONENT(ScoreAddedTag)
DEFINE_TAG(ScoreAddedTag)

#include <Gameplay/Enemy/Koopa/Components.hpp>

REGISTER_COMPONENT(KoopaTag)
DEFINE_TAG(KoopaTag)

REGISTER_COMPONENT(KoopaNormalTag)
DEFINE_TAG(KoopaNormalTag)

REGISTER_COMPONENT(KoopaFlippedTag)
DEFINE_TAG(KoopaFlippedTag)

REGISTER_COMPONENT(KoopaShellTag)
DEFINE_TAG(KoopaShellTag)

REGISTER_COMPONENT(KoopaReviveTag)
DEFINE_TAG(KoopaReviveTag)

REGISTER_COMPONENT(KoopaSlideTag)
DEFINE_TAG(KoopaSlideTag)

REGISTER_COMPONENT(KoopaJumpingTag)
DEFINE_TAG(KoopaJumpingTag)

REGISTER_COMPONENT(KoopaFlyingTag)
DEFINE_TAG(KoopaFlyingTag)

REGISTER_COMPONENT(ChangeToKoopaNormalTag)
DEFINE_TAG(ChangeToKoopaNormalTag)

REGISTER_COMPONENT(ChangeToKoopaFlippedTag)
DEFINE_TAG(ChangeToKoopaFlippedTag)

REGISTER_COMPONENT(ChangeToKoopaShellTag)
DEFINE_TAG(ChangeToKoopaShellTag)

REGISTER_COMPONENT(ChangeToKoopaReviveTag)
DEFINE_TAG(ChangeToKoopaReviveTag)

REGISTER_COMPONENT(ChangeToKoopaSlideTag)
DEFINE_TAG(ChangeToKoopaSlideTag)

REGISTER_COMPONENT(KoopaPatrol)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(KoopaPatrol, velocity, lastDirection)

REGISTER_COMPONENT(KoopaFlyingPatrol)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(KoopaFlyingPatrol, velocity, phaseDuration, timer)

#include <Gameplay/Enemy/Goomba/Components.hpp>

REGISTER_COMPONENT(ChangeToGoombaNormalTag)
DEFINE_TAG(ChangeToGoombaNormalTag)

REGISTER_COMPONENT(ChangeToGoombaFlippedTag)
DEFINE_TAG(ChangeToGoombaFlippedTag)

REGISTER_COMPONENT(ChangeToGoombaStompedTag)
DEFINE_TAG(ChangeToGoombaStompedTag)

REGISTER_COMPONENT(GoombaPatrol)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GoombaPatrol, velocity)

#include <Gameplay/Enemy/Piranha/Components.hpp>

REGISTER_COMPONENT(PiranhaPatrol)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PiranhaPatrol, velocity, maxHeight, minHeight, phaseDuration, delay, timer)

#include <Gameplay/Enemy/Bowser/Components.hpp>

REGISTER_COMPONENT(ChangeToBowserIdleTag)
DEFINE_TAG(ChangeToBowserIdleTag)

REGISTER_COMPONENT(ChangeToBowserWalkTag)
DEFINE_TAG(ChangeToBowserWalkTag)

REGISTER_COMPONENT(ChangeToBowserJumpTag)
DEFINE_TAG(ChangeToBowserJumpTag)

REGISTER_COMPONENT(ChangeToBowserHurtTag)
DEFINE_TAG(ChangeToBowserHurtTag)

REGISTER_COMPONENT(ChangeToBowserSkidTag)
DEFINE_TAG(ChangeToBowserSkidTag)

REGISTER_COMPONENT(ChangeToBowserSlideTag)
DEFINE_TAG(ChangeToBowserSlideTag)

REGISTER_COMPONENT(ChangeToBowserDeadTag)
DEFINE_TAG(ChangeToBowserDeadTag)

REGISTER_COMPONENT(BowserPatrol)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BowserPatrol, safeDist, duration, timerDura, jumpCooldown, timerJump, velocity, accelerate, lastDirection)

REGISTER_COMPONENT(BowserAttack)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BowserAttack, distance, delay, timer, castTime, isShooting)

REGISTER_COMPONENT(StateDuration)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(StateDuration, duration, timer)

#include <Gameplay/Enemy/Bowser/BowserBullet/Components.hpp>

REGISTER_COMPONENT(BowserBulletPatrol)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BowserBulletPatrol, velocity, targetY)

#include <Gameplay/CaptureFlag/Components.hpp>

REGISTER_COMPONENT(CanCaptureFlagTag)
DEFINE_TAG(CanCaptureFlagTag)

REGISTER_COMPONENT(ClimbingOnFlagPoleTag)
DEFINE_TAG(ClimbingOnFlagPoleTag)

REGISTER_COMPONENT(FlagPoleTag)
DEFINE_TAG(FlagPoleTag)

REGISTER_COMPONENT(HoldingTimer)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(HoldingTimer, duration)

#include <Gameplay/GameProperties/Components.hpp>

REGISTER_COMPONENT(ScoreComponent)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ScoreComponent, score)

REGISTER_COMPONENT(TimeComponent)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TimeComponent, timer, subtimer, isPaused, goesFaster, firstTimeReach0, firstTimePause, timeUnitLeft)

REGISTER_COMPONENT(CoinComponent)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CoinComponent, coins)

REGISTER_COMPONENT(TextComponent)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TextComponent, startX, startY, finalY, dy, size, content)

#include <Gameplay/LifeSpan/Components.hpp>

REGISTER_COMPONENT(LifeSpan)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LifeSpan, value)

REGISTER_COMPONENT(Health)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Health, hp)

#include <Gameplay/Fire/Components.hpp>

REGISTER_COMPONENT(CanFireTag)
DEFINE_TAG(CanFireTag)

REGISTER_COMPONENT(FireCooldown)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FireCooldown, timeCount)

REGISTER_COMPONENT(ShootingTag)
DEFINE_TAG(ShootingTag)

#include <Gameplay/Item/ItemEmerging.hpp>

REGISTER_COMPONENT(ItemEmerging)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ItemEmerging, finalY, speedY, finished)

#include <Gameplay/Item/Components.hpp>

REGISTER_COMPONENT(Coin1Tag)
DEFINE_TAG(Coin1Tag)

REGISTER_COMPONENT(DebrisTag)
DEFINE_TAG(DebrisTag)

REGISTER_COMPONENT(Debris1Tag)
DEFINE_TAG(Debris1Tag)

REGISTER_COMPONENT(Debris2Tag)
DEFINE_TAG(Debris2Tag)

REGISTER_COMPONENT(Debris3Tag)
DEFINE_TAG(Debris3Tag)

REGISTER_COMPONENT(Debris4Tag)
DEFINE_TAG(Debris4Tag)

REGISTER_COMPONENT(StarTag)
DEFINE_TAG(StarTag)

REGISTER_COMPONENT(MushroomTag)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MushroomTag, buff)

REGISTER_COMPONENT(FlowerTag)
DEFINE_TAG(FlowerTag)

REGISTER_COMPONENT(FireBulletTag)
DEFINE_TAG(FireBulletTag)

REGISTER_COMPONENT(SmallCoinTag)
DEFINE_TAG(SmallCoinTag)

REGISTER_COMPONENT(Coin2Tag)
DEFINE_TAG(Coin2Tag)

REGISTER_COMPONENT(FireworkComponent)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FireworkComponent, fireworksLeft)

#include <Gameplay/Stomp/Components.hpp>

REGISTER_COMPONENT(StomperTag)
DEFINE_TAG(StomperTag)

REGISTER_COMPONENT(StompableTag)
DEFINE_TAG(StompableTag)

#include <Gameplay/Patrol/Components.hpp>

REGISTER_COMPONENT(PatrolComponent)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PatrolComponent, moveSpeed, isMovingRight)

#include <Gameplay/Tele/Components.hpp>

REGISTER_COMPONENT(TelePort)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TelePort, requireCollisionDirection, intime, inVel, destination)

REGISTER_COMPONENT(hasPipeDestination)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(hasPipeDestination, pipe, OutDirection)

REGISTER_COMPONENT(TeleChanneling)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TeleChanneling, teleInTime, teleEntity)

#include <Gameplay/DamageOnContact/Components.hpp>

REGISTER_COMPONENT(CanGetDamageTag)
DEFINE_TAG(CanGetDamageTag)

REGISTER_COMPONENT(DamageOnContactComponent)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DamageOnContactComponent, validDirections)

REGISTER_COMPONENT(DamagedTag)
DEFINE_TAG(DamagedTag)

#include <Gameplay/Block/BounceBlock.hpp>

REGISTER_COMPONENT(BounceBlock)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BounceBlock, bounceTime, timer, updateY, originalY)

#include <Gameplay/Block/Components.hpp>

REGISTER_COMPONENT(CoinBlock)
DEFINE_TAG(CoinBlock)

REGISTER_COMPONENT(GroundBlock)
DEFINE_TAG(GroundBlock)

REGISTER_COMPONENT(LevelUpBlock)
DEFINE_TAG(LevelUpBlock)

REGISTER_COMPONENT(NormalBlock)
DEFINE_TAG(NormalBlock)

REGISTER_COMPONENT(StairsBlock)
DEFINE_TAG(StairsBlock)

REGISTER_COMPONENT(StarBlock)
DEFINE_TAG(StarBlock)

REGISTER_COMPONENT(CoinQuestionBlock)
DEFINE_TAG(CoinQuestionBlock)

REGISTER_COMPONENT(FlowerQuestionBlock)
DEFINE_TAG(FlowerQuestionBlock)

REGISTER_COMPONENT(MushroomQuestionBlock)
DEFINE_TAG(MushroomQuestionBlock)

REGISTER_COMPONENT(StarQuestionBlock)
DEFINE_TAG(StarQuestionBlock)

REGISTER_COMPONENT(FlagBlock)
DEFINE_TAG(FlagBlock)

REGISTER_COMPONENT(QuestionBlockTag)
DEFINE_TAG(QuestionBlockTag)

REGISTER_COMPONENT(CoinBlockComponent)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CoinBlockComponent, waitingTime, timer, hitCount, isCollected, firstTime)

REGISTER_COMPONENT(MushroomBlock)
DEFINE_TAG(MushroomBlock)

#include <Gameplay/Player/Components.hpp>

REGISTER_COMPONENT(PlayerTag)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlayerTag, movementState, sizeState, powerState)

REGISTER_COMPONENT(BigMarioTag)
DEFINE_TAG(BigMarioTag)

REGISTER_COMPONENT(FireMarioTag)
DEFINE_TAG(FireMarioTag)

REGISTER_COMPONENT(GrowUpTag)
DEFINE_TAG(GrowUpTag)

REGISTER_COMPONENT(InputTag)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(InputTag, horizontalMovement, jumpPressed)

REGISTER_COMPONENT(InvincibleTag)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(InvincibleTag, duration, timer)

#include <Engine/Core/DespawnTag.hpp>

REGISTER_COMPONENT(DespawnTag)
DEFINE_TAG(DespawnTag)

#include <Engine/Core/Transform.hpp>

REGISTER_COMPONENT(Transform)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Transform, prevPos, position, size, isFacingRight)

#include <Engine/Core/RigidBody.hpp>

REGISTER_COMPONENT(RigidBody)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RigidBody, velocity, acceleration, applyGravity, onGround)

#include <Engine/Input/Input.hpp>

REGISTER_COMPONENT(Input)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Input, moveLeft, moveRight, jumpPressed, shootPressed)

#include <Engine/Camera/FollowByCameraTag.hpp>

REGISTER_COMPONENT(FollowByCameraTag)
DEFINE_TAG(FollowByCameraTag)

#include <Engine/Camera/Camera.hpp>

REGISTER_COMPONENT(Camera)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Camera, target, trapHalfWidth, smoothing)

#include <Engine/Animation/BlinkingComponent.hpp>

REGISTER_COMPONENT(BlinkingComponent)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BlinkingComponent, interval, duration, timer, visible)

#include <Engine/Animation/Animation.hpp>

REGISTER_COMPONENT(Animation)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Animation, sprite, frameWidth, frameHeight, frameCount, frameDuration, currentFrame, timer, loop, row, hasEnded, textures)

REGISTER_COMPONENT(FlipXTag)
DEFINE_TAG(FlipXTag)

REGISTER_COMPONENT(FlipYTag)
DEFINE_TAG(FlipYTag)

// #include <Engine/Audio/Components.hpp>

// REGISTER_COMPONENT(SoundComponent)
// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SoundComponent, sound, shouldPlay, loop)

#include <Engine/Rendering/ZIndex.hpp>

REGISTER_COMPONENT(ZIndex)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ZIndex, value)

#include <Engine/Physics/BoxCollider2D.hpp>

REGISTER_COMPONENT(BoxCollider2D)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CollisionInfo, collider, direction, overlap)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BoxCollider2D, isDisabled, size, offset, bounce, rotation, origin, corners, collisions)

#include <Engine/Physics/BlockTag.hpp>

REGISTER_COMPONENT(CanHitBlockTag)
DEFINE_TAG(CanHitBlockTag)

REGISTER_COMPONENT(BlockTag)
DEFINE_TAG(BlockTag)

REGISTER_COMPONENT(PipeTag)
DEFINE_TAG(PipeTag)

