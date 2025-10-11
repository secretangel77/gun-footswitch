#include <zephyr/kernel.h>
#include "buzzer.h"

static int buzzer_sys_init(const struct device *dev) {
    buzzer_init();
    return 0;
}

SYS_INIT(buzzer_sys_init, APPLICATION, 50);
