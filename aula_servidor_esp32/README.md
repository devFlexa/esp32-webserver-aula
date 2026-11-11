# Servidor web na ESP32

Abra **esta pasta** como projeto PlatformIO. O teste independente de GPIO está em `../exemplos/teste_gpio/`.

1. Conecte um LED e um resistor de 220 a 1000 ohms em serie entre **GPIO 21** e **GND** (anodo voltado ao GPIO).
2. Execute **Upload** para gravar o firmware.
3. Execute **Upload Filesystem Image** para enviar os arquivos de `data/` ao SPIFFS.
4. Abra o Monitor Serial em **115200 baud**.
5. Conecte-se a rede **ESP32-Aula**, senha **AulaESP32**.
6. Acesse **http://192.168.4.1** e use os botoes.

No terminal do PlatformIO, os comandos equivalentes sao `pio run -t upload`, `pio run -t uploadfs` e `pio device monitor -b 115200`.

Depois de editar HTML, CSS ou JavaScript, execute novamente **Upload Filesystem Image**. Depois de editar `src/main.cpp`, execute **Upload**. O modo ponto de acesso funciona sem roteador ou Internet.

A aula completa pode ser aberta no navegador pelo arquivo `../aula_esp32.html`.
