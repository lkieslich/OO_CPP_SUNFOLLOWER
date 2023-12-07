/*
Biblioteca tem como objetivo mover o motor de passo para trás (esquerda ou anti-horario)
a partir do envio de sinal para os bits de 1/4 de passo do quarto para o primeiroa partir 
das funcões desenvolvidas na classe StepperMotor.
*/

#include "BwrdSM.h"
#include "pico/stdlib.h"


BackwardStepperMotor::BackwardStepperMotor(int in1, int in2, int in3, int in4)
    : StepperMotor<int>(in1, in2, in3, in4) {}

void BackwardStepperMotor::move(int steps, int delayTime) {
    for (int i = 0; i < steps; ++i) {
        setStep(0, 0, 0, 1);
        setStep(0, 0, 1, 0);
        setStep(0, 1, 0, 0);
        setStep(1, 0, 0, 0);
        updateLastStep(i % 4);  
        sleep_ms(delayTime);
    }
}

int BackwardStepperMotor::getLastStep() const {
    return lastStep;
}