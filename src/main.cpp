#include "mbed.h"
#include "ServoController.hpp"
#include "SolenoidController.hpp"
#include "FirstPenguin.hpp"

BufferedSerial pc(USBTX, USBRX, 250000); // Serial communication with the computer
CAN can1(PA_11, PA_12, (int)1e6);
CANMessage msg; // Changed from msg6 to msg

Timer timer;

// Declare instances of ServoController and SolenoidController globally
SolenoidController solenoidController(can1, pc);
ServoController servoController(can1, pc);

int main()
{
    printf("\nSetup\n");
    timer.start();
    auto pre = timer.elapsed_time();
    bool servoTurn = true; // サーボを先に動作させるためのフラグ
    
    while(1) {
        auto now = timer.elapsed_time();

        if(can1.read(msg)) {
            penguin.read(msg);
        }

        if(now - pre > 20ms) {
            for(auto e: penguin.receive) printf("% 5ld\t", e.enc);
            for(auto e: penguin.receive) printf("% 5ld\t", e.adc);
            printf("\n");
            for(auto& e: penguin.pwm) e = penguin.max / 4;
            penguin.send();
            pre = now;
        }

        // サーボとソレノイドのコントローラーを交互に実行する
        //  if (pc.readable()){
            char buf;
            pc.read(&buf, sizeof(buf));

        if (buf== '1' || buf=='2'||buf=='3') {
            servoController.run();
            servoTurn = false;
        } else {
            solenoidController.run();
            servoTurn = true;
        }
        // }
    }
}


