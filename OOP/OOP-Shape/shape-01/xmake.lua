-- project
set_project("demo")

-- set xmake minimum version
set_xmakever("2.6.1")

-- set project version
set_version("1.0", {build = "%Y%m%d"})

-- set warning all as error
set_warnings("all", "error")

-- set language: c99
stdc = "c99"
set_languages(stdc)

-- add build modes
add_rules("mode.release", "mode.debug")
add_includedirs("include")

target("shape")
    set_kind("static")
    add_files("lib/libshape/source/*.c")
    add_includedirs("lib/libshape/include")

target("demo")
    set_kind("binary")
    add_deps("shape")
    add_files("main.c")
    add_includedirs("lib/libshape/include")

-- include project sources
--includes("lib")
