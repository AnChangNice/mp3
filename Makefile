
# 编译输出目录
BUILD_PATH = build

# 最终目标
TARGET_ELF = $(BUILD_PATH)/main.elf

# 编译器选择
CC = arm-none-eabi-gcc

# 编译选项设置
CC_OPTIONS  = \
	-g -O0 -Wall -Wextra -Warray-bounds -Wno-unused-parameter\
	-mcpu=cortex-m7 -mthumb -mlittle-endian -mthumb-interwork\
	-mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs -lc -lm

CC_DEFINE_LISTS = \
	USE_HAL_DRIVER\
	STM32H750xx

#自动给所有的宏定义加前缀
CC_DEFINES = $(addprefix -D, ${CC_DEFINE_LISTS})

CC_FLAGS = \
	$(CC_OPTIONS)\
	$(CC_DEFINES)

# 头文件路径
CC_HEADER_PATH = \
	Drivers/CMSIS/Include\
	Drivers/CMSIS/Device/Include\
	Drivers/STM32H7xx_HAL_Driver\
	Drivers/STM32H7xx_HAL_Driver/Inc\
	Drivers/STM32H7xx_HAL_Driver/Inc/Legacy

#自动给所有的头文件路径加前缀
CC_INCLUDE = $(addprefix -I, ${CC_HEADER_PATH})

# 源文件
ASM_FILE = \
	Drivers/CMSIS/Device/Source/gcc/startup_stm32h750xx.s

CXX_FILES = \
	Drivers/CMSIS/Device/Source/system_stm32h7xx.c\
	Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c\
	Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c\
	Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c\
	Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c\
	Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c\
	Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c\
	APP/main.c

# 链接脚本
LINKER_FILE = Drivers/CMSIS/Device/Source/gcc/STM32H750XBHX_FLASH.ld

LINKER_FLAGS = -Wl,--gc-sections -Wl,-T$(LINKER_FILE)

# 编译
CXX_OBJS_FILES = $(CXX_FILES:.c=.o)
CXX_OBJS = $(addprefix $(BUILD_PATH)/, ${CXX_OBJS_FILES})

DEPENDENCYS = $(CXX_OBJS:.o=.d)

ASM_OBJS_FILES = $(ASM_FILE:.s=.o)
ASM_OBJS = $(addprefix $(BUILD_PATH)/, ${ASM_OBJS_FILES})


ALL_OBJS = $(CXX_OBJS) $(ASM_OBJS) 

.PHONY: all
all: $(TARGET_ELF)

# 由 *.c 生成 *.o 的命令
$(CXX_OBJS): $(BUILD_PATH)/%.o:%.c
	@echo Compile $<
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) $(CC_INCLUDE) -c $< -o $@

# 由 *.s 生成 *.o 的命令
$(ASM_OBJS): $(BUILD_PATH)/%.o:%.s
	@echo Compile $<
	@mkdir -p $(dir $@)
	@$(CC) $(ASM_FLAGS) $(CC_INCLUDE) -c $< -o $@

# 生成 *.d 的依赖文件，用于追踪 *.c 依赖的 *.h 改动
$(DEPENDENCYS): $(BUILD_PATH)/%.d:%.c
	@echo Generate depandency for $<
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) $(CC_INCLUDE) -MM $< | sed "s/$(subst /,\/,$(basename $(notdir $@))).o/$(subst /,\/,$(basename $@)).o $(subst /,\/,$(basename $@)).d/g" > $@

include $(DEPENDENCYS)

# 链接
%.elf: $(ALL_OBJS)
	@echo Link $@
	@$(CC) $(CC_FLAGS) $(LINKER_FLAGS) $(ALL_OBJS) -o $@ -Wl,-Map=$(BUILD_PATH)/main.map

.PHONY: clean
clean:
	rm -r $(BUILD_PATH)
