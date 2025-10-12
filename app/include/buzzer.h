#ifndef BUZZER_H
#define BUZZER_H
void buzzer_init(void);
void buzzer_play_tone(int freq_hz, int duty_pct, int duration_ms);
#endif
