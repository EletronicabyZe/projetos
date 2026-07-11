/*
  Demonstração 1 — LED RGB com acionamento digital

  Objetivo:
  Mostrar que, usando saídas digitais, cada cor do LED RGB
  pode estar apenas em dois estados: apagada ou acesa.

  Ligações:
  R do módulo RGB -> pino 9 do Arduino
  G do módulo RGB -> pino 10 do Arduino
  B do módulo RGB -> pino 11 do Arduino
  GND do módulo RGB -> GND do Arduino

  Observação:
  Este programa considera um módulo RGB de cátodo comum.
*/

const int pinoVermelho = 9;
const int pinoVerde    = 10;
const int pinoAzul     = 11;

const int tempoLento = 1000;  // 1 segundo
const int tempoRapido = 500;  // meio segundo

void setup() {
  pinMode(pinoVermelho, OUTPUT);
  pinMode(pinoVerde, OUTPUT);
  pinMode(pinoAzul, OUTPUT);

  apagarTudo();
}

void loop() {
  // Primeira sequência: mais lenta, para explicar cada cor

  // Vermelho
  acenderCor(HIGH, LOW, LOW);
  delay(tempoLento);

  // Verde
  acenderCor(LOW, HIGH, LOW);
  delay(tempoLento);

  // Azul
  acenderCor(LOW, LOW, HIGH);
  delay(tempoLento);

  // Amarelo: vermelho + verde
  acenderCor(HIGH, HIGH, LOW);
  delay(tempoLento);

  // Ciano: verde + azul
  acenderCor(LOW, HIGH, HIGH);
  delay(tempoLento);

  // Magenta: vermelho + azul
  acenderCor(HIGH, LOW, HIGH);
  delay(tempoLento);

  // Branco aproximado: vermelho + verde + azul
  acenderCor(HIGH, HIGH, HIGH);
  delay(tempoLento);

  // Tudo apagado
  apagarTudo();
  delay(tempoLento);


  // Segunda sequência: mais rápida, para reforçar a ideia de mudança em saltos

  acenderCor(HIGH, LOW, LOW);    // vermelho
  delay(tempoRapido);

  acenderCor(LOW, HIGH, LOW);    // verde
  delay(tempoRapido);

  acenderCor(LOW, LOW, HIGH);    // azul
  delay(tempoRapido);

  acenderCor(HIGH, HIGH, LOW);   // amarelo
  delay(tempoRapido);

  acenderCor(LOW, HIGH, HIGH);   // ciano
  delay(tempoRapido);

  acenderCor(HIGH, LOW, HIGH);   // magenta
  delay(tempoRapido);

  acenderCor(HIGH, HIGH, HIGH);  // branco aproximado
  delay(tempoRapido);

  apagarTudo();
  delay(tempoLento);
}


// Função para acender uma combinação de vermelho, verde e azul
void acenderCor(int vermelho, int verde, int azul) {
  digitalWrite(pinoVermelho, vermelho);
  digitalWrite(pinoVerde, verde);
  digitalWrite(pinoAzul, azul);
}


// Função para apagar todas as cores
void apagarTudo() {
  digitalWrite(pinoVermelho, LOW);
  digitalWrite(pinoVerde, LOW);
  digitalWrite(pinoAzul, LOW);
}