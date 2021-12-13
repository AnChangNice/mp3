##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.13.0-B3] date: [Mon Dec 13 22:51:26 CST 2021] 
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
Middlewares/Third_Party/lvgl/port/lv_port_disp.c \
Middlewares/Third_Party/lvgl/port/lv_port_fs.c \
Middlewares/Third_Party/lvgl/port/lv_port_indev.c \
Middlewares/Third_Party/lvgl/src/core/lv_disp.c \
Middlewares/Third_Party/lvgl/src/core/lv_event.c \
Middlewares/Third_Party/lvgl/src/core/lv_group.c \
Middlewares/Third_Party/lvgl/src/core/lv_indev.c \
Middlewares/Third_Party/lvgl/src/core/lv_indev_scroll.c \
Middlewares/Third_Party/lvgl/src/core/lv_obj.c \
Middlewares/Third_Party/lvgl/src/core/lv_obj_class.c \
Middlewares/Third_Party/lvgl/src/core/lv_obj_draw.c \
Middlewares/Third_Party/lvgl/src/core/lv_obj_pos.c \
Middlewares/Third_Party/lvgl/src/core/lv_obj_scroll.c \
Middlewares/Third_Party/lvgl/src/core/lv_obj_style.c \
Middlewares/Third_Party/lvgl/src/core/lv_obj_style_gen.c \
Middlewares/Third_Party/lvgl/src/core/lv_obj_tree.c \
Middlewares/Third_Party/lvgl/src/core/lv_refr.c \
Middlewares/Third_Party/lvgl/src/core/lv_theme.c \
Middlewares/Third_Party/lvgl/src/draw/lv_draw_arc.c \
Middlewares/Third_Party/lvgl/src/draw/lv_draw_blend.c \
Middlewares/Third_Party/lvgl/src/draw/lv_draw_img.c \
Middlewares/Third_Party/lvgl/src/draw/lv_draw_label.c \
Middlewares/Third_Party/lvgl/src/draw/lv_draw_line.c \
Middlewares/Third_Party/lvgl/src/draw/lv_draw_mask.c \
Middlewares/Third_Party/lvgl/src/draw/lv_draw_rect.c \
Middlewares/Third_Party/lvgl/src/draw/lv_draw_triangle.c \
Middlewares/Third_Party/lvgl/src/draw/lv_img_buf.c \
Middlewares/Third_Party/lvgl/src/draw/lv_img_cache.c \
Middlewares/Third_Party/lvgl/src/draw/lv_img_decoder.c \
Middlewares/Third_Party/lvgl/src/extra/layouts/flex/lv_flex.c \
Middlewares/Third_Party/lvgl/src/extra/layouts/grid/lv_grid.c \
Middlewares/Third_Party/lvgl/src/extra/libs/bmp/lv_bmp.c \
Middlewares/Third_Party/lvgl/src/extra/libs/freetype/lv_freetype.c \
Middlewares/Third_Party/lvgl/src/extra/libs/fsdrv/lv_fs_fatfs.c \
Middlewares/Third_Party/lvgl/src/extra/libs/fsdrv/lv_fs_posix.c \
Middlewares/Third_Party/lvgl/src/extra/libs/fsdrv/lv_fs_stdio.c \
Middlewares/Third_Party/lvgl/src/extra/libs/fsdrv/lv_fs_win32.c \
Middlewares/Third_Party/lvgl/src/extra/libs/gif/gifdec.c \
Middlewares/Third_Party/lvgl/src/extra/libs/gif/lv_gif.c \
Middlewares/Third_Party/lvgl/src/extra/libs/png/lodepng.c \
Middlewares/Third_Party/lvgl/src/extra/libs/png/lv_png.c \
Middlewares/Third_Party/lvgl/src/extra/libs/qrcode/lv_qrcode.c \
Middlewares/Third_Party/lvgl/src/extra/libs/qrcode/qrcodegen.c \
Middlewares/Third_Party/lvgl/src/extra/libs/rlottie/lv_rlottie.c \
Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/lv_sjpg.c \
Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/tjpgd.c \
Middlewares/Third_Party/lvgl/src/extra/lv_extra.c \
Middlewares/Third_Party/lvgl/src/extra/others/snapshot/lv_snapshot.c \
Middlewares/Third_Party/lvgl/src/extra/themes/basic/lv_theme_basic.c \
Middlewares/Third_Party/lvgl/src/extra/themes/default/lv_theme_default.c \
Middlewares/Third_Party/lvgl/src/extra/themes/mono/lv_theme_mono.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/animimg/lv_animimg.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/calendar/lv_calendar.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/chart/lv_chart.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/colorwheel/lv_colorwheel.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/imgbtn/lv_imgbtn.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/keyboard/lv_keyboard.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/led/lv_led.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/list/lv_list.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/meter/lv_meter.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/msgbox/lv_msgbox.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/span/lv_span.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/spinbox/lv_spinbox.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/lv_spinner.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/tabview/lv_tabview.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/tileview/lv_tileview.c \
Middlewares/Third_Party/lvgl/src/extra/widgets/win/lv_win.c \
Middlewares/Third_Party/lvgl/src/font/lv_font.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_dejavu_16_persian_hebrew.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_fmt_txt.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_loader.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_10.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_12.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_12_subpx.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_14.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_16.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_18.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_20.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_22.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_24.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_26.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_28.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_28_compressed.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_30.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_32.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_34.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_36.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_38.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_40.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_42.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_44.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_46.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_48.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_montserrat_8.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_simsun_16_cjk.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_unscii_16.c \
Middlewares/Third_Party/lvgl/src/font/lv_font_unscii_8.c \
Middlewares/Third_Party/lvgl/src/gpu/lv_gpu_nxp_pxp.c \
Middlewares/Third_Party/lvgl/src/gpu/lv_gpu_nxp_pxp_osa.c \
Middlewares/Third_Party/lvgl/src/gpu/lv_gpu_nxp_vglite.c \
Middlewares/Third_Party/lvgl/src/gpu/lv_gpu_sdl.c \
Middlewares/Third_Party/lvgl/src/gpu/lv_gpu_stm32_dma2d.c \
Middlewares/Third_Party/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_arc.c \
Middlewares/Third_Party/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_blend.c \
Middlewares/Third_Party/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_img.c \
Middlewares/Third_Party/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_label.c \
Middlewares/Third_Party/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_line.c \
Middlewares/Third_Party/lvgl/src/gpu/sdl/lv_gpu_sdl_draw_rect.c \
Middlewares/Third_Party/lvgl/src/gpu/sdl/lv_gpu_sdl_lru.c \
Middlewares/Third_Party/lvgl/src/gpu/sdl/lv_gpu_sdl_mask.c \
Middlewares/Third_Party/lvgl/src/gpu/sdl/lv_gpu_sdl_stack_blur.c \
Middlewares/Third_Party/lvgl/src/gpu/sdl/lv_gpu_sdl_texture_cache.c \
Middlewares/Third_Party/lvgl/src/gpu/sdl/lv_gpu_sdl_utils.c \
Middlewares/Third_Party/lvgl/src/hal/lv_hal_disp.c \
Middlewares/Third_Party/lvgl/src/hal/lv_hal_indev.c \
Middlewares/Third_Party/lvgl/src/hal/lv_hal_tick.c \
Middlewares/Third_Party/lvgl/src/misc/lv_anim.c \
Middlewares/Third_Party/lvgl/src/misc/lv_anim_timeline.c \
Middlewares/Third_Party/lvgl/src/misc/lv_area.c \
Middlewares/Third_Party/lvgl/src/misc/lv_async.c \
Middlewares/Third_Party/lvgl/src/misc/lv_bidi.c \
Middlewares/Third_Party/lvgl/src/misc/lv_color.c \
Middlewares/Third_Party/lvgl/src/misc/lv_fs.c \
Middlewares/Third_Party/lvgl/src/misc/lv_gc.c \
Middlewares/Third_Party/lvgl/src/misc/lv_ll.c \
Middlewares/Third_Party/lvgl/src/misc/lv_log.c \
Middlewares/Third_Party/lvgl/src/misc/lv_math.c \
Middlewares/Third_Party/lvgl/src/misc/lv_mem.c \
Middlewares/Third_Party/lvgl/src/misc/lv_printf.c \
Middlewares/Third_Party/lvgl/src/misc/lv_style.c \
Middlewares/Third_Party/lvgl/src/misc/lv_style_gen.c \
Middlewares/Third_Party/lvgl/src/misc/lv_templ.c \
Middlewares/Third_Party/lvgl/src/misc/lv_timer.c \
Middlewares/Third_Party/lvgl/src/misc/lv_tlsf.c \
Middlewares/Third_Party/lvgl/src/misc/lv_txt.c \
Middlewares/Third_Party/lvgl/src/misc/lv_txt_ap.c \
Middlewares/Third_Party/lvgl/src/misc/lv_utils.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_arc.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_bar.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_btn.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_btnmatrix.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_canvas.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_checkbox.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_dropdown.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_img.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_label.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_line.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_objx_templ.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_roller.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_slider.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_switch.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_table.c \
Middlewares/Third_Party/lvgl/src/widgets/lv_textarea.c \
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
-IMiddlewares/Third_Party/lvgl \
-IMiddlewares/Third_Party/lvgl/port \
-IMiddlewares/Third_Party/lvgl/src \
-IMiddlewares/Third_Party/lvgl/src/core \
-IMiddlewares/Third_Party/lvgl/src/draw \
-IMiddlewares/Third_Party/lvgl/src/extra \
-IMiddlewares/Third_Party/lvgl/src/extra/layouts \
-IMiddlewares/Third_Party/lvgl/src/extra/layouts/flex \
-IMiddlewares/Third_Party/lvgl/src/extra/layouts/grid \
-IMiddlewares/Third_Party/lvgl/src/extra/libs \
-IMiddlewares/Third_Party/lvgl/src/extra/libs/bmp \
-IMiddlewares/Third_Party/lvgl/src/extra/libs/freetype \
-IMiddlewares/Third_Party/lvgl/src/extra/libs/fsdrv \
-IMiddlewares/Third_Party/lvgl/src/extra/libs/gif \
-IMiddlewares/Third_Party/lvgl/src/extra/libs/png \
-IMiddlewares/Third_Party/lvgl/src/extra/libs/qrcode \
-IMiddlewares/Third_Party/lvgl/src/extra/libs/rlottie \
-IMiddlewares/Third_Party/lvgl/src/extra/libs/sjpg \
-IMiddlewares/Third_Party/lvgl/src/extra/others \
-IMiddlewares/Third_Party/lvgl/src/extra/others/snapshot \
-IMiddlewares/Third_Party/lvgl/src/extra/themes \
-IMiddlewares/Third_Party/lvgl/src/extra/themes/basic \
-IMiddlewares/Third_Party/lvgl/src/extra/themes/default \
-IMiddlewares/Third_Party/lvgl/src/extra/themes/mono \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/animimg \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/calendar \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/chart \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/colorwheel \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/imgbtn \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/keyboard \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/led \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/list \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/meter \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/msgbox \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/span \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/spinbox \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/spinner \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/tabview \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/tileview \
-IMiddlewares/Third_Party/lvgl/src/extra/widgets/win \
-IMiddlewares/Third_Party/lvgl/src/font \
-IMiddlewares/Third_Party/lvgl/src/gpu \
-IMiddlewares/Third_Party/lvgl/src/gpu/sdl \
-IMiddlewares/Third_Party/lvgl/src/hal \
-IMiddlewares/Third_Party/lvgl/src/misc \
-IMiddlewares/Third_Party/lvgl/src/widgets \
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
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)

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
	@arm-none-eabi-size $(OBJECTS) -t

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
