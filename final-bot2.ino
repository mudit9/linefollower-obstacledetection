// Pins for motor driver
int left1 = 2, right1 = 7, enable_left = 5; // left1, left2 and enable_left decide the polarity and speed (through PWM) of the left motor;
int left2 = 4, right2 = 8, enable_right = 6; // right1, right2 and enable_right decide the polarity and speed (through PWM) of the right motor;

float direction = 1;     // Direction of movement of the bot: +1 for forward and 0 for backward motion.

int IR_left_pin = 10;  // pin connections for left and right IR sensors
int IR_right_pin = 11;   // Output of the left IR sensor goes to pin number 10 and that of the right IR sensor goes to pin 11

int IR_front_pin = 9;   // Output of the left IR sensor goes to pin number 10 and that of the right IR sensor goes to pin 11
int IR_front;
int IR_left;        // Output of the IR sensors
int IR_right;

int speed_left=120;
int speed_right=120;

void setup() {

// modes for the pins connected to the two ultrasonic sensors.
  pinMode(IR_left_pin, INPUT);
  pinMode(IR_right_pin, INPUT);
  pinMode(IR_front, INPUT);

  pinMode(left1, OUTPUT);         // modes for the pins connected to the two dc motors.
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(enable_left, OUTPUT);
  pinMode(enable_right, OUTPUT);

  Serial.begin(9600);

}

void loop()
{
  IR_left = digitalRead(IR_left_pin);     // Reading the output givin by the IR sensors
  IR_right = digitalRead(IR_right_pin);
  IR_front = digitalRead(IR_front_pin);

if (IR_left==1 && IR_right==1)
  {
    forward(speed_left+40, speed_right+15);
  }
  if (IR_left==0 && IR_right==0)
  {
    Stop();
    delay(200);
  }
  if (IR_left==0 && IR_right==1)
  {
  analogWrite(enable_left,speed_right-60);
  analogWrite(enable_right, speed_right-20);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  }if (IR_left==1 && IR_right==0)
  {
   analogWrite(enable_left, speed_left-20);
  analogWrite(enable_right,speed_right-60);
   digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  }

  if ( IR_front == 1) 
{
  backward(speed_left,speed_right);
  delay(900);
  analogWrite(enable_left, speed_left);
  analogWrite(enable_right, 0);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  delay(1000);
  forward(speed_left, speed_right);
  delay(2500);

  
  analogWrite(enable_left,0);
  analogWrite(enable_right, speed_right);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  delay(700);

  while(IR_left==1&&IR_right==1){
     IR_left = digitalRead(IR_left_pin);     // Reading the output givin by the IR sensors
     IR_right = digitalRead(IR_right_pin);
    forward(speed_left-20,speed_right-20);
  }
  
  do{
  Stop();
  delay(500);
  forward(speed_left,speed_right);
  delay(200);
  analogWrite(enable_left, speed_left);
  analogWrite(enable_right, 0);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  delay(800);
  IR_left = digitalRead(IR_left_pin);     // Reading the output givin by the IR sensors
  IR_right = digitalRead(IR_right_pin);
  }while(!IR_left==1&&!IR_right==1);

  

  

  
 /* analogWrite(enable_left,0);
  analogWrite(enable_right, speed_right);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  delay(1000); 
  do{
  forward(speed_left, speed_right);
  IR_left = digitalRead(IR_left_pin);     // Reading the output givin by the IR sensors
  IR_right = digitalRead(IR_right_pin);
  }
  while(IR_left == 1 && IR_right ==1);
  }
  */
  
 }
}


void forward(int speed_left, int speed_right)  // Moves the bot forward. Takes PWM values (0-255) of left and right motor as input.
{
  analogWrite(enable_left, speed_left);
  analogWrite(enable_right, speed_right);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW); // Forward
}

void backward(int speed_left, int speed_right)  // Moves the bot backward. Takes PWM values (0-255) of left and right motor as input.
{
  analogWrite(enable_left, speed_left);
  analogWrite(enable_right, speed_right);
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH); // Backward
}

void Stop()
{
  analogWrite(enable_left, 0);
  analogWrite(enable_right, 0);
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW); //Stop
}
