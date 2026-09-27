#include "ServoController.h"
#include "Config.h"


/*
 * ============================================================
 *  begin()
 * ============================================================
 *
 *  初始化四个舵机。
 *
 *  attach() 的作用：
 *
 *      告诉Arduino：
 *
 *      "这个Servo对象连接在哪个数字引脚。"
 *
 * ============================================================
 */

void ServoController::begin()
{
    baseServo.attach(SERVO_BASE_PIN);

    shoulderServo.attach(SERVO_SHOULDER_PIN);

    elbowServo.attach(SERVO_ELBOW_PIN);

    gripperServo.attach(SERVO_GRIPPER_PIN);


    /*
     * 初始化完成以后，
     * 让机械臂回到初始位置。
     */
    home();
}


/*
 * ============================================================
 *  limitAngle()
 * ============================================================
 *
 *  防止舵机超过设定范围。
 *
 *  Arduino的 constrain()：
 *
 *      如果数值小于最小值
 *          → 返回最小值
 *
 *      如果数值大于最大值
 *          → 返回最大值
 *
 *      否则
 *          → 返回原值
 *
 *  例如：
 *
 *      limitAngle(200, 0, 180)
 *
 *      返回180
 *
 * ============================================================
 */

int ServoController::limitAngle(
    int angle,
    int minAngle,
    int maxAngle
)
{
    return constrain(
        angle,
        minAngle,
        maxAngle
    );
}


/*
 * ============================================================
 *  setBase()
 * ============================================================
 *
 *  设置底座角度。
 *
 * ============================================================
 */

void ServoController::setBase(int angle)
{
    /*
     * 先进行软件限位。
     */
    angle = limitAngle(
        angle,
        BASE_MIN,
        BASE_MAX
    );


    /*
     * 真正给舵机发送角度。
     */
    baseServo.write(angle);


    /*
     * 保存当前角度。
     */
    currentAngles.base = angle;
}


/*
 * ============================================================
 *  setShoulder()
 * ============================================================
 */

void ServoController::setShoulder(int angle)
{
    angle = limitAngle(
        angle,
        SHOULDER_MIN,
        SHOULDER_MAX
    );

    shoulderServo.write(angle);

    currentAngles.shoulder = angle;
}


/*
 * ============================================================
 *  setElbow()
 * ============================================================
 */

void ServoController::setElbow(int angle)
{
    angle = limitAngle(
        angle,
        ELBOW_MIN,
        ELBOW_MAX
    );

    elbowServo.write(angle);

    currentAngles.elbow = angle;
}


/*
 * ============================================================
 *  setGripper()
 * ============================================================
 */

void ServoController::setGripper(int angle)
{
    angle = limitAngle(
        angle,
        GRIPPER_MIN,
        GRIPPER_MAX
    );

    gripperServo.write(angle);

    currentAngles.gripper = angle;
}


/*
 * ============================================================
 *  setAll()
 * ============================================================
 *
 *  一次设置四个舵机。
 *
 *  注意：
 *
 *  这里的"同时"指：
 *
 *      程序几乎连续地给四个舵机发送目标角度。
 *
 *  舵机真正的物理运动仍然需要时间。
 *
 *  后面如果需要真正的同步运动，
 *  我们会另外写"运动插补"模块。
 *
 * ============================================================
 */

void ServoController::setAll(
    int base,
    int shoulder,
    int elbow,
    int gripper
)
{
    setBase(base);

    setShoulder(shoulder);

    setElbow(elbow);

    setGripper(gripper);
}


/*
 * ============================================================
 *  home()
 * ============================================================
 *
 *  让机械臂回到我们定义的初始位置。
 * ============================================================
 */

void ServoController::home()
{
    setAll(
        BASE_HOME,
        SHOULDER_HOME,
        ELBOW_HOME,
        GRIPPER_HOME
    );
}


/*
 * ============================================================
 *  getAngles()
 * ============================================================
 *
 *  返回当前程序记录的四个舵机角度。
 *
 * ============================================================
 */

ServoAngles ServoController::getAngles()
{
    return currentAngles;
}
