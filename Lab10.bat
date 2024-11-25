@echo off
echo Running ipconfig:
ipconfig
echo.
echo Running tracert to google.com:
tracert google.com
echo.
echo Running cipher command:
cipher
echo.
echo Running file compression (compact):
compact /c "C:\path\to\your\folder"  > compressed.txt
echo.
echo Running file hashing (CertUtil):
certutil -hashfile "C:\path\to\your\file.txt" SHA256
echo.
pause


