#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    setGeometry(500,200,500,500);  // The position of the window when it's pop up
    setWindowIcon(QIcon(":/Icons/logo.png"));

    textarea = new  QTextEdit();
    font->setPointSize(12); // default font = 12
    textarea->document()->setDefaultFont(*font);

    setCentralWidget(textarea);
    createMenu();
    createToolBar();
    createStatusBar();

    findWindow();

    setCurrentFile(QString(""));

    createConnections();
}

void MainWindow::createConnections()
{

    // Textarea signals & slots
    connect(textarea->document(), &QTextDocument::contentsChanged, this, &MainWindow::documntModified);
    connect(textarea,  &QTextEdit::cursorPositionChanged, this, &MainWindow::showCursorPos);

    // File signals & slots
    connect(newAction, &QAction::triggered, this, &MainWindow::New);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exit);

    // Edit signals & slots
    connect(undoAction, &QAction::triggered, this, &MainWindow::undo);
    connect(redoAction, &QAction::triggered, this, &MainWindow::redo);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copy);
    connect(cutAction, &QAction::triggered, this, &MainWindow::cut);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::paste);
    connect(findAction, &QAction::triggered, this, &MainWindow::showFindWindow);

    // View signals & slots
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOut);
    connect(darkModeAction, &QAction::triggered, this, &MainWindow::darkMode);
    connect(lightModeAction, &QAction::triggered, this, &MainWindow::lightMode);

    // Format signals & slots
    connect(leftAlignment, &QAction::triggered, this, [this]{ alignment(0); });
    connect(rightAlignment, &QAction::triggered, this, [this]{alignment(1);  });
    connect(centralAlignment, &QAction::triggered, this, [this]{ alignment(2); });
    connect(fontStyleAction, &QAction::triggered, this, &MainWindow::fontStyle);
    connect(fontColorAction, &QAction::triggered, this, &MainWindow::fontColor);
    connect(fontBgColorAction, &QAction::triggered, this, &MainWindow::fontBg);

    // Help signals & slots
    connect(viewHelpAction, &QAction::triggered, this, &MainWindow::viewHelp);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::setCurrentFile(QString filename)
{
    QString showname = filename;

    if (filename.isEmpty())
        showname = "untitled";

    setWindowFilePath(showname);
}

void MainWindow::documntModified()
{
    setWindowModified(textarea->document()->isModified());  // To put * when the file is modified
}

void MainWindow::createMenu()
{

    // File button & drop-down list
    fileMenu = menuBar()->addMenu("File");
    {
        // New file
        newAction = new QAction(QIcon(":/Icons/new.png"), "New");
        newAction->setShortcut(QKeySequence::New);

        // Open
        openAction = new QAction(QIcon(":/Icons/open.png"), "Open");
        openAction->setShortcut(QKeySequence::Open);

        fileMenu->addAction(newAction);
        fileMenu->addAction(openAction);

        fileMenu->addSeparator();

        // Save
        saveAction = new QAction(QIcon(":/Icons/save.png"), "Save");
        saveAction->setShortcut(QKeySequence::Save);

        // SaveAs
        saveAsAction = new QAction(QIcon(":/Icons/save-as.png"), "SaveAs");
        saveAsAction->setShortcut(tr("Ctrl+Shift+S"));

        fileMenu->addAction(saveAction);
        fileMenu->addAction(saveAsAction);

        fileMenu->addSeparator();

        // Exit
        exitAction = new QAction(QIcon(":/Icons/exit.png"), "Exit");
        exitAction->setShortcut(tr("Ctrl+Q"));
        fileMenu->addAction(exitAction);
    }

    // Edit button & drop-down list
    editMenu = menuBar()->addMenu("Edit");
    {
        // Undo
        undoAction = new QAction(QIcon(":/Icons/undo.png"), "Undo");
        undoAction->setShortcut(QKeySequence::Undo);

        // Redo
        redoAction = new QAction(QIcon(":/Icons/redo.png"), "Redo");
        redoAction->setShortcut(QKeySequence::Redo);

        editMenu->addAction(undoAction);
        editMenu->addAction(redoAction);

        editMenu->addSeparator();

        // Copy
        copyAction = new QAction(QIcon(":/Icons/copy.png"), "Copy");
        copyAction->setShortcut(QKeySequence::Copy);

        // Cut
        cutAction = new QAction(QIcon(":/Icons/cut.png"), "Cut");
        cutAction->setShortcut(QKeySequence::Cut);

        // Paste
        pasteAction = new QAction(QIcon(":/Icons/paste.png"), "Paste");
        pasteAction->setShortcut(QKeySequence::Paste);

        editMenu->addAction(copyAction);
        editMenu->addAction(cutAction);
        editMenu->addAction(pasteAction);

        editMenu->addSeparator();

        // Find
        findAction = new QAction(QIcon(":/Icons/find.png"), "Find");
        findAction->setShortcut(QKeySequence::Find);

        editMenu->addAction(findAction);
    }


    // View button & drop-down list
    viewMenu = menuBar()->addMenu("View");
    {
        // Zoom In
        zoomInAction = new QAction(QIcon(":/Icons/zoom-in.png"), "Zoom In");
        zoomInAction->setShortcut(tr("Shift+Ctrl+I"));

        // Zoom Out
        zoomOutAction = new QAction(QIcon(":/Icons/zoom-out.png"), "Zoom Out");
        zoomOutAction->setShortcut(tr("Shift+Ctrl+O"));

        viewMenu->addAction(zoomInAction);
        viewMenu->addAction(zoomOutAction);
        viewMenu->addSeparator();

        // Modes
        darkModeAction = new QAction(QIcon(":/Icons/dark-Mode.png"),"Dark Mode");
        lightModeAction = new QAction(QIcon(":/Icons/light-Mode.png"),"Light Mode");

        viewMenu->addAction(darkModeAction);
        viewMenu->addAction(lightModeAction);

    }


    // Format button & drop-down list
    formatMenu = menuBar()->addMenu("Format");
    {
        // Alignment
        rightAlignment = new QAction(QIcon(":/Icons/align-right.png"),"Align Right");
        centralAlignment = new QAction(QIcon(":/Icons/align-center.png"),"Align Center");
        leftAlignment = new QAction(QIcon(":/Icons/align-left.png"),"Align Left");

        formatMenu->addAction(rightAlignment);
        formatMenu->addAction(centralAlignment);
        formatMenu->addAction(leftAlignment);

        formatMenu->addSeparator();

        // Font
        fontStyleAction = new QAction(QIcon(":/Icons/fonts.png"),"Fonts");
        fontColorAction = new QAction(QIcon(":/Icons/font-colors.png"),"Font Color");
        fontBgColorAction = new QAction(QIcon(":/Icons/font-bg-color.png"),"Background Color");

        formatMenu->addAction(fontStyleAction);
        formatMenu->addAction(fontColorAction);
        formatMenu->addAction(fontBgColorAction);
    }


    // Help button & drop-down list
    helpMenu = menuBar()->addMenu("Help");
    {
        viewHelpAction = new QAction(QIcon(":/Icons/help.png"),"View Help");
        aboutAction = new QAction(QIcon(":/Icons/about.png"),"About");

        helpMenu->addAction(viewHelpAction);
        helpMenu->addSeparator();
        helpMenu->addAction(aboutAction);
    }
}

void MainWindow::createToolBar()
{

    toolbar =  new QToolBar();

    toolbar->addAction(newAction);

    toolbar->addSeparator();

    toolbar->addAction(saveAction);
    toolbar->addAction(saveAction);

    toolbar->addSeparator();

    toolbar->addAction(copyAction);
    toolbar->addAction(cutAction);
    toolbar->addAction(pasteAction);

    toolbar->addSeparator();

    toolbar->addAction(undoAction);
    toolbar->addAction(redoAction);
    toolbar->addAction(findAction);

    toolbar->addSeparator();

    toolbar->addAction(zoomInAction);
    toolbar->addAction(zoomOutAction);

    addToolBar(toolbar);
}

void MainWindow::createStatusBar()
{
    statusBar();
}

void MainWindow::showCursorPos()
{
    int line = textarea->textCursor().blockNumber()+1;
    int column = textarea->textCursor().columnNumber();
    statusBar()->showMessage(QString("Ln %1, Col %2").arg(line).arg(column));
}

void MainWindow::New()
{
    if ( maybeSave() == false )
    {
        textarea->clear();
        setWindowModified(false);
        setCurrentFile(QString(""));
    }
}

bool MainWindow::maybeSave()
{
    if (!textarea->document()->isModified())
        return false;

    QMessageBox warning;
    warning.setWindowTitle("Warning");
    warning.setWindowIcon(QIcon(":/Icons/warning.png"));
    warning.setText("The document is modified \n do you want to save ?");
    warning.setIconPixmap(QPixmap(":/Icons/warning.png"));
    warning.addButton(QMessageBox::Save);
    warning.addButton(QMessageBox::Discard);
    warning.addButton(QMessageBox::Cancel);
    warning.show();

    switch(warning.exec())
    {
    case QMessageBox::Save:
        save();
        break;
    case QMessageBox::Cancel:
        return true;
        break;
    case QMessageBox::Discard:
        break;
    }

    return false;
}

void MainWindow::open()
{
    bool flag = true;

    if (!textarea->document()->isEmpty())
        flag = maybeSave();

    if (flag)
    {
        CurrentFilename = QFileDialog::getOpenFileName(this);
        QFile file(CurrentFilename);

        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            //  when press cancel after opening the fileDialog
            QMessageBox warning;
            warning.setWindowTitle("Warning");
            warning.setWindowIcon(QIcon(":/Icons/warning.png"));
            warning.setText("<p align='center' ;  margin: 2px; >Erorr loading file</p>");
            warning.setContentsMargins(0,20,0,0);
            warning.setIconPixmap(QPixmap(":/Icons/warning.png"));
            warning.show();
            warning.exec();

        }

        QTextStream in(&file);

        QGuiApplication::setOverrideCursor(Qt::WaitCursor);
        textarea->document()->setPlainText(in.readAll());
        QGuiApplication::restoreOverrideCursor();
    }
}

void MainWindow::save()
{
    if (CurrentFilename.isEmpty())
    {
        saveAs();
    }
    else
    {
        QGuiApplication::setOverrideCursor(Qt::WaitCursor);

        QSaveFile file(CurrentFilename);

        if (file.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&file);
            out << textarea->document()->toPlainText();

            if (!file.commit())
            {
                QMessageBox::warning(this, "warning", "Error in saving file");
            }

        }
        else
        {
            QMessageBox::warning(this, "warning", "Error in open file");
        }

        QGuiApplication::restoreOverrideCursor();
        setCurrentFile(CurrentFilename);
        statusBar()->showMessage("File saved", 2000); // 2000 --> after 2 seconds
    }
}

void MainWindow::saveAs()
{
    QFileDialog dialog(this);

    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    CurrentFilename = dialog.selectedFiles().first();
    setCurrentFile(CurrentFilename);
    save();
}

void MainWindow::exit()
{
    if (!maybeSave())
    {
        close();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
        event->ignore();
    else
        event->accept();
}

void MainWindow::undo()
{
    textarea->undo();
}

void MainWindow::redo()
{
    textarea->redo();
}

void MainWindow::copy()
{
    textarea->selectAll();
    textarea->copy();
}

void MainWindow::cut()
{
    textarea->selectAll();
    textarea->cut();
}

void MainWindow::paste()
{
    textarea->paste();
}

void MainWindow::findWindow()
{
    findDialog = new QDialog(0,Qt::WindowTitleHint | Qt::WindowCloseButtonHint );

    lineEdit = new QLineEdit(findDialog);
    QPushButton *btn = new QPushButton(findDialog);

    btn->setText(tr("Find next"));

    // The find method is case insensitive
    connect(btn, &QPushButton::clicked, this,[this]{textarea->find(lineEdit->text());});

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lineEdit);
    layout->addWidget(btn);

    findDialog->setWindowTitle("Find");
    findDialog->setWindowIcon(QIcon(":/Icons/find.png"));
    findDialog->setLayout(layout);
}

void MainWindow::showFindWindow()
{
    findDialog->show();  // to show the dialog when the find button clicked
}

// Font range : [ 12 : 52 ]
void MainWindow::zoomIn()
{
    if ( fontSize < 52 )
    {
        fontSize += 4;
        font->setPointSize(fontSize);
        textarea->document()->setDefaultFont(*font);
    }
}

void MainWindow::zoomOut()
{
    if ( fontSize > 12 )
    {
        fontSize -= 4;
        font->setPointSize(fontSize );
        textarea->document()->setDefaultFont(*font);
    }
}

bool isDrak = false;
void MainWindow::darkMode(){

    isDrak = true;

    toolbar->setStyleSheet("background-color: #303030;");
    statusBar()->setStyleSheet("background-color: #303030; color:white;");
    textarea->setStyleSheet("background-color: #303030; color:white; border: 1px solid white;");
}

void MainWindow::lightMode(){

    isDrak = false;

    toolbar->setStyleSheet("background-color: #f0f0f0;");
    statusBar()->setStyleSheet("background-color: white; color:black;");
    textarea->setStyleSheet("background-color: #white; color:black; border: 1px solid black;");
}

void MainWindow::alignment(int type)
{
    QTextCursor cursor = textarea->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();

    // left = 0 , right = 1 , center = 2
    switch(type)
    {
    case 0:
        textBlockFormat.setAlignment(Qt::AlignLeft);
        break;
    case 1:
        textBlockFormat.setAlignment(Qt::AlignRight);
        break;
    case 2:
        textBlockFormat.setAlignment(Qt::AlignCenter);
        break;
    }

    cursor.mergeBlockFormat(textBlockFormat);
    textarea->setTextCursor(cursor);
}

void MainWindow::fontStyle()
{
    bool preesOK = false;

    QFont font = QFontDialog:: getFont(&preesOK, this);

    if (preesOK)
    {
        textarea->setFont(font);
    }
}

void MainWindow::fontColor()
{
    QColor color = QColorDialog:: getColor(Qt::black, this , "Colors");

    if (color.isValid())
    {
        textarea->setTextColor(color);
    }
}

void MainWindow::fontBg()
{
    QColor color = QColorDialog:: getColor(Qt::white, this , "Colors");

    if (color.isValid())
    {
        textarea->setTextBackgroundColor(color);
    }
}

void MainWindow::viewHelp()
{
    QMessageBox help;
    help.setWindowTitle("Help Menu");
    help.setWindowIcon(QIcon(":/Icons/help.png"));
    help.setText("New\t\t^N\nOpen\t\t^O\nSave\t\t^S\nSaveAs\t\t^Shift+S\nExit\t\t^Q\nUndo\t\t^Z\nRedo\t\t^Y\nCopy\t\t^C\nCut\t\t^X\nPaste\t\t^V\nFind\t\t^F\nZoom in\t^Shift+I\nZoom out\t^Shift+O");
    help.setIconPixmap(QPixmap(":/Icons/help.png"));

    help.show();
    help.exec();
}

void MainWindow::about()
{
    QMessageBox about;
    about.setWindowTitle("About");
    about.setWindowIcon(QIcon(":/Icons/about.png"));
    about.setText("<b>Femto<b/>");
    about.setInformativeText("Can u go smaller?\n");
    about.setIconPixmap(QPixmap(":/Icons/about.png"));

    about.show();
    about.exec();
}

MainWindow::~MainWindow()
{
    delete textarea;
    delete font;

    // Delete menus
    delete  fileMenu;
    delete  editMenu;
    delete  formatMenu;
    delete  viewMenu;
    delete  helpMenu;

    // Delete toolbar
    delete toolbar;

    // Delete file actions
    delete newAction;
    delete openAction;
    delete saveAction;
    delete saveAsAction;
    delete exitAction;

    // Delete edit actions
    delete undoAction;
    delete redoAction;
    delete copyAction;
    delete cutAction;
    delete pasteAction;
    delete findAction;

    // Find dialog
    delete  lineEdit;
    delete findDialog;

    // Delete view actions
    delete zoomInAction;
    delete zoomOutAction;
    delete darkModeAction;
    delete lightModeAction;
    delete fontStyleAction;
    delete fontColorAction;
    delete fontBgColorAction;

    // Delete help actions
    delete viewHelpAction;
    delete aboutAction;
}
