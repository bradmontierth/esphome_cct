#pragma once

#include "esphome.h"

class TripleWhiteLight : public Component, public light::LightOutput {
 public:
  TripleWhiteLight(output::FloatOutput *amber_output, output::FloatOutput *warm_white_output, output::FloatOutput *cool_white_output)
    : amber_output_(amber_output), warm_white_output_(warm_white_output), cool_white_output_(cool_white_output) {}

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

    float amber = calculate_amber_value(color_temp);
    float warm_white = calculate_warm_value(color_temp);
    float cool_white = calculate_cool_value(color_temp);

    amber_output_->set_level(amber * brightness);
    warm_white_output_->set_level(warm_white * brightness);
    cool_white_output_->set_level(cool_white * brightness);
  }

 private:
  output::FloatOutput *amber_output_;
  output::FloatOutput *warm_white_output_;
  output::FloatOutput *cool_white_output_;

  float calculate_amber_value(float color_temp);
  float calculate_warm_value(float color_temp);
  float calculate_cool_value(float color_temp);
};