
#include "hardware/gpio.h"

class LDR_analog {
public:
    LDR_analog(int adcPin, int gpio_initPin);
    ~LDR_analog();

    float readVoltage();

private:
    const int ADC_PIN;
    const int GPIO_INIT_PIN;
};