# mp3
A mp3 player based on ART-Pi

# Toolchain
Compiler: GNU Arm Embedded Toolchain 10.3-2021.1

Configure Tool: CubeMX

Make: GNU Make

Debug: Ozone

# Cmd
make

make debug      #Optiminization level 0.

make release    #Default optiminization level.

make clean

make -jn        #Fast compile with n jobs at once.

make OPT=-Ox    #Optiminization level setting.

make hexinfo    #Output xxx.hex regins size and address.

make hexdump    #Dump xxx.hex to xxx_hexdump.txt for human readable format.

make size       #Get program total size.

make allsize    #Get program total size and each xxx.o.

make sections   #Get program size of each section.

