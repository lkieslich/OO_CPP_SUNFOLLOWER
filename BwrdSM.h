/*
Biblioteca tem como objetivo mover o motor de passo para trás (esquerda ou anti-horario)
a partir do envio de sinal para os bits de 1/4 de passo do quarto para o primeiro a partir 
das funcões desenvolvidas na classe StepperMotor.
*/

#include "StepperMotor.h"

class BackwardStepperMotor : public StepperMotor<int> {
public:
    BackwardStepperMotor(int in1, int in2, int in3, int in4);
    void move(int steps, int delayTime) override;
    int getLastStep() const;
};