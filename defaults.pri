# Path to sources/headers/ui.
INCLUDEPATH += $$PWD/src
SRC_DIR = $$PWD

DESTDIR = $$PWD/build
# If the DESTDIR does not exist. We create it.
!exists(!$$DESTDIR) {
    QMAKE_POST_LINK += mkdir -p $$DESTDIR
    message("Creating data directory: $$DESTDIR")
}
