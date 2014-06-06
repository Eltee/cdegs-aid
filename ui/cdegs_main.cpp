/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    cdegs_main.cpp
*
* Description: CDEGS-Aid est un logiciel d'aide pour la génération de fichiers
*              de simulation compatibles avec SESCad et CDEGS-HiFreq pour des
*              simulations de champ électrics, d'affichage et d'analyse de
*              résultat de simulations CDEGS-HiFreq.
*
* Auteur:      Renaud Bigras, Hydro-Québec Transénergie
*  /Author
*
* Créé:        07-05-2014
*  /Created
*
* Copyright:   (c) Renaud Bigras 2014
*
*   This file is part of CDEGS-Aid.
*
*   CDEGS-Aid is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   CDEGS-Aid is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with CDEGS-Aid. If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#include "cdegs_main.h"
#include "ui_cdegs_main.h"

/*!
 \brief

 \fn cdegs_main::cdegs_main
 \param parent
*/
cdegs_main::cdegs_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cdegs_main){
    ui->setupUi(this);

    connectSlots();
}

/*!
 \brief

 \fn cdegs_main::~cdegs_main
*/
cdegs_main::~cdegs_main(){
    delete ui;
    project.reset();
    config.reset();
}

/*!
 \brief

 \fn cdegs_main::connectSlots
*/
void cdegs_main::connectSlots(){
    QObject::connect(ui->actionNew_Project, SIGNAL(triggered()),
                      this,  SLOT(newProject()));

    QObject::connect(ui->actionNew_Config, SIGNAL(triggered()),
                      this,  SLOT(newConfig()));

    QObject::connect(ui->actionOpen_Project, SIGNAL(triggered()),
                      this,  SLOT(openProject()));

    QObject::connect(ui->actionSave_Project, SIGNAL(triggered()),
                      this,  SLOT(saveProject()));

    QObject::connect(ui->actionSave_Project_as, SIGNAL(triggered()),
                      this,  SLOT(saveProjectAs()));

    QObject::connect(ui->actionClose_Project, SIGNAL(triggered()),
                      this,  SLOT(closeProject()));

    QObject::connect(ui->tabProjects, SIGNAL(currentChanged(int)),
                     this, SLOT(changeTab()));

    QObject::connect(ui->tabProjects, SIGNAL(tabCloseRequested(int)),
                     this, SLOT(closeProject(int)));

    QObject::connect(ui->actionAbout, SIGNAL(triggered()),
                     this, SLOT(about()));

    QObject::connect(ui->actionStylesheet, SIGNAL(triggered()),
                     this, SLOT(openStyleDialog()));

    QObject::connect(ui->actionOpen_Config, SIGNAL(triggered()),
                     this, SLOT(openConfigDialog()));
}

/*!
 \brief

 \fn cdegs_main::refresh
*/
void cdegs_main::refresh(){
    updateProject();
    updateConfig();
    updateTitle();
    updateActions();    
    updateTab();
}

/*!
 \brief

 \fn cdegs_main::updateTab
*/
void cdegs_main::updateTab(){ //TO-DO: CHANGE
    if(project && ui->tabProjects->count() > 0){
        ui->tabProjects->setTabText(ui->tabProjects->currentIndex(), QString::fromStdString(project->getFileName()));
    }
}

/*!
 \brief

 \fn cdegs_main::updateProject
*/
void cdegs_main::updateProject(){
    if(ui->tabProjects->currentIndex() != -1){
        project = dynamic_cast<project_tab_widget*>(ui->tabProjects->currentWidget())->getProject();
    }
    else{
        project.reset();
    }

}

/*!
 \brief

 \fn cdegs_main::updateConfig
*/
void cdegs_main::updateConfig(){
    if(ui->tabProjects->currentIndex() != -1){
        config = dynamic_cast<project_tab_widget*>(ui->tabProjects->currentWidget())->getConfig();
    }
    else{
        config.reset();
    }
}

/*!
 \brief

 \fn cdegs_main::updateActions
*/
void cdegs_main::updateActions(){
    if(project){
        ui->actionSave_Project->setEnabled(true);
        ui->actionSave_Project_as->setEnabled(true);
        ui->actionClose_Project->setEnabled(true);
        ui->actionNew_Config->setEnabled(true);
        ui->actionOpen_Config->setEnabled(true);
    }
    else{
        ui->actionSave_Project->setEnabled(false);
        ui->actionSave_Project_as->setEnabled(false);
        ui->actionClose_Project->setEnabled(false);
        ui->actionNew_Config->setEnabled(false);
        ui->actionOpen_Config->setEnabled(false);
    }

    if(config){
        ui->actionClose_Config->setEnabled(true);
        ui->actionSave_Config->setEnabled(true);
        ui->actionExport_Config->setEnabled(true);
        ui->actionExport_Config_as->setEnabled(true);
    }
    else{
        ui->actionClose_Config->setEnabled(false);
        ui->actionSave_Config->setEnabled(false);
        ui->actionExport_Config->setEnabled(false);
        ui->actionExport_Config_as->setEnabled(false);
    }
}

/*!
 \brief

 \fn cdegs_main::updateTitle
*/
void cdegs_main::updateTitle(){
    if(project){
        QString title;
        std::string stdTitle;
        if(config){
            stdTitle = "CDEGS Aid - " + project->getFileName() + " - " + config->getIdentifier();
        }
        else{
            stdTitle = "CDEGS Aid - " + project->getAbsPath() + "/" + project->getFileName();
        }
        title = QString::fromStdString(stdTitle);
        this->setWindowTitle(title);
    }
    else{
        this->setWindowTitle("CDEGS Aid");
    }
}

/*!
 \brief

 \fn cdegs_main::newProject
*/
void cdegs_main::newProject(){
    project.reset(new Project());

    project_tab_widget* tab = new project_tab_widget(this, this, project);

    QObject::connect(tab, SIGNAL(dataModified(QWidget*)),
            this, SLOT(tabModified(QWidget*)));

    int index = ui->tabProjects->addTab(tab, QString::fromStdString(project->getFileName()));

    ui->tabProjects->setCurrentIndex(index);


    refresh();
}

/*!
 \brief

 \fn cdegs_main::openProject
*/
void cdegs_main::openProject(){
    QString filePath = QFileDialog::getOpenFileName(this, "Choose Project to open..", "", "CDEGS-Aid Project File (*.cdp)");
    project.reset(AppUtils::getInstance().loadProject(filePath.toStdWString().c_str()));

    project_tab_widget* tab = new project_tab_widget(this, this, project);

    QObject::connect(tab, SIGNAL(dataModified(QWidget*)),
            this, SLOT(tabModified(QWidget*)));

    int index = ui->tabProjects->addTab(tab, QString::fromStdString(project->getFileName()));

    ui->tabProjects->setCurrentIndex(index);

    refresh();
}

/*!
 \brief

 \fn cdegs_main::saveProject
*/
void cdegs_main::saveProject(){
    if(project) AppUtils::getInstance().saveProject(*project.get());
}

/*!
 \brief

 \fn cdegs_main::saveProjectAs
*/
void cdegs_main::saveProjectAs(){
    if(project){
        QString filePath = QFileDialog::getSaveFileName(this, "Choose file to save..", "", "CDEGS-Aid Project File (*.cdp)");
        QDir d = QFileInfo(filePath).absoluteDir();
        project->setAbsPath(d.absolutePath().toStdString()).setRelPath(d.path().toStdString());
        project->setFileName(QFileInfo(filePath).fileName().toStdString());
        AppUtils::getInstance().saveProject(*project.get());
    }

    refresh();
}

/*!
 \brief

 \fn cdegs_main::closeProject
*/
void cdegs_main::closeProject(){
    if(QMessageBox::question(this, "Warning! Close Project?", "Closing your project will cause all unsaved changes to be lost.") == QMessageBox::Yes){
        config.reset();
        project.reset();
        ui->tabProjects->removeTab(ui->tabProjects->currentIndex());
    }

    refresh();
}

/*!
 \brief

 \fn cdegs_main::closeProject
 \param index
*/
void cdegs_main::closeProject(int index){
    if(QMessageBox::question(this, "Warning! Close Project?", "Closing your project will cause all unsaved changes to be lost.") == QMessageBox::Yes){
        dynamic_cast<project_tab_widget*>(ui->tabProjects->widget(index))->getProject().reset();
        ui->tabProjects->removeTab(index);
    }

    refresh();
}

/*!
 \brief

 \fn cdegs_main::changeProject
 \param index
*/
void cdegs_main::changeProject(int index){
    if(index != -1){
        project = dynamic_cast<project_tab_widget*>(ui->tabProjects->widget(index))->getProject();
    }
    else{
        project.reset();
    }

    refresh();
}

/*!
 \brief

 \fn cdegs_main::changeTab
*/
void cdegs_main::changeTab(){
    refresh();
}

/*!
 \brief

 \fn cdegs_main::newConfig
*/
void cdegs_main::newConfig(){
    config.reset(new Configuration());

    if(ui->tabProjects->currentIndex() != -1){
        dynamic_cast<project_tab_widget*>(ui->tabProjects->currentWidget())->addConfig(config);

        refresh();
    }
}

/*!
 \brief

 \fn cdegs_main::openConfig
*/
void cdegs_main::openConfig(std::shared_ptr<Configuration> config){
    if(ui->tabProjects->currentIndex() != -1){
        dynamic_cast<project_tab_widget*>(ui->tabProjects->currentWidget())->addConfig(config);

        refresh();
    }
}

/*!
 \brief

 \fn cdegs_main::saveConfig
*/
void cdegs_main::saveConfig(){

}

/*!
 \brief

 \fn cdegs_main::closeConfig
*/
void cdegs_main::closeConfig(){

}

/*!
 \brief

 \fn cdegs_main::exportConfig
*/
void cdegs_main::exportConfig(){

}

/*!
 \brief

 \fn cdegs_main::exportConfigAs
*/
void cdegs_main::exportConfigAs(){

}

/*!
 \brief

 \fn cdegs_main::about
*/
void cdegs_main::about(){
    QMessageBox::about(this, "CDEGS Aid", "CDEGS-Aid est un logiciel d'aide pour la génération de fichiers de simulation compatibles avec SESCad et CDEGS-HiFreq pour des simulations de champ électrics, d'affichage et d'analyse de résultat de simulations CDEGS-HiFreq.\n\n(c) Renaud Bigras 2014");
}

/*!
 \brief

 \fn cdegs_main::openStyleDialog
*/
void cdegs_main::openStyleDialog(){
    style_dialog* diag = new style_dialog(this);
    QObject::connect(diag, SIGNAL(returnStyle(std::string)),
                     this, SLOT(changeStyle(std::string)));
    diag->exec();
    QObject::disconnect(diag, SIGNAL(returnStyle(std::string)),
                     this, SLOT(changeStyle(std::string)));
    delete diag;
}

/*!
 \brief

 \fn cdegs_main::changeStyle
 \param style
*/
void cdegs_main::changeStyle(std::string style){
    QString styleSheet = AppUtils::getInstance().getStyleSheets().at(style);
    this->setStyleSheet(styleSheet);
}

/*!
 \brief

 \fn cdegs_main::openConfigDialog
*/
void cdegs_main::openConfigDialog(){
    if(project){
        configuration_chooser_dialog* diag = new configuration_chooser_dialog(this, project);
        QObject::connect(diag, SIGNAL(returnConfig(std::shared_ptr<Configuration>)),
                         this, SLOT(openConfig(std::shared_ptr<Configuration>)));
        diag->exec();
        QObject::disconnect(diag, SIGNAL(returnConfig(std::shared_ptr<Configuration>)),
                            this, SLOT(openConfig(std::shared_ptr<Configuration>)));
        delete diag;
    }
}

void cdegs_main::tabModified(QWidget* widget){
    int index = ui->tabProjects->indexOf(widget);
    QString name = ui->tabProjects->tabText(index);
    if(!name.endsWith("*")) name.append("*");
    ui->tabProjects->setTabText(index, name);
}

