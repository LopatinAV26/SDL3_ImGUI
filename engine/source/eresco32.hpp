#pragma once

#include <vector>
#include <cmath>
#include <string>
#include "implot.h"

class Eresco32
{
public:
    Eresco32();

    void Plot(const float &focusDistance, const float &mA, const int &measure_index, const float &exposureMultiplier);

    std::string xrayTubeName{"Eresco 32 MF4-C"};
    float kVmaximum{200.f};
    float mAminimum{0.5f};
    float mAmaximum{7.5f}; // по факту 10 мА для 60 кВ
    int electricPower{600};
    //float exposureMultiplier{1.5f};

private:
    /* Возвращает интенсивность излучения в зависимости от фокусного расстояния
    \param intensity_0 интенсивность излучения известная (по заводской номограмме)
    \param focusDistance_0 расстояние до источника излучения известное (по заводской номограмме)
    \param focusDistance_1 требуемое расстояние до источника
    */
    float CalculateIntensity(const float &intensity_0,
                             const float &focusDistance_0,
                             const float &focusDistance_1);

    float ToMinute(const float &exposition, const float &mA);

    float ToSecond(const float &exposition, const float &mA);

    int focusDistanceDefault{700};

    std::vector<std::vector<float>> diagramLinesDefault;
    std::vector<std::vector<float>> resultDiagramLines;

    std::vector<float> x80{0.5, 1.0, 1.9, 2.55, 3.05, 3.45, 4.0, 4.7};
    std::vector<float> y80{2, 3, 6, 10, 15, 20, 30, 50};

    std::vector<float> x100{1.1, 2.05, 3.6, 4.9, 5.7, 6.5, 7.45, 8.65};
    std::vector<float> y100{2, 3, 6, 10, 15, 20, 30, 50};

    std::vector<float> x120{3.0, 4.3, 6.5, 8.2, 9.4, 10.45, 11.8, 13.5};
    std::vector<float> y120{2, 3, 6, 10, 15, 20, 30, 50};

    std::vector<float> x140{3.7, 5.7, 9.0, 11.6, 13.3, 14.9, 17.0, 19.55};
    std::vector<float> y140{2, 3, 6, 10, 15, 20, 30, 50};

    std::vector<float> x160{6.0, 8.35, 12.25, 15.4, 17.4, 19.2, 21.65, 24.6};
    std::vector<float> y160{2, 3, 6, 10, 15, 20, 30, 50};

    std::vector<float> x180{7.4, 10.35, 15.2, 19.0, 21.6, 23.9, 26.85, 30.6};
    std::vector<float> y180{2, 3, 6, 10, 15, 20, 30, 50};

    std::vector<float> x200{11.1, 14.2, 19.45, 23.55, 26.3, 28.8, 31.9, 36.0};
    std::vector<float> y200{2, 3, 6, 10, 15, 20, 30, 50};
};