const int analogPins[] = {A0, A1, A2, A3, A4, A5};

const int notes = 6;
boolean notePlaying[notes];
int scale[] = {69, 67, 65, 64, 62, 60}; // 6 notes in C major scale
int threshold = 550;

void setup() {
  Serial.begin(31250);
}

void loop() {
  for (int i=0;i<6;i++) {
    int value = analogRead(analogPins[i]);
    if (value < threshold && notePlaying[i] == false) { // if laser is blocked and note not already played
      noteOn(0x90, scale[i], 0x45); // play note
      notePlaying[i] = true;
    } else if (value >= threshold) {
      noteOn(0x80, scale[i], 0x00); // stop playing note
      notePlaying[i] = false;
    }
  }

  delay(5);
}

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
