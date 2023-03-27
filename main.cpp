// This code is designed for use with a XKC-Y25-V sensor, or more accurately, 5 of them placed on the outside of the balck water tank at 20% intervals.  
// If you connect only to the Power/ground/data wire (leave the 4th wire disconnected), then the sensors will read 0 until the water level covers them, then they will read 1.
// The "tanks.blackwater.1.currentlevel" field will give you the current level based on the combination of sensors.  The others are available for Diagnostics at the moment

#include "sensesp/sensors/analog_input.h"
#include "sensesp/sensors/digital_input.h"
#include "sensesp/sensors/sensor.h"
#include "sensesp/signalk/signalk_output.h"
#include "sensesp/system/lambda_consumer.h"
#include "sensesp_app_builder.h"

using namespace sensesp;

reactesp::ReactESP app;

//// Start Black water tank specific code ////
float blackwaterlevel = 0;
bool black5_state = false;
bool black4_state = false;
bool black3_state = false;
bool black2_state = false;
bool black1_state = false;
float blackwaterlevel_callback() { return (blackwaterlevel);}

void blackwater_calc() {

if (black5_state == 1) {
  blackwaterlevel = 1;
} else if (black4_state == 1) {
  blackwaterlevel = 0.8;
} else if (black3_state == 1) {
  blackwaterlevel = 0.6;
} else if (black2_state == 1) {
  blackwaterlevel = 0.4;
} else if (black1_state == 1) {
  blackwaterlevel = 0.2;
} else {
  blackwaterlevel = 0.0;
}
}
/////End of Blackwater tank specific code/////

// The setup function performs one-time application initialization.
void setup() {
#ifndef SERIAL_DEBUG_DISABLED
  SetupSerialDebug(115200);
#endif

  // Construct the global SensESPApp() object
  SensESPAppBuilder builder;
  sensesp_app = (&builder)
                    // Set a custom hostname for the app.
                    ->set_hostname("my-sensesp-project")
                    // Optionally, hard-code the WiFi and Signal K server
                    // settings. This is normally not needed.
                    //->set_wifi("My WiFi SSID", "my_wifi_password")
                    //->set_sk_server("192.168.10.3", 80)
                    ->get_app();

//// Start Black water tank specific code ////

auto* black5_input_state = new DigitalInputState(2, INPUT_PULLUP, 1000); //Digital 9
black5_input_state->connect_to(
      new LambdaConsumer<bool>([](bool state5) {
        black5_state = state5;
      }));

auto* black4_input_state = new DigitalInputState(13, INPUT_PULLUP, 1000); //Digital 7
black4_input_state->connect_to(
      new LambdaConsumer<bool>([](bool state4) {
        black4_state = state4;
      }));

auto* black3_input_state = new DigitalInputState(14, INPUT_PULLUP, 1000); //Digital 6
black3_input_state->connect_to(
      new LambdaConsumer<bool>([](float state3) {
        black3_state = state3;
        blackwater_calc();
      })); 

auto* black2_input_state = new DigitalInputState(0, INPUT_PULLUP, 1000); //Digital 5
black2_input_state->connect_to(
      new LambdaConsumer<bool>([](float state2) {
        black2_state = state2;
      })); 

auto* black1_input_state = new DigitalInputState(26, INPUT_PULLUP, 1000); //Digital 3
black1_input_state->connect_to(
      new LambdaConsumer<bool>([](float state1) {
        black1_state = state1;
      }));             

  auto* blackwater_level = 
      new RepeatSensor<float>(1000, blackwaterlevel_callback); 


blackwater_level->connect_to(new SKOutputFloat("tanks.blackwater.1.currentLevel"));
black1_input_state->connect_to(new SKOutputFloat("tanks.black_state.1.currentLevel"));
black2_input_state->connect_to(new SKOutputFloat("tanks.black_state.2.currentLevel"));
black3_input_state->connect_to(new SKOutputFloat("tanks.black_state.3.currentLevel"));
black4_input_state->connect_to(new SKOutputFloat("tanks.black_state.4.currentLevel"));
black5_input_state->connect_to(new SKOutputFloat("tanks.black_state.5.currentLevel"));
/////End of Blackwater tank specific code/////

  // Start networking, SK server connections and other SensESP internals
  sensesp_app->start();
}

void loop() { app.tick(); }
