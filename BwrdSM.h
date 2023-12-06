

#include "StepperMotor.h"

class BackwardStepperMotor : public StepperMotor<int> {
public:
    BackwardStepperMotor(int in1, int in2, int in3, int in4);
    void move(int steps, int delayTime) override;
    int getLastStep() const;
};