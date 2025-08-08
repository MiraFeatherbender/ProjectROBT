#include <stdint.h>
#include <esp32-hal-adc.h>  // Required for continuous mode
#ifndef DRIVE_CONFIG_H
#define DRIVE_CONFIG_H

// Main loop state machine enum
enum BootState {
  WAITING_FOR_ADC,       // ADC not yet returned a valid sample
  BOOT_ANGLE_CAPTURED,   // Angle has been inferred and injected into servo
  RUNNING                // Normal operation mode
};

// ADC continuous mode configuration parameters
struct ADCConfig {
    // Pin list for conversion targets
    uint8_t pins[1] = {1};            // GPIO1 reads servo potentiometer
    size_t pin_count = sizeof(pins);  // Auto-sized

    // Conversion settings
    uint16_t conversions_per_pin = 1000;
    uint32_t sampling_frequency = 1000;

    uint8_t width_bits = 12;
    adc_attenuation_t attenuation = ADC_2_5db;

    // Runtime state (can be relocated if needed)
    volatile bool conversion_done = false;
    adc_continuous_data_t* result = nullptr;
};

// Pin modes for use in switch:case statement of setup
enum PinModeType {
    PINMODE_INPUT,
    PINMODE_INPUT_PULLUP,
    PINMODE_OUTPUT_HIGH,
    PINMODE_OUTPUT_LOW
};

// General pin initialization struct
struct PinInitConfig {
    const char* label;        // Human-readable function name
    uint8_t pin;              // GPIO number
    PinModeType mode;         // Desired mode / initial level
};

constexpr uint8_t PIN_HALL_NORTH = 5;
constexpr uint8_t PIN_HALL_SOUTH = 6;
constexpr uint8_t HALL_LED = 7;
constexpr uint8_t PIN_ADDR_1 = 10;
constexpr uint8_t PIN_ADDR_2 = 20;
constexpr uint8_t PIN_ADDR_3 = 21;

// Pin assignment and initialization lookup table
static const PinInitConfig leg_pin_init_table[] = {
    {"Stepper_DIR",                2, PINMODE_OUTPUT_LOW},    
    {"Stepper_STEP",               3, PINMODE_OUTPUT_LOW},
    {"Hall_Module_PWR",            4, PINMODE_OUTPUT_HIGH},
    {"Hall_North",    PIN_HALL_NORTH, PINMODE_INPUT_PULLUP},
    {"Hall_South",    PIN_HALL_SOUTH, PINMODE_INPUT_PULLUP},
    {"Hall_Module_LED",     HALL_LED, PINMODE_OUTPUT_HIGH},
    {"Address 1",         PIN_ADDR_1, PINMODE_INPUT_PULLUP}, 
    {"Address 2",         PIN_ADDR_2, PINMODE_INPUT_PULLUP}, //(Left/Right)
    {"Address 3",         PIN_ADDR_3, PINMODE_INPUT_PULLUP} //(Forward/Center/Rear)
};

// Shared LEDC config — used by both servos and steppers
struct LEDCConfig {
    int pin = -1;
    int channel = -1;
    int timer = -1;
    uint32_t frequency = 0;
    uint8_t resolution_bits = 0;
};

// Servo-specific configuration
struct ServoConfig {
    LEDCConfig ledc {
        .pin = 0,
        .channel = 0,
        .timer = 0,
        .frequency = 50,
        .resolution_bits = 14
    };

    uint16_t pulse_min_us = 500;
    uint16_t pulse_max_us = 2500;

    float angle_min_deg = 0.0f;
    float angle_max_deg = 270.0f;

    float motion_window_min = 45.0f;
    float motion_window_max = 225.0f;

    float magnet_spacing_deg = 30.0f;
    static constexpr int kTotalMagnets = 7;  

    float max_deg_per_sec = 90.0f;
};

// Stepper-specific configuration
struct StepperConfig {
    LEDCConfig ledc {
        .pin = 2, // See leg_pin_init_table: "Stepper_STEP"
        .channel = 1,
        .timer = 1,
        .frequency = 0,
        .resolution_bits = 8
    };

    uint32_t freq_min = 0;
    uint32_t freq_max = 36000;

    uint16_t microsteps_per_rev = 1600;
    float gear_ratio = 4.0f;               // 20T to 80T
    float wheel_diameter_mm = 130.0f;

    float max_velocity_mps = 2.3f;
};

#endif //DRIVE_CONFIG_H