#include <LiquidCrystal_I2C.h> // Libreria control LCD
#include <LiquidMenu.h> // Libreria Crear Menu

LiquidCrystal_I2C lcd(0x27, 20, 4); // Declaramos la pantalla con un nombre, direccion y tamaño
// Pulsadoress de navegacion
const int P_Arriba = 10;
const int P_Selec = 11;
const int P_Abajo = 12 ;

// Entradas del conector X12 para la lectura del codigo binario de la Herramienta
                   // X12:1 L
const int DI2 = 3; // X12:2 64
const int DI3 = 4; // X12:3 32
const int DI4 = 5; // X12:4 16
const int DI5 = 6; // X12:5 8
const int DI6 = 7; // X12:6 4
const int DI7 = 8; // X12:7 2
const int DI8 = 9; // X12:9 1 Bit menos significativo MSB
int decimal;

// Entradas del Conector X13 Sensores para los Sensores de la Herramienta
const int DI9 = 22; // X13:1 Herramienta Enganchada
const int DI10 = 24; // X13:2 Flotante - Herramienta Tropieza
const int DI11 = 26; // X13:3 Entrada uso General Herramienta - Presencia SN - Pieza 1 en Herramienta
const int DI12 = 28; // X13:4 Entrada uso General Herramienta - Estaño Retraido - Pinza Cerrada
const int DI13 = 30; // X13:5 Entrada uso General Herramienta - Estaño Avanzado - Pinza Abierta
const int DI14 = 32; // X13:6 Entrada uso General Herramienta - Pieza Nº2 en Herramienta - Empujador 2 Abajo
const int DI15 = 34; // X13:7 Entrada uso General Herramienta - Empujador Arriba - Centrador Arriba - soldador Retraido
const int DI16 = 36; // X13:8 Entrada uso General Herramienta - Empujador Abajo - Centrador Abajo - Soldador Avanzado
//Necesitamos meter el dato de 1 o 0 en un tipo de variable diferente para poder leer el dato
int DI9R;
int DI10R;
int DI11R;
int DI12R;
int DI13R;
int DI14R;
int DI15R;
int DI16R;

// Salidas del conector X14
#define Motor_Sn 23 // X14:1 Motor Sn S-45 que alimenta el estaño 24v
int salida_seleccionada = 0;
// X14:2 Neutro
// X14:3 Fase 220v
// X14:4 PE
// X14:5 M- 24v detecta que hay estaño en la punta cerrando el circuito

// Salidas del conector X15
// X15:1 Termopar soldador
// X15:2 Termopar soldador
// X15:3 N/C
// X15:4 PE soldador
// X15:5 24V IN
// X15:6  24V OUT
// X15:7 M-
const int DI1 = 2 ; // X15:8 128 Bit mas significativo MSB

// Salidas del conector X16
// X16:1 N/C -100V tension para alimentar el soldador
// X16:2 N/C 100V
// X16:3 N/C Tension Micro negativo para Par motor atornillado
// X16:4 Resistencia Soldador
// X16:5 Resistencia soldador

// Diseño del menu
// Pantalla 1 con las lineas que contiene
LiquidLine Linea1(2, 0, "MENU VERIFICADOR"); // empezamos en la columna 1 porque la 0 esta ocupada por la flecha
LiquidLine Linea2(1, 1, "Num Herram: ", decimal);
LiquidLine Linea3(1, 2, "Estado Sensores");
LiquidLine Linea4(1, 3, "Salidas");

LiquidScreen Pantalla1(Linea1, Linea2, Linea3, Linea4); // usamos esta clase para crear la pantalla 1 indicandole las lineas que contendra

// Creamos la pantalla 2 del mismo modo
LiquidLine Linea1_2(1, 1, "Herr_Engancha: ",DI9R);
LiquidLine Linea2_2(1, 1, "Herr_Tropieza: ",DI10R);
LiquidLine Linea3_2(1, 2, "Presencia  SN: ",DI11R);
LiquidLine Linea4_2(1, 3, "Pinza Cerrada: ",DI12R);
LiquidLine Linea5_2(1, 0, "Pinza Abierta: ",DI13R);
LiquidLine Linea6_2(1, 1, "Empujad abajo: ",DI14R);
LiquidLine Linea7_2(1, 2, "Sold_Retraido: ",DI15R);
LiquidLine Linea8_2(1, 3, "Sold_Avanzado: ",DI16R);
LiquidLine Linea9_2(1, 0, "Atras");

LiquidScreen Pantalla2; // al tener mas de 4 lineas debemos instanciarla de forma separada

LiquidLine Linea1_3(3, 0, "Motor Sn");
LiquidLine Linea2_3(1, 1, "ON");
LiquidLine Linea3_3(1, 2, "OFF");
LiquidLine Linea4_3(1, 3, "ATRAS");

LiquidScreen Pantalla3(Linea1_3, Linea2_3, Linea3_3, Linea4_3);

LiquidMenu menu(lcd, Pantalla1, Pantalla2, Pantalla3);// Declaramos un menu compuesto por la pantallas creadas, que contendra dicho menu

void setup() {
  Serial.begin(9600);
  // Definimos los pines de los pulsadores en modo entrada para lectura

  //Lineas Scroll necesario al ser instanciado aparte
  Pantalla2.add_line(Linea1_2);
  Pantalla2.add_line(Linea2_2);
  Pantalla2.add_line(Linea3_2);
  Pantalla2.add_line(Linea4_2);
  Pantalla2.add_line(Linea5_2);
  Pantalla2.add_line(Linea6_2);
  Pantalla2.add_line(Linea7_2);
  Pantalla2.add_line(Linea8_2);
  Pantalla2.add_line(Linea9_2);

  pinMode(P_Arriba, INPUT_PULLUP);
  pinMode(P_Selec, INPUT_PULLUP);
  pinMode(P_Abajo, INPUT_PULLUP);

  // Definimos los pines del codigo de herramienta en modo entrada para lectura
  pinMode(DI1, INPUT);
  pinMode(DI2, INPUT);
  pinMode(DI3, INPUT);
  pinMode(DI4, INPUT);
  pinMode(DI5, INPUT);
  pinMode(DI6, INPUT);
  pinMode(DI7, INPUT);
  pinMode(DI8, INPUT);

  pinMode(DI9, INPUT);
  pinMode(DI10, INPUT);
  pinMode(DI11, INPUT);
  pinMode(DI12, INPUT);
  pinMode(DI13, INPUT);
  pinMode(DI14, INPUT);
  pinMode(DI15, INPUT);
  pinMode(DI16, INPUT);

  // Definimos los pines que activaran las salidas de los actuadores en modo salida para escritura
  pinMode(Motor_Sn, OUTPUT);

  lcd.begin(); // inicializamos la pantalla lcd
  lcd.backlight(); // encendemos la luz de fondo de la pantalla

  menu.init(); // Inicalizamos el menu, necesaria al usar i2c
  
  // Indicamos la posicion de la flecha
  Linea3.set_focusPosition(Position::LEFT);
  Linea4.set_focusPosition(Position::LEFT);
  Linea3.attach_function(1, fn_EstadoSensores);
  Linea4.attach_function(1, fn_Salidas);
  menu.add_screen(Pantalla1);// Añadimos la pantalla al menu
  // repetiremos los pasos anteriores para las lineas de la pantalla 2
  Linea1_2.set_focusPosition(Position::LEFT);
  Linea2_2.set_focusPosition(Position::LEFT);
  Linea3_2.set_focusPosition(Position::LEFT);
  Linea4_2.set_focusPosition(Position::LEFT);
  Linea5_2.set_focusPosition(Position::LEFT);
  Linea6_2.set_focusPosition(Position::LEFT);
  Linea7_2.set_focusPosition(Position::LEFT);
  Linea8_2.set_focusPosition(Position::LEFT);
  Linea9_2.set_focusPosition(Position::LEFT);

  Linea1_2.attach_function(2, fn_vacia);  // Funcion vacia, necesaria para que exista scroll, por la propia configuracion del metodo
  Linea2_2.attach_function(2, fn_vacia);
  Linea3_2.attach_function(2, fn_vacia);
  Linea4_2.attach_function(2, fn_vacia);
  Linea5_2.attach_function(2, fn_vacia);
  Linea6_2.attach_function(2, fn_vacia);
  Linea7_2.attach_function(2, fn_vacia);
  Linea8_2.attach_function(2, fn_vacia);
  Linea9_2.attach_function(1, fn_atras); // Adjuntamos el nombre de las funciones creadas mas abajo
 
  menu.add_screen(Pantalla2); // Del mismo modo añadimos la pantalla 2 al menu

  Linea2_3.set_focusPosition(Position::LEFT);
  Linea3_3.set_focusPosition(Position::LEFT);
  Linea4_3.set_focusPosition(Position::LEFT);
  
  Linea2_3.attach_function(1, fn_on); 
  Linea3_3.attach_function(1, fn_off);
  Linea4_3.attach_function(1, fn_atras);

  menu.add_screen(Pantalla3);
  // indicamos la cantidad de lineas que tiene cada pantalla, para determinar el scroll de navegacion entre las opciones
  Pantalla1.set_displayLineCount(4);
  Pantalla2.set_displayLineCount(4);
  Pantalla3.set_displayLineCount(4);
  
  menu.set_focusedLine(0); // coloca la flecha en la posicion 0
  menu.update(); // para actualizar la informacion mostrada
  delay(1000);
}

void loop() {
  seleccionar();// llamada a la funcion para comprovar si se ha pulsado el boton de seleccion
  fn_convertir();
  
  if (digitalRead(P_Arriba) == LOW ){
    menu.switch_focus(false);
    delay(100);
  }
  if (digitalRead(P_Abajo) == LOW ){
    menu.switch_focus(true);
    delay(100);
  }
  // Introducimos el dato a leer en un nuevo formato int
  DI9R = digitalRead(DI9);
  DI10R = digitalRead(DI10);
  DI11R = digitalRead(DI11);
  DI12R = digitalRead(DI12);
  DI13R = digitalRead(DI13);
  DI14R = digitalRead(DI14);
  DI15R = digitalRead(DI15);
  DI16R = digitalRead(DI16);
  
  
  menu.update(); // refresco pantalla
  delay(1000);
}

void fn_convertir() {
  decimal = (digitalRead(DI8) * 1) + (digitalRead(DI7) * 2) + (digitalRead(DI6) * 4) + (digitalRead(DI5) * 8) + (digitalRead(DI4) * 16) + (digitalRead(DI3) * 32) + (digitalRead(DI2) * 64) + (digitalRead(DI1) * 128);
}

// funcion atras
void fn_atras() {
  menu.change_screen(1);
  menu.set_focusedLine(2);
}
// cambio de pantalla
void fn_EstadoSensores() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
}
// cambio de pantalla
void fn_Salidas() {
  menu.change_screen(3);
  menu.set_focusedLine(1);
  salida_seleccionada = 1;
}

// funcion para realizar la eleccion
void seleccionar() {
  if (digitalRead(P_Selec) == LOW ){
    menu.call_function(1);
    delay(100);
  }
}
//Funcion que cuando es llamada se enciende el motor
void fn_on(){
  switch(salida_seleccionada) {
    case 1:
    digitalWrite(Motor_Sn,HIGH);
    break;
  }
}
//Funcion que cuando es llamada se apaga el motor
void fn_off(){
  switch(salida_seleccionada) {
    case 1:
    digitalWrite(Motor_Sn,LOW);
    break;
  }
}

void fn_vacia(){
}
