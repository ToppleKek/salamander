#include <iostream>
#include "engine/Engine.h"
#include "TheSalamander.h"

int main(int, char **) {
    Engine engine(std::make_unique<TheSalamander>());

    return engine.start();
}
