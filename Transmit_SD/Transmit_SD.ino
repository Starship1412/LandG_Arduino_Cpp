uint64_t counter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Try to transmit numbers.");
  counter = 0;
}

void loop() {
  uint64_t part1 = (counter / 1000000000000ULL) % 10000;
  uint64_t part2 = (counter / 100000000ULL) % 10000;
  uint64_t part3 = (counter / 10000ULL) % 10000;
  uint64_t part4 = counter % 10000ULL;

  printPaddedNumber((unsigned long)part1);
  Serial.print(" ");
  printPaddedNumber((unsigned long)part2);
  Serial.print(" ");
  printPaddedNumber((unsigned long)part3);
  Serial.print(" ");
  printPaddedNumber((unsigned long)part4);
  Serial.println();

  counter++;
  delay(20); // 50Hz
}

void printPaddedNumber(unsigned long number) {
  if (number < 10) {
    Serial.print("000");
  } else if (number < 100) {
    Serial.print("00");
  } else if (number < 1000) {
    Serial.print("0");
  }
  Serial.print(number);
}