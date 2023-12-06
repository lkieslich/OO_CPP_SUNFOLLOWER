
#include "hardware/gpio.h"

class LDR_dig {
public:
    LDR_dig(int gpioPin);
    ~LDR_dig();

    bool isHigh();

private:
    const int GPIO_PIN;
};