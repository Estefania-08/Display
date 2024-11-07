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


//CODIGO DE LA ALU CON DISPLAY
int EstadoA = 0;
  int EstadoB = 0;

  int w = 0;
  int x = 0;
  int y = 0;
  int z = 0;
 
void setup() {
  //Pines  entrada para A, B, w, x, y, z
  pinMode(2, INPUT); 
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(14, INPUT); 
  //Salida para cada operación
  pinMode(13, OUTPUT);//A
  pinMode(12, OUTPUT);//B
  pinMode(11, OUTPUT);//C
  pinMode(10, OUTPUT);//D
  pinMode(9, OUTPUT);//E
  pinMode(8, OUTPUT);//F
  pinMode(7, OUTPUT);//G
}

void loop() {

  EstadoA = digitalRead(2); // Leer valor de A
  EstadoB = digitalRead(3); // Leer valor de B
  w = digitalRead(4);
  x = digitalRead(5);
  y = digitalRead(6);
  z = digitalRead(14);
 // Suma
  if ((EstadoA ^ EstadoB)&&(!z && !y && !x && w)) {
    UNO(); // Salida suma
  } 
  // ACARREO
  if ((EstadoA && EstadoB)&&(!z && !y && !x && w)) {
    DOS(); // Salida acarreo
  }
  if ((!EstadoA && !EstadoB)&&(!z && !y && !x && w)) {
    CERO(); // Salida suma
  }

  //RESTA
  if ((EstadoA && EstadoB)&&(!z && !y && x && !w)) {
    CERO(); // Salida suma
  }
  if ((EstadoA ^ EstadoB)&&(!z && !y && x && !w)) {
    UNO(); //Salida resta
  }
  // (!A AND B) Signo negativo de la resta
  if ((!EstadoA && EstadoB)&&(!z && !y && x && !w)) {
    SIGNO(); //Salida signo negativo
  }
  if ((!EstadoA && !EstadoB)&&(!z && !y && x && !w)) {
    CERO(); // Salida suma
  }

  //MULTIPLICACION
  if ((EstadoA && EstadoB)&&(!z && !y && x && w)) {
    UNO(); // SALIDA DE LA MULTIPLICACIÓN
  } 
  if ((EstadoA ^ EstadoB)&&(!z && !y && x && w)) {
    CERO(); // SALIDA DE LA MULTIPLICACIÓN
  } 
 if ((!EstadoA && !EstadoB)&&(!z && !y && x && w)) {
    CERO(); // SALIDA DE LA MULTIPLICACIÓN
  } 

  //DIVISION
  if ((EstadoA && EstadoB)&&(!z && y && !x && !w)) {
    UNO(); // SALIDA DE LA DIVISIÓN
  }
  // (!A AND !B) INDEFINIDO
  if ((!EstadoA && !EstadoB)&&(!z && y && !x && !w)) {
    INDEFINIDO(); // SALIDA DEL INDEFINIDO
  }
  // (A AND !B) INFINITO
  if ((EstadoA && !EstadoB)&&(!z && y && !x && !w)) {
    INFINITO(); // SALIDA DEL INFINITO
  }
  if ((!EstadoA && EstadoB)&&(!z && y && !x && !w)) {
    CERO(); // SALIDA DEL INFINITO
  }
  
  // COMPUERTAS LÓGICAS
  // AND
  if ((EstadoA && EstadoB) && (!z && y && !x && w)) {
    UNO(); // SALIDA DE AND
  }

  if ((!EstadoA && !EstadoB) && (!z && y && !x && w)) {
    CERO(); // SALIDA DE AND
  }

  if ((EstadoA ^ EstadoB) && (!z && y && !x && w)) {
    CERO(); // SALIDA DE AND
  }
// OR
  if ((EstadoA || EstadoB) && (!z && y && x && !w)) {
    UNO(); // SALIDA DE OR
  }

  if ((!EstadoA && !EstadoB) && (!z && y && x && !w)) {
    CERO(); // SALIDA DE OR
  }

  // NOT (solo A)
  if ((!EstadoA) && (!z && y && x && w)) {   
    UNO(); // NOT A: muestra 1 cuando A no está presionado
  }
  if ((EstadoA) && (!z && y && x && w)) {   
    CERO(); // NOT A: muestra 0 cuando A está presionado
}
    
  // XOR
  if ((EstadoA ^ EstadoB) && (z && !y && !x && !w)) {
    UNO(); // SALIDA DE XOR
  }

   if ((!EstadoA && !EstadoB) && (z && !y && !x && !w)) {
    CERO(); // SALIDA DE XOR
  }

   if ((EstadoA && EstadoB) && (z && !y && !x && !w)) {
    CERO(); // SALIDA DE XOR
  }

// XNOR
  if (!(EstadoA ^ EstadoB) && (z && !y && !x && w)) {
    UNO(); // SALIDA DE XOR
  }

  if ((!EstadoA && EstadoB) && (z && !y && !x && w)) {
    CERO(); // SALIDA DE XOR
  }

   if ((EstadoA && !EstadoB) && (z && !y && !x && w)) {
    CERO(); // SALIDA DE XOR
  }

  // NAND
  if (!(EstadoA && EstadoB) && (z && !y && x && !w)) {
    UNO(); // SALIDA DE NAND
  }

    if ((EstadoA && EstadoB) && (z && !y && x && !w)) {
    CERO(); // SALIDA DE NAND
  }

  // NOR
  if (!(EstadoA || EstadoB) && (z && !y && x && w)) {
    UNO(); // SALIDA DE NOR
  }

  if ((!EstadoA && EstadoB) && (z && !y && x && w)) {
    CERO(); // SALIDA DE NOR
  }

  if ((EstadoA && !EstadoB) && (z && !y && x && w)) {
    CERO(); // SALIDA DE NOR
  }
if ((EstadoA && EstadoB) && (z && !y && x && w)) {
    CERO(); // SALIDA DE NOR
  }
  

  // PARA QUE LOS LED VUELVAN A SU ESTADO OFF
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);

}
  void CERO(){
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
  }

  void UNO(){
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
  }
void DOS(){
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(7, HIGH);
  }

  void SIGNO(){
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(7, HIGH);
  }

  void INDEFINIDO(){
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
  }

 void INFINITO() {
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
}
