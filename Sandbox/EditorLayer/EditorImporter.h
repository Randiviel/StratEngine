#pragma once
#include "StratEngine.h"

namespace Editor
{
    class Scene;

    class Importer
    {
        public:
            static void ImportObject(StratEngine::Scene* scene, const char* filePath);
    };
}