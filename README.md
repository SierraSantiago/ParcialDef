SANTIAGO SIERRA Y PABLO GARCÍA

Lo primero que se hizo es que se creo una matriz 4x4, la cual ya estaba een el código del teclado de las clase pasada y también se trajeron los pines como se habían definido, para saber en donde conectarlos en la tarjeta FRDM-KL25Z. 
```bash
    $ const int numRows = 4;
      const int numCols = 4;

        char keyMap[numRows][numCols] = {{'1', '2', '3', 'A'},
                                 {'4', '5', '6', 'B'},
                                 {'7', '8', '9', 'C'},
                                 {'*', '0', '.', 'D'}};

        DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4),
                               DigitalOut(D5)};
        DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8),
                              DigitalIn(D9)};
    ```
El primer método que se trabajó fue el de leerOpcion(), el cual  lo que hace es basicamente devolver un número entre 1 y 3, que después este método se va a llamar a la hora en que el usuario ingrese el punto que quiera realizar, 1, 2 o 3. El método funnciona por medio de un ciclo while que pregunta que la variable número esté fuera del rango entre 1 y 3, ya que incialmente la variable número se inicializa en -1.Luego, debido a esto mismo entra a ese ciclo while en donde se recorre la matríz de la misma manera que en código del teclado de la clase anterior. Luego de que se recorren filas y columnas se guarda la tecla presionada por el usuario en una variable llamada keyPress. Después se pregunta si keyPress esta entre 1 y 3, si esto es verdadero el valor de la variable número es reemplazado por Keypress y si keyPress es '*' se detiene el ciclo, pero si keyPress está entre 1-3 ya se para el ciclo en la siguiente iteración y se retorna el valor de número que sería entre 1-3, si esto nunca pasa el ciclo se repite indefinidamente hasta que la tecla presionada esté entre 1 y 3. 
```bash
$ int leerOpcion() {
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

 ```
Luego el método numeroReal funciona de una manera muy similar al método leerOpcion, ya que recorre la matriz de la misma manera siempre y cuando la tecla presionada no sea '*'. Luego guarda la tecla presionada en otra varaible char llamada Keypressed, si esta es un * sale del ciclo, de lo contrario le suma a la variable x que es un string y está vacía y guarda esta suma en x. Muestra esta variable en consola y devuelve la variable x. Y obviamente vuelve a poner los pines de las filas en 1 como se hace también en el método leerOpcion().
```bash
$string numeroReal() {
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
 ```
PUNTO 1.
Al comienzo del main, lo primero es que se le pregunta al usuario cual punto quiere desarrollar, y se invoca una variable que se acaba de crear llamada num1 que va a estar igualada al método leerOpcion(), con lo que se ingresará directamente al punto que el usuario escoja.
Para el primer punto se crean 4 variables globales que seán los puntos del plano cartesiano, 2 en x y 2 en y. Se le pide al usuario que ingrese cada una de estas variables y se iguala cada variable a un stod que lo que hace es convertir el string que delvuelve el método numeroReal a un double para posteriormentye hacer los cálculos de promedio y desviación estandar como se hacen normalmente y finalmente mostrarlos en pantalla con un cout. 
```bash
$if (num1 == 1) {
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
 ```
PUNTO 2
Lo primero que hacíamos era pedirle al usuario que ingresara la cantidad de temperaturas que quería ingresar. Y eso lo guardábamos en una variable de tipo entera. También importabamos al principio del proyecto #include <vector> para poder crear un vector del tamaño de la variable N que es la cantidad total de temperaturas que el usuario va a ingresar. Luego recorríamos con un for, en donde el usuario iba ingresando las temperaturas hasta que se llegaara hasta N y estas a su vez se iban guardando en el vector de temperatura en cada ciclo en una posición diferente. Por medio de otro ciclo for recorríamos otra vez hasta la N, e íbamos sumando en una variable double que habíamos creado fuera del ciclo, todas las temperaturas que habíamos guardado en el vector en el ciclo anterior. Calcilabamos el promedio dividiendo esta suma sobre N y por último con otro ciclo for calculábamos la desviación standard en donde sumábamos en una variable double creada fuera del ciclo, en donde elevábamos cada temperatura menos el promedio, lo elevábamos al cuadrado. Y ya afuera del ciclo creábamos una variable double (desviacionStandard) en donde le sacábamos raíz cuadrada a la suma de cuadrados recien calculada en el for anterior sobre N. Y ya se mostraba en consola con el cout la desviacionstandard y el promedio.
```bash
$else if (num1 == 2) {
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
 ```
 PUNTO 3
Para el tercer punto lo que se hizo fue traer los 3 LEDs que habíamos creado en el código del RGB de clase y a cada uno asignarle el rojo, verde y azul. Posteriormente se crearon las variables double r,g y b. Para pedirle al usuario que ingresara un led a cada uno de los tres colores entre 0 y 255 y finalmente guardamos el valor que nos pasaba el usuario de rojo, verde y azul en las variables double que habíamos creado por medio nuevamente del método numeroReal concatenado del método stod para la conversión de String a double. Y finalmente dividíamos el valor de cada uno de los valores sobre 255 y lo mostrabamos por medio de LEDR.write(r/255); y así con cada color. 
 ```bash
$else if (num1 == 3) {
    PwmOut ledR(LED1);
    PwmOut ledG(LED2);
    PwmOut ledB(LED3);
    double r, g, b;
    cout << "ingresar el valor del led Rojo(de 0 a 255):";
    r = stod(numeroReal());
    cout << "ingresar el valor del led verde(de 0 a 255):";
    g = stod(numeroReal());
    cout << "ingresar el valor del led Rojo(de 0 a 255):";
    b = stod(numeroReal());
    ledR.write(r/255);
    ledG.write(g/255);
    ledB.write(b/255);
  }
 ```
