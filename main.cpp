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

// Sistema de registro de hora e data desenvolvido em aula
#include "Clock.cpp"
#include "Calendar.cpp"
#include "ClockCalendar.cpp"

// Classes inteiramente novas para o controle do sistema
#include "StepperMotor.cpp"
#include "FwrdSM.cpp"
#include "BwrdSM.cpp"
#include "LDR_A.cpp"
#include "LDR_D.cpp"
#include "List.cpp"


using namespace std;

// Abaixo consta a função externa que realiza a leitura dos dados de hora e data a serem incorporados na fila do log

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

// Função padrão do Raspberry Pi Pico para envio de dados por protocolo UART
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
    
    // Iniciando a comunicação UART e setando os pinos 16 e 17 como TXD e RXD (vide biblioteca hardware_uart)
    uart_init(uart0, 9600);  
    gpio_set_function(16, GPIO_FUNC_UART);
    gpio_set_function(17, GPIO_FUNC_UART);
    uart_set_format(uart0, 11, 1, UART_PARITY_NONE);


    // Definindo as portas gpio que serão utilizadas para o controle do motor de passo.
    const int STEPPER_IN1 = 0;
    const int STEPPER_IN2 = 1;
    const int STEPPER_IN3 = 2;
    const int STEPPER_IN4 = 3;

    // Definindo o pino da gpio 4 para ler os valores binarios do sensor LDR digital.
    const int LDR_DIG_PIN = 4;   
    LDR_dig ldrDig(LDR_DIG_PIN);

    const int LDR_ADC_PIN1 = 0; // set_gpio_init() define o pino gpio do adc (de 26-28)
    const int LDR_ADC_PIN2 = 1;
    const int LDR_GPIO_INIT_PIN1 = 26; //adc_select_input() define o pino da porta adc (de 0-2)
    const int LDR_GPIO_INIT_PIN2 = 27;

    LDR_analog ldr1(LDR_ADC_PIN1, LDR_GPIO_INIT_PIN1);
    LDR_analog ldr2(LDR_ADC_PIN2, LDR_GPIO_INIT_PIN2);

    /* Define os pinos que farão enviarão a informação para os 4 bits de controle para o driver 
       do motor de passo através de cada uma das bibliotecas de movimento.
    */
    ForwardStepperMotor forwardStepper(STEPPER_IN1, STEPPER_IN2, STEPPER_IN3, STEPPER_IN4);
    BackwardStepperMotor backwardStepper(STEPPER_IN1, STEPPER_IN2, STEPPER_IN3, STEPPER_IN4);

    // Cria as variáveis auxiliares que serão usadas para construção do log.
    int estado_LDR1;
    int estado_LDR2;
    int estado_LDRdig;

    // Inicia-se o loop infinito para manter o motor sempre em movimento
    while (true) {

        bool isDigitalHigh = ldrDig.isHigh();

        float voltage1 = ldr1.readVoltage();
        float voltage2 = ldr2.readVoltage();

        if (isDigitalHigh == 0){      // para o motor se o led digitar atender aos requisitos de iluminação
        forwardStepper.move(0, 50);  
        gpio_put(LED_PIN, 1);
        sleep_ms(10);
        estado_LDRdig = 1;           // as variáveis a serem integradas no log são atualizadas
        estado_LDR1 = 0;
        estado_LDR2 = 0;
        }
        
        else if (voltage1>=voltage2){   // faz o motor girar para a esquerda
        backwardStepper.move(5, 10);    // necessário um delay maior (5ms) para compensar construção precária do drive adquirido
        gpio_put(LED_PIN, 1);
        sleep_ms(10);
        estado_LDRdig = 0;
        estado_LDR1 = 1;
        estado_LDR2 = 0;
        }
        else{
        forwardStepper.move(1, 10);     // faz o motor girar para a direita
        sleep_ms(10); 
        estado_LDRdig = 0;
        estado_LDR1 = 1;
        estado_LDR2 = 0;
               }  

// Dados são incluídos na respectiva ordem da fila.
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



