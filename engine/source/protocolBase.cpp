#include "protocolBase.hpp"

void ProtocolBase::ParseConfig(std::string_view pathToConfig, toml::table &tbl)
{
    try
    {
        tbl = toml::parse_file(pathToConfig);
        SDL_Log("Config file '%s' parsed successfully.\n", pathToConfig.data());
    }
    catch (const toml::parse_error &err)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to parse config file '%s': %s\n", pathToConfig.data(), err.what());
    }
}

void ProtocolBase::GetDefaultProtocolData()
{
    ParseConfig(pathToDefaultProtocol, baseTable);

    if (baseProtocolData == nullptr)
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "baseProtocolData == nullptr");
    else if (baseTable.empty())
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "baseTable is empty.");
    else
    {
        std::optional<std::string> str;
        std::optional<int> index;

        // Наименование лаборатории
        str = baseTable["nameLab"].value<std::string>();
        baseProtocolData->nameLab = str.value_or("");

        // Номер свидетельства об аттестации
        str = baseTable["numberAttestation"].value<std::string>();
        baseProtocolData->numberAttestation = str.value_or("");

        // Наименование объекта
        str = baseTable["objectName"].value<std::string>();
        baseProtocolData->objectName = str.value_or("");

        // Категория трубопровода
        auto arr = baseTable["pipeCategoryVector"].as_array();
        baseProtocolData->pipeCategoryVector.clear();
        baseProtocolData->pipeCategoryVector.reserve(arr->size());
        for (const auto &i : *arr)
        {
            if (i.is_string())
                baseProtocolData->pipeCategoryVector.push_back(*i.value<std::string>());
        }
        index = baseTable["pipeCategoryIndex"].value<int>();
        baseProtocolData->pipeCategoryIndex = index.value_or(0);

        // Подрядная организация
        str = baseTable["contractorOrganization"].value<std::string>();
        baseProtocolData->contractorOrganization = str.value_or("");

        // Орзанизация заказчика
        str = baseTable["customerOrganization"].value<std::string>();
        baseProtocolData->customerOrganization = str.value_or("");
    }
}
