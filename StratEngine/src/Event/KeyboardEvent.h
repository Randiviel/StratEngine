#pragma once

#include "Event.h"

namespace StratEngine {
    class KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(int key) : m_Key(key) {}
        virtual ~KeyPressedEvent() = default;
        int GetKey() const { return m_Key; }

        EVENT_CLASS_TYPE(KeyPressed)
        EVENT_CLASS_CATEGORY(EventCategory::KeyboardEvent | EventCategory::InputEvent)
        
        private:
        int m_Key;
    };

    class KeyReleasedEvent : public Event {
    public:
        KeyReleasedEvent(int key) : m_Key(key) {}
        virtual ~KeyReleasedEvent() = default;
        int GetKey() const { return m_Key; }

        EVENT_CLASS_TYPE(KeyReleased)
        EVENT_CLASS_CATEGORY(EventCategory::KeyboardEvent | EventCategory::InputEvent)
        
        private:
        int m_Key;
    };
}