#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ce 8
#define csn 9

#define gear1 A0
#define gear2 A1
#define gear3 A2
#define auto_mode A3
#define backward A4
#define forward A5

int v_forward;
int v_backward;
int state_gear1 = 0;
int state_gear2 = 0;
int state_gear3 = 0;
int gear = 1;

RF24 radio(ce, csn); // CE, CSN

const byte address[6] = "00001";

struct data{
  int V_FORWARD;
  int V_BACKWARD;
};
data send_data;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(forward, INPUT);
  pinMode(backward, INPUT);
  pinMode(gear1, INPUT);
  pinMode(gear2, INPUT);
  pinMode(gear3, INPUT);
  pinMode(auto_mode, INPUT);
}

void find_gear(){
  state_gear1 = digitalRead(gear1);
  state_gear2 = digitalRead(gear2);
  state_gear3 = digitalRead(gear3);

    if (state_gear1 == HIGH){
      gear = 1;
    }
    else if (state_gear2 == HIGH){
      gear = 2;
    }
    else if (state_gear3 == HIGH){
      gear = 3;
    }
}

void manual_mode_forward(){
  find_gear();
  v_forward += 5;
  switch(gear){
    case 1:
      if (v_forward > 100) v_forward = 100;
      break;
    case 2:
      if (v_forward > 180) v_forward = 180;
      break;
    case 3:
      if (v_forward > 255) v_forward = 255;
      break;  
  }

}  
void manual_mode_backward(){
  find_gear();
  v_backward +=5;
  switch(gear){
    case 1:
      if (v_backward > 100) v_backward = 100;
      break;
    case 2:
      if (v_backward > 180) v_backward = 180;
      break;
    case 3:
      if (v_backward > 255) v_backward = 255;
      break;  
  }
} 
  
void automatic_mode(){
  v_forward = 0;
  find_gear();
  switch(gear){
    case 1:
      v_forward = 100;
      break;
    case 2:
      v_forward = 180;
      break;
    case 3:
      v_forward = 255;
      break;  
  }
  Serial.print("forward : ");
  Serial.println(v_forward);
}

void reset_speed(){
  v_forward = v_backward = 0;
}

void loop() {
  if ( digitalRead(auto_mode) == 0){
    if (digitalRead(forward) == 1){
      manual_mode_forward();
    }else if (digitalRead(backward) == 1){
      manual_mode_backward();
    }
    else reset_speed();
  Serial.print("forward : ");
  Serial.print(v_forward);
  Serial.print("   backward : ");
  Serial.println(v_backward);
  }
  else if ( digitalRead(auto_mode) == 1) automatic_mode();
  send_data.V_FORWARD = v_forward;
  send_data.V_BACKWARD = v_backward;
  radio.write(&send_data, sizeof(data));
}
