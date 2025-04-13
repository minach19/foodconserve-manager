QT += core gui sql charts widgets printsupport network serialport

CONFIG += c++17

SOURCES += \
    arduino.cpp \
    client.cpp \
    connection.cpp \
    employees.cpp \
    livraison.cpp \
    mailer.cpp \
    main.cpp \
    mainwindow.cpp \
    messagingwindow.cpp
    # notifier.cpp

HEADERS += \
    arduino.h \
    client.h \
    connection.h \
    employees.h \
    livraison.h \
    mailer.h \
    mainwindow.h \
    messagingwindow.h
    # notifier.h

FORMS += \
    mainwindow.ui

QT += network
