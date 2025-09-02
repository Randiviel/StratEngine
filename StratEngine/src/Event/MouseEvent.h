#pragma once

#include "Event.h"

namespace StratEngine {

    class MouseMovedEvent : public Event {
    public:
        virtual ~MouseMovedEvent() = default;
        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory::MouseEvent | EventCategory::InputEvent)
    };

    class MousePressedEvent : public Event {
    public:
        virtual ~MousePressedEvent() = default;
        EVENT_CLASS_TYPE(MouseButtonPressed)
        EVENT_CLASS_CATEGORY(EventCategory::MouseEvent | EventCategory::MouseButtonEvent | EventCategory::InputEvent)
    };

    class MouseReleasedEvent : public Event {
    public:
        virtual ~MouseReleasedEvent() = default;
    };

    class MouseScrolledEvent : public Event {
    public:
        virtual ~MouseScrolledEvent() = default;
    };
}