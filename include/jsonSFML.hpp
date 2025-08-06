#pragma once
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
// #include <Core/TextureManager.hpp>

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

    // struct adl_serializer<sf::Sprite> {
    //     static void to_json(json& j, const sf::Sprite& sprite) {
    //         j = json{{"x", vec.x}, {"y", vec.y}};
    //     }

    //     static void from_json(const json& j, sf::Sprite& sprite) {
    //         j.at("x").get_to(v.x);
    //         j.at("y").get_to(v.y);
    //     }
    // };
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
