set_languages("cxx20")

add_rules("mode.debug", "mode.release")
add_requires("boost")
add_requires("libpng")
add_requires("pyincpp")

target("main")
    set_kind("binary")
    add_packages("boost")
    add_packages("libpng")
    add_packages("pyincpp")
    add_files("*.cpp")
