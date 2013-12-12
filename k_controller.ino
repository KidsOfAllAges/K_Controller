
///////////////////////////////////////////////////////////////
//  KIDS OF ALL AGES   
//
//  K_CONTROLLER  
//  (c) 2013 CAMERA OBSCURA MEDIA MATTHIAS A. UHLIG
//
//
///////////////////////////////////////////////////////////////


//DEFINES //

#define DIR_PIN 10
#define SPEED_PIN 9 // PWM

#define POWER_LED  4
#define TRIGGER_LED  5

#define TRIG_SHT 7
#define TRIG_FOC 6

#define IN_PIN1 0 // Ring
#define IN_PIN2 1 //Tip

#define INTERVAL_POT A1
#define INTERVAL_SW 3

#define SPEED_POT A0
#define SPEED_SW 2



// VARIABLES

int   newSpeedValue =0;// 0..255 from A0  motor speed value


unsigned long  intervalValue = 1000;      //0..60000 mapped from 0..255 A1 length of interval
int   exposureTime = 200;      // exposuretime in ms

unsigned long time, previousTime = 0;

boolean continous = false;
boolean running = false;







// --------------------------------------------------------------------------- Setup
void setup() {


  pinMode(POWER_LED, OUTPUT);
  pinMode(TRIGGER_LED, OUTPUT);
  pinMode(SPEED_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(TRIG_SHT, OUTPUT);
  pinMode(TRIG_FOC, OUTPUT);
  pinMode(INTERVAL_SW, INPUT);
  pinMode(SPEED_SW, INPUT);
  pinMode(IN_PIN2, INPUT);
  
  

  digitalWrite(POWER_LED, LOW);
  digitalWrite(TRIGGER_LED, LOW);
  digitalWrite(DIR_PIN, LOW); //Direction
  digitalWrite(SPEED_PIN, LOW);
  digitalWrite(TRIG_SHT, LOW);
  digitalWrite(TRIG_FOC, LOW);
  digitalWrite(INTERVAL_SW, HIGH); //Pullup
  digitalWrite(SPEED_SW, HIGH); //Pullup
  digitalWrite(TRIG_FOC, HIGH); // Pullup
  digitalWrite(IN_PIN2, HIGH); // Pullup


  time = millis();
  previousTime = millis();

// Set the following pins to a known state because it won't work without
 pinMode(13, OUTPUT);
 digitalWrite(13, LOW); 
 pinMode(11, OUTPUT);
 digitalWrite(11, LOW); 
 pinMode(12, OUTPUT);
 digitalWrite(12, LOW); 
 
 
}

void loop() 
{ 
  checkProgram();
  checkContinous();

  time = millis();

  if(time - previousTime > intervalValue)
  {
    previousTime = time;
    fireCamera();
    if ((continous == false) && (running == true))
    // if continous is false, we can move the motor in SMS mode
      moveMotorSMS();

  }


  //if continous is true, we move the motor for setup or while exposing
  if (continous == true)
    moveMotor();
    
  if(digitalRead(IN_PIN2) == LOW)
  {
  moveMotorSMS();
  fireCamera();
  }


}



void fireCamera() 
// This function triggers the camera with the given exposure time
// we set it at 200 ms because this should be detected by most DSLRs

{
  if(running==true)
  {
    digitalWrite(TRIG_SHT, HIGH);
    digitalWrite(TRIG_FOC, HIGH);
  }
  digitalWrite(TRIGGER_LED, HIGH);
  delay(exposureTime);
  digitalWrite(TRIG_SHT, LOW);
  digitalWrite(TRIG_FOC, LOW);
  digitalWrite(TRIGGER_LED, LOW);
}




void moveMotorSMS()
//moves the motor in SMS mode



{
  
  // the speed value here is actually a delay 
  // the motor will run as long as the delay is active, so a higher value means longer running time
  // resulting in longer travel which will result in higher speed in the output video
  
  newSpeedValue = analogRead(SPEED_POT);

  // check value. if it is between 505 and 515, we insert a deadband, nothing happens there
  if ((newSpeedValue <= 515) && (newSpeedValue >= 505))
  {
    newSpeedValue = 0;
    //switch of the motors
    digitalWrite(DIR_PIN ,LOW);
    digitalWrite(SPEED_PIN ,LOW);

  }
  else if (newSpeedValue < 505)
  {
    digitalWrite(DIR_PIN ,LOW);
    digitalWrite(SPEED_PIN,HIGH);
    // divide the sensor value by 16 to get slower SMS speed
    delay((505 - newSpeedValue)/8);
    digitalWrite(SPEED_PIN,LOW);
    digitalWrite(DIR_PIN ,LOW);

  }
  else if (newSpeedValue > 515)
  {

    digitalWrite(DIR_PIN,HIGH);
    digitalWrite(SPEED_PIN,LOW);
     // divide the sensor value by 16 to get slower SMS speed
    delay((newSpeedValue - 515)/8);
    digitalWrite(SPEED_PIN,LOW);
    digitalWrite(DIR_PIN ,LOW);
  }

} 

void moveMotor()
//moves the motor in continous mode and for setup
{ 
 if(continous == true)
 {

  newSpeedValue = analogRead(SPEED_POT);

  //insert a deadband
  if ((newSpeedValue <= 525) && (newSpeedValue >= 495))
  {
    newSpeedValue = 0;
    digitalWrite(SPEED_PIN,LOW);
    digitalWrite(DIR_PIN ,LOW);

  }
  else if (newSpeedValue <495)
  {
    digitalWrite(DIR_PIN ,LOW);

    analogWrite(SPEED_PIN,(495-(newSpeedValue/2))/2);
  }
  else if (newSpeedValue > 525)
  {
    digitalWrite(DIR_PIN,HIGH);

    analogWrite(SPEED_PIN,(525-(newSpeedValue/2))/2);
  }
 }
}



void checkProgram()
{
  // read in the value from the INTERVAL_POT pin and map it from 500 to 10000
  // this represents intervals from 500 ms to 10000 ms (0,5 -10 sec)

  intervalValue= analogRead(INTERVAL_POT);
  intervalValue = map(intervalValue, 0, 1023, 500, 10000);

  if(digitalRead(INTERVAL_SW) == LOW)
  // when INTERVAL_SW is pressed, insert a short delay to debounce
  delay(250);
  if(digitalRead(INTERVAL_SW) == LOW)
  //if button is still pressed, switch running state to the opposite and set led accordingly
  {
    running = ! running; 
    digitalWrite(POWER_LED,running);
  }

}

void checkContinous()
{

  if(digitalRead(SPEED_SW) == LOW)
  // when SPEEDL_SW is pressed, insert a short delay to debounce
    delay(250);
  if(digitalRead(SPEED_SW) == LOW)
  //if button is still pressed, switch continous state
    continous = !continous; 
    // delay(250);

}

