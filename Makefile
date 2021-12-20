##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.13.0-B3] date: [Sun Dec 19 01:57:31 CST 2021] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = mp3


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rtc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rtc_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sai.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sai_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sdram.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma2d.c \
Middlewares/lvgl/port/lv_port_disp.c \
Middlewares/lvgl/port/lv_port_fs.c \
Middlewares/lvgl/port/lv_port_indev.c \
Middlewares/lvgl/src/core/lv_disp.c \
Middlewares/lvgl/src/core/lv_event.c \
Middlewares/lvgl/src/core/lv_group.c \
Middlewares/lvgl/src/core/lv_indev.c \
Middlewares/lvgl/src/core/lv_indev_scroll.c \
Middlewares/lvgl/src/core/lv_obj.c \
Middlewares/lvgl/src/core/lv_obj_class.c \
Middlewares/lvgl/src/core/lv_obj_draw.c \
Middlewares/lvgl/src/core/lv_obj_pos.c \
Middlewares/lvgl/src/core/lv_obj_scroll.c \
Middlewares/lvgl/src/core/lv_obj_style.c \
Middlewares/lvgl/src/core/lv_obj_style_gen.c \
Middlewares/lvgl/src/core/lv_obj_tree.c \
Middlewares/lvgl/src/core/lv_refr.c \
Middlewares/lvgl/src/core/lv_theme.c \
Middlewares/lvgl/src/draw/lv_draw_arc.c \
Middlewares/lvgl/src/draw/lv_draw_blend.c \
Middlewares/lvgl/src/draw/lv_draw_img.c \
Middlewares/lvgl/src/draw/lv_draw_label.c \
Middlewares/lvgl/src/draw/lv_draw_line.c \
Middlewares/lvgl/src/draw/lv_draw_mask.c \
Middlewares/lvgl/src/draw/lv_draw_rect.c \
Middlewares/lvgl/src/draw/lv_draw_triangle.c \
Middlewares/lvgl/src/draw/lv_img_buf.c \
Middlewares/lvgl/src/draw/lv_img_cache.c \
Middlewares/lvgl/src/draw/lv_img_decoder.c \
Middlewares/lvgl/src/extra/layouts/flex/lv_flex.c \
Middlewares/lvgl/src/extra/layouts/grid/lv_grid.c \
Middlewares/lvgl/src/extra/libs/bmp/lv_bmp.c \
Middlewares/lvgl/src/extra/libs/freetype/lv_freetype.c \
Middlewares/lvgl/src/extra/libs/fsdrv/lv_fs_fatfs.c \
Middlewares/lvgl/src/extra/libs/fsdrv/lv_fs_posix.c \
Middlewares/lvgl/src/extra/libs/fsdrv/lv_fs_stdio.c \
Middlewares/lvgl/src/extra/libs/fsdrv/lv_fs_win32.c \
Middlewares/lvgl/src/extra/libs/gif/gifdec.c \
Middlewares/lvgl/src/extra/libs/gif/lv_gif.c \
Middlewares/lvgl/src/extra/libs/png/lodepng.c \
Middlewares/lvgl/src/extra/libs/png/lv_png.c \
Middlewares/lvgl/src/extra/libs/qrcode/lv_qrcode.c \
Middlewares/lvgl/src/extra/libs/qrcode/qrcodegen.c \
Middlewares/lvgl/src/extra/libs/rlottie/lv_rlottie.c \
Middlewares/lvgl/src/extra/libs/sjpg/lv_sjpg.c \
Middlewares/lvgl/src/extra/libs/sjpg/tjpgd.c \
Middlewares/lvgl/src/extra/lv_extra.c \
Middlewares/lvgl/src/extra/others/snapshot/lv_snapshot.c \
Middlewares/lvgl/src/extra/themes/basic/lv_theme_basic.c \
Middlewares/lvgl/src/extra/themes/default/lv_theme_default.c \
Middlewares/lvgl/src/extra/themes/mono/lv_theme_mono.c \
Middlewares/lvgl/src/extra/widgets/animimg/lv_animimg.c \
Middlewares/lvgl/src/extra/widgets/calendar/lv_calendar.c \
Middlewares/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.c \
Middlewares/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.c \
Middlewares/lvgl/src/extra/widgets/chart/lv_chart.c \
Middlewares/lvgl/src/extra/widgets/colorwheel/lv_colorwheel.c \
Middlewares/lvgl/src/extra/widgets/imgbtn/lv_imgbtn.c \
Middlewares/lvgl/src/extra/widgets/keyboard/lv_keyboard.c \
Middlewares/lvgl/src/extra/widgets/led/lv_led.c \
Middlewares/lvgl/src/extra/widgets/list/lv_list.c \
Middlewares/lvgl/src/extra/widgets/meter/lv_meter.c \
Middlewares/lvgl/src/extra/widgets/msgbox/lv_msgbox.c \
Middlewares/lvgl/src/extra/widgets/span/lv_span.c \
Middlewares/lvgl/src/extra/widgets/spinbox/lv_spinbox.c \
Middlewares/lvgl/src/extra/widgets/spinner/lv_spinner.c \
Middlewares/lvgl/src/extra/widgets/tabview/lv_tabview.c \
Middlewares/lvgl/src/extra/widgets/tileview/lv_tileview.c \
Middlewares/lvgl/src/extra/widgets/win/lv_win.c \
Middlewares/lvgl/src/font/lv_font.c \
Middlewares/lvgl/src/font/lv_font_dejavu_16_persian_hebrew.c \
Middlewares/lvgl/src/font/lv_font_fmt_txt.c \
Middlewares/lvgl/src/font/lv_font_loader.c \
Middlewares/lvgl/src/font/lv_font_montserrat_10.c \
Middlewares/lvgl/src/font/lv_font_montserrat_12.c \
Middlewares/lvgl/src/font/lv_font_montserrat_12_subpx.c \
Middlewares/lvgl/src/font/lv_font_montserrat_14.c \
Middlewares/lvgl/src/font/lv_font_montserrat_16.c \
Middlewares/lvgl/src/font/lv_font_montserrat_18.c \
Middlewares/lvgl/src/font/lv_font_montserrat_20.c \
Middlewares/lvgl/src/font/lv_font_montserrat_22.c \
Middlewares/lvgl/src/font/lv_font_montserrat_24.c \
Middlewares/lvgl/src/font/lv_font_montserrat_26.c \
Middlewares/lvgl/src/font/lv_font_montserrat_28.c \
Middlewares/lvgl/src/font/lv_font_montserrat_28_compressed.c \
Middlewares/lvgl/src/font/lv_font_montserrat_30.c \
Middlewares/lvgl/src/font/lv_font_montserrat_32.c \
Middlewares/lvgl/src/font/lv_font_montserrat_34.c \
Middlewares/lvgl/src/font/lv_font_montserrat_36.c \
Middlewares/lvgl/src/font/lv_font_montserrat_38.c \
Middlewares/lvgl/src/font/lv_font_montserrat_40.c \
Middlewares/lvgl/src/font/lv_font_montserrat_42.c \
Middlewares/lvgl/src/font/lv_font_montserrat_44.c \
Middlewares/lvgl/src/font/lv_font_montserrat_46.c \
Middlewares/lvgl/src/font/lv_font_montserrat_48.c \
Middlewares/lvgl/src/font/lv_font_montserrat_8.c \
Middlewares/lvgl/src/font/lv_font_simsun_16_cjk.c \
Middlewares/lvgl/src/font/lv_font_unscii_16.c \
Middlewares/lvgl/src/font/lv_font_unscii_8.c \
Middlewares/lvgl/src/gpu/lv_gpu_nxp_pxp.c \
Middlewares/lvgl/src/gpu/lv_gpu_nxp_pxp_osa.c \
Middlewares/lvgl/src/gpu/lv_gpu_nxp_vglite.c \
Middlewares/lvgl/src/gpu/lv_gpu_sdl.c \
Middlewares/lvgl/src/gpu/lv_gpu_stm32_dma2d.c \
Middlewares/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_arc.c \
Middlewares/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_blend.c \
Middlewares/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_img.c \
Middlewares/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_label.c \
Middlewares/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_line.c \
Middlewares/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_rect.c \
Middlewares/lvgl/src/gpu/sdl/lv_gpu_sdl_lru.c \
Middlewares/lvgl/src/gpu/sdl/lv_gpu_sdl_mask.c \
Middlewares/lvgl/src/gpu/sdl/lv_gpu_sdl_stack_blur.c \
Middlewares/lvgl/src/gpu/sdl/lv_gpu_sdl_texture_cache.c \
Middlewares/lvgl/src/gpu/sdl/lv_gpu_sdl_utils.c \
Middlewares/lvgl/src/hal/lv_hal_disp.c \
Middlewares/lvgl/src/hal/lv_hal_indev.c \
Middlewares/lvgl/src/hal/lv_hal_tick.c \
Middlewares/lvgl/src/misc/lv_anim.c \
Middlewares/lvgl/src/misc/lv_anim_timeline.c \
Middlewares/lvgl/src/misc/lv_area.c \
Middlewares/lvgl/src/misc/lv_async.c \
Middlewares/lvgl/src/misc/lv_bidi.c \
Middlewares/lvgl/src/misc/lv_color.c \
Middlewares/lvgl/src/misc/lv_fs.c \
Middlewares/lvgl/src/misc/lv_gc.c \
Middlewares/lvgl/src/misc/lv_ll.c \
Middlewares/lvgl/src/misc/lv_log.c \
Middlewares/lvgl/src/misc/lv_math.c \
Middlewares/lvgl/src/misc/lv_mem.c \
Middlewares/lvgl/src/misc/lv_printf.c \
Middlewares/lvgl/src/misc/lv_style.c \
Middlewares/lvgl/src/misc/lv_style_gen.c \
Middlewares/lvgl/src/misc/lv_templ.c \
Middlewares/lvgl/src/misc/lv_timer.c \
Middlewares/lvgl/src/misc/lv_tlsf.c \
Middlewares/lvgl/src/misc/lv_txt.c \
Middlewares/lvgl/src/misc/lv_txt_ap.c \
Middlewares/lvgl/src/misc/lv_utils.c \
Middlewares/lvgl/src/widgets/lv_arc.c \
Middlewares/lvgl/src/widgets/lv_bar.c \
Middlewares/lvgl/src/widgets/lv_btn.c \
Middlewares/lvgl/src/widgets/lv_btnmatrix.c \
Middlewares/lvgl/src/widgets/lv_canvas.c \
Middlewares/lvgl/src/widgets/lv_checkbox.c \
Middlewares/lvgl/src/widgets/lv_dropdown.c \
Middlewares/lvgl/src/widgets/lv_img.c \
Middlewares/lvgl/src/widgets/lv_label.c \
Middlewares/lvgl/src/widgets/lv_line.c \
Middlewares/lvgl/src/widgets/lv_objx_templ.c \
Middlewares/lvgl/src/widgets/lv_roller.c \
Middlewares/lvgl/src/widgets/lv_slider.c \
Middlewares/lvgl/src/widgets/lv_switch.c \
Middlewares/lvgl/src/widgets/lv_table.c \
Middlewares/lvgl/src/widgets/lv_textarea.c \
Middlewares/FatFs/src/diskio.c \
Middlewares/FatFs/src/ff.c \
Middlewares/FatFs/src/ffsystem.c \
Middlewares/FatFs/src/ffunicode.c \
Middlewares/FatFs/port/mmc_diskio.c \
Middlewares/FatFs/port/ff_fattime.c \
Middlewares/FreeRTOS/croutine.c \
Middlewares/FreeRTOS/event_groups.c \
Middlewares/FreeRTOS/list.c \
Middlewares/FreeRTOS/portable/GCC/ARM_CM4F/port.c \
Middlewares/FreeRTOS/portable/MemMang/heap_4.c \
Middlewares/FreeRTOS/queue.c \
Middlewares/FreeRTOS/stream_buffer.c \
Middlewares/FreeRTOS/tasks.c \
Middlewares/FreeRTOS/timers.c \
Middlewares/easylogger/port/elog_port.c \
Middlewares/easylogger/src/elog.c \
Middlewares/easylogger/src/elog_async.c \
Middlewares/easylogger/src/elog_buf.c \
Middlewares/easylogger/src/elog_utils.c \
Middlewares/letter_shell/src/shell.c \
Middlewares/letter_shell/src/shell_cmd_list.c \
Middlewares/letter_shell/src/shell_companion.c \
Middlewares/letter_shell/src/shell_ext.c \
Middlewares/letter_shell/port/shell_port.c \
Core/Src/stm32h7xx_it.c \
Core/Src/stm32h7xx_hal_msp.c \
Core/Src/stm32h7xx_hal_timebase_tim.c \
Core/Src/system_stm32h7xx.c \
Core/Src/sdmmc.c \
Core/Src/spi.c \
Core/Src/fmc.c \
Core/Src/i2c.c \
Core/Src/dma.c \
Core/Src/sai.c \
Core/Src/main.c \
Core/Src/gpio.c \
Core/Src/rtc.c \
Core/Src/usart.c \
Core/Src/dma2d.c \
Drivers/IC/wm8988/wm8988.c \
Drivers/IC/wm8988/wm8988_sai.c \
Drivers/IC/aw9364/aw9364.c \
Drivers/IC/ili9488/ili9488.c \
Drivers/IC/ft6236/ft6236.c \
Drivers/IC/w9825g6kh6/w9825g6kh6.c \
BSP/touchpad/touchpad.c \
BSP/display/display.c \
BSP/backlight/backlight.c \
BSP/sdram/sdram.c \
BSP/audio/audio.c

# ASM sources
ASM_SOURCES =  \
startup_stm32h750xx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m7

# fpu
FPU = -mfpu=fpv5-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32H750xx \
-DSTM32H7


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-IDrivers/STM32H7xx_HAL_Driver/Inc \
-IDrivers/STM32H7xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32H7xx/Include \
-IDrivers/CMSIS/Include \
-IMiddlewares/lvgl \
-IMiddlewares/lvgl/port \
-IMiddlewares/lvgl/src \
-IMiddlewares/lvgl/src/core \
-IMiddlewares/lvgl/src/draw \
-IMiddlewares/lvgl/src/extra \
-IMiddlewares/lvgl/src/extra/layouts \
-IMiddlewares/lvgl/src/extra/layouts/flex \
-IMiddlewares/lvgl/src/extra/layouts/grid \
-IMiddlewares/lvgl/src/extra/libs \
-IMiddlewares/lvgl/src/extra/libs/bmp \
-IMiddlewares/lvgl/src/extra/libs/freetype \
-IMiddlewares/lvgl/src/extra/libs/fsdrv \
-IMiddlewares/lvgl/src/extra/libs/gif \
-IMiddlewares/lvgl/src/extra/libs/png \
-IMiddlewares/lvgl/src/extra/libs/qrcode \
-IMiddlewares/lvgl/src/extra/libs/rlottie \
-IMiddlewares/lvgl/src/extra/libs/sjpg \
-IMiddlewares/lvgl/src/extra/others \
-IMiddlewares/lvgl/src/extra/others/snapshot \
-IMiddlewares/lvgl/src/extra/themes \
-IMiddlewares/lvgl/src/extra/themes/basic \
-IMiddlewares/lvgl/src/extra/themes/default \
-IMiddlewares/lvgl/src/extra/themes/mono \
-IMiddlewares/lvgl/src/extra/widgets \
-IMiddlewares/lvgl/src/extra/widgets/animimg \
-IMiddlewares/lvgl/src/extra/widgets/calendar \
-IMiddlewares/lvgl/src/extra/widgets/chart \
-IMiddlewares/lvgl/src/extra/widgets/colorwheel \
-IMiddlewares/lvgl/src/extra/widgets/imgbtn \
-IMiddlewares/lvgl/src/extra/widgets/keyboard \
-IMiddlewares/lvgl/src/extra/widgets/led \
-IMiddlewares/lvgl/src/extra/widgets/list \
-IMiddlewares/lvgl/src/extra/widgets/meter \
-IMiddlewares/lvgl/src/extra/widgets/msgbox \
-IMiddlewares/lvgl/src/extra/widgets/span \
-IMiddlewares/lvgl/src/extra/widgets/spinbox \
-IMiddlewares/lvgl/src/extra/widgets/spinner \
-IMiddlewares/lvgl/src/extra/widgets/tabview \
-IMiddlewares/lvgl/src/extra/widgets/tileview \
-IMiddlewares/lvgl/src/extra/widgets/win \
-IMiddlewares/lvgl/src/font \
-IMiddlewares/lvgl/src/gpu \
-IMiddlewares/lvgl/src/gpu/sdl \
-IMiddlewares/lvgl/src/hal \
-IMiddlewares/lvgl/src/misc \
-IMiddlewares/lvgl/src/widgets \
-IMiddlewares/FatFs \
-IMiddlewares/FatFs/src \
-IMiddlewares/FatFs/port \
-IMiddlewares/FreeRTOS \
-IMiddlewares/FreeRTOS/include \
-IMiddlewares/FreeRTOS/portable/GCC/ARM_CM4F \
-IMiddlewares/easylogger/inc \
-IMiddlewares/letter_shell \
-IMiddlewares/letter_shell/src \
-IMiddlewares/letter_shell/port \
-ICore/Inc \
-IDrivers/IC/wm8988 \
-IDrivers/IC/aw9364 \
-IDrivers/IC/ili9488 \
-IDrivers/IC/ft6236 \
-IDrivers/IC/w9825g6kh6 \
-IBSP/touchpad \
-IBSP/display \
-IBSP/backlight \
-IBSP/sdram \
-IBSP/audio

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32H750XBHx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
#all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
all: $(BUILD_DIR)/$(TARGET).elf

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
#$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
#	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# build options
#######################################
debug:
	make -j8 OPT=-O0 > log.txt

release:
	make -j8 > log.txt

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
	-rm log.txt

#######################################
# info
#######################################
hexinfo:
	bincopy info $(BUILD_DIR)/$(TARGET).hex

hexdump:
	bincopy as_hexdump $(BUILD_DIR)/mp3.hex > $(BUILD_DIR)/$(TARGET)_hexdump.txt

sections:
	arm-none-eabi-size $(BUILD_DIR)/$(TARGET).elf -A -x

size:
	@arm-none-eabi-size $(BUILD_DIR)/$(TARGET).elf

allsize:
	@arm-none-eabi-size $(OBJECTS) -t

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
