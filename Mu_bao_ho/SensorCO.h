
SoftwareSerial Serial2(2, 3); // RX, TX

uint8_t bytes[8] = {
  0xFF, // byte 0
  0x01, // byte 1  
  0x86, // data 2  // 0x87 to calibrate zero point
  0x00, // data 3
  0x00, // data 4
  0x00, // data 5
  0x00, // data 6
  0x00, // data 7
//  0x79, // data 8
};  
uint8_t response[9];

int read_co()
{
  int i=0;
  int res = 0;
  int checksum = 0;
  while((Serial2.available()>0)){
    byte k = Serial2.read();
    switch(i){
      
        case (0): if (k != 255) { i = -1; }; break;
        case (1): if (k != 134) { i = -1; }; break;
        case (2): res = (k<<8);        checksum = k; break;
        case (3): res += (k);  checksum += k; break;
        case (4):                   checksum += k; break;
        case (5):                   checksum += k; break;
        case (6):                   checksum += k; break;
        case (7):                   checksum += k; break;
      }
      i++;
    if(i == 8)
    {
      return res;
      i = 0;
    }
    yield();
  }
}
uint8_t checksum( ) {
  uint8_t sum = 0x00;
  for ( int i = 1; i < 8; i++) {
    sum += bytes[i];
  }
  sum = 0xff - sum + 0x01;
  return sum;
}
void request()
{
  for(uint8_t i = 0;i<8;i++) 
  {
    Serial2.write(bytes[i]);
  }
   Serial2.write(checksum());
   Serial2.flush();
  Serial.println("GET MH-Z16 data");
  if (response != NULL) {
    int i = 0;
    while(Serial2.available() <= 0) {
      if( ++i > 10 ) {
        Serial.println("error: can't get MH-Z19 response.");
        return;
      }
      yield();
      delay(50);
    }
    Serial.println("CO2 = "+String(read_co())+"ppm");
  }
}
void readCO()
{
  request();
}
void resetCO()
{
  bytes[2] = 0x87;
  request();
  delay(1000);
  bytes[2] = 0x86;
  request();
}
void setupCO()
{
  
}
