#include "protocolVMC.hpp"

ProtocolVMC::ProtocolVMC()
{
    ParseConfig("resources/config/protocol_VIC_default.toml");
    SDL_Log("ProtocolVMC constructed.\n");
}

void ProtocolVMC::CreateProtocol(bool &showProtocol)
{
    ImGui::Begin("Protocol VMC Window", &showProtocol);
    {
        ImGui::InputText("Дата выдачи заключения", &data.dateOfIssue);
        ImGui::InputText("Дата проведения контроля", &data.controlDate);
        ImGui::InputText("Номер сварного соединения", &data.weldNumber);
        ImGui::InputTextMultiline("Наименование объекта контроля", &data.objectName);

    }

    ImGui::End();
}

void ProtocolVMC::ParseConfig(const std::string &configPath)
{
    try
    {
        configVMC = toml::parse_file(configPath);
        SDL_Log("Config file '%s' parsed successfully.\n", configPath.c_str());
    }
    catch (const toml::parse_error &err)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to parse config file '%s': %s\n", configPath.c_str(), err.what());
    }
}

void ProtocolVMC::SaveProtocol()
{
    configVMC = toml::table{{"Технологическая карта", data.techCard}};
    std::cout << configVMC << std::endl;
    std::ofstream of("/home/av26/Programming/SDL3_ImGUI/build/Debug/resources/config/protocol_VIC_default.toml");
    of << configVMC;
}

ProtocolVMC::~ProtocolVMC()
{
    SDL_Log("ProtocolVMC destructed.\n");
}