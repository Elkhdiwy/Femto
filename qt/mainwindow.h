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
    int fontSize = 12;

    QString CurrentFilename;
    void setCurrentFile(QString filename);
    void documntModified();

    void createConnections();

    // Create menus
    QMenu* file;
    QMenu* edit;
    QMenu* format;
    QMenu* view;
    QMenu* help;

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
    void newSlot();
    bool maybeSaveSlot();
    void OpenSlot();
    void SaveSlot();
    void SaveAsSlot();
    void exitSlot();
    void closeEvent(QCloseEvent *event);


    // Edit actions
    QAction* undoAction;
    QAction* redoAction;
    QAction* copyAction;
    QAction* cutAction;
    QAction* pasteAction;
    QAction* findAction;

    // Edit slots
    void undoSlot();
    void redoSlot();
    void copySlot();
    void cutSlot();
    void pasteSlot();

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
    void zoomInSlot();
    void zoomOutSlot();
    void darkModeSlot();
    void lightModeSlot();


    // Format actions
    QAction* rightAlignment;
    QAction* leftAlignment;
    QAction* centralAlignment;
    QAction* fontColor;
    QAction* fontBgColor;
    QAction* fontStyle;

    // Format slots
    void alignment(int type);
    void fontStyleSlot();
    void fontColorSlot();
    void fontBgSlot();


    // Help actions
    QAction* viewHelpAction;
    QAction* aboutAction;

    // Help slots
    void viewHelpSlot();
    void aboutSlot();


public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
