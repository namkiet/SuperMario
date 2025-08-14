// ResourceHolder.hpp
#pragma once
#include <map>
#include <memory>
#include <string>
#include <stdexcept>

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
    ResourceHolder() = default;
    ResourceHolder(const ResourceHolder&) = delete;
    ResourceHolder& operator=(const ResourceHolder&) = delete;

    // Load cơ bản: load từ file
    void load(Identifier id, const std::string& filename) {
        auto resource = std::make_unique<Resource>();
        if (!resource->loadFromFile(filename)) {
            throw std::runtime_error("ResourceHolder: Failed to load " + filename);
        }
        insertResource(id, std::move(resource));
    }

    template <typename Parameter>
    void load(Identifier id, const std::string& filename, const Parameter& secondParam) {
        auto resource = std::make_unique<Resource>();
        if (!resource->loadFromFile(filename, secondParam)) {
            throw std::runtime_error("ResourceHolder: Failed to load " + filename);
        }
        insertResource(id, std::move(resource));
    }

    Resource&       get(Identifier id)       { return *mResourceMap.at(id); }
    const Resource& get(Identifier id) const { return *mResourceMap.at(id); }

private:
    void insertResource(Identifier id, std::unique_ptr<Resource> resource) {
        auto inserted = mResourceMap.emplace(id, std::move(resource));
        if (!inserted.second) {
            throw std::runtime_error("ResourceHolder: Duplicate resource");
        }
    }

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};
