#ifndef BUZZER_H
#define BUZZER_H

void buzzer_init(void);
void buzzer_play_tone(int freq_hz, int duty_pct, int duration_ms);
void buzzer_beep_connected(void);
void buzzer_beep_disconnected(void);

#endif
