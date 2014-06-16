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

#include "configuration_chooser_dialog.h"
#include "ui_configuration_chooser_dialog.h"

configuration_chooser_dialog::configuration_chooser_dialog(QWidget *parent, std::shared_ptr<Project> project) :
    QDialog(parent),
    ui(new Ui::configuration_chooser_dialog)
{
    ui->setupUi(this);
    m_project = project;
    m_model = new QStringListModel();
    populateModel();
    ui->listView_config->setModel(m_model);
    connectSlots();
}

void configuration_chooser_dialog::populateModel(){
    QStringList stringList;

    for(int i = 1; i<= m_project->getConfigurations().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(m_project->getConfigurations().at(i)->getIdentifier());
        stringList.push_back(text);
    }

    m_model->setStringList(stringList);
}

void configuration_chooser_dialog::connectSlots(){
    QObject::connect(ui->pushButton_ok, SIGNAL(clicked()),
                     this, SLOT(buttonOk()));

    QObject::connect(ui->pushButton_cancel, SIGNAL(clicked()),
                     this, SLOT(close()));

    QObject::connect(ui->listView_config, SIGNAL(doubleClicked(QModelIndex)),
                     this, SLOT(selectConfig(QModelIndex)));
}

void configuration_chooser_dialog::buttonOk(){
    QString identifier = m_model->data(ui->listView_config->currentIndex(), Qt::DisplayRole).toString();

    try{
        identifier.truncate(identifier.indexOf(" "));
        int index = identifier.toInt();

        m_config = m_project->getConfigurations().at(index);

        emit returnConfig(m_config);
    }
    catch(std::out_of_range e){
        QMessageBox::warning(this, "Warning", "No configuration was selected.");
    }

    this->close();
}

void configuration_chooser_dialog::selectConfig(QModelIndex index){
    QString identifier = m_model->data(index, Qt::DisplayRole).toString();

    identifier.truncate(identifier.indexOf(" "));
    int ind = identifier.toInt();

    m_config = m_project->getConfigurations().at(ind);

    emit returnConfig(m_config);

    this->close();
}

configuration_chooser_dialog::~configuration_chooser_dialog()
{
    delete ui;
}
