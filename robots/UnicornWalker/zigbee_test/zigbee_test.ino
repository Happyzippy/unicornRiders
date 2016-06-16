void setup(){
  //Serial2 Serial initialize
  Serial2.begin(57600);//115200);
  //You can attach your serial interrupt
  //or, also detach the interrupt by detachInterrupt(void) method
  //Serial2.attachInterrupt(serialInterrupt);
  pinMode(BOARD_LED_PIN, OUTPUT);  //toggleLED_Pin_Out
}
void serialInterrupt(byte buffer){
  Serial2.print((char)buffer);
}
char i = 0;
void loop(){
  Serial2.print("abc");
  Serial2.println(i++);
  toggleLED();
  delay(50);
}

