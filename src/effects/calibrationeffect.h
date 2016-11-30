/*
 * calibrationeffect.h
 *
 *  Created on: Nov 30, 2016
 *      Author: gazdik
 */

#ifndef SRC_EFFECTS_CALIBRATIONEFFECT_H_
#define SRC_EFFECTS_CALIBRATIONEFFECT_H_

#include "effect.h"

class CalibrationEffect: public Effect
{
public:
    CalibrationEffect();
    virtual ~CalibrationEffect();

    float run(InputString &str, Node &inputNode, float startTime) override;
    bool acceptsString(InputString const &inputString) override;
};

#endif /* SRC_EFFECTS_CALIBRATIONEFFECT_H_ */
