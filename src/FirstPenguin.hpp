#ifndef FIRST_PENGUIN_HPP
#define FIRST_PENGUIN_HPP

#include <mbed.h>

constexpr uint32_t can_id = 30;

struct FirstPenguin {
    static constexpr int max = INT16_MAX;
    uint32_t send_id;
    int16_t pwm[4] = {};
    struct {
        int32_t enc;
        uint32_t adc;
        void set(const uint8_t data[8]) {
            memcpy(this, data, sizeof(*this));
        }
    } receive[4] = {};
    void read(const CANMessage& msg);
    bool send();
};

extern FirstPenguin penguin;

#endif
