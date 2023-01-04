#include "mbed.h"   
//Serial pc(USBTX, USBRX);
AnalogIn sensor(A1);
PwmOut motor(D6);
DigitalOut direction1(D4);
DigitalOut direction2(D5);
float sensor_input;
float value;

void set_motor_speed(int level){
    switch(level){
        case 0: motor.write(1.0); break;
        case 1: motor.write(0.6); break;
        case 2: motor.write(0.0); break;
    }
}
void set_direction(char direction){
    switch(direction)
    {
        case 'f': direction1 = 1; direction2 = 0; break;
        case 'r': direction1 = 0; direction2 = 1; break;
    }
}

int main() {
    while(1){
        sensor_input = sensor.read();
        value = sensor_input * 100;
        motor.period(0.10);
        motor.write(0.4);
        //pc.printf("Vout: %f\n",value);
        if(value > 20.0){
            set_motor_speed(0);
            set_direction('f');
        }
        else if(value > 1.0)
        {
            set_motor_speed(1);
            set_direction('r');
        }
        else if(value < 1.0)
        {
            set_motor_speed(2);
            set_direction('f');
        }
        wait_us(500000);
    } 
}

