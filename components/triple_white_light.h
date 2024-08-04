// file: triple_white_light.h
#pragma once
#include "esphome.h"

namespace esphome {
  class TripleWhiteLight : public Component, public light::LightOutput {
   public:
    void setup() override;
    light::LightTraits get_traits() override;
    void write_state(light::LightState *state) override;

   private:
    float calculate_amber_value(float color_temp);
    float calculate_warm_value(float color_temp);
    float calculate_cool_value(float color_temp);
  };
}
