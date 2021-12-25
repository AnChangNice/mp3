#include "elog.h"
#include "shell_port.h"
#include "ff.h"
#include "player.h"
#include "audio.h"
#include "gui.h"

#include "FreeRTOS.h"
#include "task.h"

static void elog_init_before_app(void)
{
    /* initialize EasyLogger */
    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    /* start EasyLogger */
    elog_start();
}

static FATFS fs; //put file system handle here.

static void app_init_task(void *params)
{

    //letter-shell init
    shell_port_init();

    //FatFs
    FRESULT res = f_mount(&fs, "1:", 1);
    if(res != FR_OK)
    {
        log_e("f_mount failed with return %d", (int)res);
    }

    //Audio init
    Audio_Init();
    Audio_SetVolume(100);

    //Player Init
    Player_Init();

    //Gui init
    Gui_Init();

    //Delect current task.
    vTaskDelete(xTaskGetCurrentTaskHandle());
}

void app_main(void)
{
    //Create app_init_task
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;

    //easylogger init before anyother tasks.
    elog_init_before_app();

    xReturned = xTaskCreate(
                    app_init_task,
                    "app_init_task",
                    1024/4,
                    NULL,
                    tskIDLE_PRIORITY+1,
                    &xHandle);

    if(xReturned != pdPASS)
    {
        log_e("app_init_task create failed!");
    }

    //Start FreeRTOS here.
    vTaskStartScheduler();
}