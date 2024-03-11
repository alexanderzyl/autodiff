find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)
qt_standard_project_setup()

include_directories(
        ../
)

qt_add_executable(differentiate_sigmoid
        ChartVisualizers.cpp
        differentiate_sigmoid.cpp
)
target_link_libraries(differentiate_sigmoid
        PRIVATE
        Qt6::Core Qt6::Widgets Qt6::Charts)
set_target_properties(differentiate_sigmoid PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)

qt_add_executable(differentiate_cos
        ChartVisualizers.cpp
        differentiate_cos.cpp
)
target_link_libraries(differentiate_cos
        PRIVATE
        Qt6::Core Qt6::Widgets Qt6::Charts)
set_target_properties(differentiate_cos PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)

qt_add_executable(differentiate_sin
        ChartVisualizers.cpp
        differentiate_sin.cpp
)
target_link_libraries(differentiate_sin
        PRIVATE
        Qt6::Core Qt6::Widgets Qt6::Charts)
set_target_properties(differentiate_sin PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)

qt_add_executable(taylor_exp
        ChartVisualizers.cpp
        taylor_exp.cpp
)
target_link_libraries(taylor_exp
        PRIVATE
        Qt6::Core Qt6::Widgets Qt6::Charts)
set_target_properties(taylor_exp PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)

qt_add_executable(taylor_cos
        ChartVisualizers.cpp
        taylor_cos.cpp
)
target_link_libraries(taylor_cos
        PRIVATE
        Qt6::Core Qt6::Widgets Qt6::Charts)
set_target_properties(taylor_cos PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)

qt_add_executable(taylor_sin
        ChartVisualizers.cpp
        taylor_sin.cpp
)
target_link_libraries(taylor_sin
        PRIVATE
        Qt6::Core Qt6::Widgets Qt6::Charts)
set_target_properties(taylor_sin PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)