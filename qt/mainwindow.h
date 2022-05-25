#include <QMainWindow>
#include<QPlainTextEdit>
#include <QCloseEvent>
#include<QMenuBar>
#include<QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QShortcut>
#include <QMessageBox>
#include <QTextStream>
#include <QGuiApplication>
#include <QSaveFile>
#include <QPixmap>
#include <QDialog>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QColor>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>


class MainWindow : public QMainWindow
{

    Q_OBJECT

private:

    QTextEdit* textarea;
    QFont* font = new QFont("Myanmar Text");
    int fontSize = 12; // default font = 12

    void createConnections();

    QString CurrentFilename;
    void setCurrentFile(QString filename);
    void documntModified();


    // Create menus
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* viewMenu;
    QMenu* formatMenu;
    QMenu* helpMenu;

    // create toolbar
    QToolBar* toolbar;


    void createMenu();
    void createToolBar();
    void createStatusBar();
    void showCursorPos(); // To show line and column number in stausBar


    // File actions
    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* exitAction;

    // File slots
    void New();
    bool maybeSave();
    void open();
    void save();
    void saveAs();
    void exit();
    void closeEvent(QCloseEvent *event);


    // Edit actions
    QAction* undoAction;
    QAction* redoAction;
    QAction* copyAction;
    QAction* cutAction;
    QAction* pasteAction;
    QAction* findAction;

    // Edit slots
    void undo();
    void redo();
    void copy();
    void cut();
    void paste();

    // Find dialog
    QLineEdit *lineEdit;
    QDialog *findDialog;

    void findWindow();
    void showFindWindow();

    // View actions
    QAction* zoomInAction;
    QAction* zoomOutAction;
    QAction* darkModeAction;
    QAction* lightModeAction;


    // View slots
    void zoomIn();
    void zoomOut();
    void darkMode();
    void lightMode();


    // Format actions
    QAction* leftAlignment;    //  0
    QAction* rightAlignment;   //  1
    QAction* centralAlignment; //  2
    QAction* fontColorAction;
    QAction* fontBgColorAction;
    QAction* fontStyleAction;

    // Format slots
    void alignment(int type);
    void fontStyle();
    void fontColor();
    void fontBg();


    // Help actions
    QAction* viewHelpAction;
    QAction* aboutAction;

    // Help slots
    void viewHelp();
    void about();


public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
