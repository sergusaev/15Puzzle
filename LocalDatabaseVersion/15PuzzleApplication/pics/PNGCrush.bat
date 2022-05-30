@echo off
CLS
FOR /F "tokens=*" %%G IN ('dir /A:-D /b *.png') DO (
    pngcrush_1_7_88_w64.exe -rem gAMA -rem cHRM -rem iCCP -rem sRGB -ow %%G
)
PAUSE