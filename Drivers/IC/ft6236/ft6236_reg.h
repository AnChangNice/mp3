#ifndef __FT6236_REG_H
#define __FT6236_REG_H

#define FT6236_REG_DEV_MODE             0x00
#define FT6236_REG_GEST_ID              0x01
#define FT6236_REG_TD_STATUS            0x02
#define FT6236_REG_P1_XH                0x03
#define FT6236_REG_P1_XL                0x04
#define FT6236_REG_P1_YH                0x05
#define FT6236_REG_P1_YL                0x06
#define FT6236_REG_P1_WEIGHT            0x07
#define FT6236_REG_P1_MISC              0x08
#define FT6236_REG_P2_XH                0x09
#define FT6236_REG_P2_XL                0x0A
#define FT6236_REG_P2_YH                0x0B
#define FT6236_REG_P2_YL                0x0C
#define FT6236_REG_P2_WEIGHT            0x0D
#define FT6236_REG_P2_MISC              0x0E
#define FT6236_REG_TH_GROUP             0x80
#define FT6236_REG_TH_DIFF              0x85
#define FT6236_REG_CTRL                 0x86
#define FT6236_REG_TIMEENTERMONITOR     0x87
#define FT6236_REG_PERIODACTIVE         0x88
#define FT6236_REG_PERIODMONITOR        0x89
#define FT6236_REG_RADIAN_VALUE         0x91
#define FT6236_REG_OFFSET_LEFT_RIGHT    0x92
#define FT6236_REG_OFFSET_UP_DOWN       0x93
#define FT6236_REG_DISTANCE_LEFT_RIGHT  0x94
#define FT6236_REG_DISTANCE_UP_DOWN     0x95
#define FT6236_REG_DISTANCE_ZOOM        0x96
#define FT6236_REG_LIB_VER_H            0xA1
#define FT6236_REG_LIB_VER_L            0xA2
#define FT6236_REG_CIPHER               0xA3
#define FT6236_REG_G_MODE               0xA4
#define FT6236_REG_PWR_MODE             0xA5
#define FT6236_REG_FIRMID               0xA6
#define FT6236_REG_FOCALTECH_ID         0xA8
#define FT6236_REG_RELEASE_CODE_ID      0xAF
#define FT6236_REG_STATE                0xBC

/* Gesture ID. */
#define FT6236_GEST_ID_None         0x00
#define FT6236_GEST_ID_MoveUp       0x10
#define FT6236_GEST_ID_MoveRight    0x14
#define FT6236_GEST_ID_MoveDown     0x18
#define FT6236_GEST_ID_MoveLeft     0x1C
#define FT6236_GEST_ID_ZoomIn       0x48
#define FT6236_GEST_ID_ZoomOut      0x49

#endif //__FT6236_REG_H