zephyr_include_directories(app/include)

target_sources(app PRIVATE
    app/src/buzzer.c
    app/src/ble_events.c
    app/src/buzzer_init.c
)
