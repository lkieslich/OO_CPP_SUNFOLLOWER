/*
Software preliminar a ser embarcado no Raspbery Pi Pico para um sistema seguidor de luz solar (sun sensor).

Lucas da Rosa Kieslich
*/

#include <iostream>
#include <stdexcept>
#include <vector>

#include <unistd.h>
#include <fcntl.h>

#include <iomanip>
#include <time.h>
#include <string>

//#include <termios.h>

//bibliotecas que foram propriamente adicionadas no arquivo CMakeList.txt
//necessario a presença do pico-sdk https://github.com/raspberrypi/pico-sdk.git

#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "pico/stdio_usb.h"

#include "Clock.cpp"
#include "Calendar.cpp"
#include "ClockCalendar.cpp"

#include "StepperMotor.cpp"
#include "FwrdSM.cpp"
#include "BwrdSM.cpp"
#include "LDR_A.cpp"
#include "LDR_D.cpp"
#include "List.cpp"


using namespace std;

void call_clock_calendar(int& hora, int& min, int& seg, int& dia, int& mes, int& ano, int& ampm){
        int64_t this_time, last_time;
        int64_t currentTime = time_us_64(); 
        int aux_hour, aux_min, aux_sec, aux_ampm, aux_dia, aux_mes, aux_ano;  
        ClockCalendar clkCalendar(aux_hour, aux_min, aux_sec, aux_ampm, aux_dia, aux_mes, aux_ano);
        double time_counter = 0;
        time_counter += (double)(this_time - last_time);

        last_time = this_time;
        
        if(time_counter > 1)
        {   
       
        clkCalendar.readClock(hora, seg, min, ampm);
        clkCalendar.readCalendar(mes, dia, ano);

        time_counter -= 1;
            //count++;
            clkCalendar.advance();
        }

    }   

void send_data_via_uart(const int* data, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        uart_putc(uart0, data[i]);
    }
}

int main() {
  List Fila_log;

  int dadosR[11] = {0};// buffer temporário para recebimento dos dados enviados pela uart.
  int hora, min, seg, dia, mes, ano, ampm;
  Fila_log.insertAfterLast(dadosR[0], dadosR[1], dadosR[2], dadosR[3], dadosR[4], dadosR[5], dadosR[6], dadosR[7], dadosR[8], dadosR[9], dadosR[10]);

    call_clock_calendar(hora, min, seg, dia, mes, ano, ampm);

    stdio_usb_init();
    
    uart_init(uart0, 9600);  
    gpio_set_function(16, GPIO_FUNC_UART);
    gpio_set_function(17, GPIO_FUNC_UART);
    uart_set_format(uart0, 8, 1, UART_PARITY_NONE);


   

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

    int estado_LDR1;
    int estado_LDR2;
    int estado_LDRdig;


    while (true) {
        printf("Hello, PC!\n");

        bool isDigitalHigh = ldrDig.isHigh();

        float voltage1 = ldr1.readVoltage();
        float voltage2 = ldr2.readVoltage();

        if (isDigitalHigh == 0){
        forwardStepper.move(0, 50);  
        gpio_put(LED_PIN, 1);
        sleep_ms(10);
        estado_LDRdig = 1; 
        estado_LDR1 = 0;
        estado_LDR2 = 0;
        }
        
        else if (voltage1>=voltage2){
        backwardStepper.move(5, 10); 
        gpio_put(LED_PIN, 1);
        sleep_ms(10);
        estado_LDRdig = 0;
        estado_LDR1 = 1;
        estado_LDR2 = 0;
        }
        else{
        forwardStepper.move(1, 10);  
        sleep_ms(10); 
        estado_LDRdig = 0;
        estado_LDR1 = 1;
        estado_LDR2 = 0;
               }  


        dadosR[0] = estado_LDR1;
        dadosR[1] = estado_LDR2;
        dadosR[2] = estado_LDRdig;
        dadosR[3] = forwardStepper.getLastStep();
        dadosR[4] = hora;
        dadosR[5] = seg;
        dadosR[6] = min;
        dadosR[7] = ampm;
        dadosR[8] = dia;
        dadosR[9] = mes;
        dadosR[10] = ano;

       send_data_via_uart(dadosR, sizeof(dadosR) / sizeof(dadosR[0]));     // Envia os dados pela UART

        }


    return 0;
}



