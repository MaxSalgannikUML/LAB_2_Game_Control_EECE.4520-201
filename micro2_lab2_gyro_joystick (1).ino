#include <MPU6050.h>
#include <Wire.h>

MPU6050 mpu;
int x = A0; //VRx
int y = A1; //VRy
int swtch = 10; //SW
int buzzer = 11; //pin for buzzer
int Eflag = 0; //when the apple is eaten

void setup() {
  
  Serial.begin(9600);
  pinMode (x, INPUT);
  pinMode (y, INPUT);
  pinMode (buzzer, OUTPUT);

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
{    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
     delay(500);
}
  mpu.calibrateGyro ();
  mpu.setThreshold (3);
}

//Main loop
void loop() {

  if (Serial.available()>0){
    Eflag = Serial.read (); //flag given when an apple is eaten
    
    if (Eflag == 'E') {
      tone(buzzer, 500);
      delay(200);
      noTone(buzzer);      
    }
  }
  joy(); //calls to joy loop
  Vector normGyro = mpu.readNormalizeGyro(); //normalized values from the gyroscope
  gyro(normGyro.XAxis, normGyro.YAxis);

}

//Joy stick 
void joy() { 

  int upDown;
  int leftRight;

  //Reads the x and y inputs
  upDown = analogRead(x);
  leftRight = analogRead(y);

  delay (50);
  if (leftRight >= 750) { //if the joystick is moved a certain distance to the left then print a
    Serial.print ("a");
    }
  else if (leftRight <= 250) { //if the joystick is moved a certain distance to the right then print d
    Serial.print ("d");
    }
  else if (upDown <= 250) { //if the joystick is moved a certain distance up then print w
    Serial.print ("w");
    }
  else if (upDown >= 750) { //if the joystick is moved a certain distance down then print s
    Serial.print ("s");
  } 
}

void gyro (int tiltUpDown, int tiltLeftRight) {

  delay (75);
   if (tiltUpDown >= 100) { //if the gyro is moved a certain distance up then print w
    Serial.print ("w");
    }
  else if (tiltUpDown <= -100) { //if the gyro is moved a certain distance down then print s
    Serial.print ("s");
    }
  else if (tiltLeftRight >= 100) { //if the gyro is moved a certain distance to the right then print d
    Serial.print ("d");
    }
  else if (tiltLeftRight <= -100) { //if the gyro is moved a certain distance to the left then print a
    Serial.print ("a");
  }
}
