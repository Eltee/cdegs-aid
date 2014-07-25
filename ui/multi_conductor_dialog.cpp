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

#include "multi_conductor_dialog.h"
#include "ui_multi_conductor_dialog.h"

MultiConductorDialog::MultiConductorDialog(QWidget *parent, std::shared_ptr<Configuration> config) :
    QDialog(parent),
    ui(new Ui::MultiConductorDialog)
{
    ui->setupUi(this);
    m_config = config;
    connectSlots();
}

MultiConductorDialog::~MultiConductorDialog()
{
    delete ui;
}

std::vector<std::shared_ptr<Conductor>> MultiConductorDialog::getConductors() const{
    return m_conductors;
}

void MultiConductorDialog::connectSlots(){
    QObject::connect(ui->pushButton_cancel, SIGNAL(released()),
                     this, SLOT(close()));

    QObject::connect(ui->pushButton_previous, SIGNAL(released()),
                     this, SLOT(previous()));

    QObject::connect(ui->pushButton_next, SIGNAL(released()),
                     this, SLOT(next()));
}

void MultiConductorDialog::disconnectSlots(){
    QObject::disconnect(ui->pushButton_cancel, SIGNAL(released()),
                     this, SLOT(close()));

    QObject::disconnect(ui->pushButton_previous, SIGNAL(released()),
                     this, SLOT(previous()));

    QObject::disconnect(ui->pushButton_next, SIGNAL(released()),
                     this, SLOT(next()));
}

void MultiConductorDialog::refresh(){

}

void MultiConductorDialog::next(){
    switch(ui->stackedWidget->currentIndex()){
        case 0: //Shape and quantity
            m_conductors.clear();
            if(ui->radioButton_first_2cHoriz->isChecked()){
                std::shared_ptr<Conductor> cond, cond2;
                cond.reset(new Conductor());
                cond2.reset(new Conductor());
                m_conductors.push_back(cond);
                m_conductors.push_back(cond2);
                ui->stackedWidget->setCurrentIndex(1);
                ui->pushButton_previous->setEnabled(true);
            }
            else if(ui->radioButton_first_2cVert->isChecked()){
                std::shared_ptr<Conductor> cond, cond2;
                cond.reset(new Conductor());
                cond2.reset(new Conductor());
                m_conductors.push_back(cond);
                m_conductors.push_back(cond2);
                ui->stackedWidget->setCurrentIndex(1);
                ui->pushButton_previous->setEnabled(true);
            }
            else if(ui->radioButton_first_3c->isChecked()){
                std::shared_ptr<Conductor> cond, cond2, cond3;
                cond.reset(new Conductor());
                cond2.reset(new Conductor());
                cond3.reset(new Conductor());
                m_conductors.push_back(cond);
                m_conductors.push_back(cond2);
                m_conductors.push_back(cond3);
                ui->stackedWidget->setCurrentIndex(1);
                ui->pushButton_previous->setEnabled(true);
            }
            else if(ui->radioButton_first_4c->isChecked()){
                std::shared_ptr<Conductor> cond, cond2, cond3, cond4;
                cond.reset(new Conductor());
                cond2.reset(new Conductor());
                cond3.reset(new Conductor());
                cond4.reset(new Conductor());
                m_conductors.push_back(cond);
                m_conductors.push_back(cond2);
                m_conductors.push_back(cond3);
                m_conductors.push_back(cond4);
                ui->stackedWidget->setCurrentIndex(1);
                ui->pushButton_previous->setEnabled(true);
            }
            else{

            }
            break;
        case 1: //Distance
            break;
        case 2: //Characteristics
            break;
        case 3: //Review and finish
            break;
        default:
            break;
    }
}

void MultiConductorDialog::previous(){
    switch(ui->stackedWidget->currentIndex()){
        case 0: //Shape and quantity
            break;
        case 1: //Distance
            ui->stackedWidget->setCurrentIndex(0);
            ui->pushButton_previous->setEnabled(false);
            break;
        case 2: //Characteristics
            break;
        case 3: //Review and finish
            break;
        default:
            break;
    }
}
