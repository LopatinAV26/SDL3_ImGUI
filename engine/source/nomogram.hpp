#pragma once

#include <memory>
#include <vector>

#include "xrayBase.hpp"

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
    bool currentAdjustment{true};
    float mAminimum{0.5f};
    float mAmaximum{10.0f};
    float mA{3.f};
    float materialThickness{10.0f};
    int measurementUnits_index{0};
    std::string plotTitle{"Диаграмма экспозиции РА"};
    std::string nameAxisY{""};
    std::string xrayInfo{""};

    std::vector<std::unique_ptr<XrayBase>> xray;
};
