#include "DriveConfig.h"
#include "LegSupervisor.h"

ADCConfig adc_cfg;  // From DriveConfig.h

void ARDUINO_ISR_ATTR adcComplete() {
  adc_cfg.conversion_done = true;
}

BootState boot_state = WAITING_FOR_ADC;
bool adc_ready = false;

ServoConfig ServoCFG;
LegSupervisor supervisor(ServoCFG);

void setup() {
   Serial.begin(115200);

   for (const auto& cfg : leg_pin_init_table) {
      switch (cfg.mode) {
          case PINMODE_INPUT:          pinMode(cfg.pin, INPUT); break;
          case PINMODE_INPUT_PULLUP:   pinMode(cfg.pin, INPUT_PULLUP); break;
          case PINMODE_OUTPUT_HIGH:    pinMode(cfg.pin, OUTPUT); digitalWrite(cfg.pin, HIGH); break;
          case PINMODE_OUTPUT_LOW:     pinMode(cfg.pin, OUTPUT); digitalWrite(cfg.pin, LOW); break;
      }
   }

  if (!supervisor.begin()) {
    Serial.println("Failed to attach LEDC");
    while (true);
  }

  supervisor.initADC(adc_cfg, &adcComplete);
  delay(100); // Delay for servo stability
}

void loop() {
  // Check for new ADC data
  if (adc_cfg.conversion_done) {
    adc_cfg.conversion_done = false;
    adc_ready = analogContinuousRead(&adc_cfg.result, 0);
  }

  switch (boot_state) {
    case WAITING_FOR_ADC:
      if (adc_ready) {
        uint16_t mv = adc_cfg.result[0].avg_read_mvolts;
        supervisor.captureInitialAngle(mv);
        boot_state = BOOT_ANGLE_CAPTURED;
      }
      break;

    case BOOT_ANGLE_CAPTURED:
      analogContinuousStop();
      supervisor.setRawSteeringAngle(135.0f);
      boot_state = RUNNING;
      break;

    case RUNNING:

      break;
  }
}