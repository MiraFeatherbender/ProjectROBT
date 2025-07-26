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

void printAngle(uint16_t mv) {
  float angle = -(mv / 3.0) + 302.0;
  Serial.printf("%.1f\n",angle);  // Tab-separated for plotter
}

void initADC(ADCConfig& cfg, void (*callback)()) {
    analogContinuousSetWidth(cfg.width_bits);
    analogContinuousSetAtten(cfg.attenuation);
    analogContinuous(cfg.pins, cfg.pin_count, cfg.conversions_per_pin, cfg.sampling_frequency, callback);
    analogContinuousStart();
}

void setup() {
  Serial.begin(115200);
  if (!supervisor.begin()) {
    Serial.println("Failed to attach LEDC");
    while (true);
  }

for (const auto& cfg : leg_pin_init_table) {
    switch (cfg.mode) {
        case PINMODE_INPUT:          pinMode(cfg.pin, INPUT); break;
        case PINMODE_INPUT_PULLUP:   pinMode(cfg.pin, INPUT_PULLUP); break;
        case PINMODE_OUTPUT_HIGH:    pinMode(cfg.pin, OUTPUT); digitalWrite(cfg.pin, HIGH); break;
        case PINMODE_OUTPUT_LOW:     pinMode(cfg.pin, OUTPUT); digitalWrite(cfg.pin, LOW); break;
    }
}


initADC(adc_cfg, &adcComplete);
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
      analogContinuousStart();
      supervisor.setRawSteeringAngle(135.0f);
      boot_state = RUNNING;
      break;

    case RUNNING:

      break;
  }

  delay(10);  // Smooth Serial Plotter
}