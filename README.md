# mp3
A mp3 player based on ART-Pi

# Toolchain
| Toolchain         | Description                              |
| ------------------|------------------------------------------|
| Compiler          | GNU Arm Embedded Toolchain 10.3-2021.1   |
| Configure Tool    | CubeMX                                   |
| Make              | GNU Make                                 |
| Debug             | Ozone                                    |
| 2MB Flash Target  | STM32H743XI                              |
| Terminal          | Git Bash                                 |

# Middleware
| Name              | Link                                         |
| ------------------|----------------------------------------------|
| FreeRTOS          | https://github.com/FreeRTOS/FreeRTOS-Kernel  |
| FatFs             | http://elm-chan.org/fsw/ff/00index_e.html    |
| letter-shell      | https://github.com/NevermindZZT/letter-shell |
| EasyLogger        | https://github.com/armink/EasyLogger         |
| lvgl              | https://github.com/lvgl/lvgl                 |

# Make Cmd
| Command        | Description                                                   |
|----------------|---------------------------------------------------------------|
| make debug     | Optiminization level 0.                                       |
| make release   | Default optiminization level.                                 |
| make clean     |                                                               |
| make -jn       | Fast compile with n jobs at once.                             |
| make OPT=-Ox   | Optiminization level setting.                                 |
| make hexinfo   | Output xxx.hex regins size and address.                       |
| make hexdump   | Dump xxx.hex to xxx_hexdump.txt for human readable format.    |
| make size      | Get program total size.                                       |
| make allsize   | Get program total size and each xxx.o.                        |
| make sections  | Get program size of each section.                             |
