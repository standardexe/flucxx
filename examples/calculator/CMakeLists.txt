set(PROJECT_SOURCES
        main.cpp

        actions/CalculatorActions.hpp
        actions/QmlActions.hpp

        middlewares/LoggingMiddleware.hpp

        stores/MainStore.hpp
)

qt5_add_resources(PROJECT_SOURCES qml/qml.qrc)

add_executable(calculator_flucxx ${PROJECT_SOURCES})

target_link_libraries(calculator_flucxx
  PRIVATE Qt5::Core Qt5::Quick flucxx)

install(TARGETS calculator_flucxx
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

