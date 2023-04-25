-- project
set_project("crontab")

-- set xmake minimum version
set_xmakever("2.6.1")

-- set project version
set_version("1.0", {build = "%Y%m%d"})

-- set warning all as error
set_warnings("error")

-- set language: c99
stdc = "c99"
set_languages(stdc)

-- add build modes
add_rules("mode.release", "mode.debug")
add_includedirs("include")

target("crontab")
    set_kind("binary")
    add_files("main.c")
    add_files("source/*.c")
    add_files("test/*.c")

-- include project sources
--includes("lib")
