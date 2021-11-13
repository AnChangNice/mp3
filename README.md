# mp3
A mp3 player based on ART-Pi

# Toolchain
Compiler: GNU Arm Embedded Toolchain 10.3-2021.1

Configure Tool: CubeMX

Make: GNU Make

Debug: Ozone

# Cmd
make

make clean

make -jn        #Fast compile with n jobs at once.

make OPT=-Ox    #Optiminization level setting.

make hexinfo    #Output xxx.hex regins size and address.

make hexdump    #Dump xxx.hex to xxx_hexdump.txt for human readable format.

