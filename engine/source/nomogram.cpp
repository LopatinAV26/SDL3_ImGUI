#include "nomogram.hpp"

Nomogram::Nomogram()
{
}

void Nomogram::NomogramWindow(bool &isOpen)
{
    // ImPlot::ShowDemoWindow();

    /* ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    ImGuiWindowFlags window_flags = // ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoSavedSettings; */

    ImGui::Begin("Диаграмма экспозиции", &isOpen /*window_flags*/);

    ImGui::RadioButton(eresco32.xrayTubeName.c_str(), &xrayTube_index, 0);
    ImGui::RadioButton(eresco65.xrayTubeName.c_str(), &xrayTube_index, 1);

    ImGui::DragInt("Фокусное расстояние, мм", &focusDistance, 1, 10, 1400);

    // ImGui::SliderFloat("Требуемая плотность снимка, е.о.п.", &opticalDensity, 1.0f, 4.0f, "%.1f");

    {
        ImGui::RadioButton("мА х мин", &measurementUnits_index, 0);
        ImGui::SameLine();
        ImGui::RadioButton("минуты", &measurementUnits_index, 1);
        ImGui::SameLine();
        ImGui::RadioButton("секунды", &measurementUnits_index, 2);

        switch (measurementUnits_index)
        {
        case 0:
            nameAxisY = "Экспозиция, мА х мин";
            break;
        case 1:
            nameAxisY = "Время экспозиции, мин";
            break;
        case 2:
            nameAxisY = "Время экспозиции, c";
            break;
        }

        bool mAIsDisabled{false};
        if (measurementUnits_index == 0)
            mAIsDisabled = true;

        ImGui::BeginDisabled(mAIsDisabled);
        ImGui::SliderFloat("Сила тока, мА", &mA, mAminimum, mAmaximum, "%.1f");
        ImGui::EndDisabled();
    }

    ImGui::SliderFloat("Множитель экспозиции", &exposureMultiplier, 0.5, 3.0, "%.1f");
    ImGui::SetItemTooltip("Подбирается индивидуально при тестовом просвечивании");

    if (ImPlot::BeginPlot(plotTitle.c_str(), ImGui::GetContentRegionAvail()))
    {
        ImPlot::SetupAxes("Толщина стали, мм", nameAxisY.c_str(), ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
        PlotNomogram(xrayTube_index);
        ImPlot::EndPlot();
    }
    ImGui::End();
}

void Nomogram::PlotNomogram(const int &xrayTube_index)
{
    switch (xrayTube_index)
    {
    case 0:
        mAminimum = eresco32.mAminimum;
        mAmaximum = eresco32.mAmaximum;
        eresco32.Plot(focusDistance, mA, measurementUnits_index, exposureMultiplier);
        break;
    case 1:
        mAminimum = eresco65.mAminimum;
        mAmaximum = eresco65.mAmaximum;
        eresco65.Plot(focusDistance, mA, measurementUnits_index, exposureMultiplier);
        break;
    }
}

Nomogram::~Nomogram()
{
    SDL_Log("Nomogram deleted");
}
