

#include "StepperMotor.h"

class ForwardStepperMotor : public StepperMotor<int> {
public:
    ForwardStepperMotor(int in1, int in2, int in3, int in4);
    void move(int steps, int delayTime) override;
    int getLastStep() const;
};
