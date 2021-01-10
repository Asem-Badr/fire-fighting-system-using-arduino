#include <LiquidCrystal.h>
#include <Servo.h>
#define conPower 110
unsigned char  servo_pin = 5;
unsigned char  sensor1 = 2;
unsigned char  sensor2 = 3;
unsigned char  sensor3 = 4;

unsigned char  fire_flag = 0;
unsigned char  buzzer_pin = A2;
int  servo_degrees = 90;
int  pump_power = 0 ;
//int  pump_enaple = 6;
unsigned char  pump_pin = 7;
unsigned char  user_fire = 14 ;
unsigned char  servo_pos[3] = {180, 90, 0};


const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo myservo;

int x, y, z, u; //digital values for the sensors & user inputs
void setup() {
  lcd.begin(20, 4);

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  //pinMode(pump_enaple, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(user_fire , INPUT); //pin
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  myservo.attach(servo_pin);
  servo_degrees = 90;
  setServo(servo_degrees); //initializing servo

}

void loop()
{
  lcdUpdate();
  cheakSensors ();
  fight ();
  delay(50);
}


void lcdUpdate()
{
  lcd.setCursor(0, 0);
  lcd.print("fire fighting unit");

  if (fire_flag == 0)
  {
    lcd.setCursor(0, 1);
    lcd.print("     No fire     ");
    digitalWrite(buzzer_pin, LOW);
    digitalWrite(pump_pin, LOW);
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("  fire fire fire");
    digitalWrite(buzzer_pin, HIGH);
  }
  lcd.setCursor(0, 2);
  lcd.print("Servo posision :");
  lcd.print(servo_degrees);
  lcd.print("   ");
  lcd.setCursor(0, 3);
  lcd.print("Pump power :");
  lcd.print(pump_power);
  lcd.print("   ");

}
void cheakSensors ()//works fine
{
  x = digitalRead (sensor1);
  y = digitalRead (sensor2);
  z = digitalRead (sensor3);
  u = digitalRead (user_fire);
  if (x == 0 ||  y == 0  ||  z == 0  ||  u == 0)
  {
    fire_flag = 1 ;
  }
  else
  {
    fire_flag = 0 ;
  }
}

void cheakUser()
{
  servo_degrees = map( analogRead(A0), 0, 1023, 0, 180);
  pump_power = map( analogRead(A1), 0, 1023, 90, 255);
}

void fight ()
{
  if (x == 0)
  {
    servo_degrees = servo_pos[0];
    pump_power = conPower;
  }
  else if (y == 0)
  {
    servo_degrees = servo_pos[1];
    pump_power = conPower;
  }
  else if (z == 0)
  {
    servo_degrees = servo_pos[2];
    pump_power = conPower;
  }
  else if (u == 0)
  {
    cheakUser();
    setServo(servo_degrees);
    setPump(pump_power);
    //lcd new instructions
  }
  else
  {
    pump_power = 0;
  }
  setServo(servo_degrees); 
  setPump(pump_power);
  delay(100);
}

void setServo ( int deg)
{
  myservo.write(deg);
}
void setPump(int power)
{
  analogWrite(pump_pin, power);
}

/*void sweepServo ()
{
  int pos ;
  pos = myservo.read();
  for (int i = 0 ; i < 10 ; i++ )
  {
    myservo.write(pos - i);
    delay(5);
  }
  for (int i = 0 ; i < 20 ; i++ )
  {
    myservo.write(pos + i);
    delay(5);
  }
  for (int i = 0 ; i < 10 ; i++ )
  {
    myservo.write(pos - i);
    delay(5);
  }
}

void sweepWater ()
{
  int x = pump_power ;
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 20; j++ )
    {
      analogWrite(pump_pin, x - 10 + j);
    }
  }

}*/
/*void pumpEnable ()
  {

  }*/
