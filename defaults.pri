# Path to sources/headers/ui.
INCLUDEPATH += $$PWD/src
SRC_DIR = $$PWD
# Path to libxl library.
INCLUDEPATH += /home/mihael/opt/libxl-lin-4.5.1/include_cpp/
# Path to libxl executable
LIBS += /home/mihael/opt/libxl-lin-4.5.1/lib64/libxl.so

DESTDIR = $$PWD/build
# If the DESTDIR does not exist. We create it.
!exists(!$$DESTDIR) {
    QMAKE_POST_LINK += mkdir -p $$DESTDIR
    message("Creating data directory: $$DESTDIR")
}

DATADIR = $$PWD/data
# if the DATADIR does not exist. We create it.
!exists(!$$DATADIR) {
    QMAKE_POST_LINK += mkdir -p $$DATADIR
    message("Creating data directory: $$DATADIR")
}
