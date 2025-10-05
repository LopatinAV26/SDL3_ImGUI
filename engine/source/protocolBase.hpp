#pragma once

#include <memory>
#include <string>
#include "toml.hpp"
#include "imgui.h"
#include <SDL3/SDL.h>

struct ProtocolData
{
    std::string nameLab{"Наименование ЛНК"};
    std::string numberAttestation{"Номер свидетельства об аттестации"};
    std::string protocolNumber{"Номер заключения"};
    std::string controlDate{"Дата проведения контроля"};
    std::string dateOfIssue{"Дата выдачи заключения"};
    std::string nameOfMethod{"Наименование метода НК"};
    std::string nOM{"Сокращённое наименование метода НК"};
    std::string objectName{"Объект контроля"};
    std::string pipeCategory{"Категория трубопровода"};
    std::string contractorOrganization{"Подрядная организация"};
    std::string customersOrganization{"Организация заказчика"};
    std::string techCard{"Технологическая карта"};
    std::string equipment{"Средства контроля"};
};

class ProtocolBase
{
public:
    ProtocolBase();
    virtual ~ProtocolBase();
    virtual void Create(bool &showProtocol) = 0;

protected:
private:
};