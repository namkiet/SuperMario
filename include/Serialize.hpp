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


#include <Gameplay/Player/Components.hpp>

DEFINE_TAG(PlayerTag)
DEFINE_TAG(BigMarioTag)
DEFINE_TAG(FireMarioTag)
DEFINE_TAG(GrowUpTag)
DEFINE_TAG(InputTag)