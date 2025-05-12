# Finance Manager
This program is used to track finances on some recurring basis.

The program is written in C++ and will adhere to the following Draft Requirements v1:

## Draft Requirements v1

### The MUSTs
* The program will provide the ability to input your expenses and income.
* It will store all of your expenses with a date attached to it and a note (if you enable noting).
   * The inputted data will be stored in an excel file with the corresponding period.
   * The program will create a new excel file every month (from the 1st of each Month).
* The program will have the ability to create a monthly recurring expenses excel file. This excel file will contain a table with recurring expenses and a note (if noting is enabled).
* The program will then read the information in the stored excel files and create a new excel file, which will have the summary of that month.
   * This excel file will contain information such as:
       * Income - Expenses (plus recurring expenses if the user has enabled that).
       * Money spent per day.
       * Money Left To Live.
           * If the monthly total is negative. The program will compute based on an inputted savings from the user, how many months can the user support such reckless spending.
           * Otherwise it will show a positive message of encouragement.
       * A graph will be created for the day to day expenses and their magnitude in the course over the month.
       * If the user has enabled noting, a pie chart will be created with the distribution of the different total expenses.
* The program will be able to create an excel file, which will be a cumulative file over the year, which will graph the expenses per month.
* The program will provide an interface in the form of a console.
* The program will run on both Windows and Ubuntu.

### The Shoulds
* The program will provide an online interface made available on the local network.
* The interface will have buttons that are interactable with.

### The Coulds
* The program will be able to handle simultaneous input from more than 1 user at a time in the same period.
