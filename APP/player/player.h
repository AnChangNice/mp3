#ifndef __PLAYER_H
#define __PLAYER_H

void Player_Init(void);
int  Player_Load(char *path);
void Player_Start(void);
void Player_Hold(void);
void Player_Stop(void);

int  Player_GetTotalSeconds(void);
int  Player_GetCurrentSeconds(void);
int  Player_SetToSeconds(int seconds);

#endif