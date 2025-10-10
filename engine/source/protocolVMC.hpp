#pragma once

#include "protocolBase.hpp"

class ProtocolVMC : public ProtocolBase
{
public:
    ProtocolVMC();
    ~ProtocolVMC();

    virtual void CreateProtocol(bool &showProtocol) override;
    virtual void ParseConfig(const std::string &configPath) override;
    virtual void SaveProtocol() override;

    ProtocolData data;

private:
    toml::table configVMC;
    ImGuiTableColumnFlags tableFlags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable;
};