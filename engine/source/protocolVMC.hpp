#pragma once

#include "protocolBase.hpp"

class ProtocolVMC : public ProtocolBase
{
public:
    ProtocolVMC();
    virtual ~ProtocolVMC();

    virtual void CreateProtocol(bool &showProtocol) override;
    virtual void SaveProtocol() override;
    void CreateTable();

private:
    std::shared_ptr<ProtocolData> protocolData = std::make_shared<ProtocolData>();
    // toml::table protocolVMC;

    ImGuiTableColumnFlags tableFlags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable;
};