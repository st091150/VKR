const byte numOutPins = 8;
const byte numInPins = 4;

byte outPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
byte AoutPins[] = {2, 4, 6, 8};
byte BoutPins[] = {3, 5, 7, 9};
byte MoutPins[] = {10, 11, 12};
byte inPins[] = {A0, A1, A2, A3};



struct SUM{
  byte A;
  byte B;

  byte ComputerResult;

  void compute(byte* outPins){
    for(int i = 0; i < 4 ; ++i){
      digitalWrite(AoutPins[i], bitRead(A, i));
    }
    for(int i = 0; i < 4 ; ++i){
      digitalWrite(BoutPins[i], bitRead(B, i));
    }
    for(int i = 0; i < 5; ++i){
      bitWrite(ComputerResult, i, digitalRead(inPins[i]));
      //Serial.print(digitalRead(inPins[i]));
    }
    Serial.println();
    Serial.print("ComputerResult : ");
    Serial.println(ComputerResult);

  }
  void printBitsA(){
    Serial.print("A : ");
    Serial.print(bitRead(A, 3));
    Serial.print(bitRead(A, 2));
    Serial.print(bitRead(A, 1));
    Serial.print(bitRead(A, 0));
    Serial.println();
  }
  void printBitsB(){
    Serial.print("B : ");
    Serial.print(bitRead(B, 3));
    Serial.print(bitRead(B, 2));
    Serial.print(bitRead(B, 1));
    Serial.print(bitRead(B, 0));
    Serial.println();
  }
};
  SUM test;
  byte result = 0;
  int testNum = 0;
  int successTest = 0;
  int failTest = 0;

  
void setup() {

  for(int i = 0; i < numOutPins; ++i){
    pinMode(outPins[i], OUTPUT);
  }
  for(int i = 0; i < numInPins; ++i){
    pinMode(inPins[i], INPUT);
  }
  Serial.begin(9600);

  for(int i = 0 ; i < 10000; ++i){
    Serial.println("############################################################");
    test.A = random(15);
    test.B = random(15);
    //test.printBitsA();
    //test.printBitsB();
    test.compute(outPins);
    result = test.A + test.B;
    for(int i = 0 ; i < 5; ++i){
      Serial.print(bitRead(result, i));
    }
    Serial.println();
    for(int i = 0; i < 5; ++i){
      Serial.print(digitalRead(inPins[i]));
    }
    Serial.println();
    if(test.ComputerResult == result){
      Serial.print("Success test : ");
      Serial.println(testNum);
      successTest++;
    }else{
      Serial.print("Fail test : ");
      Serial.println(testNum);
      failTest++;
    }
    testNum++;

  }
  Serial.print("Success : ");
  Serial.println(successTest);
  Serial.print("Fail : ");
  Serial.println(failTest);
  unsigned long time = millis();
  Serial.print(time);
}

void loop() {
}
