// Flickering Flame for Hobbit Gingerbread House

int ledOut = 3;

void setup()
{
pinMode(ledOut, OUTPUT);
}

void loop() {
analogWrite(ledOut, random(200)+55);
delay(random(150));
}

