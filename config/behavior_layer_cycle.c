#include <zmk/behavior.h>
#include <zmk/event_manager.h>
#include <zmk/keymap.h>
#include <zmk/layers.h>

static int layer_cycle_mouse(struct zmk_behavior_binding *binding,
                             struct zmk_behavior_binding_event event) {
    if (event.pressed) {
        static int current_layer = 0;
        zmk_layer_deactivate(current_layer);
        current_layer = (current_layer + 1) % 4; // 0~3 순환
        zmk_layer_activate(current_layer);
    }
    return ZMK_BEHAVIOR_OPAQUE;
}

static int layer_cycle_kb(struct zmk_behavior_binding *binding,
                          struct zmk_behavior_binding_event event) {
    if (event.pressed) {
        static int current_layer = 10;
        zmk_layer_deactivate(current_layer);
        current_layer = (current_layer + 1 > 13) ? 10 : current_layer + 1;
        zmk_layer_activate(current_layer);
    }
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api layer_cycle_mouse_api = {
    .binding_pressed = layer_cycle_mouse,
};

static const struct behavior_driver_api layer_cycle_kb_api = {
    .binding_pressed = layer_cycle_kb,
};

DEVICE_DT_INST_DEFINE(0, NULL, NULL, NULL, NULL, POST_KERNEL,
                      CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                      &layer_cycle_mouse_api);

DEVICE_DT_INST_DEFINE(1, NULL, NULL, NULL, NULL, POST_KERNEL,
                      CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                      &layer_cycle_kb_api);
