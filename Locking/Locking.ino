// LCD, KEYPAD, SERVO SMART SAFE WITH RASPBERRY PI CAM

#include <LiquidCrystal.h> //include LCD library (standard library)
#include <Servo.h>
#include <Keypad.h>

Servo ServoMotor;
char* password = "1234";  // change the password here, just pick any 3 numbers
int position = 0;
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

byte rowPins [ROWS] = {7, 6, 5, 4}; //pins of the keypad
byte colPins [COLS] = {3, 2, 1};

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); // pins of the LCD. (RS, E, D4, D5, D6, D7)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int RedpinLock = 9;
int GreenpinUnlock = 8;

void setup()
{
  pinMode(RedpinLock, OUTPUT);
  pinMode(GreenpinUnlock, OUTPUT);
  lcd.begin(16, 2);
  ServoMotor.attach(10);
  LockedPosition(true);
}

void loop()
{
  char key = keypad.getKey();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");
  if (key == '*' || key == '#'){
    position = 0;
    LockedPosition(true);
    }
  if (key == password[position]){
    position ++;
    }
  if (position == 4){
    LockedPosition(false);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Password Correct!");
    }
  delay(100);
}
void LockedPosition(int locked)
{
  if (locked){
    digitalWrite(RedpinLock, HIGH);
    digitalWrite(GreenpinUnlock, LOW);
    ServoMotor.write(11);
  }
  else{
    digitalWrite(RedpinLock, LOW);
    digitalWrite(GreenpinUnlock, HIGH);
    ServoMotor.write(90);
  }
}
