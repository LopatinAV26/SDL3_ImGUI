#pragma once

#include "xrayBase.hpp"

class Arina9 final : public XrayBase{
    public:
    explicit Arina9();
    virtual ~Arina9() = default;

    void Draw(float focusDistance, float mA, int measure_index, float exposureMultiplier) override;
    virtual XrayData GetData() override { return data; }

private:
    std::string xrayTubeName{"АРИНА-9"};
    float kVmaximum{300};
    float mAminimum{1.0f};
    float mAmaximum{1.0f};
    int electricPower{300};
    int focusDistanceDefault{700};
    // float exposureMultiplier{1.5f};

    XrayData data;

    std::vector<std::vector<float>> diagramLinesDefault;
    std::vector<std::vector<float>> resultDiagramLines;

    std::vector<float> d7x300{0};
    std::vector<float> d7y300{0};
};