[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PMSX003

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pmsx003/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PMSX003は、空気中の浮遊粒子数、すなわち粒子濃度を取得し、デジタルインターフェースで出力できるデジタル汎用粒子濃度センサーです。このセンサーは、空気中の浮遊粒子濃度に関連するさまざまな機器やその他の環境改善装置に組み込むことで、正確な濃度データをタイムリーに提供します。

LibDriver PMSX003は、LibDriverがリリースしたPMSX003のフル機能ドライバです。空気質測定機能をはじめとする様々な機能を提供します。LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver PMSX003のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver PMSX003用のプラットフォームに依存しないUARTバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver PMSX003ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver PMSX003プログラミング例が含まれています。

/ docディレクトリには、LibDriver PMSX003オフラインドキュメントが含まれています。

/ datasheetディレクトリには、PMSX003データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないUARTバステンプレートを参照して、指定したプラットフォームのUARTバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/pmsx003/index.html](https://www.libdriver.com/docs/pmsx003/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。