#pragma once

#include "xrayBase.hpp"

class Eresco65 final : public XrayBase
{
public:
    explicit Eresco65();
    virtual ~Eresco65() = default;

    void Draw(float focusDistance, float mA, int measure_index, float exposureMultiplier) override;
    virtual XrayData GetData() override { return data; }

private:
    std::string xrayTubeName{"Eresco 65 MF4"};
    float kVmaximum{300};
    float mAminimum{0.5f};
    float mAmaximum{6.0f};
    int electricPower{900};
    int focusDistanceDefault{700};
    // float exposureMultiplier{1.5f};

    XrayData data;

    std::vector<std::vector<float>> diagramLinesDefault;
    std::vector<std::vector<float>> resultDiagramLines;

    std::vector<float> x80{0.1, 1.0, 1.6, 1.9, 2.3, 2.5, 2.7, 2.9, 3.0, 3.1, 3.9, 4.4, 4.75, 5.2, 5.35, 5.55, 5.7, 5.9, 6.1, 7.0};
    std::vector<float> y80{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200};

    std::vector<float> x100{0.6, 2.3, 4.6, 6.3, 7.7, 9.9, 11.6, 13.4};
    std::vector<float> y100{1, 2, 5, 10, 20, 50, 100, 200};

    std::vector<float> x120{2.1, 4.75, 8.1, 10.7, 12.8, 16.3, 18.85, 21.95};
    std::vector<float> y120{1, 2, 5, 10, 20, 50, 100, 200};

    std::vector<float> x140{4.3, 7.8, 12.2, 15.7, 18.5, 22.9, 26.2, 29.7};
    std::vector<float> y140{1, 2, 5, 10, 20, 50, 100, 200};

    std::vector<float> x160{6.8, 10.9, 16.3, 20.3, 23.6, 28.8, 32.9, 36.9};
    std::vector<float> y160{1, 2, 5, 10, 20, 50, 100, 200};

    std::vector<float> x180{9.5, 14.2, 20.3, 24.9, 28.6, 34.8, 39.2, 43.9};
    std::vector<float> y180{1, 2, 5, 10, 20, 50, 100, 200};

    std::vector<float> x200{11.8, 17.4, 24.4, 29.5, 34.1, 41.1, 46.9, 52.0};
    std::vector<float> y200{1, 2, 5, 10, 20, 50, 100, 200};

    std::vector<float> x220{14.1, 20.5, 28.5, 34.6, 39.7, 47.8, 54.0, 60.4};
    std::vector<float> y220{1, 2, 5, 10, 20, 50, 100, 200};

    std::vector<float> x240{16.7, 23.9, 33.2, 40.1, 46.1, 55.5, 62.3, 69.5};
    std::vector<float> y240{1, 2, 5, 10, 20, 50, 100, 200};

    std::vector<float> x275{20.0, 28.6, 39.4, 47.8, 54.8, 65.7, 68.0, 69.5};
    std::vector<float> y275{1, 2, 5, 10, 20, 50, 60, 70};

    std::vector<float> x300{23.2, 32.2, 43.8, 52.7, 60.1, 65.2, 68.3, 70.0};
    std::vector<float> y300{1, 2, 5, 10, 20, 30, 40, 45};
};