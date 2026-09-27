#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Arduino.h>
#include <Servo.h>

#include "RobotTypes.h"


/*
 * ============================================================
 *  ServoController
 * ============================================================
 *
 *  这个类负责：
 *
 *      1. 初始化四个舵机
 *      2. 控制单个舵机
 *      3. 同时控制四个舵机
 *      4. 回到初始位置
 *      5. 限制舵机运动范围
 *      6. 获取当前舵机角度
 *
 *  后面的所有任务尽量不要直接使用：
 *
 *      servo.write()
 *
 *  而是通过这个类控制。
 *
 * ============================================================
 */

class ServoController
{
public:

    /*
     * 初始化四个舵机。
     *
     * 在 setup() 中调用：
     *
     *     robot.begin();
     */
    void begin();


    /*
     * 单独控制底座舵机。
     */
    void setBase(int angle);


    /*
     * 单独控制肩部舵机。
     */
    void setShoulder(int angle);


    /*
     * 单独控制肘部舵机。
     */
    void setElbow(int angle);


    /*
     * 单独控制夹爪舵机。
     */
    void setGripper(int angle);


    /*
     * 一次性设置四个舵机。
     *
     * 例如：
     *
     *     robot.setAll(90, 80, 120, 30);
     *
     */
    void setAll(
        int base,
        int shoulder,
        int elbow,
        int gripper
    );


    /*
     * 让机械臂回到初始位置。
     */
    void home();


    /*
     * 获取当前四个舵机的角度。
     */
    ServoAngles getAngles();


private:

    /*
     * Arduino Servo对象。
     *
     * 一个 Servo 对象对应一个舵机。
     */
    Servo baseServo;
    Servo shoulderServo;
    Servo elbowServo;
    Servo gripperServo;


    /*
     * 保存程序认为的当前角度。
     *
     * 注意：
     *
     * 舵机本身不会告诉Arduino：
     *
     *     "我现在到底是多少度"
     *
     * 所以这里保存的是：
     *
     *     "我们最后给它发送了多少度"
     *
     */
    ServoAngles currentAngles;


    /*
     * 限制角度。
     *
     * 例如：
     *
     *     输入200°
     *
     * 如果最大角度是180°
     *
     *     最终变成180°
     */
    int limitAngle(
        int angle,
        int minAngle,
        int maxAngle
    );
};

#endif // SERVO_CONTROLLER_H
