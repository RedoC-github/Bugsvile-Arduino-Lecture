int checkled = 6;

void setup() {
    pinMode(checkled, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int _inp_cds = analogRead(0);
    int _outp_led = map(_inp_cds, 0, 1023, 0, 255);

    Serial.print("Light Level: ");
    Serial.println(_outp_led);
    analogWrite(checkled, _outp_led);
    delay(100);
}

