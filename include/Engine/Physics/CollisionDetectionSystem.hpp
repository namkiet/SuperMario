#pragma once
#include <ECS/System.hpp>
#include <Core/Physics.hpp>
#include <unordered_map>
#include <unordered_set>

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
        for (Entity* e : entities) 
        {
            auto& tf = e->getComponent<Transform>();
            auto& col = e->getComponent<BoxCollider2D>();

            sf::FloatRect bounds(tf.position + col.offset, col.size);
            grid.insert(e, bounds);
            col.collisions.clear();
        }

        for (Entity* e : entities) {
            auto& tf = e->getComponent<Transform>();
            auto& col = e->getComponent<BoxCollider2D>();
            sf::FloatRect bounds(tf.position + col.offset, col.size);

            auto nearby = grid.query(bounds);
            for (Entity* other : nearby) 
            {
                if (e == other) continue;

                Direction dir = Physics::GetCollisionDirection(e, other);
                if (dir == Direction::None) continue;
                col.collisions.emplace_back(CollisionInfo{other, dir});
            }
        }
    }
};