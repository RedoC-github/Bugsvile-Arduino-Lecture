#define LEDCOUNT 3
int ledpin[] = {7, 8, 4};

void setup() {
    for (int i = 0; i < LEDCOUNT; i++)
        pinMode(ledpin[i], OUTPUT);
}

void loop() {
    for (int i = 0; i < LEDCOUNT; i++)
        digitalWrite(ledpin[i], HIGH);
    delay(1000);
    for (int i = 0; i < LEDCOUNT; i++)
        digitalWrite(ledpin[i], LOW);
    delay(1000);
}

