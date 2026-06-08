# ATmega328p 7-Segment Display Driver

Chronometer/clock display using direct register programming on ATmega328p (no Arduino libraries).

## Features
- 4-digit multiplexed 7-segment display
- Timer0 in CTC mode with interrupts at 1kHz
- Direct register manipulation (PORTB, PORTC, TCCR0A, TIMSK0)
- Configurable mode: MM:SS (chronometer) or HH:MM (clock)
- RS232 communication support
- Flashed using AVRDUDESS

## Hardware
- MCU: ATmega328p (16MHz)
- Display: 4-digit 7-segment (multiplexed)
- PORTB: digit select (PB0-PB3)
- PORTC: segment data

## Build & Flash
```bash
make
make flash PORT=COM3
```
Or use AVRDUDESS GUI to flash the .hex file.
