#pragma once
#include <UI/Composite.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class CommonUIPool
{
private:
    std::unordered_map<std::string, std::shared_ptr<UIComponent>> pool;

    CommonUIPool() = default;

    CommonUIPool(const CommonUIPool&) = delete;
    CommonUIPool& operator=(const CommonUIPool&) = delete;

public:
    static CommonUIPool& getInstance()
    {
        static CommonUIPool instance;
        return instance;
    }

    // API ví dụ
    void add(const std::string& key, std::shared_ptr<UIComponent> comp)
    {
        pool[key] = comp;
    }

    std::shared_ptr<UIComponent> get(const std::string& key)
    {
        auto it = pool.find(key);
        if (it != pool.end())
            return it->second;
        return nullptr;
    }

    bool exists(const std::string& key) const
    {
        return pool.find(key) != pool.end();
    }
};
