
project(kayak_logger)
cmake_minimum_required(VERSION 3.1)
message(ARDUINO_PATH: ${ARDUINO_PATH})
if(${ARDUINO_PATH} MATCHES .*arduino.*)
   message("arduino path found at:" ${ARDUINO_PATH})
else()
   message("setting arduino path from env variable ...")
   set(ARDUINO_PATH $ENV{ARDUINO_PATH} CACHE STRING "")
endif()
if(${ARDUINO_PATH} MATCHES .*arduino.*)
   message("arduino path found at:" ${ARDUINO_PATH})
else()
   message(FATAL_ERROR "ARDUINO_PATH environment variable missing! It should point to root of arduino installation, for example /home/your_name/arduino-1.6.12/")
endif()

set(AVR_COMPILER_DIR ${ARDUINO_PATH}/hardware/tools/avr/bin)
set(CMAKE_C_COMPILER ${AVR_COMPILER_DIR}/avr-gcc)
set(CMAKE_CXX_COMPILER ${AVR_COMPILER_DIR}/avr-g++)
set(ARDUINO_CORE_SRC ${ARDUINO_PATH}/hardware/arduino/avr/cores/arduino)
set(ARDUINO_LCD_SRC ${ARDUINO_PATH}/libraries/LiquidCrystal/src/)
set(ARDUINO_WIRE_SRC ${ARDUINO_PATH}/hardware/arduino/avr/libraries/Wire/src/)
set(ARDUINO_PINS ${ARDUINO_PATH}/hardware/arduino/avr/variants/standard)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(EXTERNALS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals)
set(GPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals/TinyGPS)
set(SDFAT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals/SdFat)
set(ACCELEROMETER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals/ADXL345/)
INCLUDE_DIRECTORIES(${ARDUINO_CORE_SRC} ${ARDUINO_PINS} ${SRC_DIR} ${GPS_DIR} ${SDFAT_DIR} ${ARDUINO_LCD_SRC} ${ACCELEROMETER_DIR} ${ARDUINO_WIRE_SRC})

add_definitions(-c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10800 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR)

set(sources ${SRC_DIR}/Loop.cpp ${SRC_DIR}/Setup.cpp ${SRC_DIR}/GpsReport.cpp ${SRC_DIR}/ElementQueue.cpp ${SRC_DIR}/LogElement.cpp ${SRC_DIR}/StatusIndicator.cpp ${SRC_DIR}/Logger.cpp ${SRC_DIR}/Components.cpp ${SRC_DIR}/TiltReport.cpp ${ACCELEROMETER_DIR}/ADXL345.cpp ${ARDUINO_LCD_SRC}/LiquidCrystal.cpp ${ARDUINO_WIRE_SRC}/Wire.cpp ${ARDUINO_WIRE_SRC}/utility/twi.c ${SDFAT_DIR}/ostream.cpp ${SDFAT_DIR}/SdStream.cpp ${SDFAT_DIR}/SdFat.cpp ${SDFAT_DIR}/SdBaseFile.cpp ${SDFAT_DIR}/SdVolume.cpp ${SDFAT_DIR}/Sd2Card.cpp ${GPS_DIR}/TinyGPS.cpp)

set(arduino_core_sources ${ARDUINO_CORE_SRC}/CDC.cpp ${ARDUINO_CORE_SRC}/HardwareSerial.cpp ${ARDUINO_CORE_SRC}/HardwareSerial0.cpp ${ARDUINO_CORE_SRC}/HardwareSerial1.cpp ${ARDUINO_CORE_SRC}/HardwareSerial2.cpp ${ARDUINO_CORE_SRC}/HardwareSerial3.cpp ${ARDUINO_CORE_SRC}/IPAddress.cpp ${ARDUINO_CORE_SRC}/PluggableUSB.cpp ${ARDUINO_CORE_SRC}/Print.cpp ${ARDUINO_CORE_SRC}/Stream.cpp ${ARDUINO_CORE_SRC}/Tone.cpp ${ARDUINO_CORE_SRC}/USBCore.cpp ${ARDUINO_CORE_SRC}/WInterrupts.c ${ARDUINO_CORE_SRC}/WMath.cpp ${ARDUINO_CORE_SRC}/WString.cpp ${ARDUINO_CORE_SRC}/abi.cpp ${ARDUINO_CORE_SRC}/hooks.c ${ARDUINO_CORE_SRC}/main.cpp ${ARDUINO_CORE_SRC}/new.cpp ${ARDUINO_CORE_SRC}/wiring.c ${ARDUINO_CORE_SRC}/wiring_analog.c ${ARDUINO_CORE_SRC}/wiring_digital.c ${ARDUINO_CORE_SRC}/wiring_pulse.c ${ARDUINO_CORE_SRC}/wiring_shift.c)

# Find Arduino SDK delivered programs
find_program(AR_AVR_GCC NAMES avr-gcc PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_CXX NAMES avr-g++ PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_OBJCOPY NAMES avr-objcopy PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_OBJDUMP NAMES avr-objdump PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_RANLIB NAMES avr-ranlib PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_LD NAMES avr-ld PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)

# Compiler suite specification
set(CMAKE_C_COMPILER ${AR_AVR_GCC})
set(CMAKE_CXX_COMPILER ${AR_AVR_CXX})
set(CMAKE_OBJCOPY ${AR_AVR_OBJCOPY})
set(CMAKE_OBJDUMP ${AR_AVR_OBJDUMP})
set(CMAKE_RANLIB ${AR_AVR_RANLIB})
set(CMAKE_LINKER ${AR_AVR_LD})

# Linker flags
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")   # remove -rdynamic for C
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") # remove -rdynamic for CXX
set(CMAKE_EXE_LINKER_FLAGS "-Os -Wl,--gc-sections -mmcu=atmega328p")


add_executable(${PROJECT_NAME} ${sources} ${arduino_core_sources})

#/home/mikko/arduino-1.6.12/hardware/tools/avr/bin/avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  ./kayak_logger ./kayak_logger.eep
#/home/mikko/arduino-1.6.12/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom  ./kayak_logger ./kayak_logger.hex
#/home/mikko/arduino-1.6.12/hardware/tools/avr/bin/avrdude -C/home/mikko/arduino-1.6.12/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -D -Uflash:w:./kayak_logger.hex:i

