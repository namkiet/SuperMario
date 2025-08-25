#pragma once
#include <Engine/Animation/Animation.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <imgui.h>

struct AnimationButtonInfo {
    ImTextureID textureID;
    ImVec2 uv0;
    ImVec2 uv1;
    ImVec2 size;
};

inline AnimationButtonInfo getAnimationButtonInfo(Animation anim, float buttonSize = 48.f) {
    AnimationButtonInfo info{};
    if (!anim.sprite.getTexture()) return info;

    const sf::Texture* tex = anim.sprite.getTexture();
    sf::IntRect rect = anim.sprite.getTextureRect();

    float texWidth = float(tex->getSize().x);
    float texHeight = float(tex->getSize().y);

    info.textureID = (ImTextureID)tex->getNativeHandle();
    info.uv0 = ImVec2(rect.left / texWidth, rect.top / texHeight);
    info.uv1 = ImVec2((rect.left + rect.width) / texWidth, (rect.top + rect.height) / texHeight);
    info.size = ImVec2(buttonSize, buttonSize);

    return info;
}

