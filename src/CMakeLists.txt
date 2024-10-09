idf_component_register(SRCS "OLEDManager.cpp" "NeoPixelManager.cpp" "NetworkManager.cpp" "oled_display.cpp" "hello_world_main.c"
                    INCLUDE_DIRS "")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
