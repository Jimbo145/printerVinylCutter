#ifndef _MOTOR_H
#define _MOTOR_H

    void setAbsolutePositioning(bool ab);
    void feedY();
    void setMotorSpeed(uint8_t motor, uint8_t spd);
    bool isMoving();
    void homeX();
    void moveTo(float destX, float destY);
    void moveZ(float destZ);
    void eStop();


#endif

