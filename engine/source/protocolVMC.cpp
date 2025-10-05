#include "protocolVMC.hpp"

ProtocolVMC::ProtocolVMC()
{
    SDL_Log("ProtocolVMC constructed.\n");
}

void ProtocolVMC::Create(bool &showProtocol)
{
    ImGui::Begin("Protocol VMC Window", &showProtocol);
    {
        {
            ImGui::BeginTable("Protocol VMC Table", 3, tableFlags);

            ImGui::TableSetupColumn("Column 1");
            ImGui::TableSetupColumn("Column 2");
            ImGui::TableSetupColumn("Column 3");
            ImGui::TableHeadersRow();

            // Sample Data specific to VMC
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("VMC Data 1");
            ImGui::TableNextColumn();
            ImGui::Text("VMC Data 2");
            ImGui::TableNextColumn();
            ImGui::Text("VMC Data 3");

            ImGui::EndTable();
        }
    }
    ImGui::End();
}

ProtocolVMC::~ProtocolVMC()
{
    SDL_Log("ProtocolVMC destructed.\n");
}