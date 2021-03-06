#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QIrrlichtWidget.h"

#include <QMainWindow>

namespace Ui {
class GUI_MainWindow;
}


class GUI_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GUI_MainWindow(QWidget *parent = nullptr);
    ~GUI_MainWindow();
    void initIrrlicht();

public slots :
    void convert();
    void translate();
    void changeLanguage();
    void selectFolder();

    void openAbout();
    void options();
    void search();
    void matExplorer();

    void changeOptions();
    void re_size();
    void changeLOD();
    void clearLOD();
    void clearAllLODs();
    void checkConvertButton();
    void cleanTexturesPath();
    void extFiles();


    void addMesh();
    void bifExtractor();
    void dzipExtractor();
    void bundleExtractor();
    void thecouncilExtractor();
    void dishonoredExtractor();
    void changeBaseDir(QString newDir);


    void selectMeshFile();
    void selectRigFile();
    void selectAnimationsFile();

    void selectTW1AnimationsFile();

    void selectTheCouncilTemplate();

    void loadFileGeneric(QString path);
    void loadMesh(QString path);
    void loadRig(QString path);
    void loadAnimations(QString path);

    void loadTW1Animations(QString path);

    void loadTheCouncilTemplate(QString path);


private:
    void updateWindowTitle();
    void addToUILog(QString log);
    void registerExporters();

    Ui::GUI_MainWindow *_ui;
    QIrrlichtWidget *_irrWidget;

    bool _firstSelection;
    LOD _currentLOD;

    QVector<ExporterInfos> _exporters;

signals:
    void languageChanged();

};

#endif // MAINWINDOW_H
