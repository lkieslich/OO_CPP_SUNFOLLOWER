#pragma once

#include <stdio.h>
#include <iostream>

template <typename T>
class StepperMotor {
    template <typename U>
    friend void customFunction(const StepperMotor<U>& stepper);

public:
    StepperMotor(int in1, int in2, int in3, int in4);
    virtual ~StepperMotor();

    virtual void move(int steps, int delayTime) = 0;

    // Sobrecarga de operador
    bool operator==(const StepperMotor<T>& other) const;

protected:
    const int IN1;
    const int IN2;
    const int IN3;
    const int IN4;
    int lastStep;  // Variavel para trackear o ultimo passo

    void setStep(int w1, int w2, int w3, int w4);
    void updateLastStep(int step);
};