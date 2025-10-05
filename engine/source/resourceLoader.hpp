#pragma once

#include <SDL3/SDL.h>
#include "toml.hpp"

class ResourceLoader
{
public:
    void LoadResources();
    void UnloadResources();

    void GetPathToResources();

private:
};