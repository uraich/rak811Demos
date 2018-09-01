/*
 * lis3dhDebug.c
 *
 *  Created on: Aug 18, 2018
 *      Author: uli
 */
#include "lis3dh.h"

void printErr(char *regName) {
	printf("lis3dhPrintAllRegs: Cannot read register %s\r\n",regName);
}

void lis3dhPrintAllRegs(void) {
	uint8_t regContent;
	if (!LIS3DH_ReadReg(LIS3DH_STATUS_AUX,&regContent))
		printErr("LIS3DH_STATUS_AUX");
	else
		printf("LIS3DH_STATUS_AUX: 0x%02x\r\n",regContent);

	printf("=================== OUT 1-3 registers =========================\r\n");
	if (!LIS3DH_ReadReg(LIS3DH_OUT_1_L,&regContent))
		printErr("LIS3DH_OUT_1_L");
	else
		printf("LIS3DH_OUT_1_L: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_OUT_1_H,&regContent))
		printErr("LIS3DH_OUT_1_H");
	else
		printf("LIS3DH_OUT_1_H: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_OUT_2_L,&regContent))
		printErr("LIS3DH_OUT_2_L");
	else
		printf("LIS3DH_OUT_2_L: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_OUT_2_H,&regContent))
		printErr("LIS3DH_OUT_2_H");
	else
		printf("LIS3DH_OUT_2_H: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_OUT_1_L,&regContent))
		printErr("LIS3DH_OUT_3_L");
	else
		printf("LIS3DH_OUT_3_L: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_OUT_2_H,&regContent))
		printErr("LIS3DH_OUT_3_H");
	else
		printf("LIS3DH_OUT_3_H: 0x%02x\r\n",regContent);

	printf("=================== Who am I  register =====================\r\n");

	if (!LIS3DH_ReadReg(LIS3DH_WHO_AM_I,&regContent))
		printErr("LIS3DH_WHO_AM_I");
	else
		printf("LIS3DH_WHO_AM_I: 0x%02x\r\n",regContent);

	printf("=================== Crtl registers =========================\r\n");
	if (!LIS3DH_ReadReg(LIS3DH_CTRL_REG0,&regContent))
		printErr("LIS3DH_CTRL_REG0");
	else
		printf("LIS3DH_CTRL_REG0: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_TEMP_CFG_REG,&regContent))
		printErr("LIS3DH_TEMP_CFG_REG");
	else
		printf("LIS3DH_TEMP_CFG_REG: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_CTRL_REG1,&regContent))
		printErr("LIS3DH_CTRL_REG1");
	else
		printf("LIS3DH_CTRL_REG_1: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_CTRL_REG2,&regContent))
		printErr("LIS3DH_CTRL_REG2");
	else
		printf("LIS3DH_CTRL_REG_2: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_CTRL_REG3,&regContent))
		printErr("LIS3DH_CTRL_REG3");
	else
		printf("LIS3DH_CTRL_REG_3: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_CTRL_REG4,&regContent))
		printErr("LIS3DH_CTRL_REG4");
	else
		printf("LIS3DH_CTRL_REG_4: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_CTRL_REG5,&regContent))
		printErr("LIS3DH_CTRL_REG5");
	else
		printf("LIS3DH_CTRL_REG_5: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_CTRL_REG6,&regContent))
		printErr("LIS3DH_CTRL_REG6");
	else
		printf("LIS3DH_CTRL_REG_6: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_REFERENCE_REG,&regContent))
		printErr("LIS3DH_REFERENCE_REG");
	else
		printf("LIS3DH_REFERENCE_REG: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_STATUS_REG,&regContent))
		printErr("LIS3DH_STATUS_REG");
	else
		printf("LIS3DH_STATUS_REG: 0x%02x\r\n",regContent);

	printf("=================== OUT X,Y,Z registers ====================\r\n");

	if (!LIS3DH_ReadReg(LIS3DH_OUT_X_L,&regContent))
		printErr("LIS3DH_OUT_X_L");
	else
		printf("LIS3DH_OUT_X_L: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_OUT_X_H,&regContent))
		printErr("LIS3DH_OUT_X_H");
	else
		printf("LIS3DH_OUT_X_H: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_OUT_Y_L,&regContent))
		printErr("LIS3DH_OUT_Y_L");
	else
		printf("LIS3DH_OUT_Y_L: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_OUT_Y_H,&regContent))
		printErr("LIS3DH_OUT_Y_H");
	else
		printf("LIS3DH_OUT_Y_H: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_OUT_Z_L,&regContent))
		printErr("LIS3DH_OUT_Z_L");
	else
		printf("LIS3DH_OUT_Z_L: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_OUT_Z_H,&regContent))
		printErr("LIS3DH_OUT_Z_H");
	else
		printf("LIS3DH_OUT_Z_H: 0x%02x\r\n",regContent);

	printf("=================== FIFO registers =========================\r\n");

	if (!LIS3DH_ReadReg(LIS3DH_FIFO_CTRL_REG,&regContent))
		printErr("LIS3DH_FIFO_CTRL_REG");
	else
		printf("LIS3DH_FIFO_CTRL_REG: 0x%02x\r\n",regContent);


	if (!LIS3DH_ReadReg(LIS3DH_FIFO_SRC_REG,&regContent))
		printErr("LIS3DH_FIFO_SRC_REG");
	else
		printf("LIS3DH_FIFO_SRC_REG: 0x%02x\r\n",regContent);

	printf("=================== Interrupt registers =====================\r\n");

	if (!LIS3DH_ReadReg(LIS3DH_INT1_CFG,&regContent))
		printErr("LIS3DH_INT1_CFG");
	else
		printf("LIS3DH_INT1_CFG: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_INT1_SRC,&regContent))
		printErr("LIS3DH_INT1_SRC");
	else
		printf("LIS3DH_INT1_SRC: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_INT1_THS,&regContent))
		printErr("LIS3DH_INT1_THS");
	else
		printf("LIS3DH_INT1_THS: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_INT1_DURATION,&regContent))
		printErr("LIS3DH_INT1_DURATION");
	else
		printf("LIS3DH_INT1_DURATION: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_INT2_CFG,&regContent))
		printErr("LIS3DH_INT2_CFG");
	else
		printf("LIS3DH_INT2_CFG: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_INT2_SRC,&regContent))
		printErr("LIS3DH_INT2_SRC");
	else
		printf("LIS3DH_INT2_SRC: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_INT2_THS,&regContent))
		printErr("LIS3DH_INT2_THS");
	else
		printf("LIS3DH_INT2_THS: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_INT2_DURATION,&regContent))
		printErr("LIS3DH_INT2_DURATION");
	else
		printf("LIS3DH_INT2_DURATION: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_CLICK_CFG,&regContent))
		printErr("LIS3DH_CLICK_CFG");
	else
		printf("LIS3DH_CLICK_CFG: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_CLICK_SRC,&regContent))
		printErr("LIS3DH_CLICK_SRC");
	else
		printf("LIS3DH_CLICK_SRC: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_CLICK_THS,&regContent))
		printErr("LIS3DH_CLICK_THS");
	else
		printf("LIS3DH_CLICK_THS: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_TIME_LIMIT,&regContent))
		printErr("LIS3DH_TIME_LIMIT");
	else
		printf("LIS3DH_TIME_LIMIT: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_TIME_LATENCY,&regContent))
		printErr("LIS3DH_TIME_LATENCY");
	else
		printf("LIS3DH_TIME_LATENCY: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_ACT_THS,&regContent))
		printErr("LIS3DH_ACT_THS");
	else
		printf("LIS3DH_ACT_THS: 0x%02x\r\n",regContent);

	if (!LIS3DH_ReadReg(LIS3DH_ACT_DUR,&regContent))
		printErr("LIS3DH_ACT_DUR");
	else
		printf("LIS3DH_ACT_DUR: 0x%02x\r\n",regContent);
}
