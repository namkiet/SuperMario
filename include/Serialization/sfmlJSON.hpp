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