# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/esp32/v5.1.2/esp-idf/components/bootloader/subproject"
  "C:/ejemplosESP32/Proyecto-Final/lcd_servo/build/bootloader"
  "C:/ejemplosESP32/Proyecto-Final/lcd_servo/build/bootloader-prefix"
  "C:/ejemplosESP32/Proyecto-Final/lcd_servo/build/bootloader-prefix/tmp"
  "C:/ejemplosESP32/Proyecto-Final/lcd_servo/build/bootloader-prefix/src/bootloader-stamp"
  "C:/ejemplosESP32/Proyecto-Final/lcd_servo/build/bootloader-prefix/src"
  "C:/ejemplosESP32/Proyecto-Final/lcd_servo/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/ejemplosESP32/Proyecto-Final/lcd_servo/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/ejemplosESP32/Proyecto-Final/lcd_servo/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
