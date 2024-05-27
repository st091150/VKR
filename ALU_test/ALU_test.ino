const byte numOutANumPins = 4; // количество выходных битов 1-ого операнда 
const byte numOutBNumPins = 4; // количество выходных битов 2-ого операнда
const byte numOutOperPins = 3; // количество выходных управляющих битов
const byte numInNumPins = 4; // количество входящих битов

byte numOutAPins[] = {2, 3, 4, 5}; // пины для подачи 1 операнда
byte numOutBPins[] = {A3, A2, A1, A0}; // пины для подачи 2 операнда

byte outOperPins[] = {12, 11, 10}; // пины для подачи выходных управляющих битов
byte inPins[] = {6, 7, 8, 9}; // входные пины для результата

// поддерживаемые операции
String operations[] = {"OR", "NAND", "NOR", "AND", "ADD", "SUB"};

//коды поддерживаемых операций 
byte operationsBits[][3] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
                            {1, 0, 0}, {1, 0, 1}};

struct aluTest{

  int A; // 1 операнд 
  int B; // 2 операнд

  byte operationIdx; // индекс в массиве поддерживаемых операций
  byte operation[3]; // код текущей операции

  int result; // переменная для подсчета результата
  int computerResult; // переменная для хранения результата работы стенда

  
  void test(int numOfTests, byte* outNumAPins, byte* outNumBPins, byte* outOperPins, byte* inPins){
    int successTest = 0; // количество пройденных тестов
    int failTest = 0; // количество провальных тестов
    for(int i = 0; i < numOfTests; ++i){
      result = 0;
      computerResult = 0;
      A = random(16); // получение случайного 1-ого операнда в диапазоне [0,16)
      B = random(16); // получение случайного 2-ого операнда в диапазоне [0,16)

      printA(); // вывод 1-ого операнда
      printB(); // вывод 2-ого операнда

      operationIdx = random(6); // получение случайного индекса в массиве операций
	// получение кода операции
      memcpy(operation, operationsBits[operationIdx], 3 * sizeof(byte));

      // подача на плату 1-ого операнда
      for(int i = 0; i < numOutANumPins ; ++i){
        digitalWrite(numOutAPins[i],  bitRead(A, i));
      }
	// подача на плату 2-ого опереанда
        for(int i = 0; i < numOutBNumPins ; ++i){
        digitalWrite(numOutBPins[i],  bitRead(B, i));
      }
	// подача управляющих сигналов на плату
        for(int i = 0; i < numOutOperPins ; ++i){
        digitalWrite(outOperPins[i], operation[numOutOperPins - 1 - i]);
      }
	// нахождение истинного результата
      switch(operationIdx){
        case 0:
          result = (A | B) & 15;
          break;
        case 1:
          result = ~(A & B) & 15;
          break;
        case 2:
          result = ~(A | B) & 15;
          break;
        case 3:
          result = ~(A & B) & 15;
          break;
        case 4:
          result = (A + B) & 15;
          break;
        case 5:
          result = (A - B) & 15;
          break;
      }
      printOperBits(); // вывод кода операции
      printResult(); // вывод истинного результата
      printComputerResult(); // вывод результата полученного с АЛУ

	    // проверка правильности результата
      if(result == computerResult){
        successTest++;
      }else{
        failTest++;
      }

    }
    // вывод результатов тестирования
    Serial.print("SUCCESS Test: ");
    Serial.print(successTest);
    Serial.print("/ ");
    Serial.println(numOfTests);
  }
  // функция для вывода 1-ого операнда
  void printA(){
    Serial.print("A: ");
    Serial.println(A);
    Serial.print("Abits: ");
    for(int i = 0; i < numOutANumPins; ++i){
      Serial.print(bitRead(A, numOutANumPins - 1 - i));
    }
    Serial.println();
  }
    // функция для вывода 1-ого операнда
    void printB(){
    Serial.print("B: ");
    Serial.println(B);
    Serial.print("Bbits: ");
    for(int i = 0; i < numOutBNumPins; ++i){
      Serial.print(bitRead(B, numOutBNumPins - 1 - i));
    }
    Serial.println();
  }
  // функция для вывода истинного результата
  void printResult(){
    Serial.print("Result: ");
    Serial.println(result);
    Serial.print("resultBits: ");
    for(int i = 0; i < numInNumPins; ++i){
      Serial.print(bitRead(result, numOutBNumPins - 1 - i));
    }
    Serial.println();
  }
  // функция вывода результата работы АЛУ
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

// вывод кода текущей операции
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

  // установка выходных пинов для 1-ого операнда в режим OUTPUT
  for(int i = 0; i < numOutANumPins; ++i){
    pinMode(numOutAPins[i], OUTPUT);
  }
  // установка выходных пинов для 2-ого операнда в режим OUTPUT
  for(int i = 0; i < numOutBNumPins; ++i){
    pinMode(numOutBPins[i], OUTPUT);
  }
  // установка выходных пинов для управляющих сигналов в режим OUTPUT
  for(int i = 0; i < numOutOperPins; ++i){
    pinMode(outOperPins[i], OUTPUT);
  }
  // установка входных пинов для получения результата работы АЛУ
  for(int i = 0; i < numInNumPins; ++i){
    pinMode(inPins[i], INPUT);
  }
  // запуска тестирования
  cTest.test(1000, numOutAPins, numOutBPins, outOperPins, inPins);
}
