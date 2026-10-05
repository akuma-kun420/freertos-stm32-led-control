# freertos-stm32-led-control

This project is a multi-task embedded control system developed using an STM32 Nucleo C031C6 microcontroller and FreeRTOS. The main objective is to demonstrate real-time task management by running multiple functions independently using the FreeRTOS scheduler.

The system consists of two main FreeRTOS tasks. The first task controls two LEDs in a sequential pattern, where the red LED turns ON for 1 second, followed by a 2-second delay, and then the green LED turns ON for 1 second followed by another 2-second delay. This sequence continuously repeats.

The second task manages a 16×2 I²C LCD using two push buttons. Pressing the first button turns the LCD backlight ON and displays a project status message. The LCD remains active for a maximum of 10 seconds and can also be turned OFF immediately by pressing the second button.

The project demonstrates important embedded-system concepts including FreeRTOS task creation, task scheduling, non-blocking delays using `vTaskDelay()`, GPIO control, digital input handling, internal pull-up resistors, I²C communication, LCD interfacing, and concurrent task execution.

The complete circuit was designed and simulated in Wokwi and developed using VS Code and PlatformIO with the STM32 Arduino framework. The project provides practical experience in combining hardware peripherals with a real-time operating system on an STM32 microcontroller.
