#ifndef ID_CAN_H_
#define ID_CAN_H_

#include "include.h"

//references on https://docs.google.com/spreadsheets/d/1QMofLu4PjR1f2bQfC410LiYba_z6rZJD4pPNm4Pdk8I/edit#gid=1754956647     try this

#define DRIVE_ID		0x001

#define BUS_STATE_ID	0x002

#define GYRO_ID			0x003
#define FAULTS_ID		0x00A
#define NO_STATE_ID		0x00B
#define BRAKE_ID		0x00C
#define SETTING_ID		0x00D
#define MOTOR_INFO_ID	0x010
#define MOTOR_TEMP_ID	0x011
#define INV_TEMP_ID		0x012
#define SPEED_ID		0x013
#define TORQUE_ID		0x014

#define	STAR_ID			0x042

#define HV_STATUS_ID	0x0A0
#define LV_STATUS_ID	0x0B0
#define SPRINGS_R_ID	0x0C0
#define SPRINGS_F_ID	0x0C1
#define COOLING_ID		0x0D0

#define May12			0xff

#define LTU_ID			0x100


#endif /* ID_CAN_H_ */
