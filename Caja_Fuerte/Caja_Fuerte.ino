/*
 * =============================================================
 * CAJA FUERTE v2.9 - 
 * =============================================================
 *
 * FUNCIONES:
 * - Se usa .detach() en el servo después de moverse.
 * - Esto evita el "zumbido" y reduce el consumo de energía.
 * - S1='1', S2='2', S3='3', S4='4', etc.
 */

// --- LIBRERÍAS ---
#include <LiquidCrystal_PCF8574.h> 
#include <Wire.h>                  
#include <Servo.h>                 
#include <Keypad.h>                

// =================================================
//          CONFIGURACIÓN GENERAL DEL HARDWARE
// =================================================

// --- 1. Pantalla LCD I2C ---
#define I2C_ADDR 0x27
LiquidCrystal_PCF8574 lcd(I2C_ADDR);

// --- 2. Teclado (Keypad) 4x4 ---
const byte ROWS = 4; 
const byte COLS = 4; 

/*
 * ====================================================================
 * MATRIZ DE TECLAS (v2.8 - La correcta)
 * Traduce el hardware "rotado" a la lógica S1='1', S4='4', etc.
 * ====================================================================
 */
char keys[ROWS][COLS] = {
  // colPins: C1(Pin 6) C2(Pin 7) C3(Pin 8) C4(Pin 9)
  /* R1(Pin 2) */ {'*',       '9',       '5',       '1'}, 
  /* R2(Pin 3) */ {'C',       '0',       '6',       '2'}, 
  /* R3(Pin 4) */ {'#',       'A',       '7',       '3'}, 
  /* R4(Pin 5) */ {'D',       'B',       '8',       '4'}
};

// Pines del Arduino (Tu cableado físico)
byte rowPins[ROWS] = {6, 7, 8, 9}; // C1, C2, C3, C4
byte colPins[COLS] = {2, 3, 4, 5}; // R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- 3. Servo Motor ---
Servo lockServo; 
const int servoPin = 10;          // Pin 10 (para evitar conflicto)
const int SERVO_LOCK_ANGLE = 0;   // Ángulo CERRADO
const int SERVO_OPEN_ANGLE = 90;  // Ángulo ABIERTO
const unsigned long OPEN_TIME_MS = 5000; // 5 segundos

// =================================================
//          VARIABLES Y LÓGICA DEL PROGRAMA
// =================================================

String secretCode = "1234";    // ¡Este es el PIN para abrir!
String inputBuffer = "";       
String newPinBuffer = "";      
const int INTENTOS_MAX = 3;     
int intentos = 0;               
bool lockedOut = false;         
unsigned long lockoutUntil = 0; 
const unsigned long LOCKOUT_MS = 20000; 
bool isOpen = false;            
unsigned long openedAt = 0;     

enum State {
  ST_LOCKED,
  ST_CHANGE_NEW,
  ST_CHANGE_CONFIRM
};
State currentState = ST_LOCKED; 


// =================================================
//          SETUP (Se ejecuta 1 vez al encender)
// =================================================
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setBacklight(true);
  lcd.clear();
  mostrarMensaje("Caja Fuerte", "Iniciando...", 1000);
  // No adjuntamos el servo aquí, lo haremos solo cuando se mueva
  cerrarCaja(false); // Cierra la caja al iniciar
  mostrarMensaje("Ingrese PIN:", "", 0);
}

// =================================================
//          LOOP (Se ejecuta constantemente)
// =================================================
void loop() {

  // --- 1. Manejo del Bloqueo por Intentos Fallidos ---
  if (lockedOut) {
    if (millis() >= lockoutUntil) {
      lockedOut = false;
      intentos = 0;
      mostrarMensaje("Bloqueo Finaliz.", "Ingrese PIN:", 1000);
      inputBuffer = "";
    } else {
      unsigned long remaining = (lockoutUntil - millis()) / 1000;
      lcd.setCursor(0, 0);
      lcd.print("BLOQUEADO       ");
      lcd.setCursor(0, 1);
      lcd.print("Espere: ");
      lcd.print(remaining);
      lcd.print("s   ");
      delay(200); 
      return; 
    }
  }

  // --- 2. Leer el teclado ---
  char k = keypad.getKey();

  if (k) {
    switch (currentState) {
      case ST_LOCKED:
        handleKeyLocked(k);
        break;
      case ST_CHANGE_NEW:
        handleKeyChangeNew(k);
        break;
      case ST_CHANGE_CONFIRM:
        handleKeyChangeConfirm(k);
        break;
    }
  }

  // --- 3. Control del Tiempo de Apertura ---
  if (isOpen && (millis() - openedAt >= OPEN_TIME_MS)) {
    cerrarCaja(true); // Cerrar automáticamente
  }

} // --- Fin del loop() ---


// =================================================
//          FUNCIONES DE MANEJO DE TECLAS
// =================================================

void handleKeyLocked(char k) {
  if (k == '*') { // Tecla BORRAR (S13)
    if (inputBuffer.length() > 0) {
      inputBuffer.remove(inputBuffer.length() - 1); 
      actualizarDisplayEntrada();
    }
  }
  else if (k == 'A') { // Tecla CAMBIAR PIN (S11)
    currentState = ST_CHANGE_NEW;
    inputBuffer = "";
    newPinBuffer = "";
    mostrarMensaje("NUEVO PIN:", "", 0);
    actualizarDisplayEntrada();
  }
  else if (isDigit(k)) { // Si es un NÚMERO (0-9)
    inputBuffer += k;
    actualizarDisplayEntrada();

    if (inputBuffer.length() == secretCode.length()) {
      delay(300); 
      
      if (inputBuffer == secretCode) {
        accesoConcedido();
      } else {
        accesoDenegado();
      }
      inputBuffer = "";
    }
  }
}

void handleKeyChangeNew(char k) {
  if (k == '*') { // CANCELAR (S13)
    currentState = ST_LOCKED;
    inputBuffer = "";
    newPinBuffer = "";
    mostrarMensaje("Cambio Cancelado", "Ingrese PIN:", 1000);
    return;
  }
  else if (k == '#') { // CONFIRMAR (S15)
    if (inputBuffer.length() < 4) { 
      mostrarMensaje("PIN muy corto", "Min 4 digitos", 1000);
      mostrarMensaje("NUEVO PIN:", "", 0);
      inputBuffer = ""; 
    } else {
      newPinBuffer = inputBuffer; 
      inputBuffer = "";
      currentState = ST_CHANGE_CONFIRM; 
      mostrarMensaje("Confirme PIN:", "", 0);
    }
    actualizarDisplayEntrada();
  }
  else if (isDigit(k)) { // Es un número
    inputBuffer += k;
    actualizarDisplayEntrada();
  }
}

void handleKeyChangeConfirm(char k) {
  if (k == '*') { // CANCELAR (S13)
    currentState = ST_LOCKED;
    inputBuffer = "";
    newPinBuffer = "";
    mostrarMensaje("Cambio Cancelado", "Ingrese PIN:", 1000);
    return;
  }
  else if (k == '#') { // CONFIRMAR (S15)
    if (inputBuffer == newPinBuffer) {
      secretCode = newPinBuffer; 
      currentState = ST_LOCKED;
      inputBuffer = "";
      newPinBuffer = "";
      mostrarMensaje("PIN Actualizado!", "Ingrese PIN:", 1500);
    } else {
      currentState = ST_LOCKED;
      inputBuffer = "";
      newPinBuffer = "";
      mostrarMensaje("PIN no coincide", "Intente de nuevo", 1500);
      mostrarMensaje("Ingrese PIN:", "", 0);
    }
    return;
  }
  else if (isDigit(k)) { // Es un número
    inputBuffer += k;
    actualizarDisplayEntrada();
  }
}


// =================================================
//          FUNCIONES AUXILIARES
// =================================================

/**
 * MODO DE PRUEBA: Muestra los NÚMEROS REALES.
 */
void actualizarDisplayEntrada() {
  lcd.setCursor(0, 1);
  lcd.print(inputBuffer); 

  for (int i = inputBuffer.length(); i < 16; i++) {
    lcd.print(' ');
  }
}

/*
 * MODO SEGURO: Muestra asteriscos '*'
void actualizarDisplayEntrada() {
  lcd.setCursor(0, 1);
  String mask = "";
  for (unsigned int i = 0; i < inputBuffer.length() && i < 16; i++) {
    mask += '*';
  }
  lcd.print(mask);
  for (int i = mask.length(); i < 16; i++) {
    lcd.print(' ');
  }
}
*/

void accesoConcedido() {
  intentos = 0;
  mostrarMensaje("Acceso Concedido", "Abriendo...", 500);
  abrirCaja();
}

void accesoDenegado() {
  intentos++; 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Acceso Denegado");
  lcd.setCursor(0, 1);

  if (intentos >= INTENTOS_MAX) {
    lcd.print("BLOQUEADO!");
    lockedOut = true;
    lockoutUntil = millis() + LOCKOUT_MS; 
    delay(1000);
  } else {
    lcd.print("Intentos: ");
    lcd.print(intentos);
    lcd.print("/");
    lcd.print(INTENTOS_MAX);
    delay(1000);
    mostrarMensaje("Ingrese PIN:", "", 0);
  }
}

/**
 * Mueve el servo para ABRIR la caja
 */
void abrirCaja() {
  lockServo.attach(servoPin); // "Despierta" el servo
  lockServo.write(SERVO_OPEN_ANGLE); 
  isOpen = true;                     
  openedAt = millis();
  delay(500); // Dale 0.5s para que llegue a la posición
  lockServo.detach(); // "Duerme" el servo para ahorrar energía y evitar zumbido
}

/**
 * Mueve el servo para CERRAR la caja
 */
void cerrarCaja(bool mostrarMsg) {
  lockServo.attach(servoPin); // "Despierta" el servo
  lockServo.write(SERVO_LOCK_ANGLE); 
  isOpen = false;                    
  delay(500); // Dale 0.5s para que llegue a la posición
  lockServo.detach(); // "Duerme" el servo

  if (mostrarMsg) {
    mostrarMensaje("Caja Cerrada", "Ingrese PIN:", 1000);
  }
}

/**
 * Función "helper" para mostrar mensajes en el LCD
 */
void mostrarMensaje(String l1, String l2, int pausa) {
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(l1);
  lcd.setCursor(0, 1); 
  lcd.print(l2);
  if (pausa > 0) {
    delay(pausa); 
  }
}