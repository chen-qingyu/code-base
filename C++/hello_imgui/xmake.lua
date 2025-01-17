set_project("hello_imgui")
set_version("0.1.0")
set_languages("cxx17")

add_rules("mode.debug", "mode.release")
add_requires("imgui")

target("main")
    set_kind("binary")
    add_packages("imgui")
    add_files("backends/*.cpp")
    add_files("main.cpp")
