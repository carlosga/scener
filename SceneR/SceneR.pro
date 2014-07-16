# Add more folders to ship with the application, here
folder_01.source = qml/SceneR
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

CONFIG   += c++11

QMAKE_CXXFLAGS += -stdlib=libc++ -m64
QMAKE_LFLAGS += -stdlib=libc++ -m64

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += \
    AstroBoy.cpp \
    BumbleBee.cpp \
    Felicia.cpp \
    main.cpp \
    Marcus.cpp \
    SampleRenderer.cpp \
    WarForrest.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    AstroBoy.hpp \
    BumbleBee.hpp \
    Felicia.hpp \
    Marcus.hpp \
    SampleRenderer.hpp \
    WarForrest.hpp

OTHER_FILES += \
    Content/BasicEffect.frag \
    Content/SkinnedEffect.frag \
    Content/BasicEffect.vert \
    Content/SkinnedEffect.vert

unix|win32: LIBS += -L$$PWD/../bin/debug -lSceneR.Framework
unix|win32: LIBS += -L$$PWD/../../regal/lib/linux/ -lRegal

DEPENDPATH += $$PWD/../../regal/include
INCLUDEPATH += $$PWD/../../regal/include \
               $$PWD/../SceneR.Framework/Headers \
               $$PWD/Headers

VPATH += $$PWD/Headers \
         $$PWD/Sources
