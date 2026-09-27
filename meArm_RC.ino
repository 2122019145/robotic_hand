/*
 * ============================================================
 *  meArm_RC.ino
 * ============================================================
 *
 *  这是整个程序的入口。
 *
 *  你可以把它理解成：
 *
 *      "总指挥"
 *
 *  具体工作交给：
 *
 *      ServoController
 *      Joystick
 *      SerialCommand
 *
 * ============================================================
 */

#include "Config.h"
#include "RobotTypes.h"
#include "ServoController.h"
#include "Joystick.h"
#include "SerialCommand.h"


/*
 * 创建机械臂控制对象。
 */
ServoController robot;


/*
 * 创建摇杆对象。
 */
Joystick joystick;


/*
 * 创建串口对象。
 */
SerialCommand serialCommand;


/*
 * ============================================================
 *  setup()
 * ============================================================
 *
 *  Arduino只会在开机时执行一次。
 *
 * ============================================================
 */

void setup()
{
    /*
     * 初始化机械臂。
     */
    robot.begin();


    /*
     * 初始化摇杆。
     */
    joystick.begin();


    /*
     * 初始化串口。
     */
    serialCommand.begin(
        SERIAL_BAUDRATE
    );


    /*
     * 打印启动信息。
     */
    Serial.println(
        "================================"
    );

    Serial.println(
        "meArm RC System Started"
    );

    Serial.println(
        "================================"
    );
}


/*
 * ============================================================
 *  loop()
 * ============================================================
 *
 *  Arduino会一直重复执行这里。
 *
 * ============================================================
 */

void loop()
{
    /*
     * 读取摇杆。
     */
    JoystickState joystickState =
        joystick.read();


    /*
     * 把摇杆数据打印到串口监视器。
     *
     * 例如：
     *
     *     X:512 Y:510
     *
     */
    Serial.print("X: ");

    Serial.print(
        joystickState.x
    );

    Serial.print("   Y: ");

    Serial.print(
        joystickState.y
    );


    /*
     * 显示X方向有没有明显移动。
     */
    Serial.print("   XActive: ");

    Serial.print(
        joystickState.xActive
    );


    /*
     * 显示Y方向有没有明显移动。
     */
    Serial.print("   YActive: ");

    Serial.println(
        joystickState.yActive
    );


    /*
     * 暂时每50ms读取一次。
     *
     * 后面正式控制机械臂的时候，
     * 我们会去掉这种简单delay，
     * 改成基于millis()的非阻塞控制。
     */
    delay(50);
}
