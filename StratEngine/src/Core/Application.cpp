#include "pchstrat.h"
#include "StratConfig.h"

namespace StratEngine{
    Application::Application(){
        m_WindowClass = std::make_unique<WindowsWindow>(WindowProp{StratConfig::WINDOW_TITLE, StratConfig::WINDOW_HEIGHT, StratConfig::WINDOW_WIDTH});
    }

    Application::~Application(){

    }

}
