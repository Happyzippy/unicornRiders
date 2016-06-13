/* Minimum_Source*/

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(57600); 

}

void loop() {
  // put your main code here, to run repeatedly: 
  if(Serial2.available()){
      Serial2.print((char)Serial2.read());
  }
}
