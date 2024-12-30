# EmbeddedSabryHub
---

# AVR Microcontroller Drivers Project  

This project is a comprehensive driver library for AVR microcontrollers. It includes all abstraction layers, from the lowest hardware-specific level to application-ready APIs. The drivers are modular, reusable, and designed for ease of integration into various projects.  

---

## Table of Contents  
1. [Static Design Architecture](#static-design-architecture)  
2. [Registers Overview](#registers-overview)  
3. [Microcontroller Abstraction Layer (MCAL)](#microcontroller-abstraction-layer-mcal)  
4. [Hardware Abstraction Layer (HAL)](#hardware-abstraction-layer-hal)  
5. [Services Layer](#services-layer)  
6. [Application Layer](#application-layer)  

---

## Static Design Architecture  

### Overview  
The project follows a layered architecture to ensure modularity and scalability:  

![Static Design Architecture](https://user-images.githubusercontent.com/82292548/134666422-4ddb3824-1ba4-408d-adae-df4132e63b75.png)  

1. **Microcontroller Abstraction Layer (MCAL):** Low-level drivers for MCU peripherals.  
2. **Hardware Abstraction Layer (HAL):** Drivers for external hardware components.  
3. **Services Layer:** Middleware for reusable functionality.  
4. **Application Layer:** End-user application logic.  

---

## Registers Overview  

AVR microcontrollers are equipped with a variety of registers for controlling peripherals and operations. Below is an overview of the key registers:  

| **Register Name** | **Address** | **Description**                       |  
|--------------------|-------------|---------------------------------------|  
| `DDRx`            | 0x00-0x07   | Data Direction Register (Configures pins as input/output) |  
| `PORTx`           | 0x08-0x0F   | Data Register (Writes HIGH/LOW to pins) |  
| `PINx`            | 0x10-0x17   | Pin Input Register (Reads pin states) |  
| `TCCRn`           | 0x18-0x1F   | Timer/Counter Control Register        |  
| `OCRn`            | 0x20-0x27   | Output Compare Register               |  
| `ADCSRA`          | 0x28        | ADC Control and Status Register       |  
| `UDR`             | 0x29        | UART Data Register                    |  
| `EEAR`            | 0x30        | EEPROM Address Register               |  
| `EEDR`            | 0x31        | EEPROM Data Register                  |  

For a complete list, refer to the [AVR Datasheet](https://www.microchip.com).  

---

## Microcontroller Abstraction Layer (MCAL)  

The MCAL provides low-level drivers for AVR peripherals. Each driver is designed for flexibility and performance.  

### GPIO (General Purpose Input/Output)  
**Features:**  
- Pin and port initialization.  
- Pin state read/write/toggle.  
- Internal pull-up resistor control.  

**Example:**  
```c
GPIO_init_port(GPIO_PORTB, 0xFF); // Configure PORTB as output
GPIO_write_pin(GPIO_PORTB, 2, 1); // Set pin 2 of PORTB HIGH
uint8 state = GPIO_read_pin(GPIO_PORTB, 2); // Read pin 2 state
```  

---

### ADC (Analog-to-Digital Converter)  
**Features:**  
- 10-bit resolution.  
- Selectable reference voltage.  
- Interrupt or polling-based operation.  

**Example:**  
```c
ADC_init(AVCC, ADC1); // Initialize ADC with AVCC reference and channel 1
uint16 result = ADC_read(); // Read ADC value
```  

---

### Timers  
**Features:**  
- Delay generation, PWM, and event counting.  
- Configurable compare match and overflow interrupts.  

**Example:**  
```c
TIMER1_init(CTC_MODE, PRESCALER_64, NORMAL, NORMAL);
TIMER1_periodic_ms(500, []() { /* ISR logic */ });
```  

---

### UART (Universal Asynchronous Receiver/Transmitter)  
**Features:**  
- Asynchronous serial communication.  
- Configurable baud rate.  
- Interrupt-driven TX/RX.  

**Example:**  
```c
UART_init();
UART_send_byte('A');
uint8 received = UART_receive_byte();
```  

---

### SPI (Serial Peripheral Interface)  
**Features:**  
- Full-duplex communication.  
- Configurable clock polarity and phase.  

**Example:**  
```c
SPI_init();
SPI_write(0xAA);
uint8 received = SPI_read();
```  

---

### External Interrupts  
**Features:**  
- Support for rising/falling edge, logical change, or low-level triggers.  

**Example:**  
```c
EXT_set_interrupt(INT0);
EXT_set_callback(INT0, []() { /* ISR logic */ });
```  

---

## Hardware Abstraction Layer (HAL)  

This layer contains drivers for external components connected to the microcontroller:  

| **Component**       | **Status** |  
|----------------------|------------|  
| LCD                 | ✅ Implemented |  
| Button              | ✅ Implemented |  
| Keypad              | ✅ Implemented |  
| LM35 Temperature Sensor | ✅ Implemented |  
| Seven Segment Display | ❌ Planned   |  
| Servo Motor         | ❌ Planned   |  

**Example:**  
```c
LCD_init();
LCD_print("Hello, AVR!");
```  

---

## Services Layer  

The Services Layer provides reusable middleware, such as:  

- **PWM Generation:** Simplifies PWM configuration for various applications.  
- **Serial Communication Protocols:** Abstractions over UART, SPI, and I2C for ease of use.  

---

## Application Layer  

This layer integrates all lower layers to build specific applications. Example use cases:  

- **Home Automation Systems**  
- **Temperature Monitoring with LM35**  
- **Serial Communication Tools**  

**Example:**  
```c
LCD_init();
UART_init();
LM35_init();

while (1) {
    float temp = LM35_get_temp();
    LCD_print_float(temp);
    UART_send_float(temp);
}
```  

---

## Contribution  

Contributions are welcome! Please follow the [contributing guidelines](./CONTRIBUTING.md).  

---

Let me know if this is aligned with your expectations or if you'd like further refinements!