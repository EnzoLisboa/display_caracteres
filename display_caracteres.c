#include <stdio.h>
#include <stdlib.h>
#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "hardware/uart.h"
#include "inc/ssd1306.h"
#include "inc/matriz_leds.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Pinos dos LEDs RGB
#define LED_GREEN_PIN 11
#define LED_BLUE_PIN 12

// Pinos dos botões
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6
#define BUTTON_C_PIN 22



// Variáveis globais
bool led_green = false;
bool led_blue = false;
static volatile uint32_t last_time = 0; // Define o tempo inicial (em microssegundos)




// Função para configurar os botões
void config_button(uint button)
{
    gpio_init(button);
    gpio_set_dir(button, GPIO_IN);
    gpio_pull_up(button);
}

// Função para configurar as leds

void config_led(uint led)
{
    gpio_init(led);
    gpio_set_dir(led, GPIO_OUT);
}

// Função de interrupção
void gpio_irq_handler(uint gpio, uint32_t events) {

    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 250000) // 250 ms de debouncing
    {
        last_time = current_time; // Atualiza o tempo do último evento
        if (gpio == BUTTON_A_PIN) {
            led_green = !led_green;
            gpio_put(LED_GREEN_PIN, led_green);
            printf("Botão A pressionado. LED Verde: %s\n", led_green ? "Ligado" : "Desligado");
        }
        else if (gpio == BUTTON_B_PIN) {
            led_blue = !led_blue;
            gpio_put(LED_BLUE_PIN, led_blue);
            printf("Botão B pressionado. LED Azul: %s\n", led_blue ? "Ligado" : "Desligado");
        }
        else if (gpio == BUTTON_C_PIN) {
            printf("Entrando em BOOTSEL\n");
            reset_usb_boot(0, 0);
        }
    }
}


int main()
{
    stdio_init_all();
    
    // Obtém o PIO e o state machine
    PIO pio = pio0;
    uint sm = configurar_matriz(pio);
    
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
    ssd1306_t ssd; // Inicializa a estrutura do display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    // Configura os botões
    config_button(BUTTON_A_PIN);
    config_button(BUTTON_B_PIN);
    config_button(BUTTON_C_PIN);

    // Configura as LEDs

    config_led(LED_GREEN_PIN);
    config_led(LED_BLUE_PIN);

    // Configura as interrupções para os botões
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_C_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Configura a UART
    uart_init(uart0, 9600);
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    n_off( pio, sm); // Inicia com a matriz de LEDs apagada
    
    while (true)
    {
        if (stdio_usb_connected())
        { // Certifica-se de que o USB está conectado
            char c;
            printf("Digite um caractere: \n");
            if (scanf("%c", &c) == true) // Verifica se um caractere foi lido
            {
                printf("Recebido: '%c'\n", c); // Exibe o caractere recebido
                // Se o caractere for um número, exibe na matriz de LEDs

                if (c >= '0' && c <= '9') // Se o caractere for um número
                {
                    ssd1306_fill(&ssd, false); // Limpa o display
                    ssd1306_send_data(&ssd); // Envia os dados para o display
                    int numero = c - '0';
                    switch (numero) {
                        case 0: n_zero(pio, sm); break;
                        case 1: n_um(pio, sm); break;
                        case 2: n_dois(pio, sm); break;
                        case 3: n_tres(pio, sm); break;
                        case 4: n_quatro(pio, sm); break;
                        case 5: n_cinco(pio, sm); break;
                        case 6: n_seis(pio, sm); break;
                        case 7: n_sete(pio, sm); break;
                        case 8: n_oito(pio, sm); break;
                        case 9: n_nove(pio, sm); break;
                    }
                }
                
                else if(c>='A' && c<='Z' || c>='a' && c<='z') // Se o caractere for uma letra
                {
                    n_off( pio, sm); // Apaga a matriz de LEDs
                    ssd1306_fill(&ssd, false); // Limpa o display
                    ssd1306_draw_char(&ssd, c, 64, 32); // Exibe o caractere
                    ssd1306_send_data(&ssd); // Envia os dados para o display
                }
                else // Se o caractere for inválido
                {
                    ssd1306_fill(&ssd, false); // Limpa o display
                    ssd1306_send_data(&ssd); // Envia os dados para o display
                    n_off( pio, sm); // Apaga a matriz de LEDs
                    printf("Caractere inválido\n");
                }
            }
        }
        sleep_ms(100); // Aguarda 100 ms
    }
}