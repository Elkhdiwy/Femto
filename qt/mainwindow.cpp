#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setGeometry(500,200,500,500); // The position of the window when it's pop up
    setWindowIcon(QIcon(":/Icons/logo.png"));

    textarea = new  QTextEdit();
    setCentralWidget(textarea);

    createMenu();
    createToolBar();
    createStatusBar();

    setCurrentFile(QString());

    createConnections();
}

void MainWindow::setCurrentFile(QString filename)
{
    QString showname = filename;

    if (filename.isEmpty())
        showname = "untitled.txt";

    setWindowFilePath(showname);
}


void MainWindow::documntModified()
{
    setWindowModified(textarea->document()->isModified());  // To put * when the file is modified
}


void MainWindow::createConnections()
{

    connect(textarea->document(), &QTextDocument::contentsChanged, this, &MainWindow::documntModified);
    connect(textarea,  &QTextEdit::cursorPositionChanged, this, &MainWindow::showCursorPos);

    // File signals & slots
    connect(newAction, &QAction::triggered, this, &MainWindow::newSlot);
    connect(openAction, &QAction::triggered, this, &MainWindow::OpenSlot);
    connect(saveAction, &QAction::triggered, this, &MainWindow::SaveSlot);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::SaveAsSlot);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitSlot);


   // Edit signals & slots
    connect(undoAction, &QAction::triggered, this, &MainWindow::undoSlot);
    connect(redoAction, &QAction::triggered, this, &MainWindow::redoSlot);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copySlot);
    connect(cutAction, &QAction::triggered, this, &MainWindow::cutSlot);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::pasteSlot);


    // View signals & slots
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomInSlot);
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOutSlot);
    connect(darkModeAction, &QAction::triggered, this, &MainWindow::darkModeSlot);
    connect(lightModeAction, &QAction::triggered, this, &MainWindow::lightModeSlot);



    // Format signals & slots
    connect(rightAlignment, &QAction::triggered, this,  [this]{alignment(1);  });
    connect(leftAlignment, &QAction::triggered, this,  [this]{ alignment(0); });
    connect(centralAlignment, &QAction::triggered, this, [this]{ alignment(2); });
    connect(fontStyle, &QAction::triggered, this, &MainWindow::fontStyleSlot);
    connect(fontColor, &QAction::triggered, this, &MainWindow::fontColorSlot);
    connect(fontBgColor, &QAction::triggered, this, &MainWindow::fontBgSlot);


    // Help signals & slots
    connect(viewHelpAction, &QAction::triggered, this, &MainWindow::viewHelpSlot);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutSlot);

}


void MainWindow::createMenu()
{

    // File button & drop-down list
    file = menuBar()->addMenu("File");
    {
        // New file
        newAction = new QAction(QIcon(":/Icons/new.png"), "New");
        newAction->setShortcut(QKeySequence::New);

        // Open
        openAction = new QAction(QIcon(":/Icons/open.png"), "Open");
        openAction->setShortcut(QKeySequence::Open);

        file->addAction(newAction);
        file->addAction(openAction);

        file->addSeparator();

        // Save
        saveAction = new QAction(QIcon(":/Icons/save.png"), "Save");
        saveAction->setShortcut(QKeySequence::Save);

        // SaveAs
        saveAsAction = new QAction(QIcon(":/Icons/save-as.png"), "SaveAs");
        saveAsAction->setShortcut(tr("Ctrl+Shift+S"));

        file->addAction(saveAction);
        file->addAction(saveAsAction);

        file->addSeparator();

        // Exit
        exitAction = new QAction(QIcon(":/Icons/exit.png"), "Exit");
        exitAction->setShortcut(tr("Ctrl+Q"));
        file->addAction(exitAction);
    }


    // Edit button & drop-down list
    edit = menuBar()->addMenu("Edit");
    {
        // Undo
        undoAction = new QAction(QIcon(":/Icons/undo.png"), "Undo");
        undoAction->setShortcut(QKeySequence::Undo);

        // Redo
        redoAction = new QAction(QIcon(":/Icons/redo.png"), "Redo");
        redoAction->setShortcut(QKeySequence::Redo);

        edit->addAction(undoAction);
        edit->addAction(redoAction);

        edit->addSeparator();

        // Copy
        copyAction = new QAction(QIcon(":/Icons/copy.png"), "Copy");
        copyAction->setShortcut(QKeySequence::Copy);

        // Cut
        cutAction = new QAction(QIcon(":/Icons/cut.png"), "Cut");
        cutAction->setShortcut(QKeySequence::Cut);

        // Paste
        pasteAction = new QAction(QIcon(":/Icons/paste.png"), "Paste");
        pasteAction->setShortcut(QKeySequence::Paste);

        edit->addAction(copyAction);
        edit->addAction(cutAction);
        edit->addAction(pasteAction);

        edit->addSeparator();

        // Find
        findAction = new QAction(QIcon(":/Icons/find.png"), "Find");
        findAction->setShortcut(QKeySequence::Find);

        // Replace
        replaceAction = new QAction(QIcon(":/Icons/find-and-replace.png"), "Replace");
        replaceAction->setShortcut(QKeySequence::Replace);

        edit->addAction(findAction);
        edit->addAction(replaceAction);

    }


    // View button & drop-down list
    view = menuBar()->addMenu("View");
    {
        // Zoom In
        zoomInAction = new QAction(QIcon(":/Icons/zoom-in.png"), "Zoom In");
        zoomInAction->setShortcut(tr("Shift+Ctrl+I"));

        // Zoom Out
        zoomOutAction = new QAction(QIcon(":/Icons/zoom-out.png"), "Zoom Out");
        zoomOutAction->setShortcut(tr("Shift+Ctrl+O"));

        view->addAction(zoomInAction);
        view->addAction(zoomOutAction);
        view->addSeparator();

        // Modes
        darkModeAction = new QAction(QIcon(":/Icons/dark-Mode.png"),"Dark Mode");
        lightModeAction = new QAction(QIcon(":/Icons/light-Mode.png"),"Light Mode");

        view->addAction(darkModeAction);
        view->addAction(lightModeAction);

    }


    // Format button & drop-down list
     format = menuBar()->addMenu("Format");
     {
         // Alignment
        rightAlignment = new QAction(QIcon(":/Icons/align-right.png"),"Align Right");
        centralAlignment = new QAction(QIcon(":/Icons/align-center.png"),"Align Center");
        leftAlignment = new QAction(QIcon(":/Icons/align-left.png"),"Align Left");

        // Font
        fontStyle = new QAction(QIcon(":/Icons/fonts.png"),"Fonts");
        fontColor = new QAction(QIcon(":/Icons/font-colors.png"),"Font Color");
        fontBgColor = new QAction(QIcon(":/Icons/font-bg-color.png"),"Background Color");

        format->addAction(rightAlignment);
        format->addAction(centralAlignment);
        format->addAction(leftAlignment);

        format->addSeparator();

        format->addAction(fontStyle);
        format->addAction(fontColor);
        format->addAction(fontBgColor);
     }


    // Help button & drop-down list
    help = menuBar()->addMenu("Help");
    {
        viewHelpAction = new QAction(QIcon(":/Icons/help.png"),"View Help");
        aboutAction = new QAction(QIcon(":/Icons/about.png"),"About");

        help->addAction(viewHelpAction);
        help->addSeparator();
        help->addAction(aboutAction);
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
     toolbar->addAction(QIcon(":/Icons/find-and-replace"), "Find and replace"); //xxxxxxxx

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


void MainWindow::newSlot()
{
    if (!maybeSaveSlot())
      {
          textarea->clear();
          setWindowModified(false);
          setCurrentFile(QString());
      }
}


bool MainWindow::maybeSaveSlot()
{
    if (!textarea->document()->isModified())
        return false;

    auto warning = QMessageBox::warning(this, "Warning", "The document is modified \n do you want to save ? ",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    switch (warning)
    {
        case QMessageBox::Save:
            SaveSlot();
            break;
        case QMessageBox::Cancel:
            return true;
            break;
        case QMessageBox::Discard:
            break;
    }

    return false;
}


void MainWindow::OpenSlot()
{
    if (maybeSaveSlot())
    {
        CurrentFilename = QFileDialog::getOpenFileName(this);

        if (!CurrentFilename.isEmpty())
        {
            setCurrentFile(CurrentFilename);

            QFile file(CurrentFilename);

            if (!file.open(QFile::ReadOnly | QFile::Text))
            {
                QMessageBox::warning(this, "Warning", "erorr loading file");
            }

            QTextStream in(&file);

            QGuiApplication::setOverrideCursor(Qt::WaitCursor);
            textarea->document()->setPlainText(in.readAll());
            QGuiApplication::restoreOverrideCursor();
        }
    }
}


void MainWindow::SaveSlot()
{
    if (CurrentFilename.isEmpty())
    {
        SaveAsSlot();
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
        statusBar()->showMessage("File saved", 2000);
    }
}


void MainWindow::SaveAsSlot()
{
    QFileDialog dialog(this);

    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    if(dialog.exec() != QDialog::Accepted)
    {
        // erorr
    }
    else
    {
        CurrentFilename = dialog.selectedFiles().first();
        setCurrentFile(CurrentFilename);
        SaveSlot();
    }
}


void MainWindow::exitSlot()
{
   if (!maybeSaveSlot())
     {
        close();
     }
}


void MainWindow::undoSlot()
{
    textarea->undo();
}


void MainWindow::redoSlot()
{
    textarea->redo();
}


void MainWindow::copySlot()
{
    textarea->selectAll();
    textarea->copy();
}


void MainWindow::cutSlot()
{
    textarea->selectAll();
    textarea->cut();
}


void MainWindow::pasteSlot()
{
   textarea->paste();
}


void MainWindow::findSlot()
{
    //bla bla
}

void MainWindow::replaceSlot()
{
    //bla bla
}


void MainWindow::zoomInSlot()
{
    textarea->zoomIn(5);
}


void MainWindow::zoomOutSlot()
{
    textarea->zoomOut(5);
}


bool isDrak = false;
void MainWindow::darkModeSlot(){

    isDrak = true;

    toolbar->setStyleSheet("background-color: #303030;");
    statusBar()->setStyleSheet("background-color: #303030; color:white;");
    textarea->setStyleSheet("background-color: #303030; color:white; border: 1px solid white;");
}


void MainWindow::lightModeSlot(){

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


void MainWindow::fontStyleSlot()
{
    bool preesOK = false;

    QFont font = QFontDialog:: getFont(&preesOK, this);

    if (preesOK)
    {
        textarea->setFont(font);
    }
}


void MainWindow::fontColorSlot()
{
    QColor color = QColorDialog:: getColor(Qt::black, this , "Colors");

    if (color.isValid())
    {
        textarea->setTextColor(color);
    }
}


void MainWindow::fontBgSlot()
{
    QColor color = QColorDialog:: getColor(Qt::white, this , "Colors");

    if (color.isValid())
    {
        textarea->setTextBackgroundColor(color);
    }
}


void MainWindow::viewHelpSlot()
{
    QMessageBox::about(this, tr("Help Menu"),
             tr("Bla bla bla Bla bla bla"));
}


void MainWindow::aboutSlot()
{
    QMessageBox about;
    about.setWindowTitle("About");
    about.setWindowIcon(QIcon(":/Icons/about.png"));
    about.setText("Femto");
    about.setInformativeText("Can u go smaller?\n");
    about.setIconPixmap(QPixmap(":/Icons/about.png"));

    about.show();
    about.exec();
}


MainWindow::~MainWindow()
{
    // Delete menus
    delete  file;
    delete  edit;
    delete  format;
    delete  view;
    delete  help;

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
    delete replaceAction;


    // Delete view actions
    delete zoomInAction;
    delete zoomOutAction;
    delete darkModeAction;
    delete lightModeAction;
    delete fontStyle;
    delete fontColor;
    delete fontBgColor;

    // Delete help actions
    delete viewHelpAction;
    delete aboutAction;
}
