#pragma once
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>
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
    struct adl_serializer<std::vector<const sf::Texture*>> {
        static void to_json(json& j, const std::vector<const sf::Texture*>& textures) {
            j = json::array();
            for (const sf::Texture* tex : textures)
            {
                j.push_back(TextureManager::getPath(tex));
            }
        }

        static void from_json(const json& j, std::vector<const sf::Texture*>& textures) {
            textures.clear();
            for (const auto& path : j)
            {
                textures.push_back(&TextureManager::load(path.get<std::string>()));
            }
        }
    };
}


#define REGISTER_COMPONENT(TYPE) \
    namespace { \
        struct TYPE##_registrar { \
            TYPE##_registrar() { World::getInstance().registerComponent<TYPE>(); } \
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
    REGISTER_COMPONENT(TYPE)


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