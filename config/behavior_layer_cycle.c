/*
 * Custom ZMK behavior: Layer Cycle
 * 
 * 반복해서 누를 때마다 지정된 레이어 그룹을 순환.
 * 예) 마우스 모드: 0→1→2→3→0
 *     키보드 모드: 10→11→12→13→10
 */

#include <zmk/behavior.h>
#include <zmk/keymap.h>
#include <logging/log.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

struct layer_cycle_cfg {
    int first_layer;
    int last_layer;
};

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    const struct layer_cycle_cfg *cfg = binding->param1;

    int active = zmk_keymap_layer_active();
    int next = cfg->first_layer;

    if (active >= cfg->first_layer && active < cfg->last_layer) {
        next = active + 1;
    }

    if (active == cfg->last_layer) {
        next = cfg->first_layer;
    }

    LOG_INF("LayerCycle: active=%d next=%d", active, next);

    zmk_keymap_layer_activate(next);
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api layer_cycle_api = {
    .binding_pressed = on_keymap_binding_pressed,
};

#define LAYER_CYCLE_INST(n)                                                                     \
    static struct layer_cycle_cfg layer_cycle_cfg_##n = {                                       \
        .first_layer = DT_INST_PROP(n, first_layer),                                            \
        .last_layer = DT_INST_PROP(n, last_layer)};                                             \
    DEVICE_DT_INST_DEFINE(n, NULL, NULL, NULL, &layer_cycle_cfg_##n, POST_KERNEL,               \
                          CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &layer_cycle_api);

DT_INST_FOREACH_STATUS_OKAY(LAYER_CYCLE_INST)
