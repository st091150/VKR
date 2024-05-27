const byte numOutANumPins = 4;
const byte numOutBNumPins = 4;
const byte numOutOperPins = 3;
const byte numInNumPins = 4;

byte numOutAPins[] = {2, 3, 4, 5};
byte numOutBPins[] = {A3, A2, A1, A0};

byte outOperPins[] = {12, 11, 10};
byte inPins[] = {6, 7, 8, 9};


String operations[] = {"OR", "NAND", "NOR", "AND", "ADD", "SUB"};

byte operationsBits[][3] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
                            {1, 0, 0}, {1, 0, 1}};


struct aluTest{

  int A;
  int B;

  byte operationIdx;
  byte operation[3];

  int result;
  int computerResult;

  
  void test(int numOfTests, byte* outNumAPins, byte* outNumBPins, byte* outOperPins, byte* inPins){
    int successTest = 0;
    int failTest = 0;
    for(int i = 0; i < numOfTests; ++i){
      result = 0;
      computerResult = 0;
      A = 8;
      B = 5;

      printA();
      printB();

      operationIdx = 3;
      memcpy(operation, operationsBits[operationIdx], 3 * sizeof(byte));

      
      for(int i = 0; i < numOutANumPins ; ++i){
        digitalWrite(numOutAPins[i],  bitRead(A, i));
      }
        for(int i = 0; i < numOutBNumPins ; ++i){
        digitalWrite(numOutBPins[i],  bitRead(B, i));
      }
        for(int i = 0; i < numOutOperPins ; ++i){
        digitalWrite(outOperPins[i], operation[numOutOperPins - 1 - i]);
      }

      switch(operationIdx){
        case 0:
          result = A | B;
          break;
        case 1:
          result = ~(A & B) & 15;
          break;
        case 2:
          result = ~(A | B) & 15;
          break;
        case 3:
          result = A & B;
          break;
        case 4:
          result = (A + B) & 15;
          break;
        case 5:
          result = (A - B) & 15;
          break;
      }
      printOperBits();
      printResult();
      printComputerResult();

      if(result == computerResult){
        successTest++;
      }else{
        Serial.print("#######################");
        failTest++;
      }


    }
    Serial.print("SUCCESS Test: ");
    Serial.print(successTest);
    Serial.print("/ ");
    Serial.println(numOfTests);
  }

  void printA(){
    Serial.print("A: ");
    Serial.println(A);
    Serial.print("Abits: ");
    for(int i = 0; i < numOutANumPins; ++i){
      Serial.print(bitRead(A, numOutANumPins - 1 - i));
    }
    Serial.println();
  }

    void printB(){
    Serial.print("B: ");
    Serial.println(B);
    Serial.print("Bbits: ");
    for(int i = 0; i < numOutBNumPins; ++i){
      Serial.print(bitRead(B, numOutBNumPins - 1 - i));
    }
    Serial.println();
  }

  void printResult(){
    Serial.print("Result: ");
    Serial.println(result);
    Serial.print("resultBits: ");
    for(int i = 0; i < numInNumPins; ++i){
      Serial.print(bitRead(result, numOutBNumPins - 1 - i));
    }
    Serial.println();
  }

  void printComputerResult(){
    Serial.print("ComputerResult: ");
    for(int i = 0; i < numInNumPins; ++i){
      bitWrite(computerResult, i, digitalRead(inPins[i]));
    }
    Serial.println(computerResult);
    Serial.print("ComputerResultBits: ");
    for(int i = 0; i < numInNumPins; ++i){
      Serial.print(bitRead(computerResult, numOutBNumPins - 1 - i));
    }
    Serial.println();
  }

  void printOperBits(){
    Serial.print("Operation: ");
    Serial.println(operations[operationIdx]);
    Serial.print("OperationBits: ");
    for(int i = 0; i < numOutOperPins ; ++i){
      Serial.print(operation[i]);
    }
    Serial.println();
  }

};

aluTest cTest;

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < numOutANumPins; ++i){
    pinMode(numOutAPins[i], OUTPUT);
  }
  for(int i = 0; i < numOutBNumPins; ++i){
    pinMode(numOutBPins[i], OUTPUT);
  }
    for(int i = 0; i < numOutOperPins; ++i){
    pinMode(outOperPins[i], OUTPUT);
  }

  for(int i = 0; i < numInNumPins; ++i){
    pinMode(inPins[i], INPUT);
  }
  
  cTest.test(10, numOutAPins, numOutBPins, outOperPins, inPins);

}

void loop() {

}

