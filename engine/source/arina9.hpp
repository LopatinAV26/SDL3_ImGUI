#pragma once

#include "xrayBase.hpp"

class Arina9 final : public XrayBase
{
public:
    explicit Arina9();
    virtual ~Arina9() = default;

    void Draw(float focusDistance, float mA, int measure_index, float exposureMultiplier) override;
    virtual XrayData GetData() override { return data; }

private:
    std::string xrayTubeName{"АРИНА-9"};
    std::string info{"тип РА: импульсный\nнапряжение: 300 кВ\nдиаметр фокусного пятна: 2.5 мм"};
    // float focalSpotSize{2.5f};
    float kVmaximum{300};
    bool currentAdjustment{false};
    float mAminimum{1.0f};
    float mAmaximum{1.0f};
    int electricPower{300};
    int focusDistanceDefault{700};
    // float exposureMultiplier{1.5f};

    XrayData data;

    std::vector<std::vector<float>> diagramLinesDefault;
    std::vector<std::vector<float>> resultDiagramLines;

    std::vector<float> d7x300{4.9, 8.2, 10.6, 12.4, 14.0, 15.2, 16.4, 17.4, 18.2, 20.0};
    std::vector<float> d7y300{2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.5};
};