[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PMSX003

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pmsx003/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PMSX003 is a kind of digital and universal particle concentration sensor,which can be used to obtain the number of suspended particles in the air,i.e.the concentration of particles,and output them in the form of digital interface. This sensor can be inserted into variable instruments related to the concentration of suspended particles in the air or other environmental improvement equipments to provide correct concentration data in time.

LibDriver PMSX003 is a full-featured driver for PMSX003, launched by LibDriver.It provides air quality reading and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver PMSX003 source files.

/interface includes LibDriver PMSX003 UART platform independent template.

/test includes LibDriver PMSX003 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver PMSX003 sample code.

/doc includes LibDriver PMSX003 offline document.

/datasheet includes PMSX003 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface UART platform independent template and finish your platform UART driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_pmsx003_basic.h"

uint8_t res;
uint32_t i;

/* init */
res = pmsx003_basic_init();
if (res != 0)
{
    return 1;
}

...
    
for (i = 0; i < 3; i++)
{
    pmsx003_data_t data;

    /* delay 1000ms */
    pmsx003_interface_delay_ms(1000);

    /* read data */
    res = pmsx003_basic_read(&data);
    if (res != 0)
    {
        (void)pmsx003_basic_deinit();

        return 1;
    }

    /* output */
    pmsx003_interface_debug_print("pmsx003: %d/%d.\n", i + 1, 3);
    pmsx003_interface_debug_print("pmsx003: pm1p0 standard is %d ug/m3.\n", data.pm1p0_standard_ug_m3);
    pmsx003_interface_debug_print("pmsx003: pm2p5 standard is %d ug/m3.\n", data.pm2p5_standard_ug_m3);
    pmsx003_interface_debug_print("pmsx003: pm10 standard is %d ug/m3.\n", data.pm10_standard_ug_m3);
    pmsx003_interface_debug_print("pmsx003: pm1p0 atmospheric is %d ug/m3.\n", data.pm1p0_atmospheric_ug_m3);
    pmsx003_interface_debug_print("pmsx003: pm2p5 atmospheric is %d ug/m3.\n", data.pm2p5_atmospheric_ug_m3);
    pmsx003_interface_debug_print("pmsx003: pm10 atmospheric is %d ug/m3.\n", data.pm10_atmospheric_ug_m3);
    pmsx003_interface_debug_print("pmsx003: beyond 0p3 um is %d.\n", data.beyond_0p3um);
    pmsx003_interface_debug_print("pmsx003: beyond 0p5 um is %d.\n", data.beyond_0p5um);
    pmsx003_interface_debug_print("pmsx003: beyond 1p0 um is %d.\n", data.beyond_1p0um);
    pmsx003_interface_debug_print("pmsx003: beyond 2p5 um is %d.\n", data.beyond_2p5um);
    pmsx003_interface_debug_print("pmsx003: beyond 5p0 um is %d.\n", data.beyond_5p0um);
    pmsx003_interface_debug_print("pmsx003: beyond 10 um is %d.\n", data.beyond_10um);
    pmsx003_interface_debug_print("pmsx003: version is 0x%02X.\n", data.version);
    pmsx003_interface_debug_print("pmsx003: error code is 0x%02X.\n", data.error_code);
    
    ...
}

...
    
/* sleep */
res = pmsx003_basic_sleep();
if (res != 0)
{
    (void)pmsx003_basic_deinit();
    
    return 1;
}

...
    
/* wake up */
res = pmsx003_basic_wake_up();
if (res != 0)
{
    (void)pmsx003_basic_deinit();
    
    return 1;
}

...
    
/* deinit */
(void)pmsx003_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/pmsx003/index.html](https://www.libdriver.com/docs/pmsx003/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.