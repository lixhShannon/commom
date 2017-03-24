/********************************************************************
文件名称          ：uart_send
项目代号或名称     ：
功能描述          ：
目标芯片          ：
创建人            ：Shannon Li
创建日期          ：
历史修改记录      ：
                    SL    2017-03-24    v1.0   模块创建
版本信息          ：v1.0
其他说明          ：
********************************************************************/
#include "uart_send.h"

char uart_phase=0;
char uart_check(char *buf)
{
    char crc=0xAA;
    for(char i=0;i<8;i++)
    {
        crc ^= buf[i];
    }
    return crc;
}

void sendData(unsigned char CANID)
{
    char buf[10];
    buf[0] = 0xAA;
    if(CANID<7)
    {
        buf[1] = CANID;
    }
    else
    {
        _debug();
        return;
    }
}

bool uart_send(void)
{
    switch(uart_phase)
    {
        case 0:  //给工控机
        sendData(0x02);
        uart_phase = 1;
        break;
        case 1:  //给底盘板
        sendData(0x04);
        uart_phase = 2;
        break;
        case 2:  //胸部板
        sendData(0x03);
        uart_phase = 3;
        break;
        case 3:  //头部板
        sendData(0x08);
        uart_phase = 0;
        break;
        default:
        uart_phase = 0;
        break;
    }
}