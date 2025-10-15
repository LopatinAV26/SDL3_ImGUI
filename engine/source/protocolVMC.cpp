#include "protocolVMC.hpp"

ProtocolVMC::ProtocolVMC()
{

    SDL_Log("ProtocolVMC constructed.\n");
}

void ProtocolVMC::CreateProtocol(bool &showProtocol)
{
    ImGui::Begin("Protocol VMC Window", &showProtocol);
    {
        if (ImGui::Button("Загрузить данные по умолчанию"))
        {
            ProtocolBase::GetDefaultProtocolData(); // Эта ф-я вызывается здесь для динамического обновления данных из файла по кнопке
            protocolData = ProtocolBase::baseProtocolData;
        }

        ImVec2 sizeTextField{0.f, 70.f};

        ImGui::Text("Наименование ЛНК");
        ImGui::InputTextMultiline("##Наименование ЛНК", &protocolData->nameLab, sizeTextField, ImGuiInputTextFlags_WordWrap);
        
        ImGui::Text("Номер свидетельства об аттестации");
        ImGui::InputText("##Номер свидетельства об аттестации", &protocolData->numberAttestation);

        ImGui::Text("Наименование объекта");
        ImGui::InputTextMultiline("##Наименование объекта", &protocolData->objectName, sizeTextField, ImGuiInputTextFlags_WordWrap);

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

        ImGui::Text("Подрядная организация");
        ImGui::InputTextMultiline("##Подрядная организация", &protocolData->contractorOrganization, sizeTextField, ImGuiInputTextFlags_WordWrap);

        ImGui::Text("Организация заказчика");
        ImGui::InputTextMultiline("##Организация заказчика", &protocolData->customerOrganization, sizeTextField, ImGuiInputTextFlags_WordWrap);

        ImGui::Text("Дата выдачи заключения");
        ImGui::InputText("##Дата выдачи заключения", &protocolData->dateOfIssue);

        ImGui::Text("Дата проведения контроля");
        ImGui::InputText("##Дата проведения контроля", &protocolData->controlDate);

        ImGui::Text("Номер сварного соединения");
        ImGui::InputText("##Номер сварного соединения", &protocolData->weldNumber);

        // CreateTable();
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
