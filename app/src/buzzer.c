#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/pwm.h>

#define BUZZER_NODE DT_NODELABEL(buzzer_pwm)

#if !DT_NODE_HAS_STATUS(BUZZER_NODE, okay)
#error "Buzzer PWM node not found or not okay"
#endif

static const struct device *pwm_dev;
static uint32_t pwm_channel = DT_PWMS_CHANNEL(BUZZER_NODE);

static inline uint32_t clamp_u32(uint32_t v, uint32_t lo, uint32_t hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

void buzzer_init(void) {
    pwm_dev = DEVICE_DT_GET(DT_PWMS_CTLR(BUZZER_NODE));
    if (!device_is_ready(pwm_dev)) {
        printk("buzzer: pwm device not ready\n");
        return;
    }
    /* OFF 초기화 */
    pwm_set(pwm_dev, pwm_channel, 1000000, 0, 0);
}

void buzzer_play_tone(int freq_hz, int duty_pct, int duration_ms) {
    if (!pwm_dev || !device_is_ready(pwm_dev)) return;

    freq_hz = (int)clamp_u32(freq_hz, 200, 8000);
    duty_pct = (int)clamp_u32(duty_pct, 1, 90);
    duration_ms = (int)clamp_u32(duration_ms, 10, 2000);

    uint32_t period_ns = 1000000000UL / (uint32_t)freq_hz;
    uint32_t pulse_ns = (period_ns * (uint32_t)duty_pct) / 100U;

    pwm_set(pwm_dev, pwm_channel, period_ns, pulse_ns, 0);
    k_msleep(duration_ms);
    pwm_set(pwm_dev, pwm_channel, period_ns, 0, 0);
}
