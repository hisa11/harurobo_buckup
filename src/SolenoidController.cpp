#include "SolenoidController.hpp"

int n =0;
// ソレノイド制御用データの宣言
uint8_t solenoid[8];

SolenoidController::SolenoidController(CAN& can, BufferedSerial& serial) : can(can), serial(serial)
{
    // コンストラクタの実装
    // solenoid 配列を初期化
    memset(solenoid, 1, sizeof(solenoid));
}

// ソレノイド制御の実行
void SolenoidController::run()
{
    while (1) {
        char buf; // シリアル受信バッファ
        if (serial.readable()) {
            serial.read(&buf, sizeof(buf));

            // ソレノイドの制御データを設定
            if (buf == 'x') // 左動作
            {
                solenoid[0] = 0;
                solenoid[1] = 1;
                printf("左動作\n");
            }
            else if (buf == 'v') // 右動作
            {
                solenoid[0] = 1;
                solenoid[1] = 0;
                printf("右動作\n");
            }
            else if (buf == 'z' || buf == 'Q' || buf == 'A') // 停止
            {
                solenoid[0] = 1;
                solenoid[1] = 1;
                printf("停止\n");
            }
            else if(buf =='1' ||buf == '2' || buf == '3'){
                break;
            }

            // CAN メッセージを作成し送信
            CANMessage msg2(0xf2, (const uint8_t *)solenoid, sizeof(solenoid));
            can.write(msg2);

            // 20 ミリ秒待機
            ThisThread::sleep_for(20ms);
            n++;
        }
    }
}
