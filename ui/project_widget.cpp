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

#include "project_widget.h"
#include "ui_project_widget.h"

/*!
 \brief

 \fn project_widget::project_widget
 \param parent
 \param dp
 \param p
*/
project_widget::project_widget(QWidget *parent, project_tab_widget* dp, std::shared_ptr<Project> p, std::shared_ptr<Project> p2) :
    QWidget(parent),
    ui(new Ui::project_widget)
{
    project = p;
    projectOrig = p2;
    ui->setupUi(this);
    defParent = dp;
    refresh();
    connectSlots();
}

/*!
 \brief

 \fn project_widget::getProject
 \return Project
*/
std::shared_ptr<Project> project_widget::getProject(){
    return project;
}

/*!
 \brief

 \fn project_widget::~project_widget
*/
project_widget::~project_widget()
{
    delete ui;
}

/*!
 \brief

 \fn project_widget::connectSlots
*/
void project_widget::connectSlots(){
    QObject::connect(ui->dateEdit_pDate, SIGNAL(dateChanged(QDate)),
                     this, SLOT(changeDate(QDate)));

    QObject::connect(ui->lineEdit_pAuthor, SIGNAL(textChanged(QString)),
                     this, SLOT(changeAuthor(QString)));

    QObject::connect(ui->lineEdit_pName, SIGNAL(textChanged(QString)),
                     this, SLOT(changeName(QString)));

    QObject::connect(ui->lineEdit_pPath, SIGNAL(textChanged(QString)),
                     this, SLOT(changeFilepath(QString)));

    QObject::connect(ui->textEdit_pDesc, SIGNAL(textChanged()),
                     this, SLOT(changeDescription()));

    QObject::connect(ui->toolButton, SIGNAL(clicked()),
                     this, SLOT(openFilepath()));
}

void project_widget::disconnectSlots(){
    QObject::disconnect(ui->dateEdit_pDate, SIGNAL(dateChanged(QDate)),
                     this, SLOT(changeDate(QDate)));

    QObject::disconnect(ui->lineEdit_pAuthor, SIGNAL(textChanged(QString)),
                     this, SLOT(changeAuthor(QString)));

    QObject::disconnect(ui->lineEdit_pName, SIGNAL(textChanged(QString)),
                     this, SLOT(changeName(QString)));

    QObject::disconnect(ui->lineEdit_pPath, SIGNAL(textChanged(QString)),
                     this, SLOT(changeFilepath(QString)));

    QObject::disconnect(ui->textEdit_pDesc, SIGNAL(textChanged()),
                     this, SLOT(changeDescription()));

    QObject::disconnect(ui->toolButton, SIGNAL(clicked()),
                     this, SLOT(openFilepath()));
}

/*!
 \brief

 \fn project_widget::refresh
*/
void project_widget::refresh(){
    disconnectSlots();
    defParent->refresh();
    if(project){
        std::string filePath = project->getAbsPath() + "/" + project->getFileName();
        ui->lineEdit_pAuthor->setText(QString::fromStdString(project->getMetadata().author));
        ui->lineEdit_pId->setText(QString::fromStdString(project->getId()));
        ui->lineEdit_pName->setText(QString::fromStdString(project->getMetadata().name));
        ui->lineEdit_pPath->setText(QString::fromStdString(filePath));
        ui->dateEdit_pDate->setDate(project->getMetadata().date);
        ui->textEdit_pDesc->setDocument(project->getMetadata().description.clone());
        if(*project.get() != projectOrig.get()) emit dataModified(this);
    }
    connectSlots();
}

void project_widget::changeDate(QDate date){
    if(project){
        project->setMetaDate(date);
        refresh();
    }
}

void project_widget::changeName(QString name){
    if(project){
        project->setMetaName(name.toStdString());
        refresh();
    }
}

void project_widget::changeAuthor(QString author){
    if(project){
        project->setMetaAuthor(author.toStdString());
        refresh();
    }
}

void project_widget::changeDescription(){
    if(project){
        project->setMetaDescription(ui->textEdit_pDesc->document()->toPlainText().toStdString());
        refresh();
    }
}

void project_widget::changeFilepath(QString path){
    if(project){
        int index, toGo;
        index = path.lastIndexOf("/");
        toGo = path.size() - path.lastIndexOf("/");
        project->setFileName(path.right(toGo-1).toStdString());
        path.remove(index, toGo);
        project->setAbsPath(path.toStdString());
        project->setRelPath(path.toStdString());
        refresh();
    }
}

void project_widget::openFilepath(){
    QString filepath = QFileDialog::getSaveFileName(this, "Choose file to save to..", "", "CDEGS-Aid Project File (*.cdp)");

    ui->lineEdit_pPath->setText(filepath);
}

