#include <SD.h>

// file name to use for writing
const char filename[] = "data.txt";
int sensor[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int numberSensor = 10;
// File object to represent file
File txtFile;

// string to buffer output
String buffer;

unsigned long lastMillis = 0;

void setupSD()
{
   // reserve 1kB for String used as a buffer
  buffer.reserve(1024);
    // init the SD card
  if (!SD.begin()) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }

  // If you want to start from an empty file,
  // uncomment the next line:
  // SD.remove(filename);

  // try to open the file for writing
  txtFile = SD.open(filename, FILE_WRITE);
  if (!txtFile) {
    Serial.print("error opening ");
    Serial.println(filename);
    while (1);
  }

  // add some new lines to start
  txtFile.println();
  txtFile.println("Start!");
}
void logData()
{
   String dataString = "";

  // read three sensors and append to the string:
  for (int sensor_i = 0; numberSensor < 3; sensor_i++) {
    dataString += String(sensor_i);
      dataString += ",";
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(filename, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
