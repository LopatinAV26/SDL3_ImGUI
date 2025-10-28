#include "protocolVMC.hpp"
#include "pdfCreator.hpp" //!!!!!!!!!!!!!!!!!!!!!!!!

ProtocolVMC::ProtocolVMC()
{
    SDL_Log("ProtocolVMC constructed.\n");
}

void ProtocolVMC::WindowProtocol(bool &showProtocol)
{
    ImGui::Begin("Заключение ВИК", &showProtocol);
    {
        float width = ImGui::GetContentRegionAvail().x;

        if (ImGui::Button("Загрузить данные по умолчанию"))
        {
            ProtocolBase::GetDefaultProtocolData();        // Эта ф-я вызывается здесь для динамического обновления данных из файла по кнопке
            protocolData = ProtocolBase::baseProtocolData; //!!! не верный подход наверное
        }

        ImVec2 sizeTextField{0.f, 70.f};

        ImGui::PushItemWidth(width); /////////////////////////////////////////

        ImGui::Text("Наименование ЛНК");
        ImGui::InputTextMultiline("##Наименование ЛНК", &protocolData->nameLab, sizeTextField, ImGuiInputTextFlags_WordWrap);
        ImGui::NewLine();

        ImGui::Text("Номер свидетельства об аттестации");
        ImGui::InputText("##Номер свидетельства об аттестации", &protocolData->numberAttestation);
        ImGui::NewLine();

        ImGui::Text("Наименование объекта");
        ImGui::InputTextMultiline("##Наименование объекта", &protocolData->objectName, sizeTextField, ImGuiInputTextFlags_WordWrap);
        ImGui::NewLine();

        ImGui::Text("Категория трубопровода");
        if (ImGui::BeginCombo("##Категория трубопровода",
                              protocolData->pipeCategoryVector.at(protocolData->pipeCategoryIndex).c_str()))
        {
            for (int i = 0; i < protocolData->pipeCategoryVector.size(); ++i)
            {
                const bool isSelected = (protocolData->pipeCategoryIndex == i);
                if (ImGui::Selectable(protocolData->pipeCategoryVector.at(i).c_str(), isSelected))
                    protocolData->pipeCategoryIndex = i;

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        ImGui::NewLine();

        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 150, 0, 255));
        ImGui::Text("Подрядная организация");
        ImGui::PopStyleColor();
        ImGui::InputTextMultiline("##Подрядная организация", &protocolData->contractorOrganization, sizeTextField, ImGuiInputTextFlags_WordWrap);
        ImGui::NewLine();

        ImGui::Text("Организация заказчика");
        ImGui::InputTextMultiline("##Организация заказчика", &protocolData->customerOrganization, sizeTextField, ImGuiInputTextFlags_WordWrap);
        ImGui::NewLine();

        ImGui::Text("Дата выдачи заключения");
        ImGui::InputText("##Дата выдачи заключения", &protocolData->dateOfIssue);
        ImGui::NewLine();

        ImGui::Text("Дата проведения контроля");
        ImGui::InputText("##Дата проведения контроля", &protocolData->controlDate);
        ImGui::NewLine();

        ImGui::Text("Номер сварного соединения");
        ImGui::InputText("##Номер сварного соединения", &protocolData->weldNumber);

        ImGui::PopItemWidth(); /////////////////////////////////////////////////
    }

    if (ImGui::Button("Создать PDF"))
    {
        PdfCreator pdf;
        pdf.CreateTable();
    }

    ImGui::End();
}

void ProtocolVMC::SaveProtocol()
{
    /* configVMC = toml::table{{"Технологическая карта", data->techCard}};
    std::cout << configVMC << std::endl;
    std::ofstream of("/home/av26/Programming/SDL3_ImGUI/build/Debug/resources/config/protocol_VIC_default.toml");
    of << configVMC; */
}

void ProtocolVMC::CreateTable()
{
    ImGui::BeginTable("tableVMC", 1, tableFlags);
    {

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Наименование ЛНК");

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(protocolData->nameLab.c_str());
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Номер свидетельства об аттестации");
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(protocolData->numberAttestation.c_str());
        ImGui::EndTable();
    }

    ImGui::SameLine(0, 0);

    (ImGui::BeginTable("tableVMC", 1, tableFlags));
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Наименование ЛНК");
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(protocolData->nameLab.c_str());
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Номер свидетельства об аттестации");
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(protocolData->numberAttestation.c_str());

        ImGui::EndTable();
    }
}

ProtocolVMC::~ProtocolVMC()
{
    SDL_Log("ProtocolVMC destructed.\n");
}
