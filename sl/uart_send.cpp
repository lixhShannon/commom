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
#include "SL_system.h"

uint8_t uart_phase=0;  //开关量

void sendData(uint8_t CANID)
{
    uint8_t buf[10];
    uint8_t i;
    uint8_t crc=0xAA;
    buf[0] = 0xAA;
    if(CANID<7)
    {
        buf[1] = CANID;
    }
    else
    {
        printf("error CAN ID");
        return;
    }
    crc ^= buf[0];
    for(i=0;i<8;i++)
    {
        buf[i+1] = SendBuf[i];
        crc ^= buf[i+1];
    }
    buf[10] = crc;
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
        case 4:
        break;
        default:
        uart_phase = 0;
        break;
    }
}