#include <Stepper.h>
#include <DHT.h>

#define DHTPIN 2 // set the pin that the sensor is connected to
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48) 200steps, 120 rpm
int step_mode = 8;
Stepper stepper1(STEPS, 12, 11, 10, 9,step_mode);
Stepper stepper2(STEPS, 12, 11, 10, 9,step_mode);
int step_count=0;
bool shadeOn=false;
int water;					


void setup() {
  // nothing to do
  //pinMode(5,OUTPUT);
  // pinMode(13,INPUT);
  pinMode(3,OUTPUT); //output pin for relay board, this will sent signal to the relay
pinMode(6,INPUT); //input pin coming from soil sensor
//Serial.begin(9600);

  Serial.begin(9600);
  //Serial.begin(31250); // start serial communication at 9600 baud
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  Serial.println("Temperature: ");
  Serial.println(temp);
  
water = digitalRead(6); // reading the coming signal from the soil sensor
Serial.print("Mositure : ");
Serial.print(water);
Serial.println();
if(water == 0) // if water level is full then cut the relay
{ Serial.print("Mositure in if : ");
Serial.print(water);
digitalWrite(3,0); // low is to cut the relay
}
else
{
  Serial.print("Mositure in else : ");
Serial.print(water);
digitalWrite(3,1); //high to continue proving signal and water supply
}


if(temp>30&&shadeOn==false)//temp beshi, bondho tai samne agabe
  {
    
    stepper1.setSpeed(120); // 1 rpm
    Serial.println("if");
    stepper1.step(18100);
    // Serial.print("abc");
    shadeOn=true;
    //stepper.setSpeed(0);
  } 
  else if(temp<30&&shadeOn==true)// temp kom, khola tai back krbe
  {
   Serial.println("elseif");
    stepper2.setSpeed(240); 
    stepper2.step(-18100);
    //Serial.println("baire");
    shadeOn=false;
    //stepper.setSpeed(0);
  }



  //cel>31 && flag, temperature beshi, khola
  //cel<31 && !flag, temperature kom, bondho
  delay(500);
}




