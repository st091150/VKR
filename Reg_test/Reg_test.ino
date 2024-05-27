const byte numOutPins = 4; // количество выходных пинов
const byte numInPins = 4; // количество входных пинов

byte outPins[numOutPins] = {2, 3, 4, 5}; // выходные пины
byte inSyncPin = 6; // пин синхронизации на запись
byte outSyncPin = 7; // пин на синхронизацию на чтение
byte inPins[numInPins] = {A5, A4, A3, A2}; // входные пины

// структура для тестирования
struct regTest{ 
  byte A; // число для тестирования
  byte preRes = 0; // результат регистра в момент последней записи
  byte result = 0; // текущий результат регистра
  bool sync; // переменная синхронизации

//функция тестирования
  void test(int numOfTests, byte* outPins, byte inSyncPin, byte outSyncPin, byte* inPins){
   
    int successTest = 0; // количество успешно пройденных тестов
    int failTest = 0; // количество провальных тестов
    bool inSync = 1; // переменная синхронизации на запись
    bool outSync = 1; // переменная синхронизации на чтение

     // записываем текущее состояние регистра
    for(byte i = 0; i < numInPins; ++i){
      bitWrite(preRes, i, digitalRead(inPins[i]));
    }
     // цикл тестирования
    for (int i = 0; i < numOfTests; i++){

      A = random(15); // задаем случайное число
      // случайно выбираем значение синхронизации на запись
      inSync = random(2); 
      // случайно выбираем значение синхронизации на чтение
      outSync = random(2);
      // если включена синхронизация на запись, то предыдущие значение равно текущему
      if(inSync){
        preRes = A;
      }
      // подача сигнала синхронизации на запись
      digitalWrite(inSyncPin, inSync); 
      // подача сигнала синхронизации на чтение
      digitalWrite(outSyncPin, outSync);

      // подача числа А
      for(int i = 0; i < numOutPins ; ++i){
        digitalWrite(outPins[i], bitRead(A, i));
      }
      // вывод выходных сигналов с платы, и их запись в переменную result
      Serial.print("result: ");
      for(byte i = 0; i < numInPins; ++i){
        bitWrite(result, i, digitalRead(inPins[i]));
        Serial.print(digitalRead(inPins[numInPins - i - 1]));
      }
       // побитовый вывод числа A
      Serial.println();
      Serial.print("A: ");
      for(byte i = 0; i < numInPins; ++i){
        Serial.print(bitRead(A[numInPins - i - 1]));
       }
       
      Serial.print("inSync : ");
      Serial.println(inSync);
       // вывод сигнала синхронизации на чтение
      Serial.print("OutSync : ");
      Serial.println(outSync);
       // вывод полуученного результата
      Serial.print("result : ");
      Serial.println(result);
      // вывод последнего результата, при последней синхронизации на запись
      Serial.print("preRes : ");
      Serial.println(preRes);
      // вывод текущего теста
      Serial.print("TEST :");
      Serial.print(i + 1);
      Serial.print(" / ");
      Serial.println(numOfTests);
       // проверка корректности результатов
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
     // вывод результатов тестирования
     Serial.print("successTest : ");
     Serial.print(successTest);
     Serial.print("/ ");
     Serial.println(numOfTests);
  }
};

void setup() {
  Serial.begin(9600);
  // установка выходных пинов в режим OUTPUT
  for(int i = 0; i < numOutPins; ++i){
    pinMode(outPins[i], OUTPUT);
  }
  // установка входных пинов в режим INPUT
  for(int i = 0; i < numInPins; ++i){
    pinMode(inPins[i], INPUT);
  }
  // установка выходного пина для сигнала синхронизации на запись в режим OUTPUT
  pinMode(6, OUTPUT); 
  // установка выходного пина для сигнала синхронизации на чтение в режим OUTPUT
  pinMode(7, OUTPUT);
  regTest test_1;
  // запуск программы тестирования
  test_1.test(150, outPins, inSyncPin, outSyncPin, inPins);
}
