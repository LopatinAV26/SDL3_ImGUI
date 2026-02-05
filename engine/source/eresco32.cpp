#include "eresco32.hpp"

#include "implot.h"

Eresco32::Eresco32()
{
    data.electricPower = {electricPower};
    data.focusDistanceDefault = {focusDistanceDefault};
    data.kVmaximum = {kVmaximum};
    data.mAminimum = {mAminimum};
    data.mAmaximum = {mAmaximum};
    data.xrayTubeName = {xrayTubeName};

    diagramLinesDefault = {x80, y80, x100, y100, x120, y120, x140, y140, x160, y160, x180, y180, x200, y200};
    resultDiagramLines = diagramLinesDefault;

    data.info = info;
}

void Eresco32::Draw(float focusDistance, float mA, int measure_index, float exposureMultiplier, float thicknessMarker)
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
    std::vector<DiagramLineRef> visibleLines;
    visibleLines.reserve(resultDiagramLines.size() / 2);

    if (mA <= 7.5f)
    {
        ImPlot::PlotLine("80 кВ", resultDiagramLines.at(0).data(), resultDiagramLines.at(1).data(), resultDiagramLines.at(0).size());
        visibleLines.push_back({&resultDiagramLines.at(0), &resultDiagramLines.at(1), ImPlot::GetLastItemColor(), "80 кВ"});
        if (mA <= 6.0f)
        {
            ImPlot::PlotLine("100 кВ", resultDiagramLines.at(2).data(), resultDiagramLines.at(3).data(), resultDiagramLines.at(2).size());
            visibleLines.push_back({&resultDiagramLines.at(2), &resultDiagramLines.at(3), ImPlot::GetLastItemColor(), "100 кВ"});
            if (mA <= 5.0f)
            {
                ImPlot::PlotLine("120 кВ", resultDiagramLines.at(4).data(), resultDiagramLines.at(5).data(), resultDiagramLines.at(4).size());
                visibleLines.push_back({&resultDiagramLines.at(4), &resultDiagramLines.at(5), ImPlot::GetLastItemColor(), "120 кВ"});
                if (mA <= 4.2f)
                {
                    ImPlot::PlotLine("140 кВ", resultDiagramLines.at(6).data(), resultDiagramLines.at(7).data(), resultDiagramLines.at(6).size());
                    visibleLines.push_back({&resultDiagramLines.at(6), &resultDiagramLines.at(7), ImPlot::GetLastItemColor(), "140 кВ"});
                    if (mA <= 3.7f)
                    {
                        ImPlot::PlotLine("160 кВ", resultDiagramLines.at(8).data(), resultDiagramLines.at(9).data(), resultDiagramLines.at(8).size());
                        visibleLines.push_back({&resultDiagramLines.at(8), &resultDiagramLines.at(9), ImPlot::GetLastItemColor(), "160 кВ"});
                        if (mA <= 3.3f)
                        {
                            ImPlot::PlotLine("180 кВ", resultDiagramLines.at(10).data(), resultDiagramLines.at(11).data(), resultDiagramLines.at(10).size());
                            visibleLines.push_back({&resultDiagramLines.at(10), &resultDiagramLines.at(11), ImPlot::GetLastItemColor(), "180 кВ"});
                            if (mA <= 3.0f)
                            {
                                ImPlot::PlotLine("200 кВ", resultDiagramLines.at(12).data(), resultDiagramLines.at(13).data(), resultDiagramLines.at(12).size());
                                visibleLines.push_back({&resultDiagramLines.at(12), &resultDiagramLines.at(13), ImPlot::GetLastItemColor(), "200 кВ"});
                            }
                        }
                    }
                }
            }
        }
    }

    DrawThicknessMarkers(visibleLines, thicknessMarker);
}