/*
********************************************************************************
* vtansi.h
*
*   Copyright (C) 2019 Agilent Technologies, Inc. All rights reserved.
*   Copyright (C) 2010-2018 ACEA Biosciences, Inc. All rights reserved.
*   Author: AlexShi <alex.shi@agilent.com>
*
* Note(s): ANSI/VT100 Terminal Control Escape Sequences
********************************************************************************
*/

#ifndef __VTANSI_H
#define __VTANSI_H

/*
********************************************************************************
* Included Files
********************************************************************************
*/


/*
********************************************************************************
* Documents
********************************************************************************
*/

//  BBS支持ANSI/3.64控制码标准，ANSI控制码均以Esc[作为控制码的开始标志。
//  BBS中ESC字符的输入方法是[ESC]+[ESC]，在编辑器中用"*"代表。
//  *是按两下ESC键或者按ALT+027(数字键盘)两次，在Cterm里面也可以按Insert。
//  签名档有六行的行数限制(所谓六行，是输入字符占六行 而不是显示字符占六行)，
//  BBS目前的每行字符限制在240左右，因而一个签名档总共可使用大约1320个字符。
//  做活动签名档就要掌握ANSI光标控制码，原理和动画制作一样。
//  DOS支持大部分ANSI控制码，在DOS下使用请看c:>help ansi.sys(无效命令？)
//  下面是BBS常用ANSI控制码表，注意控制符区分大小写。
//  DEVICE=ANSI.SYS
//                  BBS  常  用  ANSI  控  制  码  表
// 【光标控制】
// ┏━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃  控  制  码  ┃                说                    明                  ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃    [X;YH     ┃  将光标移至第 X 行，第 Y 列的位置。                      ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [nA      ┃  光标上移 n 列。<<若至屏幕顶端则无效>>                   ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [nB      ┃  光标下移 n 列。<<若至屏幕底端则无效>>                   ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [nC      ┃  光标向右 n 行。<<若已至屏幕最右端则无效>>               ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [nD      ┃  光标向左 n 行。<<若已至屏幕最左端则无效>>               ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [6n      ┃  报告光标位置。                                          ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [s       ┃  保存目前的光标位置。                                    ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [u       ┃  取出保存的光标位置来使用。                              ┃
// ┗━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
//  注: BBS 系统一屏显示大约是 25*80，后两行为 BBS 系统占用，实际只有 23*80。

// 【屏幕控制】
// ┏━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃  控  制  码  ┃                说                    明                  ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [2J      ┃  清除屏幕。 <<功能和 DOS 的 CLS 命令一样>>               ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [K       ┃  将光标位置开始至本列结束的所有字符清除。                ┃
// ┗━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// 【显示字符属性控制】
// ┏━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃  控  制  码  ┃                说                    明                  ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃              ┃Ⅰ设定显示字符的属性状态。                                ┃
// ┃[n1;n2;......m┃Ⅱ若有两个以上的属性状态要设定则以分号将代码(n1;n2;..)隔开┃
// ┃              ┃Ⅲ除非重新设定，否则原设定之属性一直被保留。              ┃
// ┗━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
// ┏━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃   代   码    ┃                意                    义                  ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃      0       ┃  所有属性 OFF，即返回正常显示模式 (Normal)               ┃
// ┃      1       ┃  高亮度显示 (Bright)                                     ┃
// ┃      4       ┃  加下划线 (Underline) (注1)                              ┃
// ┃      5       ┃  闪烁显示 (Flash) (注2)                                  ┃
// ┃      7       ┃  反相显示 (Inverse)                                      ┃
// ┃      8       ┃  不可见 (Invisable)                                      ┃
// ┣━━━┳━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃ 前景 ┃ 背景 ┃                颜                    色                  ┃
// ┣━━━╋━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃  30  ┃  40  ┃  黑色                                                    ┃
// ┃  31  ┃  41  ┃  红色                                                    ┃
// ┃  32  ┃  42  ┃  绿色                                                    ┃
// ┃  33  ┃  43  ┃  黄色                                                    ┃
// ┃  34  ┃  44  ┃  蓝色                                                    ┃
// ┃  35  ┃  45  ┃  紫红色                                                  ┃
// ┃  36  ┃  46  ┃  青蓝色                                                  ┃
// ┃  37  ┃  47  ┃  白色                                                    ┃
// ┗━━━┻━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
// 注1: 老版本的Sterm不支持下画线功能，现在的1.266+版本支持下划线，且下划线的颜
//      色和前景色一致。例如，前景色是绿色的，则下划线也是绿色。而使用Cterm看到
//      的下划线一律都为白色，不论前景色是什么颜色。
// 注2: Sterm和Cterm显示效果略有不同。本来背景色是没有高亮的，但是Sterm 1.266版
//      本却有显示高亮背景的本领，就是通过这个相反显示函数。例如高亮红色前景和
//      低亮的黄色背景，如果你用Sterm 1.266版来看的话，加了反显函数之后那个例子
//      变成了高亮的红色背景和低亮的黄色前景，就是前景色和背景色完全互换，连亮
//      度也互换。但如果用Cterm来看得话，加了反显函数之后的例子是低亮的红色背景
//      和高亮的黄色前景，颜色互换，亮度不换，因为Cterm无法显示出高亮的背景。

// 【字体控制】
// ┏━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃  控  制  码  ┃                说                    明                  ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [0I      ┃  恢复正常字体                                            ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [1I      ┃  宋体                                                    ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [2I      ┃  黑体                                                    ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [3I      ┃  楷体                                                    ┃
// ┗━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

// 【特殊控制】
// ┏━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃  控  制  码  ┃                说                    明                  ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [G       ┃  响铃                                                    ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [nU      ┃  URL确认(n个字节)                                        ┃
// ┣━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
// ┃     [nM      ┃  延时(n为微秒数) <<Cterm和Sterm 1.266+版本才支持此功能>> ┃
// ┗━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

//                       特  殊  的  上  色  控  制  符

// :号
// 其实就是当你回文章时系统在文章前所加的:，它会使文章颜色变为暗青色，与*[0;36m
// 效果相同，这个冒号必须是英文输入法状态下的冒号，而且必须处在该行第一的位置，
// 冒号后可以有空格，该符号只对本行内容有效。

// 【 在……………… 】格式
// 这种格式也要处在该行的起始位置，效果与*[1;33m的效果相同，【后要空上一个英文字
// 符的位置，那个"在"字不能少，而且必须是第一个字，后面的内容任意。该符号对从
// 此行开始的一屏内所有文字都有效。

// >号
// 效果和:号完全一样，也是要放在该行的起始位置，>号后面可以不空格，也可以加空格，
// 效果都一样。该符号仅对本行的内容有效。

// ==>号
// 效果相当于*[1;33m，位置也要位于该行起始位置，==>后面不需空格，加空格也可以，
// 该符号对从此开始一屏内的内容均有效。

//                                色  彩  常  识

// 三原色: 红黄蓝
// 红+黄=橙  黄+蓝=绿  红+蓝=紫  红+黄+蓝=黑

// 三原光：红绿蓝
// 红+绿=黄  绿+蓝=青  红+蓝=紫  红+绿+蓝=白

// 计算机上的颜色系统都是按照三原光设置的。

//              ANSI.SYS and NANSI.SYS Functions  -  ANSI x3.64
//
//      ESC[y,xH     Cursor position y,x
//      ESC[nA       Cursor Up n lines
//      ESC[nB       Cursor Down n lines
//      ESC[nC       Cursor Forward n characters
//      ESC[nD       Cursor Backward n characters
//      ESC[y;xf     Cursor position y,x (less frequently used)
//      ESC[y;xR     Cursor position report y,x
//      ESC[6n       Device status report (cursor pos)(n is constant 'n')
//      ESC[s        Save cursor position
//      ESC[u        Restore cursor position
//      ESC[2J       Erase display
//      ESC[K        Erase to end of line
//      ESC[nL       Inserts n blank lines at cursor line.   (NANSI)
//      ESC[nM       Deletes n lines including cursor line.  (NANSI)
//      ESC[n@       Inserts n blank chars at cursor.        (NANSI)
//      ESC[nP       Deletes n chars including cursor char.  (NANSI)
//      ESC[nP       Deletes n chars including cursor char.  (NANSI)
//      ESC[n;ny     Output char translate                   (NANSI)
//                   When first char is encountered in output request, it
//                   is replaced with the second char.  When no parameters
//                   are given, all chars are reset.
//      ESC["str"p   Keyboard Key Reassignment. The first char of str gives
//                   the key to redefine; the rest of the string is the
//                   key's new value.  To specify unprintable chars, give
//                   the ASCII value of the char outside of quotes, as a
//                   normal parm.   IBM function keys are two byte strings.
//
//                   Ex:  ESC[0;";dir a:";13;p
//
//                   redefines F1 to have the value "dir a:" followed by CR.
//                   If no parameters given, all keys are reset to their
//                   default values.  Single or double quotes are valid.
//
//      ESC[n;n;...nm  Set Graphics Rendition is used to set attributes as
//        well as foreground and background colors.  If multiple parameters
//        are used, they are executed in sequence, and the effects are
//        cumulative. 'n' is one of the following attributes or colors:
//        0  All attributes off       5  Blink
//        1  Bold                     7  Reverse Video
//        2  Dim                      8  Invisible
//        4  Underline
//
//      Foreground colors          Background colors
//
//         30  Black                  40  Black
//         31  Red                    41  Red
//         32  Green                  42  Green
//         33  Yellow                 43  Yellow
//         34  Blue                   44  Blue
//         35  Magenta                45  Magenta
//         36  Cyan                   46  Cyan
//         37  White                  47  White
//
//      ESC[=nh     Set mode (see screen modes for n)
//      ESC[=nl     Reset Mode (see screen modes for n)
//
//          Screen modes are similar to those found in the IBM BIOS:
//
//             0   text 40x25 Black & White
//             1   text 40x25 Color
//             2   text 80x25 Black & White
//             3   text 80x25 Color
//             4   320x200 4 bits/pixel
//             5   320x200 1 bit/pixel
//             6   640x200 1 bit/pixel
//             7   cursor wrap
//            13   320x200 4 bits/pixel (EGA)
//            14   640x200 4 bits/pixel (EGA)
//            16   640x350 4 bits/pixel (EGA)


/*
********************************************************************************
* Pre-processor Definitions
********************************************************************************
*/

/* ANSI/VT100 Terminal Control Escape Sequences */
/*
Many computer terminals and terminal emulators support colour and cursor control
through a system of escape sequences. One such standard is commonly referred to
as ANSI Colour. Several terminal specifications are based on the ANSI colour
standard, including VT100.

The following is a partial listing of the VT100 control set.

<ESC> represents the ASCII "escape" character, 0x1B/033. Bracketed tags represent
modifiable decimal parameters; eg. {ROW} would be replaced by a row number.
*/

/* [Device Status] */
// The following codes are used for reporting terminal/display settings, and
// vary depending on the implementation:
// Query Device Code        <ESC>[c
// Requests a Report Device Code response from the device.
#define VTANSI_QUERY_DEVICE_CODE                "\033[c"

// Report Device Code       <ESC>[{code}0c
// Generated by the device in response to Query Device Code request.
#define VTANSI_REPORT_DEV_CODE(code)            "\033["#code"0c"

// Query Device Status      <ESC>[5n
// Requests a Report Device Status response from the device.
#define VTANSI_QUERY_DEVICE_STATUS              "\033[5n"

// Report Device OK         <ESC>[0n
// Generated by the device in response to a Query Device Status request;
// indicates that device is functioning correctly.
#define VTANSI_REPORT_DEV_OK                    "\033[0n"

// Report Device Failure    <ESC>[3n
// Generated by the device in response to a Query Device Status request;
// indicates that device is functioning improperly.
#define VTANSI_REPORT_DEV_FAILED                "\033[3n"

// Query Cursor Position    <ESC>[6n
// Requests a Report Cursor Position response from the device.
#define VTANSI_QUERY_CURSOR_POS                 "\033[6n"

// Report Cursor Position   <ESC>[{ROW};{COLUMN}R
// Generated by the device in response to a Query Cursor Position request;
// reports current cursor position.
#define VTANSI_REPORT_CURSOR_POS(row,col)       "\033["#row";"#col"R"


/* [Terminal Setup] */
// The h and l codes are used for setting terminal/display mode, and vary
// depending on the implementation. Line Wrap is one of the few setup codes that
// tend to be used consistently:
// Reset Device             <ESC>c
// Reset all terminal settings to default.
#define VTANSI_RESET_DEV                        "\033c"

// Enable Line Wrap         <ESC>[7h
// Text wraps to next line if longer than the length of the display area.
#define VTANSI_ENABLE_LINE_WRAP                 "\033[7h"

// Disable Line Wrap        <ESC>[7l
// Disables line wrapping.
#define VTANSI_DISABLE_LINE_WRAP                "\033[7l"


/* [Fonts] */
// Some terminals support multiple fonts: normal/bold, swiss/italic, etc. There are
// a variety of special codes for certain terminals; the following are fairly standard:
// Font Set G0              <ESC>(
// Set default font.
#define VTANSI_FONT_SET_G0                      "\033("

// Font Set G1              <ESC>)
// Set alternate font.
#define VTANSI_FONT_SET_G1                      "\033)"


/* [Cursor Control] */
// Cursor Home              <ESC>[{ROW};{COLUMN}H
// Sets the cursor position where subsequent text will begin. If no row/column
// parameters are provided (ie. <ESC>[H), the cursor will move to the home position,
// at the upper left of the screen.
#define VTANSI_CURSOR_HOME                      "\033[H"
#define VTANSI_ROW_HOME(col)                    "\033[;"#col"H"
#define VTANSI_COL_HOME(row)                    "\033["#row";H"
#define VTANSI_SET_HOME(row, col)               "\033["#row";"#col"H"

// Cursor Up                <ESC>[{COUNT}A
// Moves the cursor up by COUNT rows; the default count is 1.
#define VTANSI_CURSOR_UP(count)                 "\033["#count"A"

// Cursor Down              <ESC>[{COUNT}B
// Moves the cursor down by COUNT rows; the default count is 1.
#define VTANSI_CURSOR_DOWN(count)               "\033["#count"B"

// Cursor Forward           <ESC>[{COUNT}C
// Moves the cursor forward by COUNT columns; the default count is 1.
#define VTANSI_CURSOR_FORWARD(count)            "\033["#count"C"

// Cursor Backward          <ESC>[{COUNT}D
// Moves the cursor backward by COUNT columns; the default count is 1.
#define VTANSI_CURSOR_BACKWARD(count)           "\033["#count"D"

// Force Cursor Position    <ESC>[{ROW};{COLUMN}f
// Identical to Cursor Home.
#define VTANSI_FORCE_CURSOR_POS(row,col)        "\033["#row";"#col"f"

// Save Cursor              <ESC>[s
// Save current cursor position.
#define VTANSI_SAVE_CURSOR                      "\033[s"

// Unsave Cursor            <ESC>[u
// Restores cursor position after a Save Cursor.
#define VTANSI_UNSAVE_CURSOR                    "\033[u"

// Save Cursor & Attrs      <ESC>7
// Save current cursor position.
#define VTANSI_SAVE_CURSOR_AND_ATTRS            "\0337"

// Restore Cursor & Attrs   <ESC>8
// Restores cursor position after a Save Cursor.
#define VTANSI_RESTORE_CURSOR_AND_ATTRS         "\0338"


/* [Scrolling] */
// Scroll Screen            <ESC>[r
// Enable scrolling for entire display.
#define VTANSI_SCROLL_ALL_SCR                   "\033[r"

// Scroll Screen            <ESC>[{start};{end}r
// Enable scrolling from row {start} to row {end}.
#define VTANSI_SCROLL_SCR(start,end)            "\033["#start";"#end"r"

// Scroll Down              <ESC>D
// Scroll display down one line.
#define VTANSI_SCROLL_DOWN                      "\033D"

// Scroll Up                <ESC>M
// Scroll display up one line.
#define VTANSI_SCROLL_UP                        "\033M"


/* [Tab Control] */
// Set Tab                  <ESC>H
// Sets a tab at the current position.
#define VTANSI_SET_TAB                          "\033H"

// Clear Tab                <ESC>[g
// Clears tab at the current position.
#define VTANSI_CLR_TAB                          "\033[g"

// Clear All Tabs           <ESC>[3g
// Clears all tabs.
#define VTANSI_CLR_ALL_TABS                     "\033[3g"


/* [Erasing Text] */
// Erase End of Line        <ESC>[K
// Erases from the current cursor position to the end of the current line.
#define VTANSI_ERASE_CUR_LINE_END_PART          "\033[K"

// Erase Start of Line	    <ESC>[1K
// Erases from the current cursor position to the start of the current line.
#define VTANSI_ERASE_CUR_LINE_START_PART        "\033[1K"

// Erase Line		        <ESC>[2K
// Erases the entire current line.
#define VTANSI_ERASE_CUR_LINE_ALL               "\033[2K"

// Erase Down		        <ESC>[J
// Erases the screen from the current line down to the bottom of the screen.
#define VTANSI_ERASE_CUR_LINE_DOWN_PART         "\033[J"

// Erase Up		            <ESC>[1J
// Erases the screen from the current line up to the top of the screen.
#define VTANSI_ERASE_CUR_LINE_UP_PART           "\033[1J"

// Erase Screen		        <ESC>[2J
// Erases the screen with the background colour and moves the cursor to home.
#define VTANSI_ERASE_SCR                        "\033[2J"


/* [Printing] */
// Some terminals support local printing:
// Print Screen		        <ESC>[i
// Print the current screen.
#define VTANSI_PRINT_SCR                        "\033[i"
// Print Line		        <ESC>[1i
// Print the current line.
#define VTANSI_PRINT_LINE                       "\033[1i"

// Stop Print Log		    <ESC>[4i
// Disable log.
#define VTANSI_STOP_PRINT_LOG                   "\033[4i"

// Start Print Log		    <ESC>[5i
// Start log; all received text is echoed to a printer.
#define VTANSI_START_PRINT_LOG                  "\033[5i"


/* [Define Key] */
// Set Key Definition	<ESC>[{key};"{string}"p
// Associates a string of text to a keyboard key. {key} indicates the key by its ASCII value in decimal.
#define VTANSI_SET_KEY(key,str)                 "\033["#key";\""#str"\"p"


/*
Set Display Attributes
    Set Attribute Mode  <ESC>[{attr1};...;{attrn}m
Sets multiple display attribute settings. The following lists standard attributes:
    0   Reset all attributes        5   Blink
    1   Bright                      7   Reverse
    2   Dim                         8   Hidden
    4   Underscore

    Foreground Colours              Background Colours
    30  Black                       40  Black
    31  Red                         41  Red
    32  Green                       42  Green
    33  Yellow                      43  Yellow
    34  Blue                        44  Blue
    35  Magenta                     45  Magenta
    36  Cyan                        46  Cyan
    37  White                       47  White
*/
#define VTANSI_DISPLAY_RESET                    "\033[m"
#define VTANSI_DISPLAY_OFF                      "\033[0m"
#define VTANSI_DISPLAY_BOLD                     "\033[1m"
#define VTANSI_DISPLAY_UNDERSCORE               "\033[4m"
#define VTANSI_DISPLAY_BLINK                    "\033[5m"
#define VTANSI_DISPLAY_REVERSE                  "\033[7m"
#define VTANSI_DISPLAY_HIDDEN                   "\033[8m"

#define VTANSI_COLOR_RED                        "\033[31m"
#define VTANSI_COLOR_GREEN                      "\033[32m"
#define VTANSI_COLOR_YELLOW                     "\033[33m"
#define VTANSI_COLOR_BLUE                       "\033[34m"
#define VTANSI_COLOR_MAGENTA                    "\033[35m"
#define VTANSI_COLOR_CYAN                       "\033[36m"
#define VTANSI_COLOR_WHITE                      "\033[37m"

#define VTANSI_COLOR_BG_BLACK                   "\033[40m"
#define VTANSI_COLOR_BG_RED                     "\033[41m"
#define VTANSI_COLOR_BG_GREEN                   "\033[42m"
#define VTANSI_COLOR_BG_YELLOW                  "\033[43m"
#define VTANSI_COLOR_BG_BLUE                    "\033[44m"
#define VTANSI_COLOR_BG_MAGENTA                 "\033[45m"
#define VTANSI_COLOR_BG_CYAN                    "\033[46m"
#define VTANSI_COLOR_BG_WHITE                   "\033[47m"

#define VTANSI_COLOR_LIGHT_RED                  "\033[1;31m"
#define VTANSI_COLOR_LIGHT_GREEN                "\033[1;32m"
#define VTANSI_COLOR_LIGHT_YELLOW               "\033[1;33m"
#define VTANSI_COLOR_LIGHT_BLUE                 "\033[1;34m"
#define VTANSI_COLOR_LIGHT_MAGENTA              "\033[1;35m"
#define VTANSI_COLOR_LIGHT_CYAN                 "\033[1;36m"


/*
********************************************************************************
* Public Types
********************************************************************************
*/



/*
********************************************************************************
* Inline Functions
********************************************************************************
*/



/*
********************************************************************************
* Public Variables
********************************************************************************
*/



/*
********************************************************************************
* Public Function Prototypes
********************************************************************************
*/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif      /* __VTANSI_H */

/*
********************************************************************************
* No More!
********************************************************************************
*/
