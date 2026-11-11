#include <Arduino.h>

// GPIOs de uso geral no ESP32-WROOM. Pinos de boot, flash e UART foram omitidos.
constexpr uint8_t OUTPUT_PINS[] = {13, 14, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33};
constexpr uint8_t INPUT_ONLY_PINS[] = {34, 35, 36, 39};
bool outputEnabled[40] = {};

bool contains(const uint8_t *pins, size_t count, int pin) {
  for (size_t i = 0; i < count; ++i) {
    if (pins[i] == pin) return true;
  }
  return false;
}

bool canOutput(int pin) {
  return contains(OUTPUT_PINS, sizeof(OUTPUT_PINS), pin);
}

bool canInput(int pin) {
  return canOutput(pin) ||
         contains(INPUT_ONLY_PINS, sizeof(INPUT_ONLY_PINS), pin);
}

void printHelp() {
  Serial.println(F("\nComandos (digite no Monitor Serial e pressione Enter):"));
  Serial.println(F("  ajuda       mostra estes comandos"));
  Serial.println(F("  pinos       lista os GPIOs permitidos"));
  Serial.println(F("  entrada N   configura GPIO N como entrada e le seu estado"));
  Serial.println(F("  saida N     configura GPIO N como saida em nivel LOW"));
  Serial.println(F("  alto N      coloca uma saida configurada em HIGH"));
  Serial.println(F("  baixo N     coloca uma saida configurada em LOW"));
  Serial.println(F("  ler N       le o estado do GPIO N"));
  Serial.println(F("  pulso N     gera 3 pulsos de 250 ms e libera o GPIO"));
}

void printPins() {
  Serial.print(F("Entrada/saida: "));
  for (uint8_t pin : OUTPUT_PINS) {
    Serial.print(pin);
    Serial.print(' ');
  }
  Serial.print(F("\nSomente entrada: "));
  for (uint8_t pin : INPUT_ONLY_PINS) {
    Serial.print(pin);
    Serial.print(' ');
  }
  Serial.println(F("\nGPIO 34-39 precisam de resistor externo para evitar leitura flutuante."));
}

void setInput(int pin) {
  if (outputEnabled[pin]) {
    digitalWrite(pin, LOW);
    outputEnabled[pin] = false;
  }
  // GPIO 34-39 nao possuem pull-up interno.
  pinMode(pin, canOutput(pin) ? INPUT_PULLUP : INPUT);
}

void printLevel(int pin) {
  Serial.print(F("GPIO "));
  Serial.print(pin);
  Serial.print(F(": "));
  Serial.println(digitalRead(pin) == HIGH ? F("HIGH") : F("LOW"));
}

void handleCommand(String line) {
  line.trim();
  line.toLowerCase();
  if (line.length() == 0) return;

  int space = line.indexOf(' ');
  String command = space < 0 ? line : line.substring(0, space);
  if (command == F("ajuda")) { printHelp(); return; }
  if (command == F("pinos")) { printPins(); return; }

  if (space < 0) {
    Serial.println(F("Informe um GPIO. Exemplo: ler 21"));
    return;
  }
  String argument = line.substring(space + 1);
  argument.trim();
  for (size_t i = 0; i < argument.length(); ++i) {
    if (!isDigit(argument[i])) {
      Serial.println(F("GPIO invalido. Digite apenas o numero do pino."));
      return;
    }
  }
  if (argument.length() == 0) {
    Serial.println(F("Informe um GPIO. Exemplo: ler 21"));
    return;
  }
  int pin = argument.toInt();
  if (!canInput(pin)) {
    Serial.println(F("GPIO fora da lista permitida. Use: pinos"));
    return;
  }

  if (command == F("entrada")) {
    setInput(pin);
    printLevel(pin);
  } else if (command == F("ler")) {
    if (!outputEnabled[pin]) setInput(pin);
    printLevel(pin);
  } else if (command == F("saida") || command == F("pulso")) {
    if (!canOutput(pin)) {
      Serial.println(F("Este GPIO aceita somente entrada."));
      return;
    }
    digitalWrite(pin, LOW);
    pinMode(pin, OUTPUT);
    outputEnabled[pin] = true;
    if (command == F("saida")) {
      Serial.printf("GPIO %d configurado como saida LOW.\n", pin);
    } else {
      for (int i = 0; i < 3; ++i) {
        digitalWrite(pin, HIGH);
        delay(250);
        digitalWrite(pin, LOW);
        delay(250);
      }
      setInput(pin);
      Serial.printf("GPIO %d: 3 pulsos concluidos; pino voltou a entrada.\n", pin);
    }
  } else if (command == F("alto") || command == F("baixo")) {
    if (!outputEnabled[pin]) {
      Serial.println(F("Configure primeiro com: saida N"));
      return;
    }
    digitalWrite(pin, command == F("alto") ? HIGH : LOW);
    printLevel(pin);
  } else {
    Serial.println(F("Comando desconhecido. Use: ajuda"));
  }
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(50);
  delay(500);
  Serial.println(F("Teste manual de GPIO - ESP32 DevKit"));
  printHelp();
  printPins();
}

void loop() {
  if (Serial.available()) {
    handleCommand(Serial.readStringUntil('\n'));
  }
}
