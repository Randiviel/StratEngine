#pragma once

#include "Event/Event.h"
#include "string"

namespace StratEngine{
    
    struct WindowProp{
        const char* name;
        int width, height;
    };

    class Window {
        public:
            virtual ~Window() = default;
            virtual void SetWindowSize() = 0;
            virtual std::pair<float, float> GetWindowSize() = 0;
        private:
    };
}
