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
const int maxSpeed = 255 * 3 / 4;
double durations[] = {0, 0, 0};
double directions[] = {0, 0, 0};
int censors[3][2] = {
    {2, 3},   // l
    {A0, A1}, // c
    {A2, A3}  // r
};

void setup() {
    for (int i = 0; i < 2; i++) {
        pinMode(moters[i].speed, OUTPUT);
        pinMode(moters[i].d_1, OUTPUT);
        pinMode(moters[i].d_2, OUTPUT);
    }
    for (int i = 0; i < 3; i++) {
        pinMode(censors[i][0], OUTPUT);
        pinMode(censors[i][1], INPUT);
    }
    Serial.begin(9600);
}

void Forward(int speed) {
    analogWrite(moter_l.speed, speed);
    analogWrite(moter_r.speed, speed);

    for (int i = 0; i < 2; i++) 
        digitalWrite(moters[i].d_1, HIGH);

    for (int i = 0; i < 2; i++) 
        digitalWrite(moters[i].d_2, LOW);
}

void Backward(int speed) {
    analogWrite(moter_l.speed, speed);
    analogWrite(moter_r.speed, speed);

    for (int i = 0; i < 2; i++) 
        digitalWrite(moters[i].d_1, LOW);

    for (int i = 0; i < 2; i++) 
        digitalWrite(moters[i].d_2, HIGH);
}

void Right(int speed) {
    analogWrite(moter_l.speed, speed);
    analogWrite(moter_r.speed, speed);

    digitalWrite(moter_l.d_1, HIGH);
    digitalWrite(moter_l.d_2, LOW);
    digitalWrite(moter_r.d_1, LOW);
    digitalWrite(moter_r.d_2, HIGH);
}

void Left(int speed) {
    analogWrite(moter_l.speed, speed);
    analogWrite(moter_r.speed, speed);

    digitalWrite(moter_l.d_1, LOW);
    digitalWrite(moter_l.d_2, HIGH);
    digitalWrite(moter_r.d_1, HIGH);
    digitalWrite(moter_r.d_2, LOW);
}

void Update() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(censors[i][0], LOW);
        digitalWrite(censors[i][1], LOW);
        delayMicroseconds(2);
        digitalWrite(censors[i][0], HIGH);
        delayMicroseconds(10);
        digitalWrite(censors[i][0], HIGH);
        durations[i] = pulseIn(censors[i][1], HIGH);
        directions[i] = (double)(340*durations[i]/10000)/2;
    }
}

void Print(int value) {
    for (int i = 0; i < (value % 101); i++)
        Serial.print("@");
    Serial.println();
}

void loop() {
    Update();
    bool left_ = directions[0] < 20;
    bool center_ = directions[1] < 20;
    bool right_ = directions[2] < 20;

    if (left_) {
        if (center_) {
            if (right_) {
                Backward(maxSpeed/4*3);
                Serial.println("BACK");
            } else {
                Right(maxSpeed/4*3);
                Serial.println("RIGHT");
            }
        } else {
            Forward(maxSpeed/4*3);
            Serial.println("FORWARD");
        }
    } else {
        if (center_) {
            if (right_) {
                Left(maxSpeed/4*3);
                Serial.println("LEFT");
            }
            else {
                Right(maxSpeed/4*3);  
                Serial.println("RIGHT");
            } 
        } else {
            Forward(maxSpeed/4*3);
            Serial.println("FORWARD");
        }
    }
    delay(100);
}

