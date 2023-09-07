#include "mbed.h"
#include <cmath>
#include <iostream>
#include <vector>

const int numRows = 4;
const int numCols = 4;

PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);

void setRGBColor(float red, float green, float blue) {
  ledR = red;
  ledG = green;
  ledB = blue;
}

char keyMap[numRows][numCols] = {{'1', '2', '3', 'A'},
                                 {'4', '5', '6', 'B'},
                                 {'7', '8', '9', 'C'},
                                 {'*', '0', '.', 'D'}};

DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4),
                               DigitalOut(D5)};
DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8),
                              DigitalIn(D9)};

int leerOpcion() {
  int numero = -1;
  while (numero < 0 || numero > 3) {
    for (int i = 0; i < numRows; i++) {
      rowPins[i] = 0;

      for (int j = 0; j < numCols; j++) {
        if (!colPins[j]) {
          char keyPressed = keyMap[i][j];

          if (keyPressed >= '0' && keyPressed <= '3') {
            numero = keyPressed - '0';
          } else if (keyPressed == '*') {
            break;
          }

          ThisThread::sleep_for(500ms);
        }
      }

      if (numero >= 0 && numero <= 3) {
        break;
      }

      rowPins[i] = 1;
    }
  }
  return numero;
}

string numeroReal() {
  string x;
  char keyPressed;
  while (keyPressed != '*') {
    for (int i = 0; i < numRows; i++) {
      rowPins[i] = 0;

      for (int j = 0; j < numCols; j++) {
        if (!colPins[j]) {
          keyPressed = keyMap[i][j];
          ThisThread::sleep_for(500ms);
          if (keyPressed == '*') {
            break;
          } else {
            x = x + keyPressed;
            cout << x << endl;
          }
        }
      }

      rowPins[i] = 1;
    }
  }
  return x;
}

int main() {
  double x1;
  double y1;
  double x2;
  double y2;
  int num1;

  cout << "Ingresa el numero 1 para determinar el intercepto con el eje y la "
          "recta entre 2 puntos, el 2 para calcular promedio o el 3 para "
          "generar colores en led. \n";

  num1 = leerOpcion();

  if (num1 == 1) {
    cout << "Ingrese la x1: " << endl;
    x1 = stod(numeroReal());
    cout << x1 << endl;

    cout << "Ingrese la y1: " << endl;
    y1 = stod(numeroReal());
    cout << y1 << endl;

    cout << "Ingrese la x2: " << endl;
    x2 = stod(numeroReal());
    cout << x2 << endl;

    cout << "Ingrese la y2: " << endl;
    y2 = stod(numeroReal());
    cout << y2 << endl;

    double pendiente = (y2 - y1) / (x2 - x1);

    double interceptoY = y1 - (pendiente * x1);

    cout << "La pendiente de la recta que pasa por los dos puntos es: "
         << pendiente << endl;
    cout << "El intercepto en el eje y es: " << interceptoY << endl;

  } else if (num1 == 2) {
    int N;
    cout << "Ingrese la cantidad de temperaturas (N): " << endl;
    N = stoi(numeroReal());

    vector<double> temperaturas(N);

    for (int i = 0; i < N; i++) {
      cout << "Ingrese la temperatura " << i + 1 << ": ";
      temperaturas[i] = stod(numeroReal());
    }

    double suma = 0;
    for (int i = 0; i < N; i++) {
      suma += temperaturas[i];
    }
    double promedio = suma / N;

    double sumaCuadrados = 0;
    for (int i = 0; i < N; i++) {
      sumaCuadrados += pow(temperaturas[i] - promedio, 2);
    }
    double desviacionEstandar = sqrt(sumaCuadrados / N);

    cout << "El promedio de las temperaturas es: " << promedio << endl;
    cout << "La desviación estándar de las temperaturas es: "
         << desviacionEstandar << endl;

  } else if (num1 == 3) {
  }
}
