@echo off
:menu
cls
echo =======================
echo 1. Display IPv4 and IPv6 addresses
echo 2. Show network path (traceroute)
echo 3. Get IP address of a given hostname
echo 4. Encrypt file or text
echo 5. Decrypt file or text
echo 6. Compress file or text
echo 7. Decompress file or text
echo 8. Calculate file or text hash
echo 9. Exit
echo =======================
set /p choice=Choose an option (1-9): 

if "%choice%"=="1" goto show_ip
if "%choice%"=="2" goto traceroute
if "%choice%"=="3" goto resolve_ip
if "%choice%"=="4" goto encrypt
if "%choice%"=="5" goto decrypt
if "%choice%"=="6" goto compress
if "%choice%"=="7" goto decompress
if "%choice%"=="8" goto hash_file
if "%choice%"=="9" goto exit
goto menu

:show_ip
echo === Device IP Addresses ===
ipconfig | findstr "IPv4 IPv6"
pause
goto menu

:traceroute
set /p host=Enter hostname or URL: 
tracert %host%
pause
goto menu

:resolve_ip
set /p host=Enter hostname or URL: 
nslookup %host%
pause
goto menu

:encrypt
set /p input=Enter text or file path to encrypt: 
set /p key=Enter encryption key: 
encrypt_tool.exe "%input%" "%key%" "encrypted_output.txt"
pause
goto menu


:decrypt
set /p input=Enter text or file path to decrypt: 
set /p key=Enter decryption key: 
decrypt_tool.exe "%input%" "%key%" "decrypted_output.txt"
pause
goto menu

:compress
set /p input=Enter text or file path to compress: 
compress_tool.exe "%input%" "compressed_output.txt"
pause
goto menu


:decompress
set /p input=Enter text or file path to decompress: 
decompress_tool.exe "%input%" "decompressed_output.txt"
pause
goto menu

:hash_file
set /p input=Enter text or file path to calculate hash: 
hash_tool.exe "%input%"
pause
goto menu


:exit
echo Exiting...
exit
