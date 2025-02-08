# Display Caracteres

Exibição de Caracteres com Matriz de LEDs e Display OLED

Este projeto implementa a exibição de caracteres utilizando uma matriz de LEDs controlada por um microcontrolador Raspberry Pi Pico e um display OLED SSD1306. O projeto permite a exibição de números de 0 a 9 na matriz de LEDs e letras(maiúsculas ou minúsculas) de A a Z no display OLED.

## Funcionalidades

- **Exibição de Números**: Números de 0 a 9 são exibidos em uma matriz de LEDs 5x5.
- **Exibição de Letras**: Letras de A a Z são exibidas no display OLED SSD1306.
- **Envio de Caracteres pelo Serial Monitor**: Caracteres enviados pelo Serial Monitor são exibidos no display OLED ou na matriz de LEDs.
- **Botões de Controle**:
  - **Botão A**: Alterna o estado do LED verde.
  - **Botão B**: Alterna o estado do LED azul.
  - **Botão C**: Entra no modo de bootsel do Raspberry Pi Pico.
- **Interrupções**: Interrupções para os botões.

## Estrutura do Código

O código está organizado da seguinte forma:

- **Inclusão de Bibliotecas**: Inclui as bibliotecas necessárias para controlar o Raspberry Pi Pico, a matriz de LEDs, o display OLED e os botões.
- **Definição de Pinos**: Define os pinos utilizados para a matriz de LEDs, display OLED, botões e LEDs indicadores.
- **Funções para Controle do Display OLED**:
  - `ssd1306_fill`: Limpa o display OLED.
  - `ssd1306_draw_char`: Desenha um caractere no display OLED.
  - `ssd1306_send_data`: Envia os dados para o display OLED.
- **Funções de Interrupção**:
  - `gpio_irq_handler`: Gerencia as interrupções dos botões, atualizando o estado dos LEDs e o modo de operação.
- **Funções Auxiliares**:
  - `config_button`: Configura os botões como entradas com pull-up.
  - `config_led`: Configura os LEDs como saídas.
- **Funções para Exibir Números na Matriz de LEDs**:
  - `n_zero` a `n_nove`: Funções que definem os padrões de LEDs para cada número de 0 a 9.
- **Função Principal (main)**:
  - Inicializa os botões, LEDs, matriz de LEDs e display OLED.
  - Entra em um loop infinito onde verifica o estado dos botões e exibe o caractere correspondente na matriz de LEDs ou no display OLED.

## Requisitos

### Hardware

- Raspberry Pi Pico.
- Matriz de LEDs 5x5.
- Display OLED SSD1306.
- Três botões.
- LEDs indicadores.
- Resistores e fios conforme necessário.

### Software

- SDK do Raspberry Pi Pico.
- Compilador compatível com C/C++.

## Como Usar

### Compilação

Compile o código utilizando o ambiente de desenvolvimento apropriado para o Raspberry Pi Pico (por exemplo, o SDK do Raspberry Pi Pico).

### Upload

Carregue o código compilado no Raspberry Pi Pico.

### Operação

- Pressione o Botão A para alternar o estado do LED verde.
- Pressione o Botão B para alternar o estado do LED azul.
- Pressione o Botão C para entrar no modo de bootsel.
- Envie caracteres pelo Serial Monitor para exibi-los no display OLED ou na matriz de LEDs.

## Demonstração

[Assista ao vídeo da demonstração](https://drive.google.com/file/d/1SY2i4aN8Uf4EV91dtX9srxX5SR73hCyl/view?usp=sharing)