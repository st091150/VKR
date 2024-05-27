const byte numOutNumPins = 7;
const byte numOutOperPins = 3;
const byte numInNumPins = 1;

byte outNumPins[] = {2, 3, 4, 5};
byte outOperPins[] = {6, 7, 8};

byte inPin[] = {10};

String operations[] = {"0", "=0", "<0", "<=0", "1", "!=0", ">=0", ">0"};

byte operationsBits[][3] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
                            {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

byte numberBits[][4] = {  {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 0, 1, 1},
                          {0, 1, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1},
                          {1, 0, 0, 0}, {1, 0, 0, 1}, {1, 0, 1, 0}, {1, 0, 1, 1},
                          {1, 1, 0, 0}, {1, 1, 0, 1}, {1, 1, 1, 0}, {1, 1, 1, 1}};
int numberArr[] = {0, 1, 2, 3, 4, 5, 6, 7, -8, -7, -6, -5, -4, -3, -2, -1};

struct ConditionTest{

  byte numberIdx;
  byte nBits[4];
  int number;

  byte operationIdx;
  byte oBits[3];
  
  bool result;
  bool computerResult;

  bool inputResult;
  
  void test(int numOfTests, byte* outNumPins, byte* outOperPins){
    int successTest = 0;
    int failTest = 0;
    for(int i = 0; i < numOfTests; ++i){
        numberIdx = random(16);
        memcpy(nBits, numberBits[numberIdx], 4 * sizeof(byte));
        number = numberArr[numberIdx];
        for(int i = 0; i < 4 ; ++i){
          digitalWrite(outNumPins[i], nBits[i]);
        }
        printNumBits();

        operationIdx = random(8);
        memcpy(oBits, operationsBits[operationIdx], 3 * sizeof(byte));
        for(int i = 0; i < 3 ; ++i){
          digitalWrite(outOperPins[i], oBits[i]);
        }
        printOperBits();

        switch(operationIdx){
          case 0:
            result = false;
            break;
          case 1:
            result = (number == 0);
            break;
          case 2:
            result = (number < 0);
            break;
          case 3:
            result = (number <= 0);
            break;
          case 4:
            result = true;
            break;
          case 5:
            result = (number != 0);
            break;
          case 6:
            result = (number >= 0);
            break;
          case 7:
            result = (number > 0);
            break;
        }
        printResults();
        if(result == computerResult){
          successTest++;
        }else{
          failTest++;
        }
    }
    Serial.print("SUCCESS Test: ");
    Serial.print(successTest);
    Serial.print("/ ");
    Serial.println(numOfTests);
  }

  void printResults(){
    bitWrite(computerResult, 0, digitalRead(inPin[0]));
    Serial.print("computerResult: ");
    Serial.println(computerResult);
    Serial.print("Result: ");
    Serial.println(result);
  }
  void printNumBits(){
    Serial.println();
    Serial.print("number: ");
    Serial.println(numberArr[numberIdx]);
    Serial.print("numberBits: ");
    Serial.print(bitRead(number, 3));
    Serial.print(bitRead(number, 2));
    Serial.print(bitRead(number, 1));
    Serial.println(bitRead(number, 0));
  }

  void printOperBits(){
    Serial.print("OperationBits: ");
    for(int i = 0; i < numOutOperPins ; ++i){
      Serial.print(oBits[i]);
    }
    Serial.println();
    Serial.print("Operation: ");
    Serial.print(operations[operationIdx]);
    Serial.println();
  }

};

ConditionTest cTest;

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < numOutNumPins; ++i){
    pinMode(outNumPins[i], OUTPUT);
  }
  for(int i = 0; i < numOutOperPins; ++i){
    pinMode(outOperPins[i], OUTPUT);
  }
  for(int i = 0; i < numInNumPins; ++i){
    pinMode(inPin[i], INPUT);
  }
  
  cTest.test(200, outNumPins, outOperPins);

}

void loop() {

}
