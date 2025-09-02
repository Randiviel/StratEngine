#pragma once
#include <cstdint>


namespace StratEngine {

        #define EVENT_CLASS_TYPE(type) \
        static EventType GetStaticType() { return EventType::type; } \
        virtual EventType GetEventType() const override { return GetStaticType(); } \
        virtual const char* GetName() const override { return #type; }

        #define EVENT_CLASS_CATEGORY(...) \
        virtual uint32_t GetCategoryFlags() const override { \
            return static_cast<uint32_t>(__VA_ARGS__); \
        }

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum class EventCategory {
        None = 0,
        ApplicationEvent    = 1 << 0,
        InputEvent          = 1 << 1,
        KeyboardEvent       = 1 << 2,
        MouseEvent          = 1 << 3,
        MouseButtonEvent    = 1 << 4
    };

    inline EventCategory operator|(EventCategory a, EventCategory b) {
        return static_cast<EventCategory>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
    }
    
    inline bool operator&(EventCategory a, EventCategory b) {
        return static_cast<unsigned int>(a) & static_cast<unsigned int>(b);
    }

    class Event {
    public:
        virtual ~Event() {};
        virtual const char* GetName() const = 0;
        virtual uint32_t GetCategoryFlags() const = 0;
        virtual EventType GetEventType() const = 0;

        bool IsInCategory(EventCategory category) const {
            return GetCategoryFlags() & static_cast<unsigned int>(category);
        }
    };
}