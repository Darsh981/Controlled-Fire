//Gravity Acceleration
#include "LIS3DHTR.h"
#ifdef SOFTWAREWIRE
    #include <SoftwareWire.h>
    SoftwareWire myWire(3, 2);
    LIS3DHTR<SoftwareWire> LIS;       //Software I2C
    #define WIRE myWire
#else
    #include <Wire.h>
    LIS3DHTR<TwoWire> LIS;           //Hardware I2C
    #define WIRE Wire
#endif

float y = 0;
float threshY = 0;
float difference = .5;
int buttonPin = 2;
int calibrate = 0;
int ledPin = 3;

void setup() {
    Serial.begin(9600);
    while (!Serial) {};
    LIS.begin(WIRE, 0x19); //IIC init
    delay(100);
    LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
    pinMode(ledPin, OUTPUT);
}
void loop() {
  y = LIS.getAccelerationY();
  Serial.print("Current Y reading is: ");
  Serial.println(y);
  
  if(digitalRead(buttonPin) == 1 && calibrate == 0)
  {
    calibrate = 1;
    threshY = LIS.getAccelerationY();
    Serial.print("Calibrated to: ");
    Serial.println(threshY);
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(2000);
  }
  if(calibrate == 1)
  {
    Serial.print("Difference between og calibration and now: ");
    Serial.println(threshY - y);
    if(threshY - y > 0.4)
    {
      digitalWrite(ledPin, HIGH);
    }
    else
    {
      digitalWrite(ledPin, LOW);
    }
    
    
  }
  delay(1000);
}
