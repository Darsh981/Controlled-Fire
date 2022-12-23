#include <SPI.h>
#include <SD.h>

File GPS;

// change this to match your SD shield or module;
const int chipSelect = 10;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin())
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  GPS = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (GPS) 
  {
    Serial.print("Writing to test.txt...");
    GPS.println("testing 1, 2, 3.");
    // close the file:
    GPS.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  GPS = SD.open("test.txt");
  if (GPS) 
  {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (GPS.available()) 
    {
      Serial.write(GPS.read());
    }
    // close the file:
    GPS.close();
  } 
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop()
{
  // nothing happens after setup
}
