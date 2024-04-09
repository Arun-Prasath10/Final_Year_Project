#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

const int echoPin_1 = 7; // Echo pin
const int trigPin_1 = 8; // Trigger pin

const int echoPin_2 = 9; // Echo pin
const int trigPin_2 = 10; // Trigger pin

const int echoPin_3 = 12; // Echo pin
const int trigPin_3 = 13; // Trigger pin

long duration_1;
int distance_1;

long duration_2;
int distance_2;

long duration_3;
int distance_3;

int buzzer = 2;

int motor_1 = 3;
int motor_2 = 4;
int motor_3 = 5;
int motor_4 = 6;

bool buzzer_operation = 0;
void setup() {


  lcd.init();
  lcd.backlight();
  // Initialize the serial communication
  Serial.begin(9600);

  // Set the trigger pin as an OUTPUT
  pinMode(trigPin_1, OUTPUT);
  // Set the echo pin as an INPUT
  pinMode(echoPin_1, INPUT);

  // Set the trigger pin as an OUTPUT
  pinMode(trigPin_2, OUTPUT);
  // Set the echo pin as an INPUT
  pinMode(echoPin_2, INPUT);

  // Set the trigger pin as an OUTPUT
  pinMode(trigPin_3, OUTPUT);
  // Set the echo pin as an INPUT
  pinMode(echoPin_3, INPUT);

  pinMode(motor_1 , OUTPUT);
  pinMode(motor_2 , OUTPUT);
  pinMode(motor_3 , OUTPUT);
  pinMode(motor_4 , OUTPUT);

  pinMode(buzzer , OUTPUT);


}

void loop() {


  ultrasonic_1();
  ultrasonic_2();
  ultrasonic_3();

  if ( distance_1 < 30 )
  {
    lcd.setCursor(0, 0);
    lcd.print("VEHICLE :");
    lcd.print(" FORWARD");
    motor_forward();
    if ( buzzer_operation == 0)
    {
      digitalWrite(buzzer , HIGH);
      delay(1000);
      digitalWrite(buzzer , LOW);
      buzzer_operation = 1;
    }
  }

  if ( distance_2 < 30 )
  {
    lcd.setCursor(0, 0);
    lcd.print("VEHICLE :");
    lcd.print(" LEFT  ");
    motor_right();
    if ( buzzer_operation == 0)
    {
      digitalWrite(buzzer , HIGH);
      delay(1000);
      digitalWrite(buzzer , LOW);
      buzzer_operation = 1;
    }
  }

  if ( distance_3 < 30 )
  {
    lcd.setCursor(0, 0);
    lcd.print("VEHICLE :");
    lcd.print(" RIGHT  ");
    motor_left();
    if ( buzzer_operation == 0)
    {
      digitalWrite(buzzer , HIGH);
      delay(1000);
      digitalWrite(buzzer , LOW);
      buzzer_operation = 1;
    }
  }

  if (distance_1 > 30 && distance_2 > 30 && distance_3 > 30 )
  {
    lcd.setCursor(0, 0);
    lcd.print("VEHICLE :");
    lcd.print(" STOP   ");
    motor_stop();
    delay(100);
    buzzer_operation = 0;

  }

}
void ultrasonic_1() {

  digitalWrite(trigPin_1, LOW);
  delayMicroseconds(2);

  // Send a 10us pulse to the trigger pin
  digitalWrite(trigPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_1, LOW);

  // Read the duration of the echo pulse
  duration_1 = pulseIn(echoPin_1, HIGH);

  // Calculate the distance in centimeters
  distance_1 = duration_1 * 0.034 / 2;

  // Display the distance on the serial monitor
  Serial.print("Distance_1: ");
  Serial.print(distance_1);
  Serial.println(" cm");

  // Add a delay before the next measurement
  delay(100); // You can adjust this delay to control the measurement rate
}

void ultrasonic_2() {

  digitalWrite(trigPin_2, LOW);
  delayMicroseconds(2);

  // Send a 10us pulse to the trigger pin
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);

  // Read the duration of the echo pulse
  duration_2 = pulseIn(echoPin_2, HIGH);

  // Calculate the distance in centimeters
  distance_2 = duration_2 * 0.034 / 2;

  // Display the distance on the serial monitor
  Serial.print("Distance_2: ");
  Serial.print(distance_2);
  Serial.println(" cm");

  // Add a delay before the next measurement
  delay(100); // You can adjust this delay to control the measurement rate
}

void ultrasonic_3() {



  digitalWrite(trigPin_3, LOW);
  delayMicroseconds(2);

  // Send a 10us pulse to the trigger pin
  digitalWrite(trigPin_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_3, LOW);

  // Read the duration of the echo pulse
  duration_3 = pulseIn(echoPin_3, HIGH);

  // Calculate the distance in centimeters
  distance_3 = duration_3 * 0.034 / 2;

  // Display the distance on the serial monitor
  Serial.print("Distance_3: ");
  Serial.print(distance_3);
  Serial.println(" cm");

  // Add a delay before the next measurement
  delay(100); // You can adjust this delay to control the measurement rate

}

void motor_forward() {
  digitalWrite(motor_1, HIGH);
  digitalWrite(motor_2, LOW);
  digitalWrite(motor_3, HIGH);
  digitalWrite(motor_4, LOW);
  delay(100);
}

void motor_right() {
  digitalWrite(motor_1, HIGH);
  digitalWrite(motor_2, LOW);
  digitalWrite(motor_3, LOW);
  digitalWrite(motor_4, HIGH);
  delay(100);
}

void motor_left() {
  digitalWrite(motor_1, LOW);
  digitalWrite(motor_2, HIGH);
  digitalWrite(motor_3, HIGH);
  digitalWrite(motor_4, LOW);
  delay(100);
}

void motor_stop() {
  digitalWrite(motor_1, LOW);
  digitalWrite(motor_2, LOW);
  digitalWrite(motor_3, LOW);
  digitalWrite(motor_4, LOW);
  delay(100);
}
