#pragma once
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>
#include <Framework/EntityManager.hpp>
#include <Framework/ComponentRegistry.hpp>
#include <vector>
#include <string>

using json = nlohmann::json;

namespace nlohmann {
    template <>
    struct adl_serializer<sf::Vector2f> {
        static void to_json(json& j, const sf::Vector2f& vec) {
            j = json{{"x", vec.x}, {"y", vec.y}};
        }

        static void from_json(const json& j, sf::Vector2f& vec) {
            j.at("x").get_to(vec.x);
            j.at("y").get_to(vec.y);
        }
    };

    template <>
    struct adl_serializer<sf::FloatRect> {
        static void to_json(json& j, const sf::FloatRect& rect) {
            j["left"] = rect.left;
            j["top"] = rect.top;
            j["width"] = rect.width;
            j["height"] = rect.height;
        }

        static void from_json(const json& j, sf::FloatRect& rect) {
            rect.left = j["left"];
            rect.top = j["top"];
            rect.width = j["width"];
            rect.height = j["height"];
        }
    };

    template <>
    struct adl_serializer<const sf::Texture*> {
        static void to_json(json& j, const sf::Texture* tex) {
            j = tex ? TextureManager::getPath(tex) : "";
        }
        static void from_json(const json& j, const sf::Texture*& tex) {
            if (j.is_string() && !j.get<std::string>().empty())
                tex = &TextureManager::load(j.get<std::string>()); 
            else
                tex = nullptr;
        }
    };

    template <>
    struct adl_serializer<sf::Sprite> {
        static void to_json(json& j, const sf::Sprite& sprite) {
            j = TextureManager::getPath(sprite.getTexture());
        }

        static void from_json(const json& j, sf::Sprite& sprite) {
            sprite.setTexture(TextureManager::load(j.get<std::string>()));
        }
    };
}


#define REGISTER_COMPONENT(TYPE) \
    namespace { \
        struct TYPE##_registrar { \
            TYPE##_registrar() { ComponentRegistry::registerComponent<TYPE>(); } \
        }; \
        static TYPE##_registrar global_##TYPE##_registrar_instance; \
    }

#define DEFINE_COMPONENT(TYPE, ...) \
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TYPE, ##__VA_ARGS__); \
    REGISTER_COMPONENT(TYPE)

#define DEFINE_TAG(TYPE) \
    namespace nlohmann { \
        template <> \
        struct adl_serializer<TYPE> { \
            static void to_json(json& j, const TYPE&) { j = json::object(); } \
            static void from_json(const json&, TYPE&) {} \
        }; \
    } \
    // REGISTER_COMPONENT(TYPE)


#include <unordered_map>
#include <memory>
#include <string>
#include <functional>
#include <stdexcept>

template <typename Base>
class StateRegistry {
public:
    using FactoryFunc = std::function<std::shared_ptr<Base>()>;

    static StateRegistry& instance() {
        static StateRegistry inst;
        return inst;
    }

    void registerType(const std::string& typeName, FactoryFunc factory) {
        registry[typeName] = std::move(factory);
    }

    std::shared_ptr<Base> create(const std::string& typeName) const {
        auto it = registry.find(typeName);
        if (it == registry.end()) {
            throw std::runtime_error("Unknown type: " + typeName);
        }
        return it->second();
    }

    const std::unordered_map<std::string, FactoryFunc>& getAll() const {
        return registry;
    }

private:
    std::unordered_map<std::string, FactoryFunc> registry;
};


inline void to_json(json& j, const Entity* entity)
{
    j = entity ? entity->getID() : -1;
}

inline void from_json(const json& j, Entity*& entity)
{
    entity = EntityManager::getEntityByID(j.get<int>());
}