#include <zephyr/kernel.h>
#include "buzzer.h"

static int buzzer_sys_init(const struct device *dev) {
    buzzer_init();
    /* 전원 켜고 0.8초 뒤 테스트 톤 */
    k_msleep(800);
    buzzer_play_tone(2400, 55, 180);
    return 0;
}

SYS_INIT(buzzer_sys_init, APPLICATION, 50);
