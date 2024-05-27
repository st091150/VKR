const byte numOutNumPins = 7; // количество выходных сигналов
const byte numOutOperPins = 3; // количество выходных управляющих сигналов
const byte numInNumPins = 1; // количество входных сигналов

byte outNumPins[] = {2, 3, 4, 5}; // выходные пины для подачи числа для проверки условий
byte outOperPins[] = {6, 7, 8}; // выходные пины для управляющих сигналов

byte inPin[] = {10}; // входной пин результата работа платы

String operations[] = {"0", "=0", "<0", "<=0", "1", "!=0", ">=0", ">0"}; // строковые представления поддерживаемых операций

// коды поддерживаемых операций 
byte operationsBits[][3] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
                            {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};
// побитовые представления поддерживаемых чисел
byte numberBits[][4] = {  {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 0, 1, 1},
                          {0, 1, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1},
                          {1, 0, 0, 0}, {1, 0, 0, 1}, {1, 0, 1, 0}, {1, 0, 1, 1},
                          {1, 1, 0, 0}, {1, 1, 0, 1}, {1, 1, 1, 0}, {1, 1, 1, 1}};
int numberArr[] = {0, 1, 2, 3, 4, 5, 6, 7, -8, -7, -6, -5, -4, -3, -2, -1}; // массив поддерживаемых чисел 

struct ConditionTest{

  byte numberIdx; // индекс в массиве поддерживаемых чисел
  byte nBits[4]; // побитовое представление числа, переданного для проверки условий
  int number; // число для проверки условий

  byte operationIdx; // индекс в массиве поддерживаемых операций
  byte oBits[3]; // побитовое представление операции
  
  bool result; // точный результат
  bool computerResult;// результат работы схемы проверки условий
  
  void test(int numOfTests, byte* outNumPins, byte* outOperPins){
    int successTest = 0; // переменная для подсчета пройденных тестов
    int failTest = 0; // переменная для подсчета провальных тестов

     // основной цикл тестирования
    for(int i = 0; i < numOfTests; ++i){
        numberIdx = random(16); // получение случайного индекса
        // получение битов текущего числа
        memcpy(nBits, numberBits[numberIdx], 4 * sizeof(byte));
        number = numberArr[numberIdx]; // запись текущего числа, по полученному индексу
        // подача числа на плату
        for(int i = 0; i < 4 ; ++i){
          digitalWrite(outNumPins[i], nBits[i]);
        }
        printNumBits(); // вывод двоичного представления подаваемого числа

        operationIdx = random(8); // получение случайного индекса поддерживаемых операций
         // получение кода текущей операции
        memcpy(oBits, operationsBits[operationIdx], 3 * sizeof(byte));
         // подача кода операции на схемы проверки условий
        for(int i = 0; i < 3 ; ++i){
          digitalWrite(outOperPins[i], oBits[i]);
        }
        printOperBits(); // вывод кода текущей операции
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
        printResults(); // вывод точного результата, и результата полученного от схемы проверки условий
        // проверка правильности результата
        if(result == computerResult){
          successTest++;
        }else{
          failTest++;
        }
    }
     // вывод количества верных тестов
    Serial.print("SUCCESS Test: ");
    Serial.print(successTest);
    Serial.print("/ ");
    Serial.println(numOfTests);
  }

   // функция вывода результатов
  void printResults(){
    bitWrite(computerResult, 0, digitalRead(inPin[0]));
    Serial.print("computerResult: ");
    Serial.println(computerResult);
    Serial.print("Result: ");
    Serial.println(result);
  }
  // функций вывода кода подаваемого числа
  void printNumBits(){
    Serial.println();
    Serial.print("number: ");
    Serial.println(numberArr[numberIdx]);
    Serial.print("numberBits: ");
    for(int i = 0; i < 4 ; ++i){
      Serial.print(bitRead(number, 3 - i));
    }
    }
  // вывод кода операции
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
  // установка выходных пинов для подачи числа в режим OUTPUT
  for(int i = 0; i < numOutNumPins; ++i){ 
    pinMode(outNumPins[i], OUTPUT);
  }
// установка выходных пинов для подачи управляющих сигналов в режим OUTPUT
  for(int i = 0; i < numOutOperPins; ++i){
    pinMode(outOperPins[i], OUTPUT);
  }
  // установка входного пина в режим INPUT
for(int i = 0; i < numInNumPins; ++i){
    pinMode(inPin[i], INPUT);
  }
  // запуск тестов
  cTest.test(200, outNumPins, outOperPins);
}
