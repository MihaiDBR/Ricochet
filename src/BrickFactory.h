#pragma once
#include "Brick.h"
#include <memory>
#include <string>

class BrickFactory {
public:
    static std::unique_ptr<Brick> create
    (const std::string& type, float x, float y, float width, float height);
};