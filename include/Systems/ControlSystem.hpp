// #pragma once
// #include <World.hpp>
// #include <Components/Input.hpp>
// #include <Components/RigidBody.hpp>
// #include <Core/Variables.hpp>

// class ControlSystem : public System
// {
// public:
//     void update(World& world, float dt) override
//     {
//         for (Entity* entity : world.findAll<Input, RigidBody>())
//         {
//             auto& input = entity->getComponent<Input>();
//             auto& rb = entity->getComponent<RigidBody>();

//             if (input.moveLeft)
//             {
//                 rb.velocity.x = -200.f;
//                 if (entity->hasComponent<Animation>())
//                 {
//                     auto& anim = entity->getComponent<Animation>();
//                     anim.flipX = true;
//                 }
//             } 

//             else if (input.moveRight)
//             {
//                 rb.velocity.x = 200.f;
//                 if (entity->hasComponent<Animation>())
//                 {
//                     auto& anim = entity->getComponent<Animation>();
//                     anim.flipX = false;
//                 }
//             }
//             else
//             {
//                 rb.velocity.x = 0.f;
//             }

//             if (input.jumpPressed && rb.onGround)
//             {
//                 rb.velocity.y = -PHYSICS::JUMP_FORCE;
//             }
//         }
//     }
// };