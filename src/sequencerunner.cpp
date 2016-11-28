#include "sequencerunner.h"

// debug
#include <iostream>

SequenceRunner::SequenceRunner(std::vector<Effect*> &effects)
{
    if (effects.size() == 0) {
        throw std::runtime_error("Cannot create SequenceRunner with no effects");
    }
    _effects = effects;
}

void SequenceRunner::run(std::string str, int seed, Node &mainNode)
{
    srand(seed);

    InputString inputString(str);
    float elapsedTime = 0;

    while (!inputString.isEmpty()) {
        // Populate effects that are interested
        std::vector<Effect*> possibleEffects;
        for (uint i = 0; i < _effects.size(); ++i) {
            if (_effects[i]->acceptsString(inputString)) {
                possibleEffects.push_back(_effects[i]);
            }
        }

        // Choose one of them
        Group *effectGroup = new Group();
        effectGroup->setPosition(-1920, 0);
        mainNode.addChild(effectGroup);
        int effectIndex = rand() % possibleEffects.size();
        elapsedTime += possibleEffects[effectIndex]->run(inputString, *effectGroup, elapsedTime);
    }
}
