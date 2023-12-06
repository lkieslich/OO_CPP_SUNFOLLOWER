#include "StepperMotor.h"

template <typename T>
StepperMotor<T>::StepperMotor(int in1, int in2, int in3, int in4)
    : IN1(in1), IN2(in2), IN3(in3), IN4(in4), lastStep(0) {
    stdio_init_all();
    gpio_init(IN1);
    gpio_init(IN2);
    gpio_init(IN3);
    gpio_init(IN4);
    gpio_set_dir(IN1, GPIO_OUT);
    gpio_set_dir(IN2, GPIO_OUT);
    gpio_set_dir(IN3, GPIO_OUT);
    gpio_set_dir(IN4, GPIO_OUT);
}

template <typename T>
StepperMotor<T>::~StepperMotor() {}

template <typename T>
bool StepperMotor<T>::operator==(const StepperMotor<T>& other) const {
    return this->lastStep == other.lastStep;
}

template <typename T>
void StepperMotor<T>::setStep(int w1, int w2, int w3, int w4) {
    gpio_put(IN1, w1);
    gpio_put(IN2, w2);
    gpio_put(IN3, w3);
    gpio_put(IN4, w4);
    sleep_ms(20);
}

template <typename T>
void StepperMotor<T>::updateLastStep(int step) {
    lastStep = step;
}