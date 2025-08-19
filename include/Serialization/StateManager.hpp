#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <typeindex>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

template<typename BaseState>
class StateManager {
public:
    using Factory = std::function<std::shared_ptr<BaseState>()>;

    template<typename DerivedState>
    static void registerState(const std::string& name) {
        registry.push_back({name, std::type_index(typeid(DerivedState)), [] {
            return std::make_shared<DerivedState>();
        }});
        getNameMap()[name] = registry.back().factory;
    }

    static std::string getName(const std::shared_ptr<BaseState>& state) {
        if (!state) return "";
        auto type = std::type_index(typeid(*state));
        for (auto& entry : registry) {
            if (entry.type == type) return entry.name;
        }
        return "";
    }

    static std::shared_ptr<BaseState> create(const std::string& name) {
        auto& map = getNameMap();
        auto it = map.find(name);
        return (it != map.end()) ? it->second() : nullptr;
    }

private:
    struct Entry {
        std::string name;
        std::type_index type;
        Factory factory;
    };

    static inline std::vector<Entry> registry;

    // function-local static để tránh static init order fiasco
    static std::unordered_map<std::string, Factory>& getNameMap() {
        static std::unordered_map<std::string, Factory> instance;
        return instance;
    }
};

template<typename StateType>
inline void to_json(json& j, const std::shared_ptr<StateType>& state) {
    j = StateManager<StateType>::getName(state);
}

template<typename StateType>
inline void from_json(const json& j, std::shared_ptr<StateType>& state) {
    if (j.is_string() && !j.get<std::string>().empty()) {
        state = StateManager<StateType>::create(j.get<std::string>());
    } else {
        state = nullptr;
    }
}
