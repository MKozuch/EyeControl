CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)
SET(CMAKE_SYSTEM_NAME Generic)

#============================================================================================
PROJECT(avr-clion)

SET(DEVICE "atmega328p")
SET(FREQ "16000000")

#============================================================================================

SET(CMAKE_C_COMPILER avr-gcc)
SET(CMAKE_CXX_COMPILER avr-g++)

#SET(CMAKE_C_FLAGS  "-Os -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -std=gnu99 -Wl,--gc-sections -Wall -g")
SET(CMAKE_C_FLAGS  "-mmcu=${DEVICE} -DF_CPU=${FREQ}UL -std=gnu99 -Wl,--gc-sections -Wall -g1")
SET(CMAKE_CXX_FLAGS "-Os -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -Wl,--gc-sections")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#============================================================================================

SET(SOURCE_FILES

        main.c
        lib/Uart.h lib/Uart.c
        lib/Timer0.c lib/Timer0.h
        lib/Led.c lib/Led.h
        lib/StringConversions.c lib/StringConversions.h
        lib/Button.c lib/Button.h
        lib/ArduinoPinMap.h
        lib/Delay.c lib/Delay.h
        lib/Adc.c lib/Adc.h
        lib/Logger.c lib/Logger.h
        eyeControl/eyeControl.c eyeControl/eyeControl.h
        lib/Timer1.c lib/Timer1.h
        eyeControl/eyeControl_buffer.c eyeControl/eyeControl_buffer.h
        eyeControl/eyeControl_filter.c eyeControl/eyeControl_filter.h
        lib/Eeprom.c lib/Eeprom.h lib/Timer2.c lib/Timer2.h)

#============================================================================================

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})

#"${PROJECT_NAME}.lss" ALL COMMAND avr-objdump -h -S ${PROJECT_NAME} > "${PROJECT_NAME}.lss"  DEPENDS ${PROJECT_NAME})
#ADD_CUSTOM_TARGET ("${PROJECT_NAME}.lss" ALL COMMAND avr-objdump -h -S ${PROJECT_NAME} > "${PROJECT_NAME}.lss"  DEPENDS ${PROJECT_NAME})

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objdump -h -S  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} > "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.lss")

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objcopy -O ihex -R.eeprom ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.eep)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-size ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} --mcu=${DEVICE} --format=avr)