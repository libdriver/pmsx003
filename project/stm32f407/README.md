### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

UART2 Pin: TX/RX PA2/PA3.

GPIO Pin: RESET/SET PA8/PA0.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. PMSX003

#### 3.1 Command Instruction

1. Show pmsx003 chip and driver information.

   ```shell
   pmsx003 (-i | --information)
   ```

2. Show pmsx003 help.

   ```shell
   pmsx003 (-h | --help)
   ```

3. Show pmsx003 pin connections of the current board.

   ```shell
   pmsx003 (-p | --port)
   ```

4. Run pmsx003 read test, num is the test times.

   ```shell
   pmsx003 (-t read | --test=read) [--times=<num>]
   ```


5. Run pmsx003 read function, num is the test times.

   ```shell
   pmsx003 (-e read | --example=read) [--times=<num>]
   ```

6. Run pmsx003 sleep function.

   ```shell
   pmsx003 (-e sleep | --example=sleep)
   ```

7. Run pmsx003 wake-up function.

   ```shell
   pmsx003 (-e wake-up | --example=wake-up)
   ```

#### 3.2 Command Example

```shell
pmsx003 -i

pmsx003: chip is PLANTOWER PMSX003.
pmsx003: manufacturer is PLANTOWER.
pmsx003: interface is UART.
pmsx003: driver version is 1.0.
pmsx003: min supply voltage is 4.5V.
pmsx003: max supply voltage is 5.5V.
pmsx003: max current is 100.00mA.
pmsx003: max temperature is 60.0C.
pmsx003: min temperature is -10.0C.
```

```shell
pmsx003 -p

pmsx003: TX connected to GPIOA PIN3.
pmsx003: RX connected to GPIOA PIN2.
pmsx003: RESET connected to GPIOA PIN8.
pmsx003: SET connected to GPIOA PIN0.
```

```shell
pmsx003 -t read --times=3

pmsx003: chip is PLANTOWER PMSX003.
pmsx003: manufacturer is PLANTOWER.
pmsx003: interface is UART.
pmsx003: driver version is 1.0.
pmsx003: min supply voltage is 4.5V.
pmsx003: max supply voltage is 5.5V.
pmsx003: max current is 100.00mA.
pmsx003: max temperature is 60.0C.
pmsx003: min temperature is -10.0C.
pmsx003: start read test.
pmsx003: active read test.
pmsx003: pm1p0 standard is 24 ug/m3.
pmsx003: pm2p5 standard is 34 ug/m3.
pmsx003: pm10 standard is 34 ug/m3.
pmsx003: pm1p0 atmospheric is 22 ug/m3.
pmsx003: pm2p5 atmospheric is 32 ug/m3.
pmsx003: pm10 atmospheric is 34 ug/m3.
pmsx003: beyond 0p3 um is 166.
pmsx003: beyond 0p5 um is 116.
pmsx003: beyond 1p0 um is 18.
pmsx003: beyond 2p5 um is 2.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: pm1p0 standard is 24 ug/m3.
pmsx003: pm2p5 standard is 34 ug/m3.
pmsx003: pm10 standard is 34 ug/m3.
pmsx003: pm1p0 atmospheric is 22 ug/m3.
pmsx003: pm2p5 atmospheric is 32 ug/m3.
pmsx003: pm10 atmospheric is 34 ug/m3.
pmsx003: beyond 0p3 um is 330.
pmsx003: beyond 0p5 um is 232.
pmsx003: beyond 1p0 um is 36.
pmsx003: beyond 2p5 um is 4.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: pm1p0 standard is 24 ug/m3.
pmsx003: pm2p5 standard is 34 ug/m3.
pmsx003: pm10 standard is 34 ug/m3.
pmsx003: pm1p0 atmospheric is 22 ug/m3.
pmsx003: pm2p5 atmospheric is 32 ug/m3.
pmsx003: pm10 atmospheric is 34 ug/m3.
pmsx003: beyond 0p3 um is 658.
pmsx003: beyond 0p5 um is 469.
pmsx003: beyond 1p0 um is 69.
pmsx003: beyond 2p5 um is 6.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: passive read test.
pmsx003: pm1p0 standard is 24 ug/m3.
pmsx003: pm2p5 standard is 34 ug/m3.
pmsx003: pm10 standard is 34 ug/m3.
pmsx003: pm1p0 atmospheric is 22 ug/m3.
pmsx003: pm2p5 atmospheric is 32 ug/m3.
pmsx003: pm10 atmospheric is 34 ug/m3.
pmsx003: beyond 0p3 um is 1161.
pmsx003: beyond 0p5 um is 842.
pmsx003: beyond 1p0 um is 121.
pmsx003: beyond 2p5 um is 7.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: pm1p0 standard is 22 ug/m3.
pmsx003: pm2p5 standard is 31 ug/m3.
pmsx003: pm10 standard is 32 ug/m3.
pmsx003: pm1p0 atmospheric is 20 ug/m3.
pmsx003: pm2p5 atmospheric is 29 ug/m3.
pmsx003: pm10 atmospheric is 32 ug/m3.
pmsx003: beyond 0p3 um is 1507.
pmsx003: beyond 0p5 um is 1100.
pmsx003: beyond 1p0 um is 158.
pmsx003: beyond 2p5 um is 7.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: pm1p0 standard is 22 ug/m3.
pmsx003: pm2p5 standard is 32 ug/m3.
pmsx003: pm10 standard is 33 ug/m3.
pmsx003: pm1p0 atmospheric is 20 ug/m3.
pmsx003: pm2p5 atmospheric is 30 ug/m3.
pmsx003: pm10 atmospheric is 33 ug/m3.
pmsx003: beyond 0p3 um is 1723.
pmsx003: beyond 0p5 um is 1284.
pmsx003: beyond 1p0 um is 174.
pmsx003: beyond 2p5 um is 2.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: sleep.
pmsx003: wake up.
pmsx003: finish read test.
```

```shell
pmsx003 -e read --times=3

pmsx003: 1/3.
pmsx003: pm1p0 standard is 24 ug/m3.
pmsx003: pm2p5 standard is 35 ug/m3.
pmsx003: pm10 standard is 47 ug/m3.
pmsx003: pm1p0 atmospheric is 22 ug/m3.
pmsx003: pm2p5 atmospheric is 33 ug/m3.
pmsx003: pm10 atmospheric is 46 ug/m3.
pmsx003: beyond 0p3 um is 152.
pmsx003: beyond 0p5 um is 118.
pmsx003: beyond 1p0 um is 18.
pmsx003: beyond 2p5 um is 4.
pmsx003: beyond 5p0 um is 2.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: 2/3.
pmsx003: pm1p0 standard is 24 ug/m3.
pmsx003: pm2p5 standard is 35 ug/m3.
pmsx003: pm10 standard is 47 ug/m3.
pmsx003: pm1p0 atmospheric is 22 ug/m3.
pmsx003: pm2p5 atmospheric is 33 ug/m3.
pmsx003: pm10 atmospheric is 46 ug/m3.
pmsx003: beyond 0p3 um is 152.
pmsx003: beyond 0p5 um is 118.
pmsx003: beyond 1p0 um is 18.
pmsx003: beyond 2p5 um is 4.
pmsx003: beyond 5p0 um is 2.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: 3/3.
pmsx003: pm1p0 standard is 24 ug/m3.
pmsx003: pm2p5 standard is 36 ug/m3.
pmsx003: pm10 standard is 47 ug/m3.
pmsx003: pm1p0 atmospheric is 22 ug/m3.
pmsx003: pm2p5 atmospheric is 33 ug/m3.
pmsx003: pm10 atmospheric is 46 ug/m3.
pmsx003: beyond 0p3 um is 312.
pmsx003: beyond 0p5 um is 242.
pmsx003: beyond 1p0 um is 37.
pmsx003: beyond 2p5 um is 8.
pmsx003: beyond 5p0 um is 3.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
```

```shell
pmsx003 -e sleep

pmsx003: sleep.
```
```shell
pmsx003 -e wake-up

pmsx003: wake up.
```

```shell
pmsx003 -h

Usage:
  pmsx003 (-i | --information)
  pmsx003 (-h | --help)
  pmsx003 (-p | --port)
  pmsx003 (-t read | --test=read) [--times=<num>]
  pmsx003 (-e read | --example=read) [--times=<num>]
  pmsx003 (-e sleep | --example=sleep)
  pmsx003 (-e wake-up | --example=wake-up)

Options:
  -e <read | sleep | wake-up>, --example=<read | sleep | wake-up>
                                  Run the driver example.
  -h, --help                      Show the help.
  -i, --information               Show the chip information.
  -p, --port                      Display the pins used by this device to connect the chip.
  -t <read>, --test=<read>        Run the driver test.
      --times=<num>               Set the running times.([default: 3])
```

