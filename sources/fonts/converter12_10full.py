# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

import os
from struct import *

def WriteByte(num_byte, file):
    value = int(symbols[num_byte])
    if value < 0:
        value += 256
    file.write(str(value))

def WriteReverseByte(num_byte, file):
    value = int(symbols[num_byte])
    if value < 0:
        value += 256
    revValue = 0
    base = 256
    while value != 0:
        revValue += (value & 1) * (base >> 1)
        base = base >> 1
        value >>= 1
    file.write(str(revValue))

def GetBit(byte, bit):
    if((byte & (1 << bit)) > 0):
        return 1
    return 0

# Возвращает ширину "двухбайтового полуслова". Т.е. 0-е полуслово находится по адресу 0,
# 1-е полуслово - по адресу 2, 3-е полуслово - по адресу 3 и т.д.
def GetWidth2Bytes(two_bytes, log):
    if log == True:
        print("two_bytes = ", two_bytes)
    for bit in range(15, -1, -1):
        if log == True:
            print(bit)
        if GetBit(two_bytes, bit) == 1:
            return bit + 1;
    return 0

def CalculateWidth(num_symbol):
    # num_word - порядковый номер "полуслова" в символе. Полуслово состоит из двух байт
    result = 0;
    for num_word in range(0, 12, 1):
        two_bytes = symbols[num_symbol * 12 * 2 + num_word] | (symbols[num_symbol * 12 * 2 + num_word + 1] << 8)
        if GetWidth2Bytes(two_bytes, num_symbol == 0) > result:
            result = GetWidth2Bytes(two_bytes, num_symbol == 0)
    return result

###### Start here ######

input = open("Font12_10.bin", "rb")
data = input.read()
input.close()
symbols = unpack("6144b", data)

output = open("font12_10.inc", "w")
output.write("#include \"font.h\"\nconst Font22 font12_10 = {\n\t12, \t10, {\n")

outTmpTable = open("table.tmp", "w")    # Temp file for table of symbols
outTmpMap = open("map.tmp", "w")        # Temp file for bit map

for num_symbol in range(256):
    output.write("/*" + str(num_symbol) + "*/")                         # Number of symbol
    outTmpTable.write("\n/* " + str(num_symbol) + " */\t    ")
    
    output.write("\t\t{ " + str(CalculateWidth(num_symbol)) + ", { ")   # Width symbol
    outTmpTable.write(str(CalculateWidth(num_symbol)) + ", ")
    offset = 8 + 4 * 256 + num_symbol * 8
    outTmpTable.write(str(offset & 0xff) + ", " + str((offset >> 8) & 0xff) + ", " + str((offset >> 16) & 0xff) + ",")

    outTmpMap.write("/* " + str(num_symbol) + " */\t        ")
    
    for num_byte in range(8):
        WriteByte(num_symbol * 8 + num_byte, output)
        WriteReverseByte(num_symbol * 8 + num_byte, outTmpMap)
        if not(num_byte == 7 and num_symbol == 255):
            outTmpMap.write(",")
        if num_byte != 7:
           output.write(",") 
        output.write("\t")

    outTmpMap.write("\n")
        
    output.write("} " + "}")
    if num_symbol != 255:
        output.write(",")
    output.write("\t\n")
output.write("} };\n")

outTmpMap.write("};\n")

outTmpTable.close()
outTmpTable = open("table.tmp")
lines = outTmpTable.readlines()

outTmpMap.close();
outTmpMap = open("map.tmp")
lines = outTmpMap.readlines()

output.close()

input = open("font12_10.inc")
#print(input.read())
input.close()
