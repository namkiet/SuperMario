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
    static void registerState() {
        std::string name = get_type_name<DerivedState>();
        registry.push_back({name, typeid(DerivedState), [] {
            return std::make_shared<DerivedState>();
        }});
        nameMap[name] = registry.back().factory;
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
        auto it = nameMap.find(name);
        return (it != nameMap.end()) ? it->second() : nullptr;
    }

private:
    struct Entry {
        std::string name;
        std::type_index type;
        Factory factory;
    };

    static inline std::vector<Entry> registry;
    static inline std::unordered_map<std::string, Factory> nameMap;
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

#define DEFINE_STATE(Base, Derived) \
    struct Derived; \
    static struct Derived##Registrar { \
        Derived##Registrar() { \
            StateManager<Base>::template registerState<Derived>(); \
        } \
    } Derived##RegistrarInstance;
