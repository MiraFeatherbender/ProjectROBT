#include "Initialization.h"

/*
Select fast food - Hot dog, Pizza, Hamburger, Cheeseburger 
Then select how many pieces 1 to 10
At the end select if you want fast delivery for extra 2$
*/
String options[] = { "Select fast food", "How many (1...10)", "Do you want fast delicery for 2$?" };

String foods[] = { "Hot dog", "Pizza", "Hamburger", "Cheeseburger" };
//String foods[] = {"   1", "   2", "   3", "   4"};
String selectedFood = "";

String delivery[] = { "Normal", "Fast for extra 2$" };
String selectedDelivery = "";

int selectedQuantity = 1;

int currentOption = 0;

void setForOption(int newOption) {
  currentOption = newOption;

  switch (newOption) {
    case 0:
      rotaryEncoder.setBoundaries(0, 3, true);  //food type 0..3
      rotaryEncoder.setEncoderValue(0);
      break;
    case 1:
      rotaryEncoder.setBoundaries(1, 10, false);  //how many pieces 1 to 10; do not go from 10 to 1
      rotaryEncoder.setEncoderValue(1);
      break;
    case 2:
      rotaryEncoder.setBoundaries(0, 1, false);  //select delivery
      rotaryEncoder.setEncoderValue(0);
      break;

    default:
      break;
  }

  Serial.println(options[currentOption]);
  showSelection();
}

void rotary_onButtonClick() {
  static unsigned long lastTimePressed = 0;
  if (millis() - lastTimePressed < 200)
    return;
  lastTimePressed = millis();

  int selecedValue = rotaryEncoder.readEncoder();

  switch (currentOption) {
    case 0:  //"Select fast food"
      selectedFood = foods[selecedValue];
      setForOption(1);
      break;
    case 1:  //"Select quantity"
      selectedQuantity = selecedValue;
      setForOption(2);
      break;
    case 2:  //"Select delivery"
      selectedDelivery = delivery[selecedValue];
      showOrder();
      setForOption(0);
      break;

    default:
      break;
  }
}

void showOrder() {
  Serial.println("++++++++++++++ ORDER DETAILS ++++++++++++++");
  Serial.print("You ordered ");
  Serial.println(selectedFood);
  Serial.print("Quantity: ");
  Serial.println(selectedQuantity);
  Serial.print("Delivery: ");
  Serial.println(selectedDelivery);
  Serial.println("-------------------------------------------");
  Serial.println("");

  Serial.print("NEW ORDER ");
}

void IRAM_ATTR readEncoderISR() {
  rotaryEncoder.readEncoder_ISR();
}

void setup() {
  // // Initialize TFT
  initializeHardware();

  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  rotaryEncoder.setAcceleration(0);

  rotaryEncoder.correctionOffset = 2;  //try with zero or ROTARY_ENCODER_STEPS/2
  rotaryEncoder.isButtonPulldown = false;
  rotaryEncoder.areEncoderPinsPulldownforEsp32 = true;

  // setForOption(0);
}

void showSelection() {
  int selecedValue = rotaryEncoder.readEncoder();

  switch (currentOption) {
    case 0:  //"Select fast food"
      Serial.println(foods[selecedValue]);
      break;
    case 1:  //"Select quantity"
      Serial.print("Quantity: ");
      Serial.println(selecedValue);
      break;
    case 2:  //"Select delivery"
      Serial.println(delivery[selecedValue]);
      break;
    default:
      break;
  }
}


unsigned long lastStateChange = 0;  // Tracks the last time a state changed.
int currentSensor = 0;              // Tracks the current sensor index.
const int stateDuration = 60;     // Duration for sending and receiving states.
bool isInitialized = false;         // Tracks if the sequence has started.
int nextSensor = currentSensor + 1;

void loop() {
  if (rotaryEncoder.encoderChanged()) {
    // showSelection();
  }
  if (rotaryEncoder.isEncoderButtonClicked()) {
    // rotary_onButtonClick();
  }
  while (Serial.available() > 0) {
    String inputLine = Serial.readStringUntil('\n');
    inputLine.trim();
    Serial.println(inputLine);
  }

  unsigned long currentTime = millis();

  // Kick-off logic to start the first sensor if uninitialized.
  if (!isInitialized) {
    robotWindow.setSensorStatus(currentSensor, robotWindow::SENDING);  // Start sequence.
    isInitialized = true;                                                // Mark as initialized.
    lastStateChange = currentTime;                                       // Initialize timer.
  }

  // Check if it's time to change state.
  if (currentTime - lastStateChange >= stateDuration) {
    lastStateChange = currentTime;

    switch (auto sensorStatus = robotWindow.getSensorStatus(currentSensor)) {
      case robotWindow::SENDING:
        robotWindow.setSensorStatus(currentSensor, robotWindow::RECEIVING);

        // Trigger the next sensor to start sending.
        nextSensor = (currentSensor + 1) % robotWindow.sensors.size();
        robotWindow.setSensorStatus(nextSensor, robotWindow::SENDING);
        break;

      case robotWindow::RECEIVING:
        robotWindow.setSensorStatus(currentSensor, robotWindow::INACTIVE);

        // Advance the currentSensor to the next one.
        currentSensor = (currentSensor + 1) % robotWindow.sensors.size();
        break;

      case robotWindow::INACTIVE:
        // No action needed if sensor is inactive.
        break;

      default:
        // Handle unexpected states if necessary.
        break;
    }
  }

  Serial.draw();
  robotWindow.draw();
}