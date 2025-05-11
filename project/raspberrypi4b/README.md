### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

UART Pin: TX/RX GPIO14/GPIO15.

GPIO Pin: RESET/SET GPIO17/GPIO27.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```
#### 2.2 Configuration

Enable serial port.

Disable serial console.

#### 2.3 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.4 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(pmsx003 REQUIRED)
```

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
./pmsx003 -i

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
./pmsx003 -p

pmsx003: TX connected to GPIO15(BCM).
pmsx003: RX connected to GPIO14(BCM).
pmsx003: RESET connected to GPIO17(BCM).
pmsx003: SET connected to GPIO27(BCM).
```

```shell
./pmsx003 -t read --times=3

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
pmsx003: pm1p0 standard is 25 ug/m3.
pmsx003: pm2p5 standard is 33 ug/m3.
pmsx003: pm10 standard is 33 ug/m3.
pmsx003: pm1p0 atmospheric is 23 ug/m3.
pmsx003: pm2p5 atmospheric is 32 ug/m3.
pmsx003: pm10 atmospheric is 33 ug/m3.
pmsx003: beyond 0p3 um is 164.
pmsx003: beyond 0p5 um is 130.
pmsx003: beyond 1p0 um is 7.
pmsx003: beyond 2p5 um is 2.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: pm1p0 standard is 25 ug/m3.
pmsx003: pm2p5 standard is 33 ug/m3.
pmsx003: pm10 standard is 33 ug/m3.
pmsx003: pm1p0 atmospheric is 23 ug/m3.
pmsx003: pm2p5 atmospheric is 32 ug/m3.
pmsx003: pm10 atmospheric is 33 ug/m3.
pmsx003: beyond 0p3 um is 331.
pmsx003: beyond 0p5 um is 263.
pmsx003: beyond 1p0 um is 15.
pmsx003: beyond 2p5 um is 3.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: pm1p0 standard is 25 ug/m3.
pmsx003: pm2p5 standard is 33 ug/m3.
pmsx003: pm10 standard is 35 ug/m3.
pmsx003: pm1p0 atmospheric is 23 ug/m3.
pmsx003: pm2p5 atmospheric is 32 ug/m3.
pmsx003: pm10 atmospheric is 35 ug/m3.
pmsx003: beyond 0p3 um is 666.
pmsx003: beyond 0p5 um is 529.
pmsx003: beyond 1p0 um is 34.
pmsx003: beyond 2p5 um is 5.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: passive read test.
pmsx003: pm1p0 standard is 25 ug/m3.
pmsx003: pm2p5 standard is 34 ug/m3.
pmsx003: pm10 standard is 35 ug/m3.
pmsx003: pm1p0 atmospheric is 23 ug/m3.
pmsx003: pm2p5 atmospheric is 32 ug/m3.
pmsx003: pm10 atmospheric is 35 ug/m3.
pmsx003: beyond 0p3 um is 1170.
pmsx003: beyond 0p5 um is 932.
pmsx003: beyond 1p0 um is 70.
pmsx003: beyond 2p5 um is 5.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: pm1p0 standard is 23 ug/m3.
pmsx003: pm2p5 standard is 32 ug/m3.
pmsx003: pm10 standard is 34 ug/m3.
pmsx003: pm1p0 atmospheric is 21 ug/m3.
pmsx003: pm2p5 atmospheric is 30 ug/m3.
pmsx003: pm10 atmospheric is 34 ug/m3.
pmsx003: beyond 0p3 um is 1515.
pmsx003: beyond 0p5 um is 1207.
pmsx003: beyond 1p0 um is 98.
pmsx003: beyond 2p5 um is 5.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: pm1p0 standard is 23 ug/m3.
pmsx003: pm2p5 standard is 33 ug/m3.
pmsx003: pm10 standard is 35 ug/m3.
pmsx003: pm1p0 atmospheric is 21 ug/m3.
pmsx003: pm2p5 atmospheric is 31 ug/m3.
pmsx003: pm10 atmospheric is 35 ug/m3.
pmsx003: beyond 0p3 um is 1723.
pmsx003: beyond 0p5 um is 1368.
pmsx003: beyond 1p0 um is 126.
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
./pmsx003 -e read --times=3

pmsx003: 1/3.
pmsx003: pm1p0 standard is 22 ug/m3.
pmsx003: pm2p5 standard is 28 ug/m3.
pmsx003: pm10 standard is 28 ug/m3.
pmsx003: pm1p0 atmospheric is 21 ug/m3.
pmsx003: pm2p5 atmospheric is 28 ug/m3.
pmsx003: pm10 atmospheric is 28 ug/m3.
pmsx003: beyond 0p3 um is 141.
pmsx003: beyond 0p5 um is 118.
pmsx003: beyond 1p0 um is 9.
pmsx003: beyond 2p5 um is 0.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: 2/3.
pmsx003: pm1p0 standard is 22 ug/m3.
pmsx003: pm2p5 standard is 28 ug/m3.
pmsx003: pm10 standard is 28 ug/m3.
pmsx003: pm1p0 atmospheric is 21 ug/m3.
pmsx003: pm2p5 atmospheric is 28 ug/m3.
pmsx003: pm10 atmospheric is 28 ug/m3.
pmsx003: beyond 0p3 um is 141.
pmsx003: beyond 0p5 um is 118.
pmsx003: beyond 1p0 um is 9.
pmsx003: beyond 2p5 um is 0.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
pmsx003: 3/3.
pmsx003: pm1p0 standard is 22 ug/m3.
pmsx003: pm2p5 standard is 28 ug/m3.
pmsx003: pm10 standard is 30 ug/m3.
pmsx003: pm1p0 atmospheric is 21 ug/m3.
pmsx003: pm2p5 atmospheric is 28 ug/m3.
pmsx003: pm10 atmospheric is 30 ug/m3.
pmsx003: beyond 0p3 um is 290.
pmsx003: beyond 0p5 um is 240.
pmsx003: beyond 1p0 um is 19.
pmsx003: beyond 2p5 um is 0.
pmsx003: beyond 5p0 um is 0.
pmsx003: beyond 10 um is 0.
pmsx003: version is 0x13.
pmsx003: error code is 0x00.
```

```shell
./pmsx003 -e sleep

pmsx003: sleep.
```
```shell
./pmsx003 -e wake-up

pmsx003: wake up.
```

```shell
./pmsx003 -h

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

