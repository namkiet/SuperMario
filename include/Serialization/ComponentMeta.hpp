#include <Serialization/sfmlJSON.hpp>
#include <Serialization/CustomJSON.hpp>
#include <Serialization/RegisterStates.hpp>
#include <Serialization/Macros.hpp>

#include <Gameplay/Obstacles/Components.hpp>
DEFINE_COMPONENT(PodobooTag, upright, lowestY, highestY)
DEFINE_COMPONENT(FireBarComponent, angle, isClockwise)

#include <Gameplay/Background/Components.hpp>
DEFINE_TAG(Castle)
DEFINE_TAG(FlagPole)
DEFINE_TAG(Flag)
DEFINE_TAG(CastleFlag)
DEFINE_TAG(BellTag)
DEFINE_TAG(BridgeTileTag)
DEFINE_COMPONENT(ElevatorComponent, isHorizontal, minX, maxX, minY, maxY)
DEFINE_TAG(Princess)

#include <Gameplay/Collect/Components.hpp>
DEFINE_TAG(CollectableTag)
DEFINE_TAG(CanCollectTag)

#include <Gameplay/Pipe/Components.hpp>
DEFINE_TAG(enterablePipe)
DEFINE_TAG(unenterablePipe)

#include <Gameplay/Enemy/Spiny/Components.hpp>
DEFINE_TAG(ChangeToSpinyNormalTag)
DEFINE_TAG(ChangeToSpinyFlippedTag)
DEFINE_COMPONENT(SpinyPatrol, velocity)

#include <Gameplay/Enemy/Lakitu/Components.hpp>
DEFINE_TAG(ChangeToLakituFlippedTag)
DEFINE_COMPONENT(LakituPatrol, distance, fastSpeed, accelerate, phase, velocity, lastDirection, freeTarget, limitX)
DEFINE_COMPONENT(LakituAttack, distance, delay, timer)

#include <Gameplay/Enemy/Components.hpp>
DEFINE_COMPONENT(EnemyTag, state, behaviour)
DEFINE_COMPONENT(TowardPlayer, direction)
DEFINE_TAG(CanKillEnemyTag)
DEFINE_TAG(NotOnPatrolYet)
DEFINE_TAG(ScoreAddedTag)

#include <Gameplay/Enemy/Koopa/Components.hpp>
DEFINE_TAG(KoopaTag)
DEFINE_TAG(KoopaNormalTag)
DEFINE_TAG(KoopaFlippedTag)
DEFINE_TAG(KoopaShellTag)
DEFINE_TAG(KoopaReviveTag)
DEFINE_TAG(KoopaSlideTag)
DEFINE_TAG(KoopaJumpingTag)
DEFINE_TAG(KoopaFlyingTag)
DEFINE_TAG(ChangeToKoopaNormalTag)
DEFINE_TAG(ChangeToKoopaFlippedTag)
DEFINE_TAG(ChangeToKoopaShellTag)
DEFINE_TAG(ChangeToKoopaReviveTag)
DEFINE_TAG(ChangeToKoopaSlideTag)
DEFINE_COMPONENT(KoopaPatrol, velocity, lastDirection)
DEFINE_COMPONENT(KoopaFlyingPatrol, velocity, phaseDuration, timer)

#include <Gameplay/Enemy/Goomba/Components.hpp>
DEFINE_TAG(ChangeToGoombaNormalTag)
DEFINE_TAG(ChangeToGoombaFlippedTag)
DEFINE_TAG(ChangeToGoombaStompedTag)
DEFINE_COMPONENT(GoombaPatrol, velocity)

#include <Gameplay/Enemy/Piranha/Components.hpp>
DEFINE_COMPONENT(PiranhaPatrol, velocity, maxHeight, minHeight, phaseDuration, delay, timer)

#include <Gameplay/Enemy/Bowser/Components.hpp>
DEFINE_TAG(ChangeToBowserIdleTag)
DEFINE_TAG(ChangeToBowserWalkTag)
DEFINE_TAG(ChangeToBowserJumpTag)
DEFINE_TAG(ChangeToBowserHurtTag)
DEFINE_TAG(ChangeToBowserSkidTag)
DEFINE_TAG(ChangeToBowserSlideTag)
DEFINE_TAG(ChangeToBowserDeadTag)
DEFINE_COMPONENT(BowserPatrol, safeDist, duration, timerDura, jumpCooldown, timerJump, velocity, accelerate, lastDirection)
DEFINE_COMPONENT(BowserAttack, distance, delay, timer, castTime, isShooting)
DEFINE_COMPONENT(StateDuration, duration, timer)

#include <Gameplay/Enemy/Bowser/BowserBullet/Components.hpp>
DEFINE_COMPONENT(BowserBulletPatrol, velocity, targetY)

#include <Gameplay/CaptureFlag/Components.hpp>
DEFINE_TAG(CanCaptureFlagTag)
DEFINE_TAG(ClimbingOnFlagPoleTag)
DEFINE_TAG(FlagPoleTag)
DEFINE_COMPONENT(HoldingTimer, duration)

#include <Gameplay/GameProperties/Components.hpp>
DEFINE_COMPONENT(ScoreComponent, score)
DEFINE_COMPONENT(TimeComponent, timer, subtimer, isPaused, goesFaster, firstTimeReach0, firstTimePause, timeUnitLeft)
DEFINE_COMPONENT(CoinComponent, coins)
DEFINE_COMPONENT(TextComponent, startX, startY, finalY, dy, size, content)

#include <Gameplay/LifeSpan/Components.hpp>
DEFINE_COMPONENT(LifeSpan, value)
DEFINE_COMPONENT(Health, hp)

#include <Gameplay/Fire/Components.hpp>
DEFINE_TAG(CanFireTag)
DEFINE_COMPONENT(FireCooldown, timeCount)
DEFINE_TAG(ShootingTag)

#include <Gameplay/Item/ItemEmerging.hpp>
DEFINE_COMPONENT(ItemEmerging, finalY, speedY, finished)

#include <Gameplay/Item/Components.hpp>
DEFINE_TAG(Coin1Tag)
DEFINE_TAG(DebrisTag)
DEFINE_TAG(Debris1Tag)
DEFINE_TAG(Debris2Tag)
DEFINE_TAG(Debris3Tag)
DEFINE_TAG(Debris4Tag)
DEFINE_TAG(StarTag)
DEFINE_COMPONENT(MushroomTag, buff)
DEFINE_TAG(FlowerTag)
DEFINE_TAG(FireBulletTag)
DEFINE_TAG(SmallCoinTag)
DEFINE_TAG(Coin2Tag)
DEFINE_COMPONENT(FireworkComponent, fireworksLeft)

#include <Gameplay/Stomp/Components.hpp>
DEFINE_TAG(StomperTag)
DEFINE_TAG(StompableTag)

#include <Gameplay/Patrol/Components.hpp>
DEFINE_COMPONENT(PatrolComponent, moveSpeed, isMovingRight)

#include <Gameplay/Tele/Components.hpp>
DEFINE_COMPONENT(TelePort, requireCollisionDirection, intime, inVel, destination)
DEFINE_COMPONENT(hasPipeDestination, pipe, OutDirection)
DEFINE_COMPONENT(TeleChanneling, teleInTime, teleEntity)

#include <Gameplay/DamageOnContact/Components.hpp>
DEFINE_TAG(CanGetDamageTag)
DEFINE_COMPONENT(DamageOnContactComponent, validDirections)
DEFINE_TAG(DamagedTag)

#include <Gameplay/Block/BounceBlock.hpp>
DEFINE_COMPONENT(BounceBlock, bounceTime, timer, updateY, originalY)

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

#include <Gameplay/Player/Components.hpp>
DEFINE_COMPONENT(PlayerTag, movementState, sizeState, powerState)
DEFINE_TAG(BigMarioTag)
DEFINE_TAG(FireMarioTag)
DEFINE_TAG(GrowUpTag)
DEFINE_COMPONENT(InputTag, horizontalMovement, jumpPressed)
DEFINE_COMPONENT(InvincibleTag, duration, timer)

#include <Engine/Core/DespawnTag.hpp>
DEFINE_TAG(DespawnTag)

#include <Engine/Core/Transform.hpp>
DEFINE_COMPONENT(Transform, prevPos, position, size, isFacingRight)

#include <Engine/Core/RigidBody.hpp>
DEFINE_COMPONENT(RigidBody, velocity, acceleration, applyGravity, onGround)

#include <Engine/Input/Input.hpp>
DEFINE_COMPONENT(Input, moveLeft, moveRight, jumpPressed, shootPressed)

#include <Engine/Camera/FollowByCameraTag.hpp>
DEFINE_TAG(FollowByCameraTag)

#include <Engine/Camera/Camera.hpp>
DEFINE_COMPONENT(Camera, target, trapHalfWidth, smoothing)

#include <Engine/Animation/BlinkingComponent.hpp>
DEFINE_COMPONENT(BlinkingComponent, interval, duration, timer, visible)

#include <Engine/Animation/Animation.hpp>
DEFINE_COMPONENT(Animation, sprite, frameWidth, frameHeight, frameCount, frameDuration, currentFrame, timer, loop, row, hasEnded, textures)
DEFINE_TAG(FlipXTag)
DEFINE_TAG(FlipYTag)

#include <Engine/Audio/Components.hpp>
// DEFINE_COMPONENT(SoundComponent, sound, buffer, shouldPlay, loop)

#include <Engine/Rendering/ZIndex.hpp>
DEFINE_COMPONENT(ZIndex, value)

#include <Engine/Physics/BoxCollider2D.hpp>
DEFINE_COMPONENT(BoxCollider2D, isDisabled, size, offset, bounce, rotation, origin, corners, collisions)

#include <Engine/Physics/BlockTag.hpp>
DEFINE_TAG(CanHitBlockTag)
DEFINE_TAG(BlockTag)
DEFINE_TAG(PipeTag)