#include "expensewindow.h"
#include "ui_expensewindow.h"

ExpenseWindow::ExpenseWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExpenseWindow)
    , _expenseManager(new ExpenseManager(this))
    , _keyPressEater(new EventEater(this))
    , _appTime(std::make_unique<AppTime>()){

    ui->setupUi(this);
    QObject::connect(_expenseManager, &ExpenseManager::UpdateUIStateRequested, this, &ExpenseWindow::UpdateUIState);
    QObject::connect(this, &ExpenseWindow::declareExpensesRequested, _expenseManager, &ExpenseManager::onRequestDeclareExpenses);
    _SetUIState(UIState::Startup);
    _ProcessUIStateChange();
}

ExpenseWindow::~ExpenseWindow(){
    delete ui;
}

bool ExpenseWindow::_isExpenseValid(void){
    bool isFloat = true;
    // We do not use the return value, only to check if it is a valid float.
    (void)ui->DailyExpenses->text().toFloat(&isFloat);

    if(!isFloat){
        return false;
    }

    return true;
}

void ExpenseWindow::_ErrorHandler(void){
    _SetErrorLabel(_GetCurrentErrorText());
}

void ExpenseWindow::_ClearDailyExpenses(void){
    ui->DailyExpenses->clear();
}
void ExpenseWindow::_ClearExpenseNote(void){
    ui->Note->clear();
}

QString ExpenseWindow::_GetExpenseType(void) const{
    return ui->TypeOfExpense->currentText();
}

QString ExpenseWindow::_GetExpenseNote(void) const{
    return ui->Note->text();
}

float ExpenseWindow::_GetDailyExpenseAsFloat(void) {
    return ui->DailyExpenses->text().toFloat();
}

QString ExpenseWindow::_GetDailyExpense(void) const{
    return ui->DailyExpenses->text();
}

void ExpenseWindow::UpdateUIState(void){
    _UpdateUIBasedOnState();
}

void ExpenseWindow::_UpdateUIBasedOnState(void){
    Boundry currentBoundry = _expenseManager->GetCurrentStateOfBoundry();
    // If we are at the head of the Vector means the user can submit expenses.
    if(currentBoundry == Boundry::HeadOfVector){
        _SetUIState(UIState::SubmittingExpenses);
        _ProcessUIStateChange();
        return;
    }
    // If we are not at the head of the Vector andeclareExpensesRequestedd the state is already scrolling,
    // means we do not need to do anything.
    if(currentBoundry != Boundry::HeadOfVector
        && _GetCurrentUIState() == UIState::Scrolling){
        return;
    }
    if(currentBoundry != Boundry::HeadOfVector){
        _SetUIState(UIState::Scrolling);
        _ProcessUIStateChange();
        return;
    }
}
// Startup->DeclareExpenses<->Scrolling(<->EditExpense && <->DeleteExpense)
// Scolling is the crossroad between most UI states.
void ExpenseWindow::_ProcessUIStateChange(void){
    UIState currentUIState = _GetCurrentUIState();
    switch(currentUIState){
    case UIState::Startup:
        // Make sure certain UI elements initialize their values with the correct values.
        unsetCursor();
        ui->CurrentMonth->setFrame(false);
        ui->CurrentMonth->setFocusPolicy(Qt::NoFocus);
        ui->CurrentMonth->setText(_appTime->GetLocalTimeAsString());
        ui->DateOfExpense->setText(_appTime->GetLocalAppTimeAsString());
        ui->HowToUseExpenses->setText("<ul>"
                                      "<li>Input an expense in the Daily Expense box.</li>"
                                      "<li>Then press the Next Day button to increase the day.</li>"
                                      "<li>Whenever you are done, press the Declare Expenses to store all of your submitted expenses.</li>"
                                      "</ul>");
        // Prepare the EventEater to intercept an event if a user clicks on the date to display the calendar.
        ui->DateOfExpense->installEventFilter(_keyPressEater);
        QObject::connect(_keyPressEater,&EventEater::showCalendarRequested,this,&ExpenseWindow::showCalendar);
        // Initialize the list of TypeOfExpenses
        _InitializeTypeOfExpenses();
        // Initialize the starting UI state.
        _SetUIState(UIState::SubmittingExpenses);
        break;
    case UIState::SubmittingExpenses:
        // Place all the UI elements in their proper state.
        unsetCursor();
        ui->Note->setReadOnly(false);
        ui->Note->setFocusPolicy(Qt::StrongFocus);
        ui->DailyExpenses->setFocusPolicy(Qt::StrongFocus);
        ui->DailyExpenses->setReadOnly(false);
        ui->PreviousDay->setEnabled(true);
        ui->NextDay->setEnabled(true);
        _SetShowCalendar(true);
        ui->TypeOfExpense->setEnabled(true);
        ui->HowToUseExpenses->setText("<ul>"
                                      "<li>Input an expense in the Daily Expense box.</li>"
                                      "<li>Then press the Next Day button to increase the day.</li>"
                                      "<li>Whenever you are done, press the Declare Expenses to store all of your submitted expenses.</li>"
                                      "</ul>");
        break;
    case UIState::Scrolling:
        unsetCursor();
        ui->LeftExpense->setEnabled(true);
        ui->RightExpense->setEnabled(true);
        ui->MaxLeft->setEnabled(true);
        ui->MaxRight->setEnabled(true);
        // We make sure the user cannot interact with certain UI elements during this period.
        ui->Note->setReadOnly(true);
        // For some reason, when compiled in WebAssembly, the Notes are still editable.
        // Which is why we also remove Focus.
        ui->Note->setFocusPolicy(Qt::NoFocus);
        ui->DailyExpenses->setReadOnly(true);
        // Same with DailyExpenses.
        ui->DailyExpenses->setFocusPolicy(Qt::NoFocus);
        ui->PreviousDay->setEnabled(false);
        ui->NextDay->setEnabled(false);
        _SetShowCalendar(false);
        ui->TypeOfExpense->setEnabled(false);
        break;
    case UIState::Edit:
        unsetCursor();
        ui->LeftExpense->setEnabled(false);
        ui->RightExpense->setEnabled(false);
        ui->MaxLeft->setEnabled(false);
        ui->MaxRight->setEnabled(false);
        ui->DailyExpenses->setReadOnly(false);
        ui->DailyExpenses->setFocusPolicy(Qt::StrongFocus);
        _SetShowCalendar(true);
        ui->NextDay->setEnabled(true);
        ui->PreviousDay->setEnabled(true);
        ui->TypeOfExpense->setEnabled(true);
        ui->Note->setReadOnly(false);
        ui->Note->setFocusPolicy(Qt::StrongFocus);
        ui->HowToUseExpenses->setText("<ul>"
                                      "<li>You are now in editing mode.</li>"
                                      "<li>Feel free to change the Expense, the Note, Date, or Type of Expense.</li>"
                                      "<li>Whenever you are done, press the Declare Expenses to store all of your newly changed expenses.</li>"
                                      "</ul>");
        break;
    case UIState::Delete:
        _DeleteExpense();
        break;
    case UIState::DeclaringExpenses:
        setCursor(Qt::WaitCursor);
        ui->LeftExpense->setEnabled(false);
        ui->RightExpense->setEnabled(false);
        ui->MaxLeft->setEnabled(false);
        ui->MaxRight->setEnabled(false);
        ui->DailyExpenses->setReadOnly(true);
        ui->DailyExpenses->setFocusPolicy(Qt::NoFocus);
        _SetShowCalendar(false);
        ui->NextDay->setEnabled(false);
        ui->PreviousDay->setEnabled(false);
        ui->TypeOfExpense->setEnabled(false);
        ui->Note->setReadOnly(true);
        ui->Note->setFocusPolicy(Qt::NoFocus);
        ui->BackBtn->setEnabled(false);
        ui->EditExpense->setEnabled(false);
        ui->SubmitExpense->setEnabled(false);
        ui->DeleteExpense->setEnabled(false);
        ui->DeclareExpenses->setEnabled(false);
        ui->HowToUseExpenses->setText("<ul>"
                                      "<li>Expenses are being currently sent over to the server for storage.</li>"
                                      "<li>In the meanwhile please wait.</li>"
                                      "<li>Whenever the sending has finished, you will be notified.</li>"
                                      "</ul>");
    default:
        // How are we here?!
        // Use the error handler to throw an error here.
        break;
    }
}

void ExpenseWindow::_DisplayExpenseNote(QString noteToDisplay){
    ui->Note->setText(noteToDisplay);
}

void ExpenseWindow::_InitializeTypeOfExpenses(void){
    ui->TypeOfExpense->addItem("Food");
    ui->TypeOfExpense->addItem("Recreation");
    ui->TypeOfExpense->addItem("Cat");
    ui->TypeOfExpense->addItem("Technology");
}

void ExpenseWindow::_DisplayCurrentErrorText(void){
    QString style = ui->ErrorLabel->styleSheet();

    if (!style.contains("color: red", Qt::CaseInsensitive)) {
        ui->ErrorLabel->setStyleSheet("color: red;");
    }

    QString currentError = _GetCurrentErrorText();
    ui->ErrorLabel->setText(currentError);
}

void ExpenseWindow::_SetErrorLabel(const QString& message){
    QString style = ui->ErrorLabel->styleSheet();

    if (!style.contains("color: red", Qt::CaseInsensitive)) {
        ui->ErrorLabel->setStyleSheet("color: red;");
    }

    ui->ErrorLabel->setText(message);
}

void ExpenseWindow::_DisplayExpenseInfo(const ExpenseInfo* selectedExpense){
    ui->DailyExpenses->setText(QString::number(selectedExpense->expenseValue,'f', 2));
    ui->TypeOfExpense->setCurrentText(selectedExpense->expenseType);
    _SetNDisplayLocalAppTime(selectedExpense->expenseDate);
    _DisplayExpenseNote(selectedExpense->expenseNote);
}

template<typename T>
void ExpenseWindow::_SetNDisplayLocalAppTime(const T& newLocalAppTime,
                              typename
                              std::enable_if<std::is_same<T,QDate>::value
                                || std::is_same<T,QDateTime>::value
                                || std::is_same<T,QString>::value>::type*){
    _appTime->SetLocalAppTime(newLocalAppTime);
    ui->DateOfExpense->setText(_appTime->GetLocalAppTimeAsString());
}

void ExpenseWindow::_StorePendingInput(void){
    _expenseManager->StoreUserInputtedInfo(_GetDailyExpense(),_appTime->GetLocalAppTime(),_GetExpenseType(),_GetExpenseNote());
}

void ExpenseWindow::_DisplayPendingInput(const LastExpenseInfo* restoredUserInput){
    // Display the value of the expense
    ui->DailyExpenses->setText(restoredUserInput->lastDailyExpense);
    // Store and Display the local app time.
    _SetNDisplayLocalAppTime(restoredUserInput->lastExpenseDate);
    // Display the type of expense
    ui->TypeOfExpense->setCurrentText(restoredUserInput->lastTypeOfExpense);
    // Display the note of the expense
    _DisplayExpenseNote(restoredUserInput->lastExpenseNote);
}

// TODO: We have to check if the expense is a valid value.
// TODO: We have to check if the month value has changed.
// if that is the case, then we need to prompt the user if
// they would like to create a new excel file for that given month.
// if they say No, then they are returned to their previous value.
void ExpenseWindow::on_DailyExpenses_returnPressed(){
    switch(_GetCurrentUIState()){
    case UIState::Scrolling:
        _SetErrorLabel("Cannot submit expense. You are currently scrolling existing expenses. Press the right double arrow to return to inputting new expenses!");
        break;
    case UIState::Edit:
        _EditExpense();
        break;
    case UIState::SubmittingExpenses:
        _DeclareExpense();
        break;
    case UIState::Delete:
        _SetErrorLabel("Cannot submit expense. You are trying to delete an expense. Press the left arrow to be able to see which expenses you can delete.");
        break;
    case UIState::DeclaringExpenses:
        _SetErrorLabel("You cannot submit further expenses while they are being declared. Please wait!");
        break;
    default:
        // AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA?!
        _SetErrorLabel("Unknown state! Internal Error!");
        break;
    }
}

void ExpenseWindow::on_NextDay_clicked(){
    // Increment the current day by 1.
    _appTime->IncrementDayOfLocalAppTime();
    ui->DateOfExpense->setText(_appTime->GetLocalAppTimeAsString());
}

void ExpenseWindow::on_PreviousDay_clicked(){
    // Decrement the current day by 1.
    _appTime->DecrementDayOfLocalAppTime();
    ui->DateOfExpense->setText(_appTime->GetLocalAppTimeAsString());
}

void ExpenseWindow::on_BackBtn_clicked(){
    // TODO:: Add a warning to the user if there is something in the expenses.
    emit closeExpenseWindowRequested();
}

void ExpenseWindow::showExpenseWindow(void){
    this->show();
}

void ExpenseWindow::on_SubmitExpense_clicked(){
    on_DailyExpenses_returnPressed();
}

void ExpenseWindow::showCalendar(){
    if(!_GetShowCalendar()){
        return;
    }
    _SetupCalendar();
    _calendar->show();
    connect(_calendar.get(), &QCalendarWidget::clicked, this, &ExpenseWindow::on_Calendar_clicked);
}

void ExpenseWindow::on_Calendar_clicked(const QDate& clicked_date){
    _SetNDisplayLocalAppTime(clicked_date);
    _calendar->close();
}

void ExpenseWindow::on_LeftExpense_clicked(){
    _expenseManager->MoveExpenseIndexLeft(1);

    if((_expenseManager->GetCurrentStateOfBoundry() == Boundry::Right
        || _expenseManager->GetCurrentStateOfBoundry() == Boundry::LeftRight) // This is in the case of expense size of 1.
        && _expenseManager->GetPreviousStateOfBoundry() == Boundry::HeadOfVector){
        _StorePendingInput();
    }

    const ExpenseInfo* selectedExpense = _expenseManager->GetExpenseAtMovingIndex();
    if(selectedExpense == nullptr){
        _SetErrorLabel("No Expenses to select");
        return;
    }

    _DisplayExpenseInfo(selectedExpense);
}

void ExpenseWindow::on_RightExpense_clicked(){
    _expenseManager->MoveExpenseIndexRight(1);

    if(_expenseManager->GetCurrentStateOfBoundry() == Boundry::HeadOfVector
        && _expenseManager->GetPreviousStateOfBoundry() != Boundry::HeadOfVector){
        const LastExpenseInfo* restoredUserInput = _expenseManager->RestoreUserInputtedInfo();
        _DisplayPendingInput(restoredUserInput);
        return;
    }

    const ExpenseInfo* selectedExpense = _expenseManager->GetExpenseAtMovingIndex();
    if(selectedExpense == nullptr){
        _SetErrorLabel("No Expenses to select");
        return;
    }

    _DisplayExpenseInfo(selectedExpense);
}

void ExpenseWindow::on_MaxRight_clicked(){
    // Restart the Boundry state to HeadOfVector
    _expenseManager->MoveExpenseIndexMaxRight();
    // Restore UserInput
    if(_expenseManager->GetCurrentStateOfBoundry() == Boundry::HeadOfVector
        && _expenseManager->GetPreviousStateOfBoundry() != Boundry::HeadOfVector){
        const LastExpenseInfo* restoredUserInput = _expenseManager->RestoreUserInputtedInfo();
        _DisplayPendingInput(restoredUserInput);
        return;
    }
}

void ExpenseWindow::on_MaxLeft_clicked(){
    // Move the Boundry state to Left
    _expenseManager->MoveExpenseIndexMaxLeft();

    if(_expenseManager->GetPreviousStateOfBoundry() == Boundry::HeadOfVector){
        _StorePendingInput();
    }

    const ExpenseInfo* selectedExpense = _expenseManager->GetExpenseAtMovingIndex();
    if(selectedExpense == nullptr){
        _SetErrorLabel("No Expenses to select");
        return;
    }

    _DisplayExpenseInfo(selectedExpense);
}

void ExpenseWindow::on_EditExpense_clicked(){
    if(_GetCurrentUIState() == UIState::Scrolling){
        _SetUIState(UIState::Edit);
        _ProcessUIStateChange();
    }else{
        _SetErrorLabel("You cannot edit this value! Please press the left arrows of Daily Expense to be able to edit the corresponding values.");
    }
}

void ExpenseWindow::on_DeleteExpense_clicked(){
    if(_GetCurrentUIState() == UIState::Scrolling){
        _SetUIState(UIState::Delete);
        _ProcessUIStateChange();
    }else{
        _SetErrorLabel("You cannot delete this value. You must be scrolling through the already existing expenses for it to work. Please press the left arrow button to see expenses that can be deleted.");
    }
}

void ExpenseWindow::on_DeclareExpenses_clicked(){
    if(_expenseManager->GetExpenses()->size() < 1){
        _SetErrorLabel("There are not expenses submitted to Declare. Please submit at least 1 expense to be able to declare it");
        return;
    }
    _submitExpensesConfirmBox = new QMessageBox(this);

    // Create the UI element of the _submitExpensesConfirmBox
    _submitExpensesConfirmBox->setIcon(QMessageBox::Question);
    _submitExpensesConfirmBox->setWindowTitle("Confirmation");
    _submitExpensesConfirmBox->setText("Are you sure you want to continue with declaring all of your expenses? This will store all of the expenses you have submitted so far.");
    // This line seems to be ignored as well (by WebAssembly), to a point. It makes it Yes/No instead of No/Yes.
    _submitExpensesConfirmBox->setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    // The below line in WebAssembly makess no difference at all. It sill selects Yes as the default
    _submitExpensesConfirmBox->setDefaultButton(QMessageBox::No);

    connect(_submitExpensesConfirmBox, &QMessageBox::finished, this, &ExpenseWindow::on_DeclareExpenses_finished);
    _submitExpensesConfirmBox->show();
}

void ExpenseWindow::on_DeclareExpenses_finished(int usrResponse){
    if(usrResponse == QMessageBox:: Yes){
        _submitExpensesConfirmBox->deleteLater();
        _SetUIState(UIState::DeclaringExpenses);
        _ProcessUIStateChange();
        emit declareExpensesRequested();
    }
}
