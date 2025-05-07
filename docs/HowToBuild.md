## Building&Debugging Finance Manager

Currently Finance Manager supports Ubuntu (or Linux based machines) with Qt. 

These are the prerequisits for this project to be buildable/debuggable:
1. Linux (In my case Ubuntu 24.04.2 LTS)
    - Currently the paths in defaults.pri are hardcoded to use linux PWD command.
    - For it to work on windows (for now) you will need to change those to your OS specific slashes.
2. Download and install open source QT [Download] (https://www.qt.io/download-qt-installer)

The steps to build are:

1. Open QT Creator
2. Open Existing Project
3. Open the directory of the project and double click on finance_manager_qt.pro.
4. You should be able to use F5 to build and debug the project.