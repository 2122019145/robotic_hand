#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

#include "RobotTypes.h"


/*
 * ============================================================
 *  Joystick
 * ============================================================
 *
 *  负责读取摇杆。
 *
 *  目前我们只使用：
 *
 *      X轴
 *      Y轴
 *
 *  后面如果你的摇杆板还有按钮，
 *  我们可以继续加入：
 *
 *      SW
 *      K1
 *      K2
 *      ...
 *
 * ============================================================
 */

class Joystick
{
public:

    /*
     * 初始化摇杆。
     *
     * 在 setup() 中调用。
     */
    void begin();


    /*
     * 读取一次摇杆状态。
     *
     * 返回：
     *
     *     JoystickState
     *
     */
    JoystickState read();


    /*
     * 获取X轴中心值。
     */
    int getCenterX();


    /*
     * 获取Y轴中心值。
     */
    int getCenterY();


private:

    /*
     * 摇杆不动时的中心值。
     *
     * 理论上约为512。
     *
     * 实际可能是：
     *
     *     507
     *     518
     *     510
     *
     * 所以我们在启动的时候自动读取。
     */
    int centerX;
    int centerY;


    /*
     * 对摇杆数据应用死区。
     */
    int applyDeadzone(
        int value,
        int center
    );
};

#endif // JOYSTICK_H
