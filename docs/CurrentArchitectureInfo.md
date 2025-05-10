# Current Architecture
![The architecture envisioned when designing the project till this point](diagrams/CurrentSystemArchitecture.svg)

## Main Window
The Main Window (MW) is responsible for the creation and destruction of all other windows. Whenever the program begins, it initializes and shows the LogInWindow to the user. When the user has successfully logged in, the MainWindow receives an event and it deallocates the resources it has provided and changes to the next appropriate window. This is how all windows function. They are allocated resources by the MW and the created window sends an event back whenever it wants to be terminated, in which case the MW deallocates the resources and makes sure the appropriate window is shown to the user.

### User Interface of the Main Window
The window provides three buttons, each of which allows the user to enter into the three different windows; Expense Window, Summary Window, and Recurring Expense Window. For each of these buttons, the MW allocates resources, shows the window to the user, and emits and event to tell the corresponding window that it is now ready to function. Each of those windows have a "back" button that allows the user to go back to the MW and in that case, the MW takes care of deallocation of all the assigned resources.

## LogIn Window & User Interface

This window serves as an authenthication step, and communicates with the MW through events. It provides two QLineEdits to the user, which allows them to input their username and password. It then provides a button which when pressed checks if the username and password match with the credentials stored on the client side. In the future the credentials will be stored on the server side, to avoid the security issue. For demonstration purposes, for now the label on the starting page states that "admin/admin" can be used as username and password.

## Expense Window

This window is in charge of allowing the user to submit/edit/delete/declare their expenses.