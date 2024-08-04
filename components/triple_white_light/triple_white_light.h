// file: triple_white_light.h
#pragma once
#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"

namespace esphome {
namespace triple_white_light {
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
} // namespace triple_white_light
} // namespace esphome
