#include <QMainWindow>
#include<QPlainTextEdit>
#include<QMenuBar>
#include<QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QShortcut>
#include <QGuiApplication>
#include <QSaveFile>
#include <QPixmap>


class MainWindow : public QMainWindow
{

    Q_OBJECT

private:

    QTextEdit* textarea;

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

    // File slots -
    void newSlot();
    bool maybeSaveSlot();
    void OpenSlot();
    void SaveSlot();
    void SaveAsSlot();
    void exitSlot();


    // Edit actions
    QAction* undoAction;
    QAction* redoAction;
    QAction* copyAction;
    QAction* cutAction;
    QAction* pasteAction;
    QAction* findAction;
    QAction* replaceAction;

    // Edit slots
    void undoSlot();
    void redoSlot();
    void copySlot();
    void cutSlot();
    void pasteSlot();
    void findSlot();
    void replaceSlot();


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

    // ~ Format slots
    void alignment(int type);


    // Help actions
    QAction* viewHelpAction;
    QAction* aboutAction;

    // ~ Help slots
    void viewHelpSlot();
    void aboutSlot();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
