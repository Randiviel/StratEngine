#pragma once
#include "Event.h"

namespace StratEngine {

    class Event;

    class EventDispatcher {
    public:
        EventDispatcher(Event& event) : m_Event(event) {};
        ~EventDispatcher() = default;

        template<typename T, typename F>
        bool Dispatch(const F& func) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };
}