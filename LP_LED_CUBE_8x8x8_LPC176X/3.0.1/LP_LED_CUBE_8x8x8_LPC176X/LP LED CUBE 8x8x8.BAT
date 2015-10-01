SET PATH=C:\Keil\ARM\ARMCC\bin\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\
SET CPU_TYPE=LPC1769
SET CPU_VENDOR=NXP (founded by Philips)
SET UV2_TARGET=LP LED CUBE 8x8x8
SET CPU_CLOCK=0x00B71B00
C:\Keil\ARM\bin\fcarm @Web\Web.inp
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\main.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\http_cgi.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\web.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\ftp_uif.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\http_err.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\http_uif.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\led_cube_8x8x8.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\net_config.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\file_config.__i"
"C:\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\obj\startup_lpc17xx._ia"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\fs_spi_flashprg.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\retarget.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\adc.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\delay.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\emac_dp83848.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\help.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\i2c.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\spi_lpc17xx.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\system_lpc17xx.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\uart.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\tlc59116.__i"
"C:\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\Obj\Http_upload.lnp"
"C:\Keil\ARM\ARMCC\bin\fromelf.exe" ".\Obj\Http_upload.axf" --i32combined --output ".\Obj\Http_upload.hex"
fromelf --bin ".\Obj\Http_upload.axf" --output ".\Flash 0x2000\firmware.bin"
