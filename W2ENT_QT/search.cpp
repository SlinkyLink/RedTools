#include "search.h"
#include "ui_search.h"

#include <iostream>

Search::Search(QWidget *parent, QString language) :
    QDialog(parent),
    _ui(new Ui::Search)
{
    _ui->setupUi(this);

    translate(language);

    QObject::connect(_ui->button_search, SIGNAL(clicked()), this, SLOT(search()));
    QObject::connect(_ui->pushButton, SIGNAL(clicked()), this, SLOT(load()));
    QObject::connect(_ui->listWidget_results, SIGNAL(currentRowChanged(int)), this, SLOT(enableButton()));
}

Search::~Search()
{
    delete _ui;
}

void Search::translate(QString language)
{
    _ui->label_name->setText(Translator::findTranslation("search_name", language) + " :");
    _ui->label_result->setText(Translator::findTranslation("search_result", language) + " :");
    _ui->label->setText(Translator::findTranslation("search_progress", language) + " :");
    _ui->checkBox_folder->setText(Translator::findTranslation("search_check_folder", language));
    _ui->button_search->setText(Translator::findTranslation("search_button", language));
    _ui->pushButton->setText(Translator::findTranslation("search_load", language));
}

void Search::search()
{
    _ui->button_search->setEnabled(false);
    _ui->pushButton->setEnabled(false);
    _ui->listWidget_results->clear();

    QString name = _ui->lineEdit_name->text();
    std::vector<QString> keywords;
    QString word;
    for (int i = 0; i < name.size(); i++)
    {
        if(name[i] == ' ')
        {
            keywords.push_back(word);
            word.clear();
        }
        else
        {
            word.push_back(name[i]);
        }
    }
    keywords.push_back(word);

    _pack0lastSearch = OptionsData::_pack0;
    QTime time;
    time.start();
    scanFolder(OptionsData::_pack0, 0, keywords);
    //timer.stop();
    //std::cout << time.elapsed() << std::endl;
    _ui->button_search->setEnabled(true);
}

void Search::scanFolder(QString repName, int level, std::vector<QString> keywords)
{
    level++;

    // search the w2ent and w2mesh file
    QDir dirFiles(repName);
    dirFiles.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dirFiles.setNameFilters(QStringList() << "*.w2mesh" << "*.w2ent" << "*.w2rig");

    foreach(QFileInfo fileInfo, dirFiles.entryInfoList())
    {
        bool ok = true;
        QString target = fileInfo.fileName();

        if (_ui->checkBox_folder->isChecked())
        {
            target = fileInfo.absolutePath() + fileInfo.fileName();
            target.remove(0, OptionsData::_pack0.size());
        }

        for (unsigned int i = 0; i < keywords.size(); i++)
        {
            if (!target.toUpper().contains(keywords[i].toUpper()))
            {
                ok = false;
            }
        }
        if (ok)
            _ui->listWidget_results->addItem(new QListWidgetItem("{pack0}" + fileInfo.absoluteFilePath().remove(0, OptionsData::_pack0.size())));
    }

    // search in the subfolders
    //QDir dirSubfolder(repName);
    dirFiles.setNameFilters(QStringList());
    dirFiles.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    double i = 0;
    foreach(QFileInfo fileInfo, dirFiles.entryInfoList())
    {
        scanFolder(fileInfo.absoluteFilePath(), level, keywords);
        i++;
        if (level == 1)
        {
            _ui->progressBar_search->setValue((i/dirFiles.entryInfoList().size())*(100));
            QCoreApplication::processEvents();
        }
    }
}

void Search::load()
{
    emit loadPressed(_pack0lastSearch + _ui->listWidget_results->currentItem()->text().remove(0, 7));
}

void Search::enableButton()
{
    _ui->pushButton->setEnabled(_ui->listWidget_results->currentRow() != -1);
}
