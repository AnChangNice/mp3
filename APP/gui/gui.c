#include "gui.h"

#include "elog.h"

#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"

#include "backlight.h"
#include "audio.h"
#include "player.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

static lv_obj_t * backlight_label;

static void backlight_slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);

    Backlight_Update(lv_slider_get_value(slider));

    /*Refresh the text*/
    lv_label_set_text_fmt(backlight_label, "backlight %"LV_PRId32, lv_slider_get_value(slider));
    lv_obj_align_to(backlight_label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

/**
 * Create a slider and write its value on a label.
 */
void lv_backlight_control_slider(void)
{
    /*Create a slider in the center of the display*/
    lv_obj_t * slider = lv_slider_create(lv_scr_act());
    lv_slider_set_value(slider, 100, LV_ANIM_ON);
    lv_obj_set_width(slider, 200);                          /*Set the width*/
    lv_obj_center(slider);                                  /*Align to the center of the parent (screen)*/
    lv_obj_add_event_cb(slider, backlight_slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*Assign an event function*/

    /*Create a label below the slider*/
    backlight_label = lv_label_create(lv_scr_act());
    lv_label_set_text(backlight_label, "backlight 100");
    lv_obj_align_to(backlight_label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

static lv_obj_t * vol_label;

static void vol_slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);

    Audio_SetVolume(lv_slider_get_value(slider));

    /*Refresh the text*/
    lv_label_set_text_fmt(vol_label, "vol %"LV_PRId32, lv_slider_get_value(slider));
    lv_obj_align_to(vol_label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

/**
 * Create a slider and write its value on a label.
 */
void lv_player_vol_control_slider(void)
{
    /*Create a slider in the center of the display*/
    lv_obj_t * slider = lv_slider_create(lv_scr_act());
    lv_slider_set_value(slider, 100, LV_ANIM_ON);
    lv_obj_set_width(slider, 200);                          /*Set the width*/
    //lv_obj_center(slider);                                  /*Align to the center of the parent (screen)*/
    lv_obj_align_to(slider, backlight_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 100);
    lv_obj_add_event_cb(slider, vol_slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*Assign an event function*/

    /*Create a label below the slider*/
    vol_label = lv_label_create(lv_scr_act());
    lv_label_set_text(vol_label, "vol 100");
    lv_obj_align_to(vol_label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

static lv_obj_t * seconds_label;
static lv_obj_t * seconds_slider;

static void seconds_slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);

    Player_SetToSeconds(lv_slider_get_value(slider));

    /*Refresh the text*/
    lv_label_set_text_fmt(seconds_label, "seconds %"LV_PRId32"/%"LV_PRId32, Player_GetCurrentSeconds(), Player_GetTotalSeconds());
    lv_obj_align_to(seconds_label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

static void slider_timer_callback(lv_timer_t * timer)
{
    static int total_seconds = 0;

    if(total_seconds != Player_GetTotalSeconds())
    {
        total_seconds = Player_GetTotalSeconds();
        lv_slider_set_range(seconds_slider, 0, total_seconds);
    }

    lv_slider_set_value(seconds_slider, Player_GetCurrentSeconds(), LV_ANIM_OFF);
    lv_label_set_text_fmt(seconds_label, "seconds %"LV_PRId32"/%"LV_PRId32, Player_GetCurrentSeconds(), total_seconds);
}

/**
 * Create a slider and write its value on a label.
 */
void lv_player_seconds_control_slider(void)
{
    /*Create a slider in the center of the display*/
    seconds_slider = lv_slider_create(lv_scr_act());
    lv_slider_set_value(seconds_slider, 0, LV_ANIM_ON);
    lv_obj_set_width(seconds_slider, 200);                          /*Set the width*/
    //lv_obj_center(slider);                                  /*Align to the center of the parent (screen)*/
    lv_obj_align_to(seconds_slider, backlight_label, LV_ALIGN_OUT_BOTTOM_MID, 0, -100);
    lv_obj_add_event_cb(seconds_slider, seconds_slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*Assign an event function*/

    /*Create a label below the slider*/
    seconds_label = lv_label_create(lv_scr_act());
    lv_label_set_text(seconds_label, "seconds 0");
    lv_obj_align_to(seconds_label, seconds_slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/

    //Create a timer for
    lv_timer_t * timer = lv_timer_create(slider_timer_callback, 1000, NULL);
}

static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        static uint8_t state = 0;
        state = (state == 0) ? 1 : 0;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        if(state == 1)
        {
            lv_label_set_text_fmt(label, "Hold");
            Player_Start();
        }
        else
        {
            lv_label_set_text_fmt(label, "Play");
            Player_Hold();
        }
    }
}

/**
 * Create a button with a label and react on click event.
 */
void lv_play_button(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Play");                     /*Set the labels text*/
    lv_obj_center(label);
}



static void gui_task(void *params)
{
    //lvgl init
    lv_init();
    
    //Init display,touchpad,backlight
    lv_port_disp_init();
    lv_port_indev_init();

    //widgets init.
    lv_backlight_control_slider();
    lv_player_vol_control_slider();
    lv_player_seconds_control_slider();
    lv_play_button();

    for(;;)
    {
        lv_timer_handler();
        vTaskDelay(5/portTICK_PERIOD_MS);
    }
}

void Gui_Init(void)
{
    //Create gui_task
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;

    xReturned = xTaskCreate(
                    gui_task,
                    "gui_task",
                    2048/4,
                    NULL,
                    tskIDLE_PRIORITY+1,
                    &xHandle);

    if(xReturned != pdPASS)
    {
        log_e("gui_task create failed!");
    }
}