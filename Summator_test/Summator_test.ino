const byte numOutPins = 8; // количество выходных пинов
const byte numInPins = 5; // количество входных пинов

byte outPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // массив выходных пинов
byte AoutPins[] = {2, 4, 6, 8}; // массив выходных пинов для 1 операнда
byte BoutPins[] = {3, 5, 7, 9}; // массив выходных пинов для 2 операнда
byte inPins[] = {10, 11, 12 , 13, A0}; // массив входных пинов


struct SUM{
  byte A; // 1 операнд
  byte B; // 2 операнд

  byte ComputerResult; // Результат работы стенда

  void compute(byte* outPins){ // функция подсчета суммы на стенде
    for(int i = 0; i < numOutPins/2 ; ++i){
      digitalWrite(AoutPins[i], bitRead(A, i)); // подача 1 операнда на плату
    }
    for(int i = 0; i < numOutPins/2 ; ++i){
      digitalWrite(BoutPins[i], bitRead(B, i)); // подача 2 операнда на плату
    }

// считывание выходных сигналов с платы
    for(int i = 0; i < numInPins; ++i){
      bitWrite(ComputerResult, i, digitalRead(inPins[i])); 
    }
    Serial.println();
    Serial.print("ComputerResult : ");
    Serial.println(ComputerResult); // вывод результата платы

  }
  void printBitsA(){ // Функция вывода 1 операнда
    Serial.print("A: ");
    for(int i = 0; i < numOutPins/2; ++i){
      Serial.print(bitRead(A, numOutPins/2 - 1 - i));
    }
    Serial.println();
  }
  void printBitsB(){ // Функция вывода 2 операнда
    Serial.print("B: ");
    for(int i = 0; i < numOutPins/2; ++i){
      Serial.print(bitRead(B, numOutPins/2 - 1 - i));
    }
    Serial.println();
  }
};
  SUM test; 
  byte result = 0;
  int testNum = 0;
  int successTest = 0;
  int failTest = 0;

  
void setup() {

  for(int i = 0; i < numOutPins; ++i){ // установка выходных пинов в режим OUTPUT
    pinMode(outPins[i], OUTPUT);
  }
  for(int i = 0; i < numInPins; ++i){ // установка входных пинов в режим INPUT
    pinMode(inPins[i], INPUT);
  }
  Serial.begin(9600);

  for(int i = 0 ; i < 1000; ++i){ // цикл на 1000 операций ADD 
   
// задание 1 операнда случайным значением в диапозоне [0,16)
    test.A = random(16);  
// задание 1 операнда случайным значением в диапозоне [0,16)
    test.B = random(16);
    test.printBitsA(); // побитовый вывод 1 операнда
    test.printBitsB(); // побитовый вывод 2 операнда
    test.compute(outPins); // вычисление суммы A + B на плате
    result = test.A + test.B; // подсчет точного результата
    for(int i = 0 ; i < numInPins; ++i){
      Serial.print(bitRead(result, i)); // побитовый вывод точного результата
    }
    Serial.println();

// получение побитового вывода схемы 4-битного сумматора
    for(int i = 0; i < numInPins; ++i){
      Serial.print(digitalRead(inPins[i])); 
    }
    Serial.println();

// сравнение полученного результата и точного
    if(test.ComputerResult == result){ 
      Serial.print("Success test: ");
      Serial.println(testNum);
      successTest++;
    }else{
      Serial.print("Fail test: ");
      Serial.println(testNum);
      failTest++;
    }
    testNum++;

  }
// Вывод результатов тестирования
  Serial.print("Success: ");
  Serial.println(successTest);
  Serial.print("Fail: ");
  Serial.println(failTest);
}
