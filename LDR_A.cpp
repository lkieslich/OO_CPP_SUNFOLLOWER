/*
Classe onde é feita a implementação para leitura dos sensores analógicos.
*/
#include "LDR_A.h"


LDR_analog::LDR_analog(int adcPin, int gpio_initPin)
    : ADC_PIN(adcPin), GPIO_INIT_PIN(gpio_initPin) {
    adc_init();
    adc_gpio_init(adcPin); // seta a gpio como adc
    adc_select_input(gpio_initPin); // inicia o pino previamente definido para leitura analogica
    adc_set_temp_sensor_enabled(true);
}

LDR_analog::~LDR_analog() {}

float LDR_analog::readVoltage() {
    adc_select_input(GPIO_INIT_PIN); 
    adc_select_input(ADC_PIN);

    // Permite o ADC fazer a conversão completa
    sleep_ms(1);

    // Lê o resultado
    uint16_t rawValue = adc_read();

    float voltage = (rawValue /3.3) / (1 << 12); // porque o Vref é 3.3V
    return voltage;
}