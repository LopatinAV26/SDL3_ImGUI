#include "arina9.hpp"

Arina9::Arina9()
{
    data.electricPower = {electricPower};
    data.focusDistanceDefault = {focusDistanceDefault};
    data.kVmaximum = {kVmaximum};
    data.mAminimum = {mAminimum};
    data.mAmaximum = {mAmaximum};
    data.xrayTubeName = {xrayTubeName};

    diagramLinesDefault = {d7x300, d7y300};
    resultDiagramLines = diagramLinesDefault;
}

void Arina9::Draw(float focusDistance, float mA, int measure_index, float exposureMultiplier)
{
    for (size_t i = 1; i < resultDiagramLines.size(); i += 2)
    {
        for (size_t j = 0; j < resultDiagramLines.at(i).size(); ++j)
        {
            resultDiagramLines.at(i).at(j) = CalculateIntensity(diagramLinesDefault.at(i).at(j), focusDistanceDefault, focusDistance);
            resultDiagramLines.at(i).at(j) *= exposureMultiplier;
            switch (measure_index)
            {
            case 1:
                resultDiagramLines.at(i).at(j) = ToMinute(resultDiagramLines.at(i).at(j), mA);
                break;
            case 2:
                resultDiagramLines.at(i).at(j) = ToSecond(resultDiagramLines.at(i).at(j), mA);
                break;
            }
        }
    }

    ImPlot::PlotLine("D7 + Pb 0.027 мм", resultDiagramLines.at(0).data(), resultDiagramLines.at(1).data(), resultDiagramLines.at(0).size());
}
