/*
  Código para Arduino Uno:
  - Controla 3 motores DC utilizando o L293D.
  - Cada motor é acionado (ligado/desligado) por um botão de 4 pinos.
  - Os botões são conectados utilizando o resistor pull-up interno.
  - Ao pressionar um botão (detectado por mudança de HIGH para LOW),
    o código alterna o estado do motor (on/off) e aciona as entradas do L293D.
  
  Configuração do hardware (exemplo):
    - Botões: pinos 2, 3 e 4.
    - Motor 1: pinos 5 e 6.
    - Motor 2: pinos 7 e 8.
    - Motor 3: pinos 9 e 10.
*/

const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;

const int motor1Pin1 = 5;
const int motor1Pin2 = 6;

const int motor2Pin1 = 7;
const int motor2Pin2 = 8;

const int motor3Pin1 = 9;
const int motor3Pin2 = 10;

// Variáveis para controlar o estado de cada motor
bool motor1State = false;
bool motor2State = false;
bool motor3State = false;

// Variáveis para fazer debounce dos botões
int lastButton1State = HIGH;
int lastButton2State = HIGH;
int lastButton3State = HIGH;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long debounceDelay = 50; // atraso em milissegundos

void setup() {
  // Inicializa os botões como entrada com resistor de pull-up
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);

  // Inicializa os pinos dos motores como saída
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);

  // Inicialmente, todos os motores estão desligados
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
}

void loop() {
  // Leitura dos botões
  int reading1 = digitalRead(button1Pin);
  int reading2 = digitalRead(button2Pin);
  int reading3 = digitalRead(button3Pin);
  
  // Processa o botão do Motor 1
  if (reading1 != lastButton1State) {
    lastDebounceTime1 = millis();
  }
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    // Detecta a transição de não pressionado para pressionado
    if (reading1 == LOW && lastButton1State == HIGH) { 
      motor1State = !motor1State;  // Inverte o estado do motor 1
      if (motor1State) {
        // Liga o motor 1 (sentido definido: um pino HIGH, outro LOW)
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);
      } else {
        // Desliga o motor 1
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
      }
    }
  }
  lastButton1State = reading1;
  
  // Processa o botão do Motor 2
  if (reading2 != lastButton2State) {
    lastDebounceTime2 = millis();
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 == LOW && lastButton2State == HIGH) {
      motor2State = !motor2State;  // Inverte o estado do motor 2
      if (motor2State) {
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
      } else {
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
      }
    }
  }
  lastButton2State = reading2;
  
  // Processa o botão do Motor 3
  if (reading3 != lastButton3State) {
    lastDebounceTime3 = millis();
  }
  if ((millis() - lastDebounceTime3) > debounceDelay) {
    if (reading3 == LOW && lastButton3State == HIGH) {
      motor3State = !motor3State;  // Inverte o estado do motor 3
      if (motor3State) {
        digitalWrite(motor3Pin1, HIGH);
        digitalWrite(motor3Pin2, LOW);
      } else {
        digitalWrite(motor3Pin1, LOW);
        digitalWrite(motor3Pin2, LOW);
      }
    }
  }
  lastButton3State = reading3;
}