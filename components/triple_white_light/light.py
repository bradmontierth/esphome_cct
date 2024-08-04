import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light, output
from esphome.const import CONF_OUTPUT_ID, CONF_NAME

CONF_AMBER = "amber"
CONF_WARM_WHITE = "warm_white"
CONF_COOL_WHITE = "cool_white"

triple_white_ns = cg.esphome_ns.namespace('triple_white_light')
TripleWhiteLight = triple_white_ns.class_('TripleWhiteLight', light.LightOutput, cg.Component)

CONFIG_SCHEMA = light.RGB_LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(TripleWhiteLight),
    cv.Required(CONF_AMBER): cv.use_id(output.FloatOutput),
    cv.Required(CONF_WARM_WHITE): cv.use_id(output.FloatOutput),
    cv.Required(CONF_COOL_WHITE): cv.use_id(output.FloatOutput),
})

def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    yield light.register_light(var, config)
    yield cg.register_component(var, config)

    amber = yield cg.get_variable(config[CONF_AMBER])
    cg.add(var.set_amber(amber))
    warm_white = yield cg.get_variable(config[CONF_WARM_WHITE])
    cg.add(var.set_warm_white(warm_white))
    cool_white = yield cg.get_variable(config[CONF_COOL_WHITE])
    cg.add(var.set_cool_white(cool_white))

    cg.add_define("USE_TRIPLE_WHITE_LIGHT")

    # Add the C++ code for the custom light
    cg.add_global(triple_white_ns.using)
    cg.add_library("Vector", None)
    
    cg.add_global("""
    class TripleWhiteLight : public Component, public LightOutput {
     public:
      void set_amber(output::FloatOutput *amber) { amber_ = amber; }
      void set_warm_white(output::FloatOutput *warm_white) { warm_white_ = warm_white; }
      void set_cool_white(output::FloatOutput *cool_white) { cool_white_ = cool_white; }
      
      LightTraits get_traits() override {
        auto traits = LightTraits();
        traits.set_supports_brightness(true);
        traits.set_supports_rgb(false);
        traits.set_supports_rgb_white_value(false);
        traits.set_supports_color_temperature(true);
        traits.set_min_mireds(153);
        traits.set_max_mireds(500);
        return traits;
      }
      
      void write_state(LightState *state) override {
        float brightness, color_temp;
        state->current_values_as_brightness(&brightness);
        state->current_values_as_color_temperature(&color_temp);
        
        float amber, warm_white, cool_white;
        if (color_temp <= 2000) {
          amber = 1.0f;
          warm_white = 0.0f;
          cool_white = 0.0f;
        } else if (color_temp <= 2700) {
          amber = 1.0f - (color_temp - 2000) / 700;
          warm_white = (color_temp - 2000) / 700;
          cool_white = 0.0f;
        } else if (color_temp <= 4600) {
          amber = 0.0f;
          warm_white = 1.0f - (color_temp - 2700) / 1900;
          cool_white = (color_temp - 2700) / 1900;
        } else if (color_temp <= 6500) {
          amber = 0.0f;
          warm_white = 0.5f - 0.5f * (color_temp - 4600) / 1900;
          cool_white = 0.5f + 0.5f * (color_temp - 4600) / 1900;
        } else {
          amber = 0.0f;
          warm_white = 0.0f;
          cool_white = 1.0f;
        }
        
        amber_->set_level(amber * brightness);
        warm_white_->set_level(warm_white * brightness);
        cool_white_->set_level(cool_white * brightness);
      }
      
     protected:
      output::FloatOutput *amber_;
      output::FloatOutput *warm_white_;
      output::FloatOutput *cool_white_;
    };
    """)
