/*
Software preliminar a ser embarcado no Raspbery Pi Pico para um sistema seguidor de luz solar (sun sensor).

Lucas da Rosa Kieslich
*/

#include <iostream>
#include <stdexcept>
#include <vector>

#include <unistd.h>
#include <fcntl.h>
//#include <termios.h>

//bibliotecas que foram propriamente adicionadas no arquivo CMakeList.txt
//necessario a presença do pico-sdk https://github.com/raspberrypi/pico-sdk.git
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "hardware/uart.h"

using namespace std;

template <typename T>
class StepperMotor {
    template <typename U>
    friend void customFunction(const StepperMotor<U>& stepper);

public:
    StepperMotor(int in1, int in2, int in3, int in4)
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

    virtual ~StepperMotor() {}

    virtual void move(int steps, int delayTime) = 0;

    // Sobrecarga de operador
    bool operator==(const StepperMotor<T>& other) const {
        return this->lastStep == other.lastStep;
    }

protected:
    const int IN1;
    const int IN2;
    const int IN3;
    const int IN4;
    int lastStep;  // Variavel para trackear o ultimo passo

    void setStep(int w1, int w2, int w3, int w4) {
        gpio_put(IN1, w1);
        gpio_put(IN2, w2);
        gpio_put(IN3, w3);
        gpio_put(IN4, w4);
        sleep_ms(20);
    }

    void updateLastStep(int step) {
        lastStep = step;
    }
};

// Função friend para o StepperMotor
template <typename T>
void customFunction(const StepperMotor<T>& stepper) {
    cout << "Friend function called. Last step: " << stepper.lastStep << endl;
}

class ForwardStepperMotor : public StepperMotor<int> {
public:
    ForwardStepperMotor(int in1, int in2, int in3, int in4)
        : StepperMotor<int>(in1, in2, in3, in4) {}

    void move(int steps, int delayTime) override {
        for (int i = 0; i < steps; ++i) {
            setStep(1, 0, 0, 0);
            setStep(0, 1, 0, 0);
            setStep(0, 0, 1, 0);
            setStep(0, 0, 0, 1);
            updateLastStep(i % 4);  // Atualiza o passo de acordo com o passo atual
            sleep_ms(delayTime);
        }
    }
    int getLastStep() const {
        return lastStep;
     }
};

class BackwardStepperMotor : public StepperMotor<int> {
public:
    BackwardStepperMotor(int in1, int in2, int in3, int in4)
        : StepperMotor<int>(in1, in2, in3, in4) {}

    void move(int steps, int delayTime) override {
        for (int i = 0; i < steps; ++i) {
            setStep(0, 0, 0, 1);
            setStep(0, 0, 1, 0);
            setStep(0, 1, 0, 0);
            setStep(1, 0, 0, 0);
            updateLastStep(i % 4);  
            sleep_ms(delayTime);
        }
    }
    int getLastStep() const {
    return lastStep;
     }
};

class LDR_analog {
public:
    LDR_analog(int adcPin, int gpio_initPin)
        : ADC_PIN(adcPin), GPIO_INIT_PIN(gpio_initPin) {
        adc_init();
        adc_gpio_init(adcPin); 
        adc_select_input(gpio_initPin);
        adc_set_temp_sensor_enabled(true);

        
    }

    ~LDR_analog() {}

    float readVoltage() {
        adc_select_input(GPIO_INIT_PIN); 
        adc_select_input(ADC_PIN);

        // Permite o ADC fazer a conversão completa
        sleep_ms(1);

        // Lê o resultado
        uint16_t rawValue = adc_read();

        float voltage = (rawValue /3.3) / (1 << 12); // porque o Vref é 3.3V
        return voltage;
    }

private:
    const int ADC_PIN;
    const int GPIO_INIT_PIN;
};

class LDR_dig {
public:
    LDR_dig(int gpioPin)
        : GPIO_PIN(gpioPin) {
        gpio_init(GPIO_PIN);
        gpio_set_dir(GPIO_PIN, GPIO_IN);

     
    }

    ~LDR_dig() {}

    bool isHigh() {
        return gpio_get(GPIO_PIN) == 1;
    }

private:
    const int GPIO_PIN;
};


std::vector<float> listaVoltage1;
std::vector<float> listaVoltage2;
std::vector<int> listaLastStep;

int main() {

    uart_init(uart0, 9600);  // Baud rate a definir................
    uart_set_format(uart0, 8, 1, UART_PARITY_NONE);

    uart_puts(uart0, "Hello, USB!\n");

    const int STEPPER_IN1 = 0;
    const int STEPPER_IN2 = 1;
    const int STEPPER_IN3 = 2;
    const int STEPPER_IN4 = 3;

    const int LDR_DIG_PIN = 4;   
    LDR_dig ldrDig(LDR_DIG_PIN);

    const int LDR_ADC_PIN1 = 0; // set_gpio_init() define o pino gpio do adc (de 26-28)
    const int LDR_ADC_PIN2 = 1;
    const int LDR_GPIO_INIT_PIN1 = 26; //adc_select_input() define o pino da porta adc (de 0-2)
    const int LDR_GPIO_INIT_PIN2 = 27;

    LDR_analog ldr1(LDR_ADC_PIN1, LDR_GPIO_INIT_PIN1);
    LDR_analog ldr2(LDR_ADC_PIN2, LDR_GPIO_INIT_PIN2);

    ForwardStepperMotor forwardStepper(STEPPER_IN1, STEPPER_IN2, STEPPER_IN3, STEPPER_IN4);
    BackwardStepperMotor backwardStepper(STEPPER_IN1, STEPPER_IN2, STEPPER_IN3, STEPPER_IN4);


    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);



    while (true) {
        bool isDigitalHigh = ldrDig.isHigh();

        float voltage1 = ldr1.readVoltage();
        float voltage2 = ldr2.readVoltage();

        if (isDigitalHigh == 0){
        forwardStepper.move(0, 50);  
        gpio_put(LED_PIN, 1);
        sleep_ms(10); 
        }
        
        else if (voltage1>=voltage2){
        backwardStepper.move(5, 50); 
        gpio_put(LED_PIN, 1);
        sleep_ms(10);
        }
        else{
        forwardStepper.move(1, 10);  
        sleep_ms(10); 
               }  
  //      uart_puts(uart0, ("Voltage1: " + to_string(voltage1) + "\n").c_str());
  //      uart_puts(uart0, ("Voltage2: " + to_string(voltage2) + "\n").c_str());
  //      uart_puts(uart0, ("LastStep: " + to_string(forwardStepper.getLastStep()) + "\n").c_str());
    listaVoltage1.push_back(voltage1);
    listaVoltage2.push_back(voltage2);
    listaLastStep.push_back(forwardStepper.getLastStep());

    // Envia os dados pela UART
    for (size_t i = 0; i < listaVoltage1.size(); ++i) {
        printf("Voltage1: %.2f, Voltage2: %.2f, LastStep: %d\n", listaVoltage1[i], listaVoltage2[i], listaLastStep[i]);
     }
        }


    return 0;
}



