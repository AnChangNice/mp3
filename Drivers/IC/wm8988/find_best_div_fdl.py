
def find_best_div_fdl(clk_in, fs, bits):
    find = False
    best_d = clk_in

    # div could be 1-63
    for div in range(1, 64):
        # FDL could be 2*bits-256
        for fdl in range(bits * 2, 256+1):
            if (fdl % 2) != 0:
                continue
            err = abs(clk_in - (fs * div * fdl))
            if err <= best_d:
                best_d = err

    # div could be 1-63
    for div in range(1, 64):
        # FDL could be 2*bits-256
        for fdl in range(bits * 2, 256+1):
            if (fdl % 2) != 0:
                continue
            err = abs(clk_in - (fs * div * fdl))
            if err <= best_d:
                best_d = err
                print("fs:%d, bits:%d, err:%f, div:%d, fdl:%d, clk:%d, real_fs:%f"%(fs, bits, err, div, fdl, (fs * div * fdl), (clk_in // div // fdl)))

if __name__ == "__main__":
    SAI_CLOCK = 24000000
    find_best_div_fdl(SAI_CLOCK, 8000, 8)
    find_best_div_fdl(SAI_CLOCK, 8000, 16)
    find_best_div_fdl(SAI_CLOCK, 8000, 20)
    find_best_div_fdl(SAI_CLOCK, 8000, 24)
    find_best_div_fdl(SAI_CLOCK, 8000, 32)
    
    find_best_div_fdl(SAI_CLOCK, 11025, 8)
    find_best_div_fdl(SAI_CLOCK, 11025, 16)
    find_best_div_fdl(SAI_CLOCK, 11025, 20)
    find_best_div_fdl(SAI_CLOCK, 11025, 24)
    find_best_div_fdl(SAI_CLOCK, 11025, 32)
    
    find_best_div_fdl(SAI_CLOCK, 12000, 8)
    find_best_div_fdl(SAI_CLOCK, 12000, 16)
    find_best_div_fdl(SAI_CLOCK, 12000, 20)
    find_best_div_fdl(SAI_CLOCK, 12000, 24)
    find_best_div_fdl(SAI_CLOCK, 12000, 32)
    
    find_best_div_fdl(SAI_CLOCK, 16000, 8)
    find_best_div_fdl(SAI_CLOCK, 16000, 16)
    find_best_div_fdl(SAI_CLOCK, 16000, 20)
    find_best_div_fdl(SAI_CLOCK, 16000, 24)
    find_best_div_fdl(SAI_CLOCK, 16000, 32)
    
    find_best_div_fdl(SAI_CLOCK, 22050, 8)
    find_best_div_fdl(SAI_CLOCK, 22050, 16)
    find_best_div_fdl(SAI_CLOCK, 22050, 20)
    find_best_div_fdl(SAI_CLOCK, 22050, 24)
    find_best_div_fdl(SAI_CLOCK, 22050, 32)
    
    find_best_div_fdl(SAI_CLOCK, 24000, 8)
    find_best_div_fdl(SAI_CLOCK, 24000, 16)
    find_best_div_fdl(SAI_CLOCK, 24000, 20)
    find_best_div_fdl(SAI_CLOCK, 24000, 24)
    find_best_div_fdl(SAI_CLOCK, 24000, 32)
    
    find_best_div_fdl(SAI_CLOCK, 32000, 8)
    find_best_div_fdl(SAI_CLOCK, 32000, 16)
    find_best_div_fdl(SAI_CLOCK, 32000, 20)
    find_best_div_fdl(SAI_CLOCK, 32000, 24)
    find_best_div_fdl(SAI_CLOCK, 32000, 32)
    
    find_best_div_fdl(SAI_CLOCK, 44100, 8)
    find_best_div_fdl(SAI_CLOCK, 44100, 16)
    find_best_div_fdl(SAI_CLOCK, 44100, 20)
    find_best_div_fdl(SAI_CLOCK, 44100, 24)
    find_best_div_fdl(SAI_CLOCK, 44100, 32)
    
    find_best_div_fdl(SAI_CLOCK, 48000, 8)
    find_best_div_fdl(SAI_CLOCK, 48000, 16)
    find_best_div_fdl(SAI_CLOCK, 48000, 20)
    find_best_div_fdl(SAI_CLOCK, 48000, 24)
    find_best_div_fdl(SAI_CLOCK, 48000, 32)

    find_best_div_fdl(SAI_CLOCK, 96000, 8)
    find_best_div_fdl(SAI_CLOCK, 96000, 16)
    find_best_div_fdl(SAI_CLOCK, 96000, 20)
    find_best_div_fdl(SAI_CLOCK, 96000, 24)
    find_best_div_fdl(SAI_CLOCK, 96000, 32)
    
    find_best_div_fdl(SAI_CLOCK, 128000, 8)
    find_best_div_fdl(SAI_CLOCK, 128000, 16)
    find_best_div_fdl(SAI_CLOCK, 128000, 20)
    find_best_div_fdl(SAI_CLOCK, 128000, 24)
    find_best_div_fdl(SAI_CLOCK, 128000, 32)