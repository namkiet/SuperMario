#pragma once
#include <Framework/ComponentRegistry.hpp>
#include <Serialization/StateManager.hpp>

#define REGISTER_COMPONENT(TYPE) \
    namespace { \
        struct TYPE##_registrar { \
            TYPE##_registrar() { ComponentRegistry::registerComponent<TYPE>(#TYPE); } \
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

#define DEFINE_STATE(Base, Derived) \
    struct Derived; \
    static struct Derived##Registrar { \
        Derived##Registrar() { \
            StateManager<Base>::template registerState<Derived>(#Derived); \
        } \
    } Derived##RegistrarInstance;
