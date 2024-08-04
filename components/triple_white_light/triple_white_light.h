#pragma once

#include "esphome.h"

namespace esphome {
namespace triple_white_light {

class TripleWhiteLight : public Component, public light::LightOutput {
 public:
  TripleWhiteLight() = default;

  void set_amber_output(output::FloatOutput *amber_output) { amber_output_ = amber_output; }
  void set_warm_white_output(output::FloatOutput *warm_white_output) { warm_white_output_ = warm_white_output; }
  void set_cool_white_output(output::FloatOutput *cool_white_output) { cool_white_output_ = cool_white_output; }

  light::LightTraits get_traits() override;
  void write_state(light::LightState *state) override;

 protected:
  output::FloatOutput *amber_output_{nullptr};
  output::FloatOutput *warm_white_output_{nullptr};
  output::FloatOutput *cool_white_output_{nullptr};

  float calculate_amber_value(float color_temp);
  float calculate_warm_value(float color_temp);
  float calculate_cool_value(float color_temp);
};

}  // namespace triple_white_light
}  // namespace esphome