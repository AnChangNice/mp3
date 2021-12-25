#include "gui.h"

#include "elog.h"

#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"

#include "backlight.h"
#include "audio.h"

#include "FreeRTOS.h"
#include "task.h"

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