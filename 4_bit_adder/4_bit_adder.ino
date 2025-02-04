//RICCARDO VESCIO
//My GitHub profile --> https://github.com/Richard-VR0
//My personal website --> https://rvescio.altervista.org
//My linktree --> https://linktr.ee/riccardovescio

#include <U8glib.h>     //Importing library

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 

int A[4];         //Vector that contain the first number
int B[4];         //Vector that contain the second number
int Y[5];         //Vector that contain the third number (result of the sum)

int sw = 10;      //Input switch

int red = 11;     //Signaling led for first number
int blue = 12;    //Signaling led for second number
int green = 13;   //Warning led

int aux;          //Auxiliary variable

void setup() {
  u8g.begin();

  pinMode(sw, INPUT);         //Sets the switch as an input
  
  pinMode(red, OUTPUT);       //Sets the red led as an output
  pinMode(blue, OUTPUT);      //Sets the blue led as an output
  pinMode(green, OUTPUT);     //Sets the green led as an output
}

void loop() {
  u8g.firstPage();

  do {
    draw();
  } while (u8g.nextPage());
}

void draw() {
  if (digitalRead(sw) == HIGH) {        //Switch status check
    solve();                            //Function call
  }

  String i = "A    " + String(A[0]) + String(A[1]) + String(A[2]) + String(A[3]) + " +";              //Creation of a string that contain the first number
  String j = "B    " + String(B[0]) + String(B[1]) + String(B[2]) + String(B[3]) + " =";              //Creation of a string that contain the second number
  String k = "Y   " + String(Y[0]) + String(Y[1]) + String(Y[2]) + String(Y[3]) + String(Y[4]);       //Creation of a string that contain the third number

  u8g.setFont(u8g_font_unifont);              //Sets the used font 

  u8g.drawFrame(0, 0, 128, 64);               //Frame creation

  u8g.drawStr(20, 20, i.c_str());             //Print the first number on the screen

  u8g.drawStr(20, 35, j.c_str());             //Print the second number on the screen

  u8g.drawLine(15, 40, 110, 40);              //Print a line on the screen
  
  u8g.drawStr(20, 55, k.c_str());             //Print the third number on the screen
}

void solve() {
  //Loading data alert
  digitalWrite(green, HIGH);
  delay(3000);
  digitalWrite(green, LOW);
  //End loading data alert

  //Wait loading
  delay(1000);

  //Switching ON the red led to indicate the loading of the first number
  digitalWrite(red, HIGH);

  delay(1000);

  //Loading first number
  for (int j = 3; j >= 0; j--) {

    for (int k = 0; k <= j; k++) {
      digitalWrite(green, HIGH);
      delay(250);
      digitalWrite(green, LOW);
      delay(250);
    }
    
    aux = 0;

    for (int i = 0; i < 100; i++) {
      if (aux == 0) {
        aux = digitalRead(sw);
      }

      delay(50);
    }

    A[j] = aux;
  }

  digitalWrite(red, LOW);
  //End loading first number

  //Loading data alert
  digitalWrite(green, HIGH);
  delay(3000);
  digitalWrite(green, LOW);
  //End loading data alert

  //Wait loading
  delay(1000);

  //Switching ON the blue led to indicate the loading of the second number
  digitalWrite(blue, HIGH);

  //Loading second number
  for (int j = 3; j >= 0; j--) {

    for (int k = 0; k <= j; k++) {
      digitalWrite(green, HIGH);
      delay(250);
      digitalWrite(green, LOW);
      delay(250);
    }
    
    aux = 0;

    for (int i = 0; i < 100; i++) {
      if (aux == 0) {
        aux = digitalRead(sw);
      }

      delay(50);
    }

    B[j] = aux;
  }

  digitalWrite(blue, LOW);
  //End loading second number

  int aux1, aux2, aux3, aux4;       //Auxiliary variables

  //Calculation of the sum          //You can find the logical scheme in "4 bit adder.dig"
  Y[4] = A[3] xor B[3];

  aux1 = A[3] and B[3];

  aux2 = A[2] xor B[2];

  Y[3] = aux1 xor aux2;

  aux3 = (aux1 and aux2) or (A[2] and B[2]);

  Y[2] = (A[1] xor B[1]) xor aux3;

  aux4 = ((aux3 and (A[1] xor B[1])) or (A[1] and B[1]));

  Y[1] = aux4 xor (A[0] xor B[0]);

  Y[0] = ((aux4 and A[0]) or (aux4 and B[0])) or (A[0] and B[0]);
  //End calculation of the sum
}
