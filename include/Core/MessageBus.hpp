#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <algorithm>

class MessageBus {
public:
    using Callback = std::function<void(const std::string&)>;

    struct Entry {
        void* owner;   // pointer to the subscriber (identity)
        Callback cb;
    };

    // Register a receiver for a specific message
    static void subscribe(const std::string& messageKey, void* owner, Callback cb) {
        observers()[messageKey].push_back({owner, std::move(cb)});
    }

    // Unsubscribe all callbacks for a given owner
    static void unsubscribe(const std::string& messageKey, void* owner) {
        auto it = observers().find(messageKey);
        if (it != observers().end()) {
            auto& vec = it->second;
            vec.erase(
                std::remove_if(vec.begin(), vec.end(),
                               [owner](const Entry& e) { return e.owner == owner; }),
                vec.end());
        }
    }

    // Publish a message (only matching observers will be called)
    static void publish(const std::string& messageKey, const std::string& payload = "") {
        auto it = observers().find(messageKey);
        if (it != observers().end()) {
            for (auto& entry : it->second) {
                entry.cb(payload);
            }
        }
    }

private:
    // Map of message key -> list of entries
    static std::unordered_map<std::string, std::vector<Entry>>& observers() {
        static std::unordered_map<std::string, std::vector<Entry>> inst;
        return inst;
    }
};
