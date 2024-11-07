// Pines del display 
int displayPins[] = {2, 3, 4, 5, 6, 7, 8};

//  botones para el modo binario
int btn1 = 12;  // Bit menos significativo (LSB)
int btn2 = 11;  // Bit medio
int btn3 = 10;  // Bit más significativo (MSB)
int btn4 = 9;   // Nuevo bit más significativo

// Variable para almacenar el número actual
int number = 0;

// Mapa de los números y letras (0-15) para encender los segmentos
byte numbers[16][7] = {
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},   // 0
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},       // 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},    // 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},    // 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},     // 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},    // 5
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},   // 6
  {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},      // 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},  // 8
  {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH},   // 9
  {HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH},   // A
 {LOW, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},    // b
  {HIGH, LOW, LOW, HIGH, HIGH, HIGH, LOW},     // C
  {LOW, HIGH, HIGH, HIGH, HIGH, LOW, HIGH},    // d
  {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH},    // E
  {HIGH, LOW, LOW, LOW, HIGH, HIGH, HIGH}      // F
};

void setup() {
  //  pines del display como salidas
  for (int i = 0; i < 7; i++) {
    pinMode(displayPins[i], OUTPUT);
  }

  //  pines de los botones como entradas
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);

  // Mostrar el número inicial (0)
  mostrarNumero(number);
}

void loop() {
  // Leer el estado de los botones
  int bit1 = digitalRead(btn1);  // LSB
  int bit2 = digitalRead(btn2);  // Medio
  int bit3 = digitalRead(btn3);  // MSB
  int bit4 = digitalRead(btn4);  // Nuevo bit más significativo

  // Calcular el número en decimal a partir de los bits binarios
  number = (bit4 << 3) | (bit3 << 2) | (bit2 << 1) | bit1;
// Mostrar el número o letra correspondiente en el display
  mostrarNumero(number);

  delay(200);  //  evitar lecturas erróneas
}

//  mostrar un número o letra en el display
void mostrarNumero(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(displayPins[i], numbers[num][i]);
}
} 
