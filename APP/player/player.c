#include "player.h"

#include "wav.h"
#include "audio.h"
#include "elog.h"
#include "shell_cmd_group.h"
#include "ff.h"

#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#define PLAY_STATE_IDLE 0
#define PLAY_STATE_LOAD 1
#define PLAY_STATE_SET  2
#define PLAY_STATE_PLAY 3
#define PLAY_STATE_HOLD 4
#define PLAY_STATE_STOP 5

#define PLAY_TEMP_BUFF_SIZE (8*1024)

typedef struct _play_state
{
    uint32_t state;
    uint32_t fs;
    uint32_t ch;
    uint32_t bits;
    uint32_t mpos;
    uint32_t msize;
    uint32_t current_seconds;
    uint32_t total_seconds;
    uint32_t buff_index;
    FIL      file;
    uint32_t fpos;
    uint8_t  buff[2][PLAY_TEMP_BUFF_SIZE];
} Play_State_t;
static Play_State_t play;

static char path_buff[64];

static void player_task(void *params)
{
    FRESULT res;
    UINT readout;

    play.state == PLAY_STATE_IDLE;

    res = f_chdir("1:");

    while(1)
    {
        if(play.state == PLAY_STATE_IDLE || (play.state == PLAY_STATE_HOLD))
        {
            vTaskDelay(100/portTICK_PERIOD_MS);
        }
        if(play.state == PLAY_STATE_LOAD)
        {
            if(0 != Player_Load(path_buff))
            {
                log_e("load: %s failed", path_buff);
            }
            play.state = PLAY_STATE_IDLE;
        }
        if(play.state == PLAY_STATE_SET)
        {
            //Move file read pointer to right pos for setting seconds.
            res = f_lseek(&play.file, play.fpos + play.mpos);
            play.state = PLAY_STATE_IDLE;
        }
        if(play.state == PLAY_STATE_PLAY)
        {
            res = f_read(&play.file, &play.buff[play.buff_index][0], PLAY_TEMP_BUFF_SIZE, &readout);
            play.mpos += readout;
            play.current_seconds = play.mpos / (play.fs * (play.bits / 8) * play.ch);

            if(res != FR_OK)
            {
                log_e("read: failed with code %d", (int)res);
                play.state = PLAY_STATE_STOP;
            }
            else
            {
                while(Audio_IsBusy());
                
                if(0 != Audio_Play(&play.buff[play.buff_index][0], readout, NULL))
                {
                    log_e("play: failed at ch %d when readout %d bytes", play.buff_index, readout);
                    play.state = PLAY_STATE_STOP;
                }

                play.buff_index = (play.buff_index == 0) ? 1 : 0;
                if(readout < PLAY_TEMP_BUFF_SIZE)
                {
                    play.state = PLAY_STATE_STOP;
                }
            }
        }
        if(play.state == PLAY_STATE_STOP)
        {
            res = f_close(&play.file);
            if(res != FR_OK)
            {
                log_e("close: failed!");
            }
            else
            {
                log_i("play: stoped!");
            }
            play.state = PLAY_STATE_IDLE;
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

int Player_Load(char *path)
{
    FRESULT res;
    WAV wav;

    if((play.state == PLAY_STATE_PLAY) || (play.state == PLAY_STATE_HOLD))
    {
        return -1;
    }

    res = f_open(&play.file, path, FA_READ);
    if(res != FR_OK)
    {
        log_e("Load file: %s faild!", path);
        return -1;
    }

    readWavInfo(&wav, &play.file);

    play.fpos = f_tell(&play.file); //Get where the music data start.

    play.fs   = wav.SampleRate;
    play.bits = wav.BitsPerSample;
    play.ch   = wav.NumChannels;
    play.msize = wav.ChunkSize;
    play.mpos  = 0;
    play.total_seconds = play.msize / (play.fs * (play.bits / 8) * play.ch);
    play.current_seconds = 0;

    Audio_SetFormat(play.fs, play.ch, play.bits);

    return 0;
}

void Player_Start(void)
{
    play.state = PLAY_STATE_PLAY;
}
void Player_Hold(void)
{
    play.state = PLAY_STATE_HOLD;
}
void Player_Stop(void)
{
    play.state = PLAY_STATE_STOP;
}

int Player_GetTotalSeconds(void)
{
    return (int)play.total_seconds;
}
int Player_GetCurrentSeconds(void)
{
    return (int)play.current_seconds;
}
int Player_SetToSeconds(int seconds)
{
    play.current_seconds = seconds;
    play.mpos = seconds * (play.fs * (play.bits / 8) * play.ch);
    
    play.state = PLAY_STATE_SET;

    return 0;
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
    strcpy(path_buff, argv[1]);
    play.state = PLAY_STATE_LOAD;
    return 0;
}

static int player_stop_music(int argc, char *argv[])
{
    Player_Stop();
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