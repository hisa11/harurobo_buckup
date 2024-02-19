#include "FirstPenguin.hpp"

// CAN オブジェクトを削除

void FirstPenguin::read(const CANMessage& msg) {
    if(msg.format == CANStandard && msg.type == CANData && msg.len == sizeof(receive[0]) && send_id < msg.id &&
        msg.id <= send_id + 5) {
        receive[msg.id - send_id - 1].set(msg.data);
    }
}

bool FirstPenguin::send() {
    static CAN can1(PA_11, PA_12, (int)1e6); // CAN オブジェクトをここで定義
    return can1.write(CANMessage{send_id, reinterpret_cast<const uint8_t*>(pwm), 8}); // can を can1 に変更
}

FirstPenguin penguin{can_id};
