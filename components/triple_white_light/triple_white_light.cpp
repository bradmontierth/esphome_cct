#include "triple_white_light.h"

namespace esphome {
namespace triple_white_light {

class TripleWhiteLight : public Component, public light::LightOutput {
 public:
  void setup() override {
    // Initialization code here (if necessary)
  }

  light::LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supports_brightness(true);
    traits.set_supports_rgb(false);
    traits.set_supports_rgb_white_value(false);
    traits.set_supports_color_temperature(true);
    return traits;
  }

  void write_state(light::LightState *state) override {
    float brightness, color_temp;
    state->current_values_as_brightness(&brightness);
    state->current_values_as_color_temperature(&color_temp);

    // Calculate the levels for each color temperature
    float amber = calculate_amber_value(color_temp);
    float warm_white = calculate_warm_value(color_temp);
    float cool_white = calculate_cool_value(color_temp);

    // Output to the appropriate channels
    id(amber_output).set_level(amber * brightness);
    id(warm_white_output).set_level(warm_white * brightness);
    id(cool_white_output).set_level(cool_white * brightness);
  }

 private:
  float calculate_amber_value(float color_temp) {
    if (color_temp <= 2000) return 1.0;
    else if (color_temp <= 2700) return 1.0 - (color_temp - 2000) / 700;
    else return 0.0;
  }

  float calculate_warm_value(float color_temp) {
    if (color_temp <= 2000) return 0.0;
    else if (color_temp <= 2700) return (color_temp - 2000) / 700;
    else if (color_temp <= 4600) return 1.0 - (color_temp - 2700) / 1900;
    else if (color_temp <= 6500) return 0.5 - 0.5 * (color_temp - 4600) / 1900;
    else return 0.0;
  }

  float calculate_cool_value(float color_temp) {
    if (color_temp <= 2700) return 0.0;
    else if (color_temp <= 4600) return (color_temp - 2700) / 1900;
    else if (color_temp <= 6500) return 0.5 + 0.5 * (color_temp - 4600) / 1900;
    else return 1.0;
  }
};
}
}
