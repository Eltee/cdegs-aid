/******************************************************************************
* Projet:     PROJECT_NAME
*  /Project
*
* Nom/Name:    name_here.h
*
* Description: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
*              Vestibulum posuere venenatis aliquet. Proin sit amet ornare
*              libero, nec aliquam mi. Curabitur iaculis, quam ultrices
*              vulputate laoreet, felis risus consectetur sem, quis semper
*              tortor ante ac lacus. Sed porttitor aliquam blandit. Nullam
*              vel eros ac velit mattis scelerisque.
*
* Auteur:      Renaud Bigras, Hydro-Qu�bec Trans�nergie
*  /Author
*
* Cr��:        07-05-2014
*  /Created
*
* Copyright:   (c) Renaud Bigras 2014
*
*   This file is part of PROJECT_NAME.
*
*   PROJECT_NAME is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   PROJECT_NAME is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with PROJECT_NAME. If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#include "project_tab_widget.h"
#include "ui_project_tab_widget.h"

/*!
 \brief

 \fn project_tab_widget::project_tab_widget
 \param parent
 \param dp
 \param p
*/
project_tab_widget::project_tab_widget(QWidget *parent, cdegs_main* dp, std::shared_ptr<Project> p, QString name) :
    QWidget(parent),
    ui(new Ui::project_tab_widget)
{
    ui->setupUi(this);
    m_name = name;
    projectOrig.reset(new Project(p.get()));
    project = p;
    connectSlots();
    defParent = dp;
    project_widget* tab = new project_widget(this, this, project, projectOrig, "Project Settings");

    QObject::connect(defParent, SIGNAL(saveOccurred()),
                     tab, SLOT(refresh()));

    ui->tabProject->addTab(tab, tab->getName());
}

/*!
 \brief

 \fn project_tab_widget::~project_tab_widget
*/
project_tab_widget::~project_tab_widget()
{
    delete ui;
}

/*!
 \brief

 \fn project_tab_widget::getProject
 \return Project
*/
std::shared_ptr<Project> project_tab_widget::getProject(){
    return project;
}

QString const& project_tab_widget::getName() const{
    return m_name;
}

/*!
 \brief

 \fn project_tab_widget::connectSlots
*/
void project_tab_widget::connectSlots(){
    QObject::connect(ui->tabProject, SIGNAL(currentChanged(int)),
                     this, SLOT(changeTab()));

    QObject::connect(ui->tabProject, SIGNAL(tabCloseRequested(int)),
                     this, SLOT(closeConfig(int)));
}

/*!
 \brief

 \fn project_tab_widget::getConfig
 \return Configuration
*/
std::shared_ptr<Configuration> project_tab_widget::getConfig(){
    if(ui->tabProject->currentIndex() > 0){
        return dynamic_cast<configuration_widget*>(ui->tabProject->currentWidget())->getConfig();
    }
    else{
        std::shared_ptr<Configuration> nol;
        return nol;
    }
}

/*!
 \brief

 \fn project_tab_widget::refresh
*/
void project_tab_widget::refresh(){
    m_name = QString::fromStdString(project->getFileName());
    if(project->isModified()){
        QString newName = m_name;
        newName.append("*");
        defParent->changeTabName(this, newName);
    }
    else{
        defParent->changeTabName(this, m_name);
    }
    defParent->refresh();
}

/*!
 \brief

 \fn project_tab_widget::addConfig
 \param config
*/
void project_tab_widget::addConfig(std::shared_ptr<Configuration> config){
    bool alreadyPresent = false;

    for(int i = 1; i < ui->tabProject->count(); i++){
        if(dynamic_cast<configuration_widget*>(ui->tabProject->widget(i))->getConfig()->getId() == config->getId()) alreadyPresent = true;
    }

    if(!alreadyPresent){
        configuration_widget* tab = new configuration_widget(this, this, config, QString::fromStdString(config->getIdentifier()));

        QObject::connect(defParent, SIGNAL(saveOccurred()),
                         tab, SLOT(refresh()));

        project->setModified(true);
        int index = ui->tabProject->addTab(tab, QString::fromStdString(config->getIdentifier()));
        ui->tabProject->setCurrentIndex(index);
    }
}

/*!
 \brief

 \fn project_tab_widget::changeTab
*/
void project_tab_widget::changeTab(){
    refresh();
}

void project_tab_widget::closeConfig(){
    if(ui->tabProject->currentIndex() > 0){
        if(QMessageBox::question(this, "Warning! Close Configuration?", "Closing your configuration will cause all unsaved changes to be lost.") == QMessageBox::Yes){
            if(dynamic_cast<configuration_widget*>(ui->tabProject->widget(ui->tabProject->currentIndex()))->getConfig()->isModified()){
                if(QMessageBox::question(this, "Save changes?", "Save configuration before closing?") == QMessageBox::Yes){
                    saveConfig();
                }
            }
            dynamic_cast<configuration_widget*>(ui->tabProject->widget(ui->tabProject->currentIndex()))->getConfig().reset();
            ui->tabProject->removeTab(ui->tabProject->currentIndex());
        }
    }

    refresh();
}

/*!
 \brief

 \fn project_tab_widget::closeConfig
 \param index
*/
void project_tab_widget::closeConfig(int index){

    if(index > 0){
        if(QMessageBox::question(this, "Warning! Close Configuration?", "Closing your configuration will cause all unsaved changes to be lost.") == QMessageBox::Yes){
            if(dynamic_cast<configuration_widget*>(ui->tabProject->widget(index))->getConfig()->isModified()){
                if(QMessageBox::question(this, "Save changes?", "Save configuration before closing?") == QMessageBox::Yes){
                    std::shared_ptr<Configuration> config = dynamic_cast<configuration_widget*>(ui->tabProject->widget(index))->getConfig();

                    if(project->getConfigurations().count(config->getId()) > 0){
                        project->replaceConfiguration(config);
                    }
                    else{
                        project->addConfiguration(config, true);
                    }

                    config->setModified(false);

                    refresh();
                }
            }
            dynamic_cast<configuration_widget*>(ui->tabProject->widget(index))->getConfig().reset();
            ui->tabProject->removeTab(index);
        }
    }

    refresh();
}

void project_tab_widget::changeTabName(QWidget* widget, QString name){
    int index = ui->tabProject->indexOf(widget);
    ui->tabProject->setTabText(index, name);
}

void project_tab_widget::modifyProject(){
    project->setModified(true);
}

void project_tab_widget::saveConfig(){
    defParent->saveConfig();
}

void project_tab_widget::saveAllConfigs(){
    std::shared_ptr<Configuration> config;

    for(int i = 1; i < ui->tabProject->count(); i++){
        config = dynamic_cast<configuration_widget*>(ui->tabProject->widget(i))->getConfig();

        if(project->getConfigurations().count(config->getId()) > 0){
            project->replaceConfiguration(config);
        }
        else{
            project->addConfiguration(config, true);
        }

        config->setModified(false);

        refresh();
    }
}
