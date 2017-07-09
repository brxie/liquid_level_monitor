# Liquid level monitor.

Liquid level monitor device based on following hardware stack:

### Software details:
- **Compiler**: SDCC 3.5.0
- **Programmer**: [stm8flash](https://github.com/vdudouyt/stm8flash)

### Hardware details:
- **MCU**: STM8S103 (testes with STM8S103F3P6)
- **LCD**: PCD8544, SPI interface
- **Sensor**: 4-20MA level transmitter handled by ADC converter.
