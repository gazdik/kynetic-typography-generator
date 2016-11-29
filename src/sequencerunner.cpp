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

    InputString *inputString = new InputString(str);
    planRandomEffect(0, *inputString, mainNode);
}

void SequenceRunner::planRandomEffect(float time, InputString &inputString, Node &mainNode)
{
    if (inputString.isEmpty()) {
        delete(&inputString);
        return;
    }

    std::vector<Effect*> possibleEffects;
    for (uint i = 0; i < _effects.size(); ++i) {
        if (_effects[i]->acceptsString(inputString)) {
            possibleEffects.push_back(_effects[i]);
        }
    }

    // Choose one of them
    int effectIndex = rand() % possibleEffects.size();
    Effect *chosenEffect = possibleEffects[effectIndex];

    auto cb = new CallFunction(time, [
        this, &mainNode, &inputString, chosenEffect, time
    ]{
        // Create group for the effect
        Group *effectGroup = new Group();
        effectGroup->setPosition(0, -1080);

        mainNode.addChild(effectGroup);

        float duration = chosenEffect->run(inputString, *effectGroup, 0);


        // Plan group destruction
        //effectGroup->runAction(duration + 5, new RemoveNode());

        // Plan next effect
        planRandomEffect(duration, inputString, mainNode);

    });

    cb->run();
}
