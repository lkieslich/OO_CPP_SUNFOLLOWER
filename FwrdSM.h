/*
Biblioteca tem como objetivo mover o motor de passo para frente (direita ou horario)
a partir do envio de sinal para os bits de 1/4 de passo do primeiro para o últimoa partir 
das funcões desenvolvidas na classe StepperMotor.
*/

#include "StepperMotor.h"

class ForwardStepperMotor : public StepperMotor<int> {
public:
    ForwardStepperMotor(int in1, int in2, int in3, int in4);
    void move(int steps, int delayTime) override;
    int getLastStep() const;
};
