#include "BrickFactory.h"
#include "NormalBrick.h"
#include "HardBrick.h"
#include "ExplosiveBrick.h"
#include "InvisibleBrick.h"
#include <stdexcept>

std::unique_ptr<Brick> BrickFactory::create(const std::string& type, float x, float y, float width, float height) {
    if (type == "normal")
        return std::make_unique<NormalBrick>(x, y, width, height);
    if (type == "hard")
        return std::make_unique<HardBrick>(x, y, width, height);
    if (type == "explosive")
        return std::make_unique<ExplosiveBrick>(x, y, width, height);
    if (type == "invisible")
        return std::make_unique<InvisibleBrick>(x, y, width, height);
    throw std::invalid_argument("Tip brick necunoscut: " + type);
}