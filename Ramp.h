#pragma once

#include <Arduino.h>
#include <Servo.h>

typedef enum
{
    close = 0,
    open
} stanjeRampe;

class Ramp
{

private:
    Servo *ramp_servo = NULL; // create servo object to control a servo
    uint32_t IR_enterence_pin;
    uint32_t IR_exit_pin;
    uint32_t Motor_pin;
    bool pre_IR_enterence_state = false;
    bool change_exit_occured = false;
    bool change_enterence_occured = false;
    bool pre_IR_ent_state = false;
    bool pre_IR_ext_state = true;
    bool ramp_state = false;
    void (*car_enterd)() = NULL;
    void (*car_passed)() = NULL;
    uint32_t car_counter = 0;
    stanjeRampe rampState = stanjeRampe::close;
    uint32_t state_exit_change_timestamp;
    uint32_t state_enterence_change_timestamp;
    uint32_t debounce_period = 5;

    uint8_t open_ramp_pos = 90;
    uint8_t close_ramp_pos = 0;
    bool closed_confirmed = false;

public:
    Ramp(uint32_t IR_enterence_pin_, uint32_t IR_exit_pin_, uint32_t Motor_pin_, void (*car_enterd_)(), void (*car_passed_)());
    Ramp(int Motor_pin_);
    Ramp(Servo * rampServo_, uint32_t IR_enterence_pin_, uint32_t IR_exit_pin_, void (*car_enterd_)(), void (*car_passed_)());

    bool get_car_on_rump();
    void run();
    void open_ramp();
    void close_ramp();
};