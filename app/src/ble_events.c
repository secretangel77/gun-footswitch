#include <zephyr/kernel.h>
#include <zmk/event_manager.h>
#include <zmk/events/ble_connection_state_changed.h>
#include "buzzer.h"

static int buzzer_ble_handler(const zmk_event_t *eh) {
    const struct zmk_ble_connection_state_changed *conn_evt =
        as_zmk_ble_connection_state_changed(eh);
    if (conn_evt) {
        if (conn_evt->connected) {
            buzzer_beep_connected();
        } else {
            buzzer_beep_disconnected();
        }
    }
    return 0;
}

ZMK_LISTENER(buzzer_ble_listener, buzzer_ble_handler);
ZMK_SUBSCRIPTION(buzzer_ble_listener, zmk_ble_connection_state_changed);
