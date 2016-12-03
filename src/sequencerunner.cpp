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
    planRandomEffect(4, *inputString, mainNode);
}

void SequenceRunner::planRandomEffect(float time, InputString &inputString, Node &mainNode)
{
    if (inputString.isEmpty()) {
        delete(&inputString);
        return;
    }

    std::vector<Effect*> possibleEffects;
    std::vector<int> probab;
    int sum = 0;
    for (uint i = 0; i < _effects.size(); ++i) {
        int exc = _effects[i]->acceptsString(inputString);
        if (exc > 0) {
            possibleEffects.push_back(_effects[i]);
            sum += exc;
            probab.push_back(sum);
        }
    }

    // Choose one of them with weight
    int r = rand() % sum;
    Effect *chosenEffect = nullptr;
    for (uint i = 0; i < possibleEffects.size(); ++i) {
        if (probab[i] > r) {
            chosenEffect = possibleEffects[i];
            break;
        }
    }

    auto cb = new CallFunction(time, [
        this, &mainNode, &inputString, chosenEffect, time
    ]{
        // Create group for the effect
        Group *effectGroup = new Group();
        effectGroup->setContentSize(1920, 1080);
        effectGroup->setAnchorPoint(0, 0);
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
