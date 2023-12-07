/*
Classe para leitura do sensor digital.
Simplesmente seta a gpio que deverá ser lida
*/
#include "LDR_D.h"

LDR_dig::LDR_dig(int gpioPin)
    : GPIO_PIN(gpioPin) {
    gpio_init(GPIO_PIN);
    gpio_set_dir(GPIO_PIN, GPIO_IN);
}

LDR_dig::~LDR_dig() {}

bool LDR_dig::isHigh() {
    return gpio_get(GPIO_PIN) == 1;
}