QT += quick

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	src/main/source/main.cpp \
	src/main/source/syst.cpp \
	src/process/source/process_manager.cpp \
	src/process/source/processes_manager.cpp \

HEADERS += \
	src/main/header/factory_default_config.h \
	src/main/header/syst.h \
	src/process/header/process_manager.h \
	src/process/header/processes_manager.h \

INCLUDEPATH += \
	src/main/header \
	src/process/header \

RESOURCES += \
	ihm/qml.qrc

TRANSLATIONS += \
	MountDrive_fr_FR.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
