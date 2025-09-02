#pragma once

#include "Event.h"

namespace StratEngine {
    class KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(const char key) : m_Key(key) {}
        virtual ~KeyPressedEvent() = default;
        int GetKey() const { return m_Key; }

        EVENT_CLASS_TYPE(KeyPressed)
        EVENT_CLASS_CATEGORY(EventCategory::KeyboardEvent | EventCategory::InputEvent)
        
        private:
        int m_Key;
    };
}