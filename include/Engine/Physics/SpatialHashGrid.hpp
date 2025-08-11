#pragma once
#include <ECS/Entity.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <unordered_set>

struct SpatialHashGrid
{
public:
    static SpatialHashGrid& getInstance()
    {
        static SpatialHashGrid instance;
        return instance;
    }

private:
    SpatialHashGrid() = default;
    ~SpatialHashGrid() = default;

    SpatialHashGrid(const SpatialHashGrid&) = delete;
    SpatialHashGrid(SpatialHashGrid&&) = delete;
    SpatialHashGrid& operator=(const SpatialHashGrid&) = delete;
    SpatialHashGrid& operator=(SpatialHashGrid&&) = delete;

public:
    std::unordered_map<int64_t, std::vector<Entity *>> grid;
    const int CELL_SIZE = 48;

    void clear()
    {
        grid.clear();
    }

    int64_t hash(int x, int y)
    {
        return (static_cast<int64_t>(abs(x)) << 32) | static_cast<uint32_t>(abs(y));
    }

    void insert(Entity *e, const sf::FloatRect &bounds)
    {
        int minX = bounds.left / CELL_SIZE;
        int maxX = (bounds.left + bounds.width) / CELL_SIZE;
        int minY = bounds.top / CELL_SIZE;
        int maxY = (bounds.top + bounds.height) / CELL_SIZE;

        for (int x = minX; x <= maxX; x++)
        {
            for (int y = minY; y <= maxY; y++)
            {
                grid[hash(x, y)].push_back(e);
            }
        }
    }

    std::vector<Entity*> query(const sf::FloatRect &bounds)
    {
        std::unordered_set<Entity *> result;
        int minX = bounds.left / CELL_SIZE;
        int maxX = (bounds.left + bounds.width) / CELL_SIZE;
        int minY = bounds.top / CELL_SIZE;
        int maxY = (bounds.top + bounds.height) / CELL_SIZE;

        for (int x = minX; x <= maxX; x++)
        {
            for (int y = minY; y <= maxY; y++)
            {
                int64_t key = hash(x, y);
                for (Entity *e : grid[key])
                {
                    result.insert(e);
                }
            }
        }
        return std::vector<Entity *>(result.begin(), result.end());
    }

    std::vector<Entity*> query(const sf::Vector2f& point)
    {
        std::unordered_set<Entity *> result;

        int x = point.x / CELL_SIZE;
        int y = point.y / CELL_SIZE;

        for (Entity *e : grid[hash(x, y)])
        {
            result.insert(e);
        }
        return std::vector<Entity*>(result.begin(), result.end());
    }
};