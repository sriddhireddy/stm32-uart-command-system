# STM32 Bare-Metal UART Command Line Interface (CLI)

A register-level embedded systems project developed on the **STM32F446RE Nucleo** board without using the HAL library.

This project demonstrates how to build a reusable GPIO and UART driver from scratch and use them to create an interactive UART Command Line Interface (CLI).

---

## Features

- Register-level GPIO programming
- Register-level UART (USART2) programming
- Modular GPIO Driver
- Modular UART Driver
- UART Character Transmission
- UART Character Reception
- UART String Transmission
- UART String Reception
- Custom String Comparison Function
- UART Command Processor
- LED Control through UART Commands
- Command Line Interface (CLI)

---

## Hardware

- STM32F446RE Nucleo Board
- ST-Link Virtual COM Port
- On-board LED (PA5 / LD2)
- USB Cable

---

## Software

- STM32CubeIDE
- RealTerm Serial Terminal
- Git & GitHub

---

## Project Architecture

```
                   +----------------+
                   |    main.c      |
                   +--------+-------+
                            |
                            |
                            v
              +--------------------------+
              | command_processor.c      |
              +-----------+--------------+
                          |
            +-------------+-------------+
            |                           |
            v                           v
    +---------------+           +---------------+
    | gpio_driver.c |           | uart_driver.c |
    +-------+-------+           +-------+-------+
            |                           |
            |                           |
            v                           v
      STM32 GPIO Registers       STM32 USART Registers
```

---

## Folder Structure

```
Project
│
├── Core
│   ├── Src
│   │   ├── main.c
│   │   ├── gpio_driver.c
│   │   ├── uart_driver.c
│   │   └── command_processor.c
│   │
│   └── Inc
│       ├── gpio_driver.h
│       ├── uart_driver.h
│       └── command_processor.h
│
└── README.md
```

---

## Supported Commands

| Command | Description |
|----------|-------------|
| LEDON | Turns ON the onboard LED |
| LEDOFF | Turns OFF the onboard LED |
| STATUS | Displays current LED status |
| HELP | Lists all available commands |

---

## Example Output

```
HELP

Available Commands
------------------
LEDON  - Turn LED ON
LEDOFF - Turn LED OFF
HELP   - Show commands
STATUS - Show LED status
```

```
LEDON

LED turned ON
```

```
STATUS

LED Status : ON
```

---

## GPIO Driver API

```c
void GPIO_Init(void);
void GPIO_SetPin(void);
void GPIO_ResetPin(void);
uint8_t GPIO_ReadPin(void);
void GPIO_TogglePin(void);
```

---

## UART Driver API

```c
void UART_Init(void);

void UART_WriteChar(char c);
void UART_WriteString(const char *str);

char UART_ReadChar(void);
void UART_ReadString(char *buffer, uint32_t maxLen);

int String_Compare(const char *s1,const char *s2);
```

---

## Concepts Learned

- STM32 Register Programming
- RCC Clock Configuration
- GPIO Configuration
- Alternate Function Registers (AFR)
- UART Initialization
- Baud Rate Calculation
- Polling
- UART Transmission
- UART Reception
- Pointer Arithmetic
- C Strings
- Buffer Handling
- Driver Development
- Embedded Software Architecture
- Command Line Interface Design

---

## Git Commit Progress

- Bare-metal LED Blink
- GPIO Driver
- UART Initialization
- UART Transmission
- UART Reception
- UART String Receive
- Command Recognition
- LED Control
- HELP Command
- STATUS Command
- Command Processor Refactoring

---

## Future Improvements

- Interrupt-driven UART
- Ring Buffer
- Command Table using Function Pointers
- PWM LED Brightness Control
- Timer Driver
- FreeRTOS Integration

---

## Author

**S Riddhi Reddy**

Electronics and Communication Engineering (ECE)

RV College of Engineering

---

## License

This project is intended for educational purposes.