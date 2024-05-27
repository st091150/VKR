const byte numOutPins = 4;
const byte numInPins = 4;

byte outPins[numOutPins] = {2, 3, 4, 5};
byte inSyncPin = 6;
byte outSyncPin = 7;
byte inPins[numInPins] = {A5, A4, A3, A2};


struct regTest{
  byte A;
  byte preRes = 0;
  byte result = 0;
  bool sync;

  void test(int numOfTests, byte* outPins, byte inSyncPin, byte outSyncPin, byte* inPins){
   
    int successTest = 0;
    int failTest = 0;
    bool inSync = 1;
    bool outSync = 1;
    for(byte i = 0; i < numInPins; ++i){
      bitWrite(preRes, i, digitalRead(inPins[i]));
    }
    for (int i = 0; i < numOfTests; i++){
      Serial.println("########################################################");

      A = random(15);
      inSync = random(2);
      outSync = random(2);
      if(inSync){
        preRes = A;
      }
      digitalWrite(inSyncPin, inSync);
      digitalWrite(outSyncPin, outSync);
      for(int i = 0; i < numOutPins ; ++i){
        digitalWrite(outPins[i], bitRead(A, i));
      }


    
      Serial.print("result : ");
      for(byte i = 0; i < numInPins; ++i){
        bitWrite(result, i, digitalRead(inPins[i]));
        Serial.print(digitalRead(inPins[numInPins - i - 1]));
      }

      Serial.println();
      Serial.print("A : ");
      Serial.print(bitRead(A, 3));
      Serial.print(bitRead(A, 2));
      Serial.print(bitRead(A, 1));
      Serial.println(bitRead(A, 0));

      Serial.print("inSync : ");
      Serial.println(inSync);

      Serial.print("OutSync : ");
      Serial.println(outSync);

      Serial.print("result : ");
      Serial.println(result);

      Serial.print("preRes : ");
      Serial.println(preRes);

      Serial.print("TEST :");
      Serial.print(i + 1);
      Serial.print(" / ");
      Serial.println(numOfTests);
      if(outSync){
        if(inSync){
          if(result == A){
            Serial.print(" ( SUCCESS )");
            successTest++;
          }else{
            Serial.print(" ( FAIL )");
            failTest++;
          }
        }else{
          if(preRes == result){
            Serial.print(" ( SUCCESS )");
            successTest++;
          }else{
            Serial.print(" ( FAIL )");
            failTest++;
          }
        }
      }else{
        if(result == 0){
            Serial.print(" ( SUCCESS )");
            successTest++;
          }else{
            Serial.print(" ( FAIL )");
            failTest++;
          }
      }
      Serial.println();
    }
     Serial.print("successTest : ");
     Serial.print(successTest);
     Serial.print("/ ");
     Serial.println(numOfTests);
  }
};

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < numOutPins; ++i){
    pinMode(outPins[i], OUTPUT);
  }
  for(int i = 0; i < numInPins; ++i){
    pinMode(inPins[i], INPUT);
  }
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  regTest test_1;
  test_1.test(150, outPins, inSyncPin, outSyncPin, inPins);

}

void loop() {

}
