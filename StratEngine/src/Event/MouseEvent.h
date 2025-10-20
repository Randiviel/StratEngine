#pragma once

#include "Event.h"

namespace StratEngine {

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(double xpos, double ypos) : m_x{xpos}, m_y{ypos} {}
        virtual ~MouseMovedEvent() = default;
        inline std::pair<double, double> GetMousePos() { return std::make_pair(m_x, m_y); };
        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory::MouseEvent | EventCategory::InputEvent)

    private:
        double m_x, m_y;
    };

    class MousePressedEvent : public Event {
    public:
        MousePressedEvent(int butnum) : m_butnum(butnum) {};
        virtual ~MousePressedEvent() = default;
        inline int GetMouseButton() {return m_butnum; };
        EVENT_CLASS_TYPE(MouseButtonPressed)
        EVENT_CLASS_CATEGORY(EventCategory::MouseEvent | EventCategory::MouseButtonEvent | EventCategory::InputEvent)
    private:
        int m_butnum;
    };

    class MouseReleasedEvent : public Event {
    public:
        MouseReleasedEvent(int butnum) : m_butnum(butnum) {};
        virtual ~MouseReleasedEvent() = default;
        inline int GetMouseButton() {return m_butnum; };
        EVENT_CLASS_TYPE(MouseButtonReleased)
        EVENT_CLASS_CATEGORY(EventCategory::MouseEvent | EventCategory::MouseButtonEvent | EventCategory::InputEvent)

    private:
        int m_butnum;
    };

    class MouseScrolledEvent : public Event {
    public:
        virtual ~MouseScrolledEvent() = default;
    };
}