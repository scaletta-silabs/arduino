/*
   Matter multiple lightbulb example

   The example shows how to create multiple on/off lightbulb instances with the Arduino Matter API.

   The example lets users control the onboard LEDs through Matter.
   The device has to be commissioned to a Matter hub first.

   Compatible boards:
   - SparkFun Thing Plus MGM240P
   - xG24 Explorer Kit

   Author: Tamas Jozsi (Silicon Labs)
 */
#include <Matter.h>
#include <MatterLightbulb.h>

// If the board doesn't have a second onboard LED - define a pin on which a second LED can be connected
#ifndef LED_BUILTIN_1
#define LED_BUILTIN_1 PA0
#endif

MatterLightbulb matter_bulb_0;
MatterLightbulb matter_bulb_1;

void handle_bulb_0();
void handle_bulb_1();

void setup()
{
  Serial.begin(115200);
  Matter.begin();
  matter_bulb_0.begin();
  matter_bulb_1.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(LED_BUILTIN_1, OUTPUT);
  digitalWrite(LED_BUILTIN_1, LOW);

  Serial.println("Matter multiple lightbulbs");

  if (!Matter.isDeviceCommissioned()) {
    Serial.println("Matter device is not commissioned");
    Serial.println("Commission it to your Matter hub with the manual pairing code or QR code");
    Serial.printf("Manual pairing code: %s\n", Matter.getManualPairingCode().c_str());
    Serial.printf("QR code URL: %s\n", Matter.getOnboardingQRCodeUrl().c_str());
  }
  while (!Matter.isDeviceCommissioned()) {
    delay(200);
  }

  if (!Matter.isDeviceConnected()) {
    Serial.println("Waiting for network connection...");
  }
  while (!Matter.isDeviceConnected()) {
    delay(200);
  }
  Serial.println("Device connected");
}

void loop()
{
  handle_bulb_0();
  handle_bulb_1();
}

void handle_bulb_0()
{
  static bool matter_lightbulb_last_state = false;
  bool matter_lightbulb_current_state = matter_bulb_0.get_onoff();

  // If the current state is ON and the previous was OFF - turn on the LED
  if (matter_lightbulb_current_state && !matter_lightbulb_last_state) {
    matter_lightbulb_last_state = matter_lightbulb_current_state;
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("#0 - bulb ON");
  }

  // If the current state is OFF and the previous was ON - turn off the LED
  if (!matter_lightbulb_current_state && matter_lightbulb_last_state) {
    matter_lightbulb_last_state = matter_lightbulb_current_state;
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("#0 - bulb OFF");
  }
}

void handle_bulb_1()
{
  static bool matter_lightbulb_last_state = false;
  bool matter_lightbulb_current_state = matter_bulb_1.get_onoff();

  // If the current state is ON and the previous was OFF - turn on the LED
  if (matter_lightbulb_current_state && !matter_lightbulb_last_state) {
    matter_lightbulb_last_state = matter_lightbulb_current_state;
    digitalWrite(LED_BUILTIN_1, HIGH);
    Serial.println("#1 - bulb ON");
  }

  // If the current state is OFF and the previous was ON - turn off the LED
  if (!matter_lightbulb_current_state && matter_lightbulb_last_state) {
    matter_lightbulb_last_state = matter_lightbulb_current_state;
    digitalWrite(LED_BUILTIN_1, LOW);
    Serial.println("#1 - bulb OFF");
  }
}
