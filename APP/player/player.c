#include "player.h"

#include "wav.h"
#include "audio.h"
#include "elog.h"
#include "shell_cmd_group.h"

#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

uint8_t audio_buff[2][8*1024];
WAV wav;
int ch = 0;

#include "ff.h"
FIL file;
UINT readout;

#define PLAYER_IDLE 0
#define PLAYER_SET  1
#define PLAYER_PLAY 2
#define PLAYER_HOLD 3
#define PLAYER_STOP 4

static char music_path[64];
static int  player_state = PLAYER_IDLE;

static void player_task(void *params)
{
    FRESULT res;

    res = f_chdir("1:");

    while(1)
    {
        if(player_state == PLAYER_IDLE)
        {
            vTaskDelay(100/portTICK_PERIOD_MS);
        }
        if(player_state == PLAYER_SET)
        {
            res = f_open(&file, music_path, FA_READ);
            if(res != FR_OK)
            {
                log_e("open: %s failed with code %d", music_path, (int)res);
                player_state = PLAYER_IDLE;
            }
            else
            {
                readWavInfo(&wav, &file);
                Audio_SetFormat(wav.SampleRate, wav.NumChannels, wav.BitsPerSample);
                log_i("wav fs:%d, ch:%d, bits:%d", wav.SampleRate, wav.NumChannels, wav.BitsPerSample);
                player_state = PLAYER_PLAY;
            }
        }
        if(player_state == PLAYER_PLAY)
        {
            res = f_read(&file, &audio_buff[ch][0], 8*1024, &readout);
            if(res != FR_OK)
            {
                log_e("read: failed with code %d", (int)res);
                player_state = PLAYER_STOP;
            }
            else
            {
                while(Audio_IsBusy());
                
                if(0 != Audio_Play(&audio_buff[ch][0], readout, NULL))
                {
                    log_e("play: failed at ch %d when readout %d bytes", ch, readout);
                    player_state = PLAYER_STOP;
                }

                ch = (ch == 0) ? 1 : 0;
                if(readout < 8*1024)
                {
                    player_state = PLAYER_STOP;
                }
            }
        }
        if(player_state == PLAYER_STOP)
        {
            res = f_close(&file);
            if(res != FR_OK)
            {
                log_e("close: failed!");
            }
            else
            {
                log_i("play: stoped!");
            }
            player_state = PLAYER_IDLE;
        }
    }
}

void Player_Init(void)
{
    //Create player_task
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;

    xReturned = xTaskCreate(
                    player_task,
                    "player_task",
                    2048/4,
                    NULL,
                    tskIDLE_PRIORITY+1,
                    &xHandle);

    if(xReturned != pdPASS)
    {
        log_e("player_task create failed!");
    }
}

static int player_list_music(int argc, char *argv[])
{
    FRESULT res;
    DIR dir;
    FILINFO finfo;

    res = f_findfirst(&dir, &finfo, "1:", "*.wav");
    while ((res == FR_OK) && (finfo.fname[0] != '\0'))
    {
        log_i("%s", finfo.fname);
        res = f_findnext(&dir, &finfo);
        if(res != FR_OK)
        {
            break;
        }
    }
    return 0;
}

static int player_play_music(int argc, char *argv[])
{
    strcpy(music_path, argv[1]);
    player_state = PLAYER_SET;
    return 0;
}

static int player_stop_music(int argc, char *argv[])
{
    if(player_state != PLAYER_IDLE)
    {
        player_state = PLAYER_STOP;
    }
    return 0;
}

static int player_set_volume(int argc, char *argv[])
{
    int vol = atoi(argv[1]);
    Audio_SetVolume(vol);
    return 0;
}

ShellCommand playerGroup[] =
{
    SHELL_CMD_GROUP_ITEM(SHELL_TYPE_CMD_MAIN,
        list,
        player_list_music,
        player list\n\t List all music in root path),
    SHELL_CMD_GROUP_ITEM(SHELL_TYPE_CMD_MAIN,
        play, 
        player_play_music,
        player play *.wav),
    SHELL_CMD_GROUP_ITEM(SHELL_TYPE_CMD_MAIN,
        stop, 
        player_stop_music,
        player stop),
    SHELL_CMD_GROUP_ITEM(SHELL_TYPE_CMD_MAIN,
        vol, 
        player_set_volume,
        player vol\n\tvolume range [0-100]),
    SHELL_CMD_GROUP_END()
};
SHELL_EXPORT_CMD_GROUP(
    SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN)|SHELL_CMD_DISABLE_RETURN,
    player,
    playerGroup,
    player cmds);