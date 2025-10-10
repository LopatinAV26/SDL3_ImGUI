#pragma once

#include <memory>
#include <string>
/// #include <array> or <vector>
#include <iostream>
#include "toml.hpp"
#include "imgui.h"
#include "imgui_stdlib.h"
#include <SDL3/SDL.h>

struct ProtocolData
{
    std::string nameLab{"Наименование ЛНК"};
    std::string numberAttestation{"Номер свидетельства об аттестации"};
    std::string weldNumber{"Номер сварного соединения"};
    std::string protocolNumber{"Номер заключения"};
    std::string controlDate{"Дата проведения контроля"};
    std::string dateOfIssue{"15.03.1989"};
    std::string nameOfMethod{"Наименование метода НК"};
    std::string objectName{"Объект контроля"};
    std::string pipeCategory{"Категория трубопровода"};
    std::string contractorOrganization{"Подрядная организация"};
    std::string customersOrganization{"Организация заказчика"};
    std::string techCard{"ТК-ТНДВ-ВИК-396-С-57-159х4-8"};
    std::string equipment{"Средства контроля"};
    std::string normativeDoc{"РД-25.160.10-КТН-0016-23 с Изм.1"};
    std::string weldType{"Тип сварного соединения"};
    std::string weldingMethod{"Способ сварки"};
    int diameter{0};
    float thicknes_1{0.f};
    float thicknes_2{0.f};
    float perimeter{0.f};
    std::string typeOfSection_1{"Тип секции 1"};
    std::string typeOfSection_2{"Тип секции 2"};
    int coordSec_1Weld_1{0};
    int coordSec_1Weld_2{0};
    int coordSec_2Weld_1{0};
    int coordSec_2Weld_2{0};
    std::string weldersMark_1{"Клеймо сварщика 1"};
    std::string weldersMark_2{"Клеймо сварщика 2"};
    int brightness{0};
    int roughness{0};
    std::string stringOfDefects{""};
    std::string acceptDefect{"допустим"};
    std::string unacceptDefect{"не допустим"};

    float extentOfUnacceptableDefects{0.f}; // Суммарная протяжённость недопуст. дефектов
    float maxHeightOfWeld{0.f};
    float minHeightOfWeld{0.f};
    float maxWidthOfWeld{0.f};
    float minWidthOfWeld{0.f};
    float edgeDisplacement{0.f};
    

    std::string controllerName{"Контроль провёл"};
    std::string conclusionCreateName{"Заключение выдал"};
    std::string inspectorName{"Надзор"};
    std::string masterName{"Производитель работ"};
};

class ProtocolBase
{
public:
    ProtocolBase();
    virtual ~ProtocolBase();
    virtual void CreateProtocol(bool &showProtocol) = 0;
    virtual void ParseConfig(const std::string &configPath) = 0;
    virtual void SaveProtocol() = 0;

protected:
private:
};