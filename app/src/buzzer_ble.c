#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/behavior.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int ble_profile_changed_listener(const struct zmk_event_header *eh) {
    const struct zmk_ble_active_profile_changed *ev = cast_zmk_ble_active_profile_changed(eh);

    if (ev->conn_handle >= 0) {
        // BLE 연결됨
        behavior_invoke_macro("beep_one");
    } else {
        // BLE 해제됨
        behavior_invoke_macro("beep_two");
    }
    return 0;
}

ZMK_LISTENER(buzzer_ble, ble_profile_changed_listener);
ZMK_SUBSCRIPTION(buzzer_ble, zmk_ble_active_profile_changed);
