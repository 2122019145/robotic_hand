#ifndef SERIAL_COMMAND_H
#define SERIAL_COMMAND_H

#include <Arduino.h>


/*
 * ============================================================
 *  SerialCommand
 * ============================================================
 *
 *  负责：
 *
 *      从电脑串口读取命令。
 *
 *  例如：
 *
 *      O
 *      S
 *      H
 *      L
 *
 * ============================================================
 */

class SerialCommand
{
public:

    /*
     * 初始化串口。
     */
    void begin(long baudrate);


    /*
     * 检查串口有没有收到新的数据。
     *
     * 返回：
     *
     *     true  → 收到了
     *     false → 没收到
     */
    bool available();


    /*
     * 获取收到的字符。
     *
     * 例如：
     *
     *     收到 O
     *
     *     返回 'O'
     */
    char read();


private:

    /*
     * 保存最近收到的命令。
     */
    char lastCommand;
};

#endif // SERIAL_COMMAND_H
