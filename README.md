# Teste de GPIO do ESP32 com PlatformIO

Projeto para **ESP32 DevKit / ESP32-WROOM**, com framework Arduino. Se a sua placa for outro modelo (ESP8266, ESP32-S3, ESP32-C3 etc.), ajuste `board` em `platformio.ini` e a lista de pinos em `src/main.cpp` antes de gravar.

## Gravar e testar

1. Abra esta pasta no VS Code com a extensao PlatformIO.
2. Conecte o ESP32 por USB e use **PlatformIO: Upload**.
3. Abra **PlatformIO: Serial Monitor** em **115200 baud**. Configure o fim de linha como **Newline**.
4. Envie `pinos` para ver os GPIOs disponiveis.
5. Para testar uma saida, conecte um LED com resistor de 220 a 1000 ohms entre o GPIO escolhido e GND. Envie `pulso 21`, por exemplo. O LED deve piscar tres vezes.
6. Para testar uma entrada, envie `entrada 21`, conecte temporariamente o GPIO 21 ao GND e envie `ler 21`. Sem a conexao, a leitura sera `HIGH`; com ela, `LOW`.

Tambem ha comandos `saida N`, `alto N` e `baixo N` para controle manual. `entrada N` libera o pino depois do teste. GPIOs 34, 35, 36 e 39 so podem ser entradas e **nao possuem pull-up interno**; use um resistor externo para definir seu nivel. O programa nao altera os GPIOs automaticamente ao iniciar.

**Cuidados:** use somente sinais de 3,3 V; nao ligue um GPIO diretamente a 5 V. Confira o esquema da sua placa e desconecte dispositivos externos antes de testar pinos que possam estar ligados a eles.
