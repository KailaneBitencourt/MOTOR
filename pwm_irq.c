#include <stdio.h> // biblioteca padrão da linguagem C
#include "pico/stdlib.h" // subconjunto central de bibliotecas do SDK Pico
#include "pico/time.h" // biblioteca para gerenciamento de tempo
#include "hardware/pwm.h" // biblioteca para controlar o hardware de PWM

#define SERVOMOTOR 12 // pino do SERVOMOTOR conectado

// Função para configurar o PWM
void pwm_setup(uint32_t sliceNum, uint32_t pwmPin, uint32_t pulseWidth){
    gpio_set_function(pwmPin, GPIO_FUNC_PWM); // Habilitar o pino GPIO como PWM
    sliceNum = pwm_gpio_to_slice_num(pwmPin); // Obtém o slice PWM correspondente ao pino

    pwm_set_wrap(sliceNum, 20000); // Define o valor de wrap para 20 ms 
    pwm_set_clkdiv(sliceNum, 125000000.0f / (50.0f * 20000.0f)); // Define o divisor de clock para 50 Hz 
    pwm_set_gpio_level(pwmPin, pulseWidth); // Define o ciclo ativo 

    pwm_set_enabled(sliceNum, true); // Habilita o PWM para o slice
}

// Função para ajustar a posição do servomotor
void move_servo(int position) {
    uint32_t pulseWidth;

    if (position == 180) {
        pulseWidth = 2400; 
    } else if (position == 90) {
        pulseWidth = 1470; 
    } else if (position == 0) {
        pulseWidth = 500; 
    } else {
        return;
    }

    uint32_t sliceNum = 0; 
    pwm_setup(sliceNum, SERVOMOTOR, pulseWidth); 
    sleep_ms(5000); 
}

//Função para a movimentação periodica
void movimentacao_periodica() {
    uint32_t pulseWidth = 500; 
    uint32_t sliceNum = 0; 
    while (pulseWidth <= 2400) { 
        pwm_setup(sliceNum, SERVOMOTOR, pulseWidth); 
        sleep_ms(10); 
        pulseWidth += 5; 
    }
    while (pulseWidth >= 500) { 
        pwm_setup(sliceNum, SERVOMOTOR, pulseWidth); 
        sleep_ms(10); 
        pulseWidth -= 5; 
    }
}


int main() {
    stdio_init_all(); 
    printf("Movendo para 180 graus...\n");
    move_servo(180); 
    printf("Movendo para 90 graus...\n");
    move_servo(90); 
    printf("Movendo para 0 graus...\n");
    move_servo(0); 
    while (1) { 
        movimentacao_periodica();
    }
}
