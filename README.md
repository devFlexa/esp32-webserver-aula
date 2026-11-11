# ESP32 como servidor web — aula prática

Material para jovens de 14 a 16 anos, com diagramas, simulador de requisições HTTP, atividades e quiz.

## Comece pela aula

Baixe o repositório e abra `aula_esp32.html` no navegador. A aula funciona offline e explica conceitos, montagem, programação e testes.

## Projeto da ESP32

Abra a pasta `aula_servidor_esp32` no VS Code com a extensão PlatformIO. O projeto usa ESP32 DevKit / ESP32-WROOM e framework Arduino.

1. Ligue GPIO 21 → resistor de 220 a 1000 Ω → ânodo do LED; cátodo → GND.
2. Execute **Upload** para gravar o firmware.
3. Execute **Upload Filesystem Image** para enviar a página.
4. Conecte-se à rede **ESP32-Aula**, senha **AulaESP32**.
5. Abra **http://192.168.4.1** no navegador.

Use o Monitor Serial em **115200 baud**. As instruções completas estão no README do projeto e na aula.

## Organização

- `aula_esp32.html`: aula ilustrada e interativa.
- `aula_servidor_esp32/`: projeto PlatformIO do servidor e arquivos HTML, CSS e JavaScript.
- `exemplos/teste_gpio/`: projeto independente para testar entradas e saídas.

O firmware precisa ser compilado e testado em uma placa física. Não aplique 5 V aos GPIOs.
