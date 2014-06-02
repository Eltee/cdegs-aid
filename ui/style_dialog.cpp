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

#include "style_dialog.h"
#include "ui_style_dialog.h"

style_dialog::style_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::style_dialog)
{
    ui->setupUi(this);
    m_model = new QStringListModel();
    populateModel();
    ui->listView_style->setModel(m_model);
    connectSlots();
}

void style_dialog::populateModel(){
    QStringList stringList;

    for(auto& entry : AppUtils::getInstance().getStyleSheets()){
        stringList.push_back(QString::fromStdString(entry.first));
    }

    m_model->setStringList(stringList);
}

void style_dialog::connectSlots(){
    QObject::connect(ui->pushButton_ok, SIGNAL(clicked()),
                     this, SLOT(buttonOk()));

    QObject::connect(ui->pushButton_cancel, SIGNAL(clicked()),
                     this, SLOT(close()));

    QObject::connect(ui->listView_style, SIGNAL(doubleClicked(QModelIndex)),
                     this, SLOT(selectStyle(QModelIndex)));
}

void style_dialog::buttonOk(){
    m_style = m_model->data(ui->listView_style->currentIndex(), Qt::DisplayRole).toString().toStdString();

    emit returnStyle(m_style);

    this->close();
}

void style_dialog::selectStyle(QModelIndex index){
    m_style = m_model->data(index, Qt::DisplayRole).toString().toStdString();

    emit returnStyle(m_style);

    this->close();
}

style_dialog::~style_dialog()
{
    delete ui;
    delete m_model;
}
