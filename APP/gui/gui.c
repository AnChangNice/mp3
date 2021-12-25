#include "gui.h"

#include "elog.h"

#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"

#include "backlight.h"

#include "FreeRTOS.h"
#include "task.h"

static lv_obj_t * label;

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);

    Backlight_Update(lv_slider_get_value(slider));

    /*Refresh the text*/
    lv_label_set_text_fmt(label, "%"LV_PRId32, lv_slider_get_value(slider));
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

/**
 * Create a slider and write its value on a label.
 */
void lv_backlight_control_slider(void)
{
    /*Create a slider in the center of the display*/
    lv_obj_t * slider = lv_slider_create(lv_scr_act());
    lv_obj_set_width(slider, 200);                          /*Set the width*/
    lv_obj_center(slider);                                  /*Align to the center of the parent (screen)*/
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*Assign an event function*/

    /*Create a label below the slider*/
    label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "0");
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
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