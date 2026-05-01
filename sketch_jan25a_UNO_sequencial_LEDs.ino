/*
  Efeito "vai-e-vem" (Supermáquina) em LEDs nas saídas:
  2..13, A0, A1, A2  (total 15 LEDs)

  Velocidades:
  - 5 s com passo de 75 ms
  - 5 s com passo de 150 ms
  - 5 s com passo de 200 ms
  Repete em loop.
*/

const byte pins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2};
const byte N = sizeof(pins) / sizeof(pins[0]);

const unsigned long stepDelays[] = {75UL, 150UL, 200UL};
const unsigned long modeDurationMs = 5000UL; // 5 segundos por velocidade

int indexLed = 0;   // LED atual (0..N-1)
int direction = 1;  // +1 indo, -1 voltando

unsigned long lastStepMs = 0;
unsigned long modeStartMs = 0;
byte mode = 0;      // 0,1,2

void setOnlyOneLedOn(int idx) {
  for (byte i = 0; i < N; i++) {
    digitalWrite(pins[i], (i == idx) ? HIGH : LOW);
  }
}

void advanceIndexVaiEVem() {
  indexLed += direction;

  if (indexLed >= (N - 1)) {
    indexLed = N - 1;
    direction = -1;
  } else if (indexLed <= 0) {
    indexLed = 0;
    direction = 1;
  }
}

void setup() {
  for (byte i = 0; i < N; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  // Inicializa no primeiro LED da lista
  setOnlyOneLedOn(indexLed);
  lastStepMs = millis();
  modeStartMs = millis();
}

void loop() {
  unsigned long now = millis();

  // Troca a velocidade a cada 5 segundos
  if (now - modeStartMs >= modeDurationMs) {
    modeStartMs = now;
    mode = (mode + 1) % 3;
  }

  // Dá o próximo passo conforme a velocidade atual
  if (now - lastStepMs >= stepDelays[mode]) {
    lastStepMs = now;

    advanceIndexVaiEVem();
    setOnlyOneLedOn(indexLed);
  }
}
