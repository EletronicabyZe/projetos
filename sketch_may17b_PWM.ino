 /*
  Demonstração 2 — LED RGB com controle por PWM

  Objetivo:
  Mostrar que, usando PWM, cada cor do LED RGB pode ter
  vários níveis aparentes de intensidade.

  Esta versão inclui uma etapa específica para observação
  do PWM no osciloscópio, usando:
  - pino 9  -> vermelho
  - pino 11 -> azul

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

const int tempoPassoFade = 10;     // Velocidade do fade individual
const int tempoCorFixa   = 1000;   // Tempo para manter uma cor fixa
const int tempoDegrau    = 800;    // Tempo entre níveis de brilho

void setup() {
  pinMode(pinoVermelho, OUTPUT);
  pinMode(pinoVerde, OUTPUT);
  pinMode(pinoAzul, OUTPUT);

  apagarTudo();
}

void loop() {
  /*
    Parte 1:
    Fade individual de cada cor.

    Aqui mostramos que cada canal pode variar de intensidade,
    em vez de apenas ligar ou desligar.
  */

  fadeCor(pinoVermelho);
  delay(300);

  fadeCor(pinoVerde);
  delay(300);

  fadeCor(pinoAzul);
  delay(300);


  /*
    Parte 2:
    Demonstração dedicada para o osciloscópio.

    Nesta etapa, o verde permanece apagado.
    O vermelho, no pino 9, diminui o duty cycle.
    O azul, no pino 11, aumenta o duty cycle.

    Esta é a melhor parte para mostrar as duas formas de onda
    no osciloscópio.
  */

  demonstracaoOsciloscopioVermelhoAzul();


  /*
    Parte 3:
    Degraus de brilho usando apenas o vermelho.

    Esta parte também é boa para mostrar o PWM no osciloscópio,
    especialmente se estiver usando apenas um canal.
  */

  setCor(0, 0, 0);       // apagado
  delay(tempoDegrau);

  setCor(50, 0, 0);      // vermelho fraco
  delay(tempoDegrau);

  setCor(128, 0, 0);     // vermelho médio
  delay(tempoDegrau);

  setCor(200, 0, 0);     // vermelho forte
  delay(tempoDegrau);

  setCor(255, 0, 0);     // vermelho máximo
  delay(tempoDegrau);

  apagarTudo();
  delay(500);


  /*
    Parte 4:
    Mistura de cores com intensidades diferentes.

    Aqui mostramos que o PWM permite criar tons intermediários,
    e não apenas as combinações fixas do modo digital.
  */

  setCor(255, 60, 0);      // tom próximo do laranja
  delay(tempoCorFixa);

  setCor(120, 0, 255);     // tom próximo do violeta
  delay(tempoCorFixa);

  setCor(0, 180, 80);      // tom próximo do verde-água
  delay(tempoCorFixa);

  setCor(180, 180, 40);    // tom amarelado mais suave
  delay(tempoCorFixa);

  setCor(80, 80, 255);     // azul claro / arroxeado
  delay(tempoCorFixa);

  apagarTudo();
  delay(500);


  /*
    Parte 5:
    Transição suave entre cores.

    Esta é a parte visualmente mais bonita:
    vermelho -> amarelo -> verde -> ciano -> azul -> magenta -> vermelho.
  */

  transicaoSuave(255, 0,   0,   255, 255, 0);    // vermelho para amarelo
  transicaoSuave(255, 255, 0,   0,   255, 0);    // amarelo para verde
  transicaoSuave(0,   255, 0,   0,   255, 255);  // verde para ciano
  transicaoSuave(0,   255, 255, 0,   0,   255);  // ciano para azul
  transicaoSuave(0,   0,   255, 255, 0,   255);  // azul para magenta
  transicaoSuave(255, 0,   255, 255, 0,   0);    // magenta para vermelho

  apagarTudo();
  delay(1000);
}


// Ajusta a cor do LED RGB usando PWM
void setCor(int vermelho, int verde, int azul) {
  analogWrite(pinoVermelho, vermelho);
  analogWrite(pinoVerde, verde);
  analogWrite(pinoAzul, azul);
}


// Apaga todas as cores
void apagarTudo() {
  setCor(0, 0, 0);
}


// Faz uma cor aumentar e depois diminuir suavemente
void fadeCor(int pino) {
  for (int brilho = 0; brilho <= 255; brilho++) {
    analogWrite(pino, brilho);
    delay(tempoPassoFade);
  }

  for (int brilho = 255; brilho >= 0; brilho--) {
    analogWrite(pino, brilho);
    delay(tempoPassoFade);
  }
}


// Demonstração específica para observar PWM no osciloscópio
void demonstracaoOsciloscopioVermelhoAzul() {
  /*
    Parte A:
    Degraus fixos de duty cycle.

    Esta parte é boa para explicar com calma no vídeo,
    porque cada condição fica parada por alguns segundos.
  */

  setCor(255, 0, 0);     // vermelho 100%, azul 0%
  delay(4000);

  setCor(192, 0, 64);    // vermelho alto, azul baixo
  delay(4000);

  setCor(128, 0, 128);   // vermelho médio, azul médio
  delay(4000);

  setCor(64, 0, 192);    // vermelho baixo, azul alto
  delay(4000);

  setCor(0, 0, 255);     // vermelho 0%, azul 100%
  delay(4000);


  /*
    Parte B:
    Rampa lenta.

    Aqui o vermelho diminui gradualmente enquanto o azul aumenta.
    No osciloscópio, o pulso do vermelho vai ficando mais estreito,
    enquanto o pulso do azul vai ficando mais largo.
  */

  for (int i = 0; i <= 255; i++) {
    int vermelho = 255 - i;
    int azul = i;

    setCor(vermelho, 0, azul);
    delay(40);
  }

  delay(1000);


  /*
    Parte C:
    Rampa inversa.

    Agora o azul diminui gradualmente enquanto o vermelho aumenta.
  */

  for (int i = 0; i <= 255; i++) {
    int vermelho = i;
    int azul = 255 - i;

    setCor(vermelho, 0, azul);
    delay(40);
  }

  delay(1000);

  apagarTudo();
  delay(500);
}


// Faz uma transição suave entre duas cores RGB
void transicaoSuave(
  int vermelhoInicial, int verdeInicial, int azulInicial,
  int vermelhoFinal,   int verdeFinal,   int azulFinal
) {
  const int passos = 255;
  const int tempoEntrePassos = 15;

  for (int i = 0; i <= passos; i++) {
    int vermelho = map(i, 0, passos, vermelhoInicial, vermelhoFinal);
    int verde    = map(i, 0, passos, verdeInicial, verdeFinal);
    int azul     = map(i, 0, passos, azulInicial, azulFinal);

    setCor(vermelho, verde, azul);
    delay(tempoEntrePassos);
  }
}