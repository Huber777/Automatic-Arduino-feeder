
//initail force sensor value
int FSR = 0;
//initail feed quantity value
int feedQty = 0;

//Include LCD library
#include <LiquidCrystal.h>
//Include Stepper motor library
#include <Stepper.h>

//initailize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 13, 5 , 4, 3, 2);

// change this to fit the number of steps per revolution for your motor
const int stepsPerRevolution = 64;  

// initialize the stepper library on pins 8 through 11:
int in1Pin = 8;
int in2Pin = 9;
int in3Pin = 10;
int in4Pin = 11;
Stepper myStepper(stepsPerRevolution,in1Pin, in2Pin, in3Pin, in4Pin);

void setup() {
  //set up the LCD's number of columns and rows:
  lcd.begin(16,2);
  //print a message to the LCD.
  lcd.print("FEED QUANTITY:");
   // set the speed at 100 rpm:
  myStepper.setSpeed(100);
  // initialize the serial port:
  Serial.begin(9600);
  // set the force resistor pin:
  pinMode(7, OUTPUT);


}

void loop() {
  int FSRValue = analogRead(FSR);



  Serial.println(FSRValue);
  delay(1000);
  if (FSRValue>50){
  //  Serial.print("aaa");
    digitalWrite(7,HIGH);
    //count the feedQty
    feedQty++;
     // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution*10);
  delay(500);
  //set the cursor to colum 0,line 1
  //(note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  //Print a message to second line of LCD
  lcd.print(feedQty);

  
  }
  else
  //no force on the sensor, the light goes off 
  //and the stepper motor stop rotate
  digitalWrite(7,LOW);
  myStepper.step(0);
}
