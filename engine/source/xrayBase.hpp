#pragma once

#include <vector>
#include <cmath>
#include <string>
#include "implot.h"

struct XrayData
{
    std::string xrayTubeName{"-"};
    std::string info{""};
    float focalSpotSize{1.0f};
    float kVmaximum{300.0f};
    bool currentAdjustment{true};
    float mAminimum{0.5f};
    float mAmaximum{10.0f};
    int electricPower{1000};
    int focusDistanceDefault{700};
    float exposureMultiplier{1.5f};
};

class XrayBase
{
public:
    virtual ~XrayBase() = default;

    virtual void Draw(float focusDistance, float mA, int measure_index, float exposureMultiplier) = 0;
    virtual XrayData GetData() = 0;

protected:
    /* Возвращает интенсивность излучения в зависимости от фокусного расстояния
        \param intensity_0 интенсивность излучения известная (по заводской номограмме)
        \param focusDistance_0 расстояние до источника излучения известное (по заводской номограмме)
        \param focusDistance_1 требуемое расстояние до источника
        */
    virtual float CalculateIntensity(float intensity_0,
                                     float focusDistance_0,
                                     float focusDistance_1) const;

    virtual float ToMinute(float exposition, float mA) const;

    virtual float ToSecond(float exposition, float mA) const;
};