#include "mbed.h"
#include <iostream>
PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);

std::string inputHexR = "00";
std::string inputHexG = "00";
std::string inputHexB = "00";
void updateLED() {
  std::string inputHex = inputHexR + inputHexG + inputHexB;
  uint32_t hexValue = std::stoul(inputHex, nullptr, 16);
  float r, g, b;
  r = ((hexValue >> 16) & 0xFF) / 255.0;
  g = ((hexValue >> 8) & 0xFF) / 255.0;
  b = (hexValue & 0xFF) / 255.0;
  ledR.write(r);
  ledG.write(g);
  ledB.write(b);
}

const int numRows = 4;
const int numCols = 4;

char keyMap[numRows][numCols] = {{'1', '2', '3', 'A'},
                                 {'4', '5', '6', 'B'},
                                 {'7', '8', '9', 'C'},
                                 {',', '0', '#', 'D'}};

DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4),
                               DigitalOut(D5)};
DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8),
                              DigitalIn(D9)};

// main() runs in its own thread in the OS
int numero() {
  int x;
  for (int i = 0; i < numRows; i++) {
    rowPins[i] = 0;

    for (int j = 0; j < numCols; j++) {
      if (!colPins[j]) {
        x = keyMap[i][j];
        ThisThread::sleep_for(500ms);
      }
    }

    rowPins[i] = 1;
  }
  return x;
}

int main() {
  int num1;
  int x1;
  int y1;
  int x2;
  int y2;
  std::cout
      << "Ingresa el numero 1 para determinar el intercepto con el eje y la "
         "recta entre 2 puntos, el 2 para calcular promedio o el 3 para "
         "generar colores en led ";

  while (true) {

    num1 = numero();

    if (num1 == 1) {
      cout << "Ingrese la x1: ";
      x1 = numero();

      cout << "Ingrese la y1: ";
      y1 = numero();

      cout << "Ingrese la x2: ";
      x2 = numero();

      cout << "Ingrese la y2: ";
      y2 = numero();

      double pendiente = (y2 - y1) / (x2 - x1);

      // Calcula el intercepto en el eje y (b en la ecuación y = mx + b)
      double interceptoY = y1 - (pendiente * x1);

      cout << "La pendiente de la recta que pasa por los dos puntos es: "
                << pendiente << std::endl;
      cout << "El intercepto en el eje y es: " << interceptoY << std::endl;
    } else if (num1 == 2) {

    } else if (num1 == 3) {
      int colorIndex = 0;
      while (true) {
        for (int i = 0; i < numRows; i++) {
          rowPins[i] = 0;

          for (int j = 0; j < numCols; j++) {
            if (!colPins[j]) {
              char keyPressed = keyMap[i][j];
              if (keyPressed >= '0' && keyPressed <= '9') {
                int decimalValue = keyPressed - '0';

                if (colorIndex == 0) {
                  inputHexR = std::to_string(decimalValue);
                } else if (colorIndex == 1) {
                  inputHexG = std::to_string(decimalValue);
                } else {
                  inputHexB = std::to_string(decimalValue);
                }

                cout << "Valor actual (R, G, B): %s, %s, %s\n",
                       inputHexR.c_str(), inputHexG.c_str(), inputHexB.c_str();
                updateLED();
                colorIndex = (colorIndex + 1) % 3;
                ThisThread::sleep_for(500ms);
              }
            }
          }
        }
      }
    }
  }
  }
