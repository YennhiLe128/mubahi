SoftwareSerial gprsSerial(5,4);

#define TIMEOUT 30000

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    gprsSerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(gprsSerial.available()) 
  {
    Serial.write(gprsSerial.read());//Forward what Software Serial received to Serial Port
  }
}
void setupSim()
{
  gprsSerial.println("AT");
  updateSerial();
  gprsSerial.println("AT+CSQ"); 
  updateSerial();
  gprsSerial.println("AT+CCID"); 
  updateSerial();
  gprsSerial.println("AT+CREG?");
  updateSerial();
}
void Call2People()
{
    Serial.println("Bat dau cuoc goi");
  setupSim();
  gprsSerial.println("ATD+ +84359581461;");
  updateSerial();
  delay(10000);
  gprsSerial.println("ATH");
  updateSerial();
  
}
void smartDelay(int n)
{
  delay(n);
}
void sendData2Server()
{
   
  if (gprsSerial.available())
    Serial.write(gprsSerial.read());
 
  gprsSerial.println("AT");
  smartDelay(50);
 
  gprsSerial.println("AT+CPIN?");
  smartDelay(50);
 
  gprsSerial.println("AT+CREG?");
  smartDelay(50);
 
  gprsSerial.println("AT+CGATT?");
  smartDelay(200);
 
  gprsSerial.println("AT+CIPSHUT");
  smartDelay(200);
 
  gprsSerial.println("AT+CIPSTATUS");
  smartDelay(500);
 
  gprsSerial.println("AT+CIPMUX=0");
  smartDelay(500);
 
//  ShowSerialData();
 
  gprsSerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  smartDelay(500);
 
//  ShowSerialData();
 
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  smartDelay(600);
 
//  ShowSerialData();
 
  gprsSerial.println("AT+CIFSR");//get local IP adress
  smartDelay(500);
 
//  ShowSerialData();
 
  gprsSerial.println("AT+CIPSPRT=0");
  smartDelay(600);
 
//  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  smartDelay(1000);
 
//  ShowSerialData();
 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  smartDelay(1200);
//  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=GREVUBB6XWPZZ0G8&field1=";
  Serial.println(str);
    for (int sensor_i = 0; numberSensor < 3; sensor_i++) {
    str += "&field"+String(sensor_i)+"="+String(sensor[sensor_i]);
  }
   Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  float  maxgiatoc = 0;
  smartDelay(1200);
//  ShowSerialData();
 
  gprsSerial.println((char)26);//sending
  smartDelay(2000);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
 
 // ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");//close the connection
  smartDelay(100);
//  ShowSerialData();
} 
