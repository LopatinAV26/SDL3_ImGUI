#pragma once

#include <memory>

#include "imgui.h"
#include "imgui_stdlib.h"
#include "implot.h"
// #include "implot_internal.h"
#include "SDL3/SDL_log.h"

#include "eresco32.hpp"
#include "eresco65.hpp"

class Nomogram
{
public:
    explicit Nomogram();
    void NomogramWindow(bool &isOpen);

private:
    void DrawNomogram(int xrayTube_index);

    int xrayTube_index{0};
    int focusDistance{700};
    float exposureMultiplier{1.f};
    // float opticalDensity{2.0f};
    float mAminimum{0.f};
    float mAmaximum{10.0f};
    float mA{3.f};
    int measurementUnits_index{0};
    std::string plotTitle{"Диаграмма экспозиции РА"};
    std::string nameAxisY{};

    std::vector<std::unique_ptr<XrayBase>> xray;
};
