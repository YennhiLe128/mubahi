const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
float vectorprevious;
float vector;
float totalvector;
double x;
double y;
double z;
int Steps = 0;
int accelX;  int accelY;  int accelZ;;
double Distance_all_time = 0;
void setupMPU()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}
void readMPU()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
   
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
   
  Serial.print("AngleX= ");
  Serial.println(x);
   
  Serial.print("AngleY= ");
  Serial.println(y);
   
  Serial.print("AngleZ= ");
  Serial.println(z);
  Serial.println("-----------------------------------------");
  delay(400);
}


void readSteps() {
   readMPU();
   vector = sqrt( (x * x) + (y * y) + (z * z) );
   //OzOled.printString("Vec:", 0, 2);
   //OzOled.printNumber(vector, 0, 5, 2);
   totalvector = vector - vectorprevious;
   //OzOled.printString("Pre:", 0, 4);
   //OzOled.printNumber(vectorprevious, 0, 5, 4);
   //OzOled.printString("Diff:", 0, 6);
   //OzOled.printNumber(totalvector, 0, 5, 6); 
  if (totalvector > 6){
    Steps++;
  }
  //String Step_count = String(Steps);
  //char data[2];
  //Step_count.toCharArray(data, 2);
  //OzOled.printBigNumber(data, 6, 2, 3);
  Serial.println("STEPS: "+String(Steps)+"/n");
  vectorprevious = vector;
  delay(600);
  //OzOled.clearDisplay(); 
}
void readDistance()
{
  Distance_all_time += sqrt( (x * x) + (y * y) + (z * z) );
}
