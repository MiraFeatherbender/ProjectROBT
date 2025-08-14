#include <Arduino.h>

#define STEP_PIN 18

hw_timer_t *timerA = NULL; // PPS timer
hw_timer_t *timerB = NULL; // Pulse width timer

volatile bool stepActive = false;

// Timer B ISR: Set STEP LOW, stop timer B
void IRAM_ATTR onTimerB() {
  digitalWrite(STEP_PIN, LOW);
  timerAlarmDisable(timerB); // Stop timer B until next trigger
  stepActive = false;
}

// Timer A ISR: Set STEP HIGH, start timer B for pulse width
void IRAM_ATTR onTimerA() {
  if (!stepActive) {
    digitalWrite(STEP_PIN, HIGH);
    stepActive = true;
    timerAlarmWrite(timerB, 3, true); // 3us pulse width
    timerAlarmEnable(timerB);         // Start timer B
  }
}

void setup() {
  pinMode(STEP_PIN, OUTPUT);

  // Timer A: PPS interval (e.g., 150us for ~6,667 PPS)
  timerA = timerBegin(1000000); // 1MHz: 1us ticks
  timerAttachInterrupt(timerA, &onTimerA);
  timerAlarm(timerA, 150, true, 0); // 150us interval, repeat, unlimited

  // Timer B: Pulse width (3us, started by Timer A ISR)
  timerB = timerBegin(1000000); // 1MHz: 1us ticks
  timerAttachInterrupt(timerB, &onTimerB);
  // Do NOT enable timerB here; it is started by timerA ISR
}

void loop() {
  // ...existing code...
}
