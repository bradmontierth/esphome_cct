#include "triple_white_light.h"

namespace esphome {
namespace triple_white_light {

void TripleWhiteLight::setup() {
  // Initialization code here (if necessary)
}

float TripleWhiteLight::calculate_amber_value(float color_temp) {
  if (color_temp <= 2000) return 1.0;
  else if (color_temp <= 2700) return 1.0 - (color_temp - 2000) / 700;
  else return 0.0;
}

float TripleWhiteLight::calculate_warm_value(float color_temp) {
  if (color_temp <= 2000) return 0.0;
  else if (color_temp <= 2700) return (color_temp - 2000) / 700;
  else if (color_temp <= 4600) return 1.0 - (color_temp - 2700) / 1900;
  else if (color_temp <= 6500) return 0.5 - 0.5 * (color_temp - 4600) / 1900;
  else return 0.0;
}

float TripleWhiteLight::calculate_cool_value(float color_temp) {
  if (color_temp <= 2700) return 0.0;
  else if (color_temp <= 4600) return (color_temp - 2700) / 1900;
  else if (color_temp <= 6500) return 0.5 + 0.5 * (color_temp - 4600) / 1900;
  else return 1.0;
}

}  // namespace triple_white_light
}  // namespace esphome