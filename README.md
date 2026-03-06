# Device Drivers

A collection of **MCAL** (Microcontroller Abstraction Layer) modules and  
**ECUAL** (Embedded Component Abstraction Layer) interfaces for a variety  
of peripherals.  
Originally written for AVR/ATmega328p and PIC16F887, the code is intended  
for hobby and educational projects requiring direct access to hardware.

![oled_gif](https://github.com/user-attachments/assets/47afbaf4-9e89-4e60-9bbc-8a46220875b5)

## 📁 Repository layout

```
.
├── examples/                # simple demo programs (e.g. gpio.c)
├── images/                  # assorted images and assets
├── lib/
│   ├── ecual/               # high‑level drivers
│   │   ├── button/
│   │   ├── char_lcd/
│   │   ├── keypad/
│   │   ├── led/
│   │   ├── oled_display/    # see [OLED driver](#oled-driver)
│   │   ├── ultrasonic_sensors/
│   │   └── wifi_module/
│   └── mcal/                # low‑level MCU support
│       ├── atmega328p/
│       └── pic16f887/
└── simulations/             # project‑specific simulation files
```

## 🔧 Features

- **MCAL drivers** for GPIO, I²C, USART, timers, ADC, interrupts, …  
- **ECUAL modules** – ready‑to‑use interfaces for buttons, LCDs, OLEDs,  
  ultrasonic sensors, Wi‑Fi modules, etc.
- Designed to be portable across AVR and PIC micros; adapt by swapping  
  the `mcal/*` folder.

## 🚀 Getting started

1. Clone the repository:

   ```bash
   git clone https://github.com/your‑username/device-drivers.git
   cd device-drivers
   ```

2. Browse the code under `lib/mcal/<your‑mcu>` and `lib/ecual`.

3. Compile an example or integrate the drivers into your own project.  
   (No build system included; use your preferred toolchain/IDE for AVR or PIC.)

## 📝 Examples

Checkout the `examples/` directory for small test programs such as  
`gpio.c` demonstrating basic usage.

## 📦 OLED driver

The OLED display implementation lives in `lib/ecual/oled_display`.  
It includes source, fonts, images and even GIF routines.

## 🤝 Contributing

Feel free to submit issues or pull requests. Open‑source drivers are  
always better with more hardware support and documentation!

## ⚖️ License

This project is released under the [MIT License](LICENSE)  
(or specify whichever license you intend to use).
