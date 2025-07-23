#pragma once
#include <ECS/System.hpp>
#include <Core/Physics.hpp>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

struct SpatialHashGrid 
{
    std::unordered_map<int64_t, std::vector<Entity*>> grid;
    const int CELL_SIZE = 64;

    void clear() {
        grid.clear();
    }

    int64_t hash(int x, int y) {
        return (static_cast<int64_t>(x) << 32) | static_cast<uint32_t>(y);
    }

    void insert(Entity* e, const sf::FloatRect& bounds) {
        int minX = bounds.left / CELL_SIZE;
        int maxX = (bounds.left + bounds.width) / CELL_SIZE;
        int minY = bounds.top / CELL_SIZE;
        int maxY = (bounds.top + bounds.height) / CELL_SIZE;

        for (int x = minX; x <= maxX; x++) {
            for (int y = minY; y <= maxY; y++) {
                grid[hash(x, y)].push_back(e);
            }
        }
    }

    std::vector<Entity*> query(const sf::FloatRect& bounds) {
        std::unordered_set<Entity*> result;
        int minX = bounds.left / CELL_SIZE;
        int maxX = (bounds.left + bounds.width) / CELL_SIZE;
        int minY = bounds.top / CELL_SIZE;
        int maxY = (bounds.top + bounds.height) / CELL_SIZE;

        for (int x = minX; x <= maxX; x++) {
            for (int y = minY; y <= maxY; y++) {
                int64_t key = hash(x, y);
                for (Entity* e : grid[key]) {
                    result.insert(e);
                }
            }
        }
        return std::vector<Entity*>(result.begin(), result.end());
    }
};


class CollisionDetectionSystem : public System {
private:
    SpatialHashGrid grid;

public:
    void update(World& world, float dt) override {
        grid.clear();

        auto entities = world.findAll<BoxCollider2D, Transform>();

        // Insert entities into spatial grid
        for (Entity* e : entities) {
            auto& tf = e->getComponent<Transform>();
            auto& col = e->getComponent<BoxCollider2D>();

            sf::FloatRect bounds(tf.position + col.offset, col.size);
            grid.insert(e, bounds);
            col.collisions.clear();
        }

        // // Collision detection
        // std::unordered_set<std::pair<Entity*, Entity*>, PairHash> checkedPairs;

        for (Entity* e : entities) {
            auto& tf = e->getComponent<Transform>();
            auto& col = e->getComponent<BoxCollider2D>();
            sf::FloatRect bounds(tf.position + col.offset, col.size);

            auto nearby = grid.query(bounds);
            for (Entity* other : nearby) {
                if (e == other) continue;

                // auto pair = std::minmax(e, other); // avoid duplicate checks
                // if (!checkedPairs.insert(pair).second) continue;

                // sf::FloatRect otherBounds(
                //     other->getComponent<Transform>().position + 
                //     other->getComponent<BoxCollider2D>().offset,
                //     other->getComponent<BoxCollider2D>().size
                // );

                // if (bounds.intersects(otherBounds)) {
                    Direction dir = Physics::GetCollisionDirection(e, other, dt);
                    if (dir != Direction::None) {
                        col.collisions.emplace_back(CollisionInfo{other, dir});
                        // // Optional: bidirectional
                        // other->getComponent<BoxCollider2D>().collisions.emplace_back(CollisionInfo{e, Direction::None});
                    }
                // }
            }
        }
    }

    // Helper hash for unordered_set of pairs
    struct PairHash {
        std::size_t operator()(const std::pair<Entity*, Entity*>& p) const {
            return std::hash<Entity*>()(p.first) ^ std::hash<Entity*>()(p.second);
        }
    };
};
