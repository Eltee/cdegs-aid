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
    populateCharacteristics();
    ui->stackedWidget->setCurrentIndex(0);
    connectSlots();
    initPlot();
    complete = false;
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

void MultiConductorDialog::initPlot(){
    ui->qcustomplot_fourth_graph->plotLayout()->insertRow(0);
    QCPPlotTitle* title = new QCPPlotTitle(ui->qcustomplot_fourth_graph, tr("Position of Conductors"));
    title->setTextColor(Qt::white);
    title->setAntialiased(true);
    ui->qcustomplot_fourth_graph->plotLayout()->addElement(0, 0, title);
    ui->qcustomplot_fourth_graph->legend->setVisible(false);
    ui->qcustomplot_fourth_graph->legend->setAntialiased(true);

    ui->qcustomplot_fourth_graph->addGraph();
    ui->qcustomplot_fourth_graph->addGraph();

    ui->qcustomplot_fourth_graph->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->qcustomplot_fourth_graph->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->qcustomplot_fourth_graph->graph(0)->setPen(QPen(QColor(141, 95, 0), 3));
    ui->qcustomplot_fourth_graph->graph(0)->setName(tr("Ground"));
    ui->qcustomplot_fourth_graph->graph(0)->setAntialiased(true);

    ui->qcustomplot_fourth_graph->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->qcustomplot_fourth_graph->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QColor(0, 102, 255), 10));
    ui->qcustomplot_fourth_graph->graph(1)->setPen(QPen(QColor(120, 120, 120), 1));
    ui->qcustomplot_fourth_graph->graph(1)->setName(tr("Conductors"));
    ui->qcustomplot_fourth_graph->graph(1)->setAntialiased(true);

    ui->qcustomplot_fourth_graph->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->qcustomplot_fourth_graph->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->qcustomplot_fourth_graph->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->qcustomplot_fourth_graph->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->qcustomplot_fourth_graph->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->qcustomplot_fourth_graph->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->qcustomplot_fourth_graph->xAxis->setTickLabelColor(Qt::white);
    ui->qcustomplot_fourth_graph->yAxis->setTickLabelColor(Qt::white);
    ui->qcustomplot_fourth_graph->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::SolidLine));
    ui->qcustomplot_fourth_graph->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::SolidLine));
    ui->qcustomplot_fourth_graph->xAxis->grid()->setSubGridVisible(false);
    ui->qcustomplot_fourth_graph->yAxis->grid()->setSubGridVisible(false);
    ui->qcustomplot_fourth_graph->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->qcustomplot_fourth_graph->xAxis->grid()->setAntialiased(true);
    ui->qcustomplot_fourth_graph->yAxis->grid()->setAntialiased(true);
    ui->qcustomplot_fourth_graph->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->qcustomplot_fourth_graph->xAxis->setUpperEnding(QCPLineEnding::esSkewedBar);
    ui->qcustomplot_fourth_graph->yAxis->setUpperEnding(QCPLineEnding::esSkewedBar);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->qcustomplot_fourth_graph->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->qcustomplot_fourth_graph->axisRect()->setBackground(axisRectGradient);
    ui->qcustomplot_fourth_graph->axisRect()->setAntialiased(true);

    ui->qcustomplot_fourth_graph->xAxis->setLabel(tr("Y - Distance from Line Center (m)"));
    ui->qcustomplot_fourth_graph->xAxis->setLabelColor(Qt::white);
    ui->qcustomplot_fourth_graph->xAxis->setAntialiased(true);
    ui->qcustomplot_fourth_graph->xAxis->setTicks(true);
    ui->qcustomplot_fourth_graph->xAxis->setAutoTicks(true);
    ui->qcustomplot_fourth_graph->xAxis->setRange(-5, 5);
    ui->qcustomplot_fourth_graph->xAxis->setAutoTickStep(false);
    ui->qcustomplot_fourth_graph->xAxis->setTickStep(1);
    ui->qcustomplot_fourth_graph->xAxis->setTickLength(0, 2);
    ui->qcustomplot_fourth_graph->xAxis->setSubTickCount(1);
    ui->qcustomplot_fourth_graph->xAxis->setSubTickLength(0,1);

    ui->qcustomplot_fourth_graph->yAxis->setLabel(tr("Z - Height (m)"));
    ui->qcustomplot_fourth_graph->yAxis->setLabelColor(Qt::white);
    ui->qcustomplot_fourth_graph->yAxis->setAntialiased(true);
    ui->qcustomplot_fourth_graph->yAxis->setTicks(true);
    ui->qcustomplot_fourth_graph->yAxis->setAutoTicks(true);
    ui->qcustomplot_fourth_graph->yAxis->setRange(-10, 5);
    ui->qcustomplot_fourth_graph->yAxis->setRangeReversed(true);
    ui->qcustomplot_fourth_graph->yAxis->setAutoTickStep(false);
    ui->qcustomplot_fourth_graph->yAxis->setTickStep(1);
    ui->qcustomplot_fourth_graph->yAxis->setTickLength(0, 2);
    ui->qcustomplot_fourth_graph->yAxis->setSubTickCount(1);
    ui->qcustomplot_fourth_graph->yAxis->setSubTickLength(0,1);

    ui->qcustomplot_fourth_graph->rescaleAxes();
}

void MultiConductorDialog::refreshPlot(){
    QVector<double> keys, values, groundKeys, groundValues;
    int lowX = -4;
    int lowY = -9;
    int highX = 4;
    int highY = 4;
    for(std::shared_ptr<Conductor> cond : m_conductors){
        if(cond->getStartCoords().y < lowX) lowX = cond->getStartCoords().y;
        if(cond->getStartCoords().z < lowY) lowY = cond->getStartCoords().z;
        if(cond->getEndCoords().y > highX) highX = cond->getEndCoords().y;
        if(cond->getEndCoords().z > highY) highY = cond->getEndCoords().z;
        keys.push_back(cond->getStartCoords().y);
        values.push_back(cond->getStartCoords().z);
    }
    for(double i = lowX - 1; i <= highX + 1; i+= 0.5){
        groundKeys.push_back(i);
        groundValues.push_back(0);
    }
    ui->qcustomplot_fourth_graph->xAxis->setRange((lowX - 1), (highX + 1));
    ui->qcustomplot_fourth_graph->yAxis->setRange((lowY - 1), (highY + 1));
    ui->qcustomplot_fourth_graph->yAxis->setRangeReversed(true);
    ui->qcustomplot_fourth_graph->graph(0)->setData(groundKeys, groundValues);
    ui->qcustomplot_fourth_graph->graph(1)->setData(keys, values);
    ui->qcustomplot_fourth_graph->replot();
}

void MultiConductorDialog::populateCharacteristics(){
    ui->comboBox_third_lType->clear();
    for(unsigned int i = 0; i < m_config->getLeadTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(m_config->getLeadTypes().at(i)->getName());
        ui->comboBox_third_lType->addItem(text);
    }

    ui->comboBox_third_coat->clear();
    for(unsigned int i = 0; i < m_config->getCoatings().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(m_config->getCoatings().at(i)->getName());
        ui->comboBox_third_coat->addItem(text);
    }

    ui->comboBox_third_ener->clear();
    for(unsigned int i = 0; i < m_config->getEnergizations().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(m_config->getEnergizations().at(i)->getIdentification());
        ui->comboBox_third_ener->addItem(text);
    }

    ui->comboBox_third_cType->clear();
    for(unsigned int i = 0; i < m_config->getConductorTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(m_config->getConductorTypes().at(i)->getName());
        ui->comboBox_third_cType->addItem(text);
    }

    ui->comboBox_third_cbType->clear();
    for(unsigned int i = 0; i < m_config->getCableTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(m_config->getCableTypes().at(i)->getName());
        ui->comboBox_third_cbType->addItem(text);
    }
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
            break;
        case 1: //Distance
            if(ui->doubleSpinBox_second_distance->value() > 0){
                coords start, end;
                start.x = -(ui->doubleSpinBox_second_x->value());
                end.x = ui->doubleSpinBox_second_x->value();
                start.y = ui->doubleSpinBox_second_y->value();
                end.y = ui->doubleSpinBox_second_y->value();
                start.z = ui->doubleSpinBox_second_z->value();
                end.z = ui->doubleSpinBox_second_z->value();

                for(std::shared_ptr<Conductor> cond : m_conductors){
                    cond->setCoords(start, end);
                }

                if(ui->radioButton_first_2cHoriz->isChecked()){
                    start.y = start.y - (ui->doubleSpinBox_second_distance->value() / 2);
                    end.y = start.y;
                    m_conductors[0]->setCoords(start, end);
                    start.y = start.y + (ui->doubleSpinBox_second_distance->value());
                    end.y = start.y;
                    m_conductors[1]->setCoords(start, end);
                }
                else if(ui->radioButton_first_2cVert->isChecked()){
                    start.z = start.z - (ui->doubleSpinBox_second_distance->value() / 2);
                    end.z = start.z;
                    m_conductors[0]->setCoords(start, end);
                    start.z = start.z + (ui->doubleSpinBox_second_distance->value());
                    end.z = start.z;
                    m_conductors[1]->setCoords(start, end);
                }
                else if(ui->radioButton_first_3c->isChecked()){
                    start.z = start.z - (ui->doubleSpinBox_second_distance->value() / 2);
                    end.z = start.z;
                    m_conductors[0]->setCoords(start, end);
                    start.z = start.z + (ui->doubleSpinBox_second_distance->value());
                    end.z = start.z;
                    start.y = start.y - (ui->doubleSpinBox_second_distance->value() / 2);
                    end.y = start.y;
                    m_conductors[1]->setCoords(start, end);
                    start.y = start.y + (ui->doubleSpinBox_second_distance->value());
                    end.y = start.y;
                    m_conductors[2]->setCoords(start, end);
                }
                else if(ui->radioButton_first_4c->isChecked()){
                    start.y = start.y - (ui->doubleSpinBox_second_distance->value() / 2);
                    end.y = start.y;
                    start.z = start.z - (ui->doubleSpinBox_second_distance->value() / 2);
                    end.z = start.z;
                    m_conductors[0]->setCoords(start, end);
                    start.y = start.y + (ui->doubleSpinBox_second_distance->value());
                    end.y = start.y;
                    m_conductors[1]->setCoords(start, end);
                    start.z = start.z + (ui->doubleSpinBox_second_distance->value());
                    end.z = start.z;
                    m_conductors[2]->setCoords(start, end);
                    start.y = start.y - (ui->doubleSpinBox_second_distance->value());
                    end.y = start.y;
                    m_conductors[3]->setCoords(start, end);
                }

                ui->stackedWidget->setCurrentIndex(2);
                ui->pushButton_previous->setEnabled(true);
            }
            else{
                QMessageBox::critical(this, tr("Failure"), tr("Invalid distance."));
            }
            break;
        case 2: //Characteristics
            for(std::shared_ptr<Conductor> cond : m_conductors){
                cond->setLeadType(m_config->getLeadTypes().at(ui->comboBox_third_lType->currentIndex()));
                cond->setCoating(m_config->getCoatings().at(ui->comboBox_third_coat->currentIndex()));
                cond->setConductorType(m_config->getConductorTypes().at(ui->comboBox_third_cType->currentIndex()));
                cond->setEnergization(m_config->getEnergizations().at(ui->comboBox_third_ener->currentIndex()));
                cond->setCableType(m_config->getCableTypes().at(ui->comboBox_third_cbType->currentIndex()));
                cond->setRadius(ui->doubleSpinBox_third_radius->value());
            }
            refreshPlot();
            ui->stackedWidget->setCurrentIndex(3);
            ui->pushButton_next->setText(tr("Finish.."));
            ui->pushButton_previous->setEnabled(true);
            if(m_conductors.size() == 2){
                ui->lineEdit_fourth_cond->setText(tr("Conductor - (X): ") + QString::number(m_conductors[0]->getStartCoords().x) + " (Y): " + QString::number(m_conductors[0]->getStartCoords().y) + " (Z): " + QString::number(m_conductors[0]->getStartCoords().z));
                ui->lineEdit_fourth_cond2->setText(tr("Conductor - (X): ") + QString::number(m_conductors[1]->getStartCoords().x) + " (Y): " + QString::number(m_conductors[1]->getStartCoords().y) + " (Z): " + QString::number(m_conductors[1]->getStartCoords().z));
            }
            else if(m_conductors.size() == 3){
                ui->lineEdit_fourth_cond->setText(tr("Conductor - (X): ") + QString::number(m_conductors[0]->getStartCoords().x) + " (Y): " + QString::number(m_conductors[0]->getStartCoords().y) + " (Z): " + QString::number(m_conductors[0]->getStartCoords().z));
                ui->lineEdit_fourth_cond2->setText(tr("Conductor - (X): ") + QString::number(m_conductors[1]->getStartCoords().x) + " (Y): " + QString::number(m_conductors[1]->getStartCoords().y) + " (Z): " + QString::number(m_conductors[1]->getStartCoords().z));
                ui->lineEdit_fourth_cond3->setText(tr("Conductor - (X): ") + QString::number(m_conductors[2]->getStartCoords().x) + " (Y): " + QString::number(m_conductors[2]->getStartCoords().y) + " (Z): " + QString::number(m_conductors[2]->getStartCoords().z));
            }
            else if(m_conductors.size() == 4){
                ui->lineEdit_fourth_cond->setText(tr("Conductor - (X): ") + QString::number(m_conductors[0]->getStartCoords().x) + " (Y): " + QString::number(m_conductors[0]->getStartCoords().y) + " (Z): " + QString::number(m_conductors[0]->getStartCoords().z));
                ui->lineEdit_fourth_cond2->setText(tr("Conductor - (X): ") + QString::number(m_conductors[1]->getStartCoords().x) + " (Y): " + QString::number(m_conductors[1]->getStartCoords().y) + " (Z): " + QString::number(m_conductors[1]->getStartCoords().z));
                ui->lineEdit_fourth_cond3->setText(tr("Conductor - (X): ") + QString::number(m_conductors[2]->getStartCoords().x) + " (Y): " + QString::number(m_conductors[2]->getStartCoords().y) + " (Z): " + QString::number(m_conductors[2]->getStartCoords().z));
                ui->lineEdit_fourth_cond4->setText(tr("Conductor - (X): ") + QString::number(m_conductors[3]->getStartCoords().x) + " (Y): " + QString::number(m_conductors[3]->getStartCoords().y) + " (Z): " + QString::number(m_conductors[3]->getStartCoords().z));
            }
            break;
        case 3: //Review and finish
            close();
            complete = true;
            ui->stackedWidget->setCurrentIndex(0);
            ui->pushButton_next->setText(tr("Next"));
            ui->pushButton_previous->setEnabled(false);
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
            ui->stackedWidget->setCurrentIndex(1);
            break;
        case 3: //Review and finish
            ui->stackedWidget->setCurrentIndex(2);
            ui->pushButton_next->setText(tr("Next"));
            break;
        default:
            break;
    }
}

bool MultiConductorDialog::isComplete(){
    return complete;
}
