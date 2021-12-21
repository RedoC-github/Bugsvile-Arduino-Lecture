typedef struct moter_inf {
    int speed;
    int d_1;
    int d_2;
} Moter;

const Moter moter_l = {
    6, // speed
    5,
    4
};

const Moter moter_r = {
    9,
    8,
    7
};

const Moter moters[] = { moter_l, moter_r };
const int maxSpeed = 255;

void setup() {
    for (int i = 0; i < 2; i++) {
        pinMode(moters[i].speed, OUTPUT);
        pinMode(moters[i].d_1, OUTPUT);
        pinMode(moters[i].d_2, OUTPUT);
    }
}

void forward(int speed) {
    analogWrite(moter_l.speed, speed-random(0, 50));
    analogWrite(moter_r.speed, speed-random(0, 50));

    for (int i = 0; i < 2; i++) 
        digitalWrite(moters[i].d_1, HIGH);

    for (int i = 0; i < 2; i++) 
        digitalWrite(moters[i].d_2, LOW);
}

void backward(int speed) {
    analogWrite(moter_l.speed, speed-random(0, 50));
    analogWrite(moter_r.speed, speed-random(0, 50));

    for (int i = 0; i < 2; i++) 
        digitalWrite(moters[i].d_1, LOW);

    for (int i = 0; i < 2; i++) 
        digitalWrite(moters[i].d_2, HIGH);
}

void right(int speed) {
    analogWrite(moter_l.speed, speed-random(0, 50));
    analogWrite(moter_r.speed, speed-random(0, 50));

    digitalWrite(moter_l.d_1, HIGH);
    digitalWrite(moter_l.d_2, LOW);
    digitalWrite(moter_r.d_1, LOW);
    digitalWrite(moter_r.d_2, HIGH);
}

void left(int speed) {
    analogWrite(moter_l.speed, speed-random(0, 50));
    analogWrite(moter_r.speed, speed-random(0, 50));

    digitalWrite(moter_l.d_1, LOW);
    digitalWrite(moter_l.d_2, HIGH);
    digitalWrite(moter_r.d_1, HIGH);
    digitalWrite(moter_r.d_2, LOW);
}

void loop() {
}

