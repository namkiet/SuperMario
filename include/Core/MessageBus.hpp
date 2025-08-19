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

    // Register a receiver for a specific message
    static void subscribe(const std::string& messageKey, Callback cb) {
        observers()[messageKey].push_back(std::move(cb));
    }

    // Publish a message (only matching observers will be called)
    static void publish(const std::string& messageKey, const std::string& payload = "") {
        auto it = observers().find(messageKey);
        if (it != observers().end()) {
            for (auto& cb : it->second) {
                cb(payload);
            }
        }
    }

private:
    // Map of message key -> list of callbacks
    static std::unordered_map<std::string, std::vector<Callback>>& observers() {
        static std::unordered_map<std::string, std::vector<Callback>> inst;
        return inst;
    }
};
