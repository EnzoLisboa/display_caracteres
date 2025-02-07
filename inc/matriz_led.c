#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "matriz_leds.h"

// Arquivo .pio para controle da matriz
#include "pio_matrix.pio.h"

// Pino que realizará a comunicação do microcontrolador com a matriz
#define OUT_PIN 7

// Definir constantes para os valores RGB
#define RGB_OFF {0.0, 0.0, 0.0}
#define RGB_ON {0.3, 0.3, 0.3}


// Funções para matriz de LEDs
uint32_t gerar_binario_cor(double red, double green, double blue)
{
  unsigned char RED, GREEN, BLUE;
  RED = red * 255.0;
  GREEN = green * 255.0;
  BLUE = blue * 255.0;
  return (GREEN << 24) | (RED << 16) | (BLUE << 8);
}

uint configurar_matriz(PIO pio){
    bool ok;

    // Define o clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    printf("iniciando a transmissão PIO");
    if (ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));

    //configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    return sm;
}

void imprimir_desenho(Matriz_leds_config configuracao, PIO pio, uint sm){
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--){
        if(contadorLinha % 2){
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna ++){
                uint32_t valor_cor_binario = gerar_binario_cor(
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green,
                    configuracao[contadorLinha][contadorColuna].blue
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }else{
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna --){
                uint32_t valor_cor_binario = gerar_binario_cor(
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green,
                    configuracao[contadorLinha][contadorColuna].blue
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }
    }
}

// Função genérica para imprimir números
void imprimir_numero(PIO pio, uint sm, Matriz_leds_config matriz)
{
    imprimir_desenho(matriz, pio, sm);
}


// Funções para imprimir os números
void n_zero(PIO pio, uint sm)
{
    Matriz_leds_config matriz_zero = {
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 0
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 1
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 2
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 3
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 4
    };
    imprimir_numero(pio, sm, matriz_zero);
}

void n_um(PIO pio, uint sm)
{
    Matriz_leds_config matriz_um = {
        {RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF, RGB_OFF}, // Linha 0
        {RGB_OFF, RGB_ON, RGB_ON, RGB_OFF, RGB_OFF}, // Linha 1
        {RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF, RGB_OFF}, // Linha 2
        {RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF, RGB_OFF}, // Linha 3
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 4
    };
    imprimir_numero(pio, sm, matriz_um);
}

void n_dois(PIO pio, uint sm)
{
    Matriz_leds_config matriz_dois = {
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 0
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 1
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 2
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_OFF, RGB_OFF}, // Linha 3
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 4
    };
    imprimir_numero(pio, sm, matriz_dois);
}

void n_tres(PIO pio, uint sm)
{
    Matriz_leds_config matriz_tres = {
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 0
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 1
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 2
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 3
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 4
    };
    imprimir_numero(pio, sm, matriz_tres);
}

void n_quatro(PIO pio, uint sm)
{
    Matriz_leds_config matriz_quatro = {
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 0
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 1
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 2
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 3
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 4
    };
    imprimir_numero(pio, sm, matriz_quatro);
}

void n_cinco(PIO pio, uint sm)
{
    Matriz_leds_config matriz_cinco = {
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 0
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_OFF, RGB_OFF}, // Linha 1
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 2
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 3
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 4
    };
    imprimir_numero(pio, sm, matriz_cinco);
}

void n_seis(PIO pio, uint sm)
{
    Matriz_leds_config matriz_seis = {
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 0
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_OFF, RGB_OFF}, // Linha 1
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 2
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 3
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 4
    };
    imprimir_numero(pio, sm, matriz_seis);
}

void n_sete(PIO pio, uint sm)
{
    Matriz_leds_config matriz_sete = {
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 0
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 1
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 2
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 3
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 4
    };
    imprimir_numero(pio, sm, matriz_sete);
}

void n_oito(PIO pio, uint sm)
{
    Matriz_leds_config matriz_oito = {
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 0
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 1
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 2
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 3
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 4
    };
    imprimir_numero(pio, sm, matriz_oito);
}

void n_nove(PIO pio, uint sm)
{
    Matriz_leds_config matriz_nove = {
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 0
        {RGB_OFF, RGB_ON, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 1
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 2
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_ON, RGB_OFF}, // Linha 3
        {RGB_OFF, RGB_ON, RGB_ON, RGB_ON, RGB_OFF}, // Linha 4
    };
    imprimir_numero(pio, sm, matriz_nove);
}

void n_off(PIO pio, uint sm)
{
    Matriz_leds_config matriz_off = {
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_OFF, RGB_OFF}, // Linha 0
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_OFF, RGB_OFF}, // Linha 1
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_OFF, RGB_OFF}, // Linha 2
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_OFF, RGB_OFF}, // Linha 3
        {RGB_OFF, RGB_OFF, RGB_OFF, RGB_OFF, RGB_OFF}, // Linha 4
    };
    imprimir_numero(pio, sm, matriz_off);
}