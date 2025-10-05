#pragma once

#include "protocolBase.hpp"

class ProtocolVMC : public ProtocolBase
{
public:
    ProtocolVMC();
    ~ProtocolVMC();

    virtual void Create(bool &showProtocol) override;

    ProtocolData data;

private:
    ImGuiTableColumnFlags tableFlags = ImGuiTableFlags_Borders;
};