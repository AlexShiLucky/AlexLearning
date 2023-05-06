# Kconfig 语言

==========

## 1. 菜单入口

====

Kconifg 文件包含一系列以关键字开头的菜单入口（菜单项）。

### 1.1 config

------

定义一个符号 `symbol`。它是构成 Kconfig 的绝大数菜单入口，其他菜单入口帮助组织此类型入口。 语法如下：

```kconfig
config <symbol>
<config options>
```

### 1.2 menuconfig

----------

此入口和简单 config 入口相似，定义一个符号 `symbol`，但是也暗示一个菜单块，后接子入口。需保证所有子入口应该在此入口下方，且依赖于此入口符号。语法如下：

```kconfig
menuconfig <symbol>
  <config options>
```

### 1.3 choice/endchoice

----------------

定义一个选择组。选择组类型仅仅可以设置为 `bool` 或 `tristate`，如果未指定类型，则取决于第一个选择项的类型。`bool` 类型只允许单个 config 入口被选择，`tristate` 类型允许多个 config 入口被设置为 `m`。 支持语法如下：

```kconfig
choice [<symbol>]
  <choice options>
  <choice block>
endchoice
```

### 1.4 comment

-------

定义注释语句。将在配置阶段显示给用户，并且打印到输出文件中。仅支持依赖属性。语法如下：

```kconfig
comment <prompt>
<comment options>
```

### 1.5 menu/endmunu

------------

定义一个菜单块。菜单块内的其他子入口继承此项的依赖。仅支持依赖和可视属性。语法如下：

```kconfig
menu <prompt>
  <menu options>
  <menu block>
endmenu
```

### 1.6 if/endif

--------

定义一个条件块。条件块内的其他菜单入口追加此项的依赖表达式 `expr`。

```kconfig
if <expr>
  <if block>
endif
```

### 1.7 source

------

读取一个指定的配置文件，此文件总会被解析。

```kconfig
source <file>
```

### 1.8 mainmenu

--------

定义配置程序的标题栏。应该被放在配置文件的开头。

```kconfig
mainmenu <prompt>
```

## 2. 菜单属性

====

菜单项可以有一些属性。但是并不是所有菜单项都支持任意属性，详看菜单项说明。

### 2.1 类型 - type

---------

定义类型的语法如下：

```kconfig
<type>
```

有以下几种类型:

| 类型       | 说明                        |
| -------- | ------------------------- |
| bool     | 布尔类型                      |
| tristate | 三态类型，可以设置为 `y`、`m` 或 `n`。 |
| string   | 字符串类型                     |
| hex      | 十六进制整数类型                  |
| int      | 整数类型                      |

### 2.2 输入提示 - prompt

-------------

每个菜单项最多可以含有一个提示属性，此属性接收一个字符串，直接显示给用户提示输出。语法如下：

```kconfig
prompt <prompt> [if <expr>]
```

也可以在类型后面直接跟输入提示。

```kconfig
<type> <prompt>
```

### 2.3 默认值 - default

-------------

一个配置菜单项可以接收多个默认值，但是仅第一个默认值有效。未指定默认值的 config 入口默认未选定。语法如下：

```kconfig
default <value> [if <expr>]
```

也可以在类型后面直接跟默认值。

```kconfig
def_bool/def_tristate <value> [if <expr>]
```

### 2.4 依赖 - depends

------------

菜单项的依赖属性会应用到所有的其他属性上。同时指定多个依赖属性时，它必须同时满足，即为`逻辑与`关系。语法如下：

```kconfig
depends on <expr>
```

### 2.5 反向依赖 - select

-------------

此属性可以强制选定一个符号，无论此符号的依赖是否满足。被选定的符号仅支持 `bool` 或 `tristate` 类型。语法如下：

```kconfig
select <symbol> [if <expr>]
```

### 2.6 弱反向依赖 - imply

-------------

此属性和 `select` 相似，用于选定一个符号，但是被选定的符号仍有可能被直接依赖或用户输入设置为 `n`。语法如下：

```kconfig
imply <symbol> [if <expr>]
```

> 例子：
> 
> 假设有如下定义：
> 
> config FOO    tristate "foo"
>     imply BAZconfig BAZ    tristate "baz"
>     depends on BAR
> 
> 则它们可能的值如下：
> 
> | FOO | BAR | BAZ 的默认值 | BAZ 可选值 |
> | --- | --- | -------- | ------- |
> | n   | y   | n        | y/m/n   |
> | m   | y   | m        | y/m/n   |
> | y   | y   | y        | y/m/n   |
> | n   | m   | n        | m/n     |
> | m   | m   | m        | m/n     |
> | y   | m   | n        | m/n     |
> | y   | n   | n        | n       |

### 2.7 可见性 - visible

-------------

此属性仅用于菜单块，根据条件来决定是否向用户显示菜单块（但是包含的符号依然可以被其他符号选定），和应用于单个菜单项的 `prompt` 属性相似。定义语法如下：

```kconfig
visible if <expr>
```

### 2.8 数字范围 - range

------------

此属性用于限制 `int` 和 `hex` 类型符号的输出值的范围。定义语法如下：

```kconfig
range <symbol> <symbol> [if <expr>]
```

### 2.9 帮助文本 - help

-----------

此属性定义一段帮助文本。可以为多行或空行，当行的缩进级别小于帮助文本的第一行时，表示结束。定义语法如下：

```kconfig
help
    <help text>
```

### 2.10 表达式 expr

========

很多菜单属性都可以使用表达式 expr，表达式含有以下几种：

| 表达式                  | 说明                                              |
| -------------------- | ----------------------------------------------- |
| <symbol>             | `bool` 和 `tristate` 符号简单转换为相应表达式的值。其他类型转换为 `n`。 |
| <symbol> = <symbol>  | 如果两个符号相等，就返回 y，否则返回 n。                          |
| <symbol> != <symbol> | 参考上述                                            |
| <symbol> < <symbol>  | 参考上述                                            |
| <symbol> > <symbol>  | 参考上述                                            |
| <symbol> <= <symbol> | 参考上述                                            |
| <symbol> >= <symbol> | 参考上述                                            |
| ( <expr> )           | 返回表达式的值，用于优先级。                                  |
| ! <expr>             | 取反                                              |
| <expr> && <expr>     | 逻辑与                                             |
| <expr> \| <expr>     | 逻辑或                                             |

## 3. 宏定义

===

Kconfig 也支持宏定义，和 Makefile 语法非常相似。

### 3.1 变量

--

和 Makefile 相似，Kconfig 变量作为一个宏变量，被扩展为一个字符串。有两种类型的变量

1. 简单扩展变量
   使用 `:=` 赋值符号定义的变量。当读到该行时，它的右边立刻扩展。

2. 递归扩展变量
   使用 `=` 赋值符号定义的变量。它的右边被简单保存字面值（未扩展的值），当变量使用时才真正扩展。

可以使用 `+=` 赋值符号向变量追加文本，不改变符号的类型。使用一个变量的语法如下：

```kconfig
$(var)
```

### 3.2 函数

--

Kconfig 提供和 Makefile 类似的定义使用宏函数的功能。调用函数的语法如下：

```kconfig
$(func,arg1,arg2...)
```

> 注意：
> 
> 1. Kconfig 仅使用 `,` 作为分隔符，但是 Makefile 的函数名和第一个参数用空白字符分隔。如下：
>    $(func arg1,arg2...)
> 
> 2. Kconfig 调用用户定义的函数和内建函数使用相同的方式，但是 Makefile 调用用户定义的函数时，必须使用关键字 `call` 触发。如下：
>    $(call my-func,arg1,arg2...)

Kconfig 目前支持以下内建函数：

- 扩展为执行的子命令 command 的标准输出。

```kconfig
$(shell,command)
```

- 发送一段文本 text 到标准输出。

```kconfig
$(info,text)
```

- 如果条件为真，则发送文本 text 和当前 Kconfig 文件名以及行号到错误输出。

```kconfig
$(warning-if,condition,text)
```

- 和 warning-if 相似，但是会立刻终止解析。

```kconfig
$(error-if,condition,text)
```

- 扩展为被解析的文件名。

```kconfig
$(filename)
```

- 扩展为被解析的行号。

```kconfig
$(lineno)
```
