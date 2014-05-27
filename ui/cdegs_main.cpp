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

cdegs_main::cdegs_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cdegs_main){
    ui->setupUi(this);

    connectSlots();
}

cdegs_main::~cdegs_main(){
    delete ui;
    if(project != NULL){
        config = NULL;
        delete(project);
        project = NULL;
    }
}

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
}

void cdegs_main::refresh(){
    updateProject();
    updateConfig();
    updateTitle();
    updateActions();    
    updateTab();
}

void cdegs_main::updateTab(){ //TO-DO: CHANGE
    if(project != NULL && ui->tabProjects->count() > 0){
        ui->tabProjects->setTabText(ui->tabProjects->currentIndex(), QString::fromStdString(project->getFileName()));
    }
}

void cdegs_main::updateProject(){
    if(ui->tabProjects->currentIndex() != -1){
        project = dynamic_cast<project_tab_widget*>(ui->tabProjects->currentWidget())->getProject();
    }
    else{
        project = NULL;
    }

}

void cdegs_main::updateConfig(){
    if(ui->tabProjects->currentIndex() != -1){
        config = dynamic_cast<project_tab_widget*>(ui->tabProjects->currentWidget())->getConfig();
    }
    else{
        config = NULL;
    }
}

void cdegs_main::updateActions(){
    if(project != NULL){
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

    if(config != NULL){
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

void cdegs_main::updateTitle(){
    if(project != NULL){
        QString title;
        std::string stdTitle;
        if(config != NULL){
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

void cdegs_main::newProject(){
    project = new Project();

    int index = ui->tabProjects->addTab(new project_tab_widget(this, this, project), QString::fromStdString(project->getFileName()));

    ui->tabProjects->setCurrentIndex(index);


    refresh();
}

void cdegs_main::openProject(){
    QString filePath = QFileDialog::getOpenFileName(this, "Choose Project to open..", "", "CDEGS-Aid Project File (*.cdp)");
    project = AppUtils::getInstance().loadProject(filePath.toStdWString().c_str());

    int index = ui->tabProjects->addTab(new project_tab_widget(this, this, project), QString::fromStdString(project->getFileName()));
    ui->tabProjects->setCurrentIndex(index);

    refresh();
}

void cdegs_main::saveProject(){
    if(project != NULL) AppUtils::getInstance().saveProject(*project);
}

void cdegs_main::saveProjectAs(){
    if(project!= NULL){
        QString filePath = QFileDialog::getSaveFileName(this, "Choose file to save..", "", "CDEGS-Aid Project File (*.cdp)");
        QDir d = QFileInfo(filePath).absoluteDir();
        project->setAbsPath(d.absolutePath().toStdString()).setRelPath(d.path().toStdString());
        project->setFileName(QFileInfo(filePath).fileName().toStdString());
        AppUtils::getInstance().saveProject(*project);
    }

    refresh();
}

void cdegs_main::closeProject(){
    if(QMessageBox::question(this, "Warning! Close Project?", "Closing your project will cause all unsaved changes to be lost.") == QMessageBox::Yes){
        delete(project);
        config = NULL;
        project = NULL;
        ui->tabProjects->removeTab(ui->tabProjects->currentIndex());
    }

    refresh();
}

void cdegs_main::closeProject(int index){
    if(QMessageBox::question(this, "Warning! Close Project?", "Closing your project will cause all unsaved changes to be lost.") == QMessageBox::Yes){
        delete(dynamic_cast<project_tab_widget*>(ui->tabProjects->widget(index))->getProject());
        ui->tabProjects->removeTab(index);
    }

    refresh();
}

void cdegs_main::changeProject(int index){
    if(index != -1){
        project = dynamic_cast<project_tab_widget*>(ui->tabProjects->widget(index))->getProject();
    }
    else{
        project = NULL;
    }

    refresh();
}

void cdegs_main::changeTab(){
    refresh();
}

void cdegs_main::newConfig(){
    config = new Configuration();

    if(ui->tabProjects->currentIndex() != -1){
        dynamic_cast<project_tab_widget*>(ui->tabProjects->currentWidget())->addConfig(config);

        refresh();
    }
}

void cdegs_main::openConfig(){

}

void cdegs_main::saveConfig(){

}

void cdegs_main::closeConfig(){

}

void cdegs_main::exportConfig(){

}

void cdegs_main::exportConfigAs(){

}

void cdegs_main::about(){
    QMessageBox::about(this, "CDEGS Aid", "CDEGS-Aid est un logiciel d'aide pour la génération de fichiers de simulation compatibles avec SESCad et CDEGS-HiFreq pour des simulations de champ électrics, d'affichage et d'analyse de résultat de simulations CDEGS-HiFreq.\n\n(c) Renaud Bigras 2014");
}
