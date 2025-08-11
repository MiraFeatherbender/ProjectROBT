#include "DriveConfig.h"
#include "LegSupervisor.h"
#include "SerialInputHandler.h"
#include "CommandParser.h"
#include "CommandDispatcher.h"
#include "CommandFactory.h"

ADCConfig adc_cfg;  // From DriveConfig.h

void ARDUINO_ISR_ATTR adcComplete() {
  adc_cfg.conversion_done = true;
}

BootState boot_state = WAITING_FOR_ADC;
bool adc_ready = false;

SerialInputHandler serialHandler;
ServoConfig ServoCFG;
LegSupervisor supervisor(ServoCFG);
CommandDispatcher dispatcher;
CommandParser parser; // Set this node's number

void setup() {
  serialHandler.begin();
  // Wire up the pipeline: Serial -> Parser -> Supervisor

  for (const auto& cfg : leg_pin_init_table) {
     switch (cfg.mode) {
        case PINMODE_INPUT:          pinMode(cfg.pin, INPUT); break;
        case PINMODE_INPUT_PULLUP:   pinMode(cfg.pin, INPUT_PULLUP); break;
        case PINMODE_OUTPUT_HIGH:    pinMode(cfg.pin, OUTPUT); digitalWrite(cfg.pin, HIGH); break;
        case PINMODE_OUTPUT_LOW:     pinMode(cfg.pin, OUTPUT); digitalWrite(cfg.pin, LOW); break;
    }
  }

  uint8_t Address = digitalRead(PIN_ADDR_1) << 2 | digitalRead(PIN_ADDR_2) << 1 | digitalRead(PIN_ADDR_3);
  parser.setNodeNumber(Address);

  serialHandler.setLineCallback([&](const String& line, const CommandSourceContext& ctx) {
      parser.parseAndDispatch(line, ctx);
  });
  parser.setDispatchCallback([&](const ParsedCommand& cmd) {
    // Early gate: unknown command
    if (!dispatcher.getCommandInfo(cmd.command.c_str())) {
        cmd.context.respond("+ERR:UNKNOWN_COMMAND");
        return;
    }
    // Gating: command not allowed in current state/priority
    if (!dispatcher.dispatch(cmd, supervisor)) {
        cmd.context.respond("+ERR:COMMAND_NOT_ALLOWED");
        return;
    }
    // If allowed and dispatched, handler will respond as needed
  });

  if (!supervisor.begin()) {
    Serial.println("Failed to attach LEDC");
    while (true);
  }

  supervisor.initADC(adc_cfg, &adcComplete);
  delay(100); // Delay for servo stability
  CommandFactory::registerAll(dispatcher, supervisor);
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
      analogContinuousDeinit();
      {
          CommandSourceContext ctx;
          ctx.source = CommandSourceContext::serial_;
          ctx.respond = [](const String& resp) { Serial.println(resp); };
          parser.parseAndDispatch("AT+HOME", ctx);
          supervisor.update();
      }
      boot_state = RUNNING;
      break;

    case RUNNING:
      serialHandler.update();
      supervisor.update();
      break;
  }
}