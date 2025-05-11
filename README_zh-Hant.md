[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PMSX003

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pmsx003/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PMSX003是一種數位通用顆粒物濃度感測器，可用於獲取空氣中懸浮顆粒物的數量，即顆粒物的濃度，並以數位介面的形式輸出。 該感測器可以插入與空氣中懸浮顆粒濃度相關的可變儀器或其他環境改善設備中，及時提供正確的濃度數據。

LibDriver PMSX003是LibDriver推出的PMSX003全功能驅動，該驅動提供空氣品質讀取等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver PMSX003的源文件。

/interface目錄包含了LibDriver PMSX003與平台無關的UART總線模板。

/test目錄包含了LibDriver PMSX003驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver PMSX003編程範例。

/doc目錄包含了LibDriver PMSX003離線文檔。

/datasheet目錄包含了PMSX003數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的UART總線模板，完成指定平台的UART總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/pmsx003/index.html](https://www.libdriver.com/docs/pmsx003/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
