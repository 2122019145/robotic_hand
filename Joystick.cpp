#include "Joystick.h"
#include "Config.h"


/*
 * ============================================================
 *  begin()
 * ============================================================
 *
 *  初始化摇杆。
 *
 * ============================================================
 */

void Joystick::begin()
{
    /*
     * 设置A0、A1为输入。
     */
    pinMode(
        JOYSTICK_X_PIN,
        INPUT
    );

    pinMode(
        JOYSTICK_Y_PIN,
        INPUT
    );


    /*
     * 读取当前摇杆位置作为中心值。
     *
     * 所以：
     *
     *     开机时不要碰摇杆。
     *
     * 否则程序会把偏移的位置当成"中心"。
     */
    centerX = analogRead(
        JOYSTICK_X_PIN
    );

    centerY = analogRead(
        JOYSTICK_Y_PIN
    );
}


/*
 * ============================================================
 *  applyDeadzone()
 * ============================================================
 *
 *  摇杆死区。
 *
 *  假设：
 *
 *      center = 512
 *
 *      deadzone = 60
 *
 *  那么：
 *
 *      452 ~ 572
 *
 *  都被认为是"摇杆没动"。
 *
 * ============================================================
 */

int Joystick::applyDeadzone(
    int value,
    int center
)
{
    /*
     * abs()：
     *
     * 计算两个数字之间的距离。
     */
    if (
        abs(value - center)
        <
        JOYSTICK_DEADZONE
    )
    {
        /*
         * 在死区内。
         *
         * 直接返回中心值。
         */
        return center;
    }


    /*
     * 超过死区。
     *
     * 返回原始数据。
     */
    return value;
}


/*
 * ============================================================
 *  read()
 * ============================================================
 *
 *  读取摇杆。
 *
 * ============================================================
 */

JoystickState Joystick::read()
{
    JoystickState state;


    /*
     * 从A0读取X轴。
     *
     * Arduino UNO：
     *
     *     analogRead()
     *
     * 返回：
     *
     *     0 ~ 1023
     */
    state.x = analogRead(
        JOYSTICK_X_PIN
    );


    /*
     * 从A1读取Y轴。
     */
    state.y = analogRead(
        JOYSTICK_Y_PIN
    );


    /*
     * 应用死区。
     */
    state.x = applyDeadzone(
        state.x,
        centerX
    );

    state.y = applyDeadzone(
        state.y,
        centerY
    );


    /*
     * 判断X方向是否真的有移动。
     */
    state.xActive =
        abs(state.x - centerX)
        >=
        JOYSTICK_DEADZONE;


    /*
     * 判断Y方向是否真的有移动。
     */
    state.yActive =
        abs(state.y - centerY)
        >=
        JOYSTICK_DEADZONE;


    return state;
}


/*
 * ============================================================
 *  getCenterX()
 * ============================================================
 */

int Joystick::getCenterX()
{
    return centerX;
}


/*
 * ============================================================
 *  getCenterY()
 * ============================================================
 */

int Joystick::getCenterY()
{
    return centerY;
}
