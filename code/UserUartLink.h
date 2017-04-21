#ifndef _USER_UARTLINK_H_
#define _USER_UARTLINK_H_


/**
******************************************************************************
* @file    UserUartLink.c
* @author  Liqi
* @version V1.1.0
* @date    2016-3-1
* @brief   User Uart Link API
******************************************************************************

******************************************************************************
*/ 

/** @addtogroup UserUartApi
* @{
*/

#define UART_LINK_LEN_MIN 0x01   ///< Len�ֽ���Сֵ
#define UART_LINK_LEN_MAX 500   ///< Len�ֽ����ֵ

typedef enum
{
	UART_LINK_CHECK_NONE=0,
	UART_LINK_CHECK_CRC=2,
	UART_LINK_CHECK_BCC=3,
}uart_link_check;


/**
	 @brief ģ���ʼ��
	 @retval none
*/
extern void initUserUartLink(void);


/**
	 @brief ����������·�����������������
   @attention �����յ����ݺ󣬵��øýӿ�
   @param data ���δ��������ָ��
   @param len ���δ�������ݳ���
	 @retval none
*/
extern bool UserUartLinkUnpack(unsigned char* data, int len);


/**
	 @brief ��ȡ���յ�������֡
   @attention ��ѯ��ȡ���յ���֡������ֵ���������ʾ�����Ч֡
   @param des �������ݵ�ָ��
	 @retval ���ݳ���(0:������)
*/
extern int getUserUartLinkMsg(unsigned char* des);


/**
	 @brief ����������·������������ͨ������㷢�ͳ�ȥ
   @attention ����Ҫ���͵��������
   @param des ���մ��������ݵ�ָ��
   @param src ��Ҫ���͵ĸ������ݣ�����֡���ͺ�����
   @param len ���δ�������ݳ���
   @param check У������(2:crc8408,3:bcc,else:none)
	 @retval �������ֽڳ���
*/
extern int UserUartLinkPack(unsigned char* des, unsigned char*src, int srclen, unsigned char check);


#endif

/** 
* @}
*/

