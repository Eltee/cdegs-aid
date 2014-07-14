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

#include "configuration_widget.h"
#include "ui_configuration_widget.h"

/*!
 \brief

 \fn configuration_widget::configuration_widget
 \param parent
 \param dp
 \param config
*/
configuration_widget::configuration_widget(QWidget *parent, project_tab_widget* dp, std::shared_ptr<Configuration> config, QString name) :
    QWidget(parent),
    ui(new Ui::configuration_widget)
{
    m_name = name;
    configuration.reset(new Configuration(config.get()));
    ui->setupUi(this);
    defParent = dp;
    initPlot();
    populateFields();
    ui->stackedWidget_config->setCurrentIndex(0);
    connectSlots();
}

void configuration_widget::initPlot(){
    ui->cond_plot->plotLayout()->insertRow(0);
    QCPPlotTitle* title = new QCPPlotTitle(ui->cond_plot, "Position of Conductors");
    title->setTextColor(Qt::white);
    title->setAntialiased(true);
    ui->cond_plot->plotLayout()->addElement(0, 0, title);
    ui->cond_plot->legend->setVisible(false);
    ui->cond_plot->legend->setAntialiased(true);

    ui->cond_plot->addGraph();
    ui->cond_plot->addGraph();

    ui->cond_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->cond_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QColor(0, 102, 255), 10));
    ui->cond_plot->graph(0)->setPen(QPen(QColor(120, 120, 120), 1));
    ui->cond_plot->graph(0)->setName("Conductors");
    ui->cond_plot->graph(0)->setAntialiased(true);

    ui->cond_plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->cond_plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QColor(220, 0, 0), 10));
    ui->cond_plot->graph(1)->setPen(QPen(QColor(120, 120, 120), 1));
    ui->cond_plot->graph(1)->setName("Conductors");
    ui->cond_plot->graph(1)->setAntialiased(true);

    ui->cond_plot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->cond_plot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->cond_plot->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->cond_plot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->cond_plot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->cond_plot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->cond_plot->xAxis->setTickLabelColor(Qt::white);
    ui->cond_plot->yAxis->setTickLabelColor(Qt::white);
    ui->cond_plot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::SolidLine));
    ui->cond_plot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::SolidLine));
    ui->cond_plot->xAxis->grid()->setSubGridVisible(false);
    ui->cond_plot->yAxis->grid()->setSubGridVisible(false);
    ui->cond_plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->cond_plot->xAxis->grid()->setAntialiased(true);
    ui->cond_plot->yAxis->grid()->setAntialiased(true);
    ui->cond_plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->cond_plot->xAxis->setUpperEnding(QCPLineEnding::esSkewedBar);
    ui->cond_plot->yAxis->setUpperEnding(QCPLineEnding::esSkewedBar);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->cond_plot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->cond_plot->axisRect()->setBackground(axisRectGradient);
    ui->cond_plot->axisRect()->setAntialiased(true);

    ui->cond_plot->xAxis->setLabel("Y - Distance from Line Center (m)");
    ui->cond_plot->xAxis->setLabelColor(Qt::white);
    ui->cond_plot->xAxis->setAntialiased(true);
    ui->cond_plot->xAxis->setTicks(true);
    ui->cond_plot->xAxis->setAutoTicks(true);
    ui->cond_plot->xAxis->setRange(-5, 5);
    ui->cond_plot->xAxis->setAutoTickStep(false);
    ui->cond_plot->xAxis->setTickStep(1);
    ui->cond_plot->xAxis->setTickLength(0, 2);
    ui->cond_plot->xAxis->setSubTickCount(1);
    ui->cond_plot->xAxis->setSubTickLength(0,1);

    ui->cond_plot->yAxis->setLabel("Z - Height (m)");
    ui->cond_plot->yAxis->setLabelColor(Qt::white);
    ui->cond_plot->yAxis->setAntialiased(true);
    ui->cond_plot->yAxis->setTicks(true);
    ui->cond_plot->yAxis->setAutoTicks(true);
    ui->cond_plot->yAxis->setRange(-10, 5);
    ui->cond_plot->yAxis->setRangeReversed(true);
    ui->cond_plot->yAxis->setAutoTickStep(false);
    ui->cond_plot->yAxis->setTickStep(1);
    ui->cond_plot->yAxis->setTickLength(0, 2);
    ui->cond_plot->yAxis->setSubTickCount(1);
    ui->cond_plot->yAxis->setSubTickLength(0,1);

    ui->cond_plot->rescaleAxes();
}

void configuration_widget::connectSlots(){
    QObject::connect(ui->comboBox_page, SIGNAL(currentIndexChanged(int)),
                     ui->stackedWidget_config, SLOT(setCurrentIndex(int)));


    //COMBOBOX CONNECTIONS
    QObject::connect(ui->comboBox_lTypes_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchLType(QString)));

    QObject::connect(ui->comboBox_coatings_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchCoating(QString)));

    QObject::connect(ui->comboBox_energizations_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchEnergization(QString)));

    QObject::connect(ui->comboBox_cTypes_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchCType(QString)));

    QObject::connect(ui->comboBox_cbTypes_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchCbType(QString)));

    QObject::connect(ui->comboBox_profiles_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchProfile(QString)));

    QObject::connect(ui->comboBox_conductors, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchConductor(QString)));

    QObject::connect(ui->comboBox_buildings, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchBuilding(QString)));

    //COND CONNECTIONS
    QObject::connect(ui->pushButton_cond_add, SIGNAL(clicked()),
                     this, SLOT(newCond()));

    QObject::connect(ui->pushButton_cond_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateCond()));

    QObject::connect(ui->pushButton_cond_remove, SIGNAL(clicked()),
                     this, SLOT(removeCond()));

    QObject::connect(ui->pushButton_cond_save, SIGNAL(clicked()),
                     this, SLOT(saveCond()));

    QObject::connect(ui->comboBox_cond_cbType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeCondCbType(int)));

    QObject::connect(ui->comboBox_cond_coating, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeCondCoat(int)));

    QObject::connect(ui->comboBox_cond_cType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeCondCType(int)));

    QObject::connect(ui->comboBox_cond_energization, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeCondEner(int)));

    QObject::connect(ui->comboBox_cond_lType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeCondLType(int)));

    QObject::connect(ui->doubleSpinBox_cond_endX, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondEndX(double)));

    QObject::connect(ui->doubleSpinBox_cond_endY, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondEndY(double)));

    QObject::connect(ui->doubleSpinBox_cond_endZ, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondEndZ(double)));

    QObject::connect(ui->doubleSpinBox_cond_startX, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondStartX(double)));

    QObject::connect(ui->doubleSpinBox_cond_startY, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondStartY(double)));

    QObject::connect(ui->doubleSpinBox_cond_startZ, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondStartZ(double)));

    QObject::connect(ui->doubleSpinBox_cond_radius, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondRadius(double)));

    QObject::connect(ui->checkBox_cond_advanced, SIGNAL(clicked()),
                     this, SLOT(refreshConductor()));


    //BUILD CONNECTIONS
    QObject::connect(ui->pushButton_add_building, SIGNAL(clicked()),
                     this, SLOT(newBuilding()));

    QObject::connect(ui->pushButton_build_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateBuilding()));

    QObject::connect(ui->pushButton_remove_building, SIGNAL(clicked()),
                     this, SLOT(removeBuilding()));

    QObject::connect(ui->pushButton_save_building, SIGNAL(clicked()),
                     this, SLOT(saveBuilding()));

    QObject::connect(ui->comboBox_building_sides, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeBuildFaces(QString)));

    QObject::connect(ui->spinBox_building_height, SIGNAL(valueChanged(int)),
                     this, SLOT(changeBuildHeight(int)));

    QObject::connect(ui->comboBox_building_step, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeBuildStep(QString)));

    QObject::connect(ui->spinBox_building_distance, SIGNAL(valueChanged(int)),
                     this, SLOT(changeBuildDistance(int)));

    QObject::connect(ui->spinBox_building_length, SIGNAL(valueChanged(int)),
                     this, SLOT(changeBuildLength(int)));

    QObject::connect(ui->spinBox_building_width, SIGNAL(valueChanged(int)),
                     this, SLOT(changeBuildWidth(int)));

    QObject::connect(ui->doubleSpinBox_building_radius, SIGNAL(valueChanged(double)),
                     this, SLOT(changeBuildRadius(double)));

    QObject::connect(ui->comboBox_building_cbType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeBuildCbType(int)));

    QObject::connect(ui->comboBox_building_coat, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeBuildCoat(int)));

    QObject::connect(ui->comboBox_building_cType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeBuildCType(int)));

    QObject::connect(ui->comboBox_building_ener, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeBuildEner(int)));

    QObject::connect(ui->comboBox_building_lType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeBuildLType(int)));

    QObject::connect(ui->pushButton_building_generate, SIGNAL(clicked()),
                     this, SLOT(generateBuildingConductors()));

    QObject::connect(ui->pushButton_building_clear, SIGNAL(clicked()),
                     this, SLOT(clearBuildingConductors()));

    //CONF CONNECTIONS

    QObject::connect(ui->lineEdit_settings_identifier, SIGNAL(textChanged(QString)),
                     this, SLOT(changeConfIdentifier(QString)));

    QObject::connect(ui->comboBox_settings_units, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeConfUnits(QString)));

    QObject::connect(ui->comboBox_settings_frequency, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeConfFrequency(QString)));

    QObject::connect(ui->pushButton_save_conf, SIGNAL(clicked()),
                     this, SLOT(saveConfig()));

    //LTYPE CONNECTIONS
    QObject::connect(ui->lineEdit_lType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeLTypeName(QString)));

    QObject::connect(ui->pushButton_new_lType, SIGNAL(clicked()),
                     this, SLOT(newLType()));

    QObject::connect(ui->pushButton_lType_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateLType()));

    QObject::connect(ui->pushButton_remove_lType, SIGNAL(clicked()),
                     this, SLOT(removeLType()));

    QObject::connect(ui->pushButton_save_lType, SIGNAL(clicked()),
                     this, SLOT(saveLType()));

    //COATING CONNECTIONS
    QObject::connect(ui->lineEdit_coating_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCoatName(QString)));

    QObject::connect(ui->pushButton_new_coating, SIGNAL(clicked()),
                     this, SLOT(newCoat()));

    QObject::connect(ui->pushButton_coat_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateCoat()));

    QObject::connect(ui->pushButton_remove_coating, SIGNAL(clicked()),
                     this, SLOT(removeCoat()));

    QObject::connect(ui->pushButton_save_coating, SIGNAL(clicked()),
                     this, SLOT(saveCoat()));

    //ENERG CONNECTIONS
    QObject::connect(ui->comboBox_energizations_frequency, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeEnerFreq(QString)));

    QObject::connect(ui->lineEdit_energization_identification, SIGNAL(textChanged(QString)),
                     this, SLOT(changeEnerIdent(QString)));

    QObject::connect(ui->lineEdit_energization_type, SIGNAL(textChanged(QString)),
                     this, SLOT(changeEnerType(QString)));

    QObject::connect(ui->spinBox_energization_magnitude, SIGNAL(valueChanged(int)),
                     this, SLOT(changeEnerMag(int)));

    QObject::connect(ui->doubleSpinBox_energization_angle, SIGNAL(valueChanged(double)),
                     this, SLOT(changeEnerAng(double)));

    QObject::connect(ui->pushButton_new_energization, SIGNAL(clicked()),
                     this, SLOT(newEner()));

    QObject::connect(ui->pushButton_ener_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateEner()));

    QObject::connect(ui->pushButton_remove_energization, SIGNAL(clicked()),
                     this, SLOT(removeEner()));

    QObject::connect(ui->pushButton_save_energization, SIGNAL(clicked()),
                     this, SLOT(saveEner()));

    //CTYPE CONNECTIONS
    QObject::connect(ui->lineEdit_cType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCTypeName(QString)));

    QObject::connect(ui->lineEdit_cType_type, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCTypeType(QString)));

    QObject::connect(ui->doubleSpinBox_cType_permeability, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCTypePerm(double)));

    QObject::connect(ui->doubleSpinBox_cType_resistivity, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCTypeRes(double)));

    QObject::connect(ui->pushButton_new_cType, SIGNAL(clicked()),
                     this, SLOT(newCType()));

    QObject::connect(ui->pushButton_cType_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateCType()));

    QObject::connect(ui->pushButton_remove_cType, SIGNAL(clicked()),
                     this, SLOT(removeCType()));

    QObject::connect(ui->pushButton_save_cType, SIGNAL(clicked()),
                     this, SLOT(saveCType()));

    //CBTYPE CONNECTIONS
    QObject::connect(ui->lineEdit_cbType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCbTypeName(QString)));

    QObject::connect(ui->pushButton_new_cbType, SIGNAL(clicked()),
                     this, SLOT(newCbType()));

    QObject::connect(ui->pushButton_cbType_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateCbType()));

    QObject::connect(ui->pushButton_remove_cbType, SIGNAL(clicked()),
                     this, SLOT(removeCbType()));

    QObject::connect(ui->pushButton_save_cbType, SIGNAL(clicked()),
                     this, SLOT(saveCbType()));

    //PROFILE CONNECTIONS
    QObject::connect(ui->spinBox_number_points, SIGNAL(valueChanged(int)),
                     this, SLOT(changeProNumPt(int)));

    QObject::connect(ui->spinBox_number_profiles, SIGNAL(valueChanged(int)),
                     this, SLOT(changeProNumPr(int)));

    QObject::connect(ui->doubleSpinBox_point_step_x, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPtStepX(double)));

    QObject::connect(ui->doubleSpinBox_point_step_y, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPtStepY(double)));

    QObject::connect(ui->doubleSpinBox_point_step_z, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPtStepZ(double)));

    QObject::connect(ui->doubleSpinBox_profile_start_x, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProStartX(double)));

    QObject::connect(ui->doubleSpinBox_profile_start_y, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProStartY(double)));

    QObject::connect(ui->doubleSpinBox_profile_start_z, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProStartZ(double)));

    QObject::connect(ui->doubleSpinBox_profile_step_x, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPrStepX(double)));

    QObject::connect(ui->doubleSpinBox_profile_step_y, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPrStepY(double)));

    QObject::connect(ui->doubleSpinBox_profile_step_z, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPrStepZ(double)));

    QObject::connect(ui->pushButton_new_profile, SIGNAL(clicked()),
                     this, SLOT(newPro()));

    QObject::connect(ui->pushButton_pro_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicatePro()));

    QObject::connect(ui->pushButton_remove_profile, SIGNAL(clicked()),
                     this, SLOT(removePro()));

    QObject::connect(ui->pushButton_save_profile, SIGNAL(clicked()),
                     this, SLOT(savePro()));

    QObject::connect(ui->radioButton_profile_endPts, SIGNAL(clicked()),
                     this, SLOT(refreshProfile()));

    QObject::connect(ui->radioButton_profile_steps, SIGNAL(clicked()),
                     this, SLOT(refreshProfile()));

    //COMPUTATION CONNECTIONS

    QObject::connect(ui->checkBox_comp_ELECTRIC, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));

    QObject::connect(ui->checkBox_comp_GPR, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));

    QObject::connect(ui->checkBox_comp_GRADIENT_SCALAR, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));

    QObject::connect(ui->checkBox_comp_MAGNETIC, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));

    QObject::connect(ui->checkBox_comp_POTENTIAL_SCALAR, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));

    QObject::connect(ui->checkBox_comp_VECTOR_POTENTIAL, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));
}

void configuration_widget::disconnectSlots(){
    QObject::disconnect(ui->comboBox_page, SIGNAL(currentIndexChanged(int)),
                     ui->stackedWidget_config, SLOT(setCurrentIndex(int)));


    //COMBOBOX CONNECTIONS
    QObject::disconnect(ui->comboBox_lTypes_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchLType(QString)));

    QObject::disconnect(ui->comboBox_coatings_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchCoating(QString)));

    QObject::disconnect(ui->comboBox_energizations_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchEnergization(QString)));

    QObject::disconnect(ui->comboBox_cTypes_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchCType(QString)));

    QObject::disconnect(ui->comboBox_cbTypes_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchCbType(QString)));

    QObject::disconnect(ui->comboBox_profiles_chooser, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchProfile(QString)));

    QObject::disconnect(ui->comboBox_conductors, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchConductor(QString)));

    QObject::disconnect(ui->comboBox_buildings, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(fetchBuilding(QString)));

    //COND CONNECTIONS
    QObject::disconnect(ui->pushButton_cond_add, SIGNAL(clicked()),
                     this, SLOT(newCond()));

    QObject::disconnect(ui->pushButton_cond_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateCond()));

    QObject::disconnect(ui->pushButton_cond_remove, SIGNAL(clicked()),
                     this, SLOT(removeCond()));

    QObject::disconnect(ui->pushButton_cond_save, SIGNAL(clicked()),
                     this, SLOT(saveCond()));

    QObject::disconnect(ui->comboBox_cond_cbType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeCondCbType(int)));

    QObject::disconnect(ui->comboBox_cond_coating, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeCondCoat(int)));

    QObject::disconnect(ui->comboBox_cond_cType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeCondCType(int)));

    QObject::disconnect(ui->comboBox_cond_energization, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeCondEner(int)));

    QObject::disconnect(ui->comboBox_cond_lType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeCondLType(int)));

    QObject::disconnect(ui->doubleSpinBox_cond_endX, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondEndX(double)));

    QObject::disconnect(ui->doubleSpinBox_cond_endY, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondEndY(double)));

    QObject::disconnect(ui->doubleSpinBox_cond_endZ, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondEndZ(double)));

    QObject::disconnect(ui->doubleSpinBox_cond_startX, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondStartX(double)));

    QObject::disconnect(ui->doubleSpinBox_cond_startY, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondStartY(double)));

    QObject::disconnect(ui->doubleSpinBox_cond_startZ, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondStartZ(double)));

    QObject::disconnect(ui->doubleSpinBox_cond_radius, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCondRadius(double)));

    QObject::disconnect(ui->checkBox_cond_advanced, SIGNAL(clicked()),
                     this, SLOT(refreshConductor()));

    //BUILD CONNECTIONS
    QObject::disconnect(ui->pushButton_add_building, SIGNAL(clicked()),
                     this, SLOT(newBuilding()));

    QObject::disconnect(ui->pushButton_build_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateBuilding()));

    QObject::disconnect(ui->pushButton_remove_building, SIGNAL(clicked()),
                     this, SLOT(removeBuilding()));

    QObject::disconnect(ui->pushButton_save_building, SIGNAL(clicked()),
                     this, SLOT(saveBuilding()));

    QObject::disconnect(ui->comboBox_building_sides, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeBuildFaces(QString)));

    QObject::disconnect(ui->spinBox_building_height, SIGNAL(valueChanged(int)),
                     this, SLOT(changeBuildHeight(int)));

    QObject::disconnect(ui->comboBox_building_step, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeBuildStep(QString)));

    QObject::disconnect(ui->spinBox_building_distance, SIGNAL(valueChanged(int)),
                     this, SLOT(changeBuildDistance(int)));

    QObject::disconnect(ui->spinBox_building_length, SIGNAL(valueChanged(int)),
                     this, SLOT(changeBuildLength(int)));

    QObject::disconnect(ui->spinBox_building_width, SIGNAL(valueChanged(int)),
                     this, SLOT(changeBuildWidth(int)));

    QObject::disconnect(ui->doubleSpinBox_building_radius, SIGNAL(valueChanged(double)),
                     this, SLOT(changeBuildRadius(double)));

    QObject::disconnect(ui->comboBox_building_cbType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeBuildCbType(int)));

    QObject::disconnect(ui->comboBox_building_coat, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeBuildCoat(int)));

    QObject::disconnect(ui->comboBox_building_cType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeBuildCType(int)));

    QObject::disconnect(ui->comboBox_building_ener, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeBuildEner(int)));

    QObject::disconnect(ui->comboBox_building_lType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeBuildLType(int)));

    QObject::disconnect(ui->pushButton_building_generate, SIGNAL(clicked()),
                     this, SLOT(generateBuildingConductors()));

    QObject::disconnect(ui->pushButton_building_clear, SIGNAL(clicked()),
                     this, SLOT(clearBuildingConductors()));

    //CONF CONNECTIONS

    QObject::disconnect(ui->lineEdit_settings_identifier, SIGNAL(textChanged(QString)),
                     this, SLOT(changeConfIdentifier(QString)));

    QObject::disconnect(ui->comboBox_settings_units, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeConfUnits(QString)));

    QObject::disconnect(ui->comboBox_settings_frequency, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeConfFrequency(QString)));

    QObject::disconnect(ui->pushButton_save_conf, SIGNAL(clicked()),
                     this, SLOT(saveConfig()));

    //LTYPE CONNECTIONS
    QObject::disconnect(ui->lineEdit_lType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeLTypeName(QString)));

    QObject::disconnect(ui->pushButton_new_lType, SIGNAL(clicked()),
                     this, SLOT(newLType()));

    QObject::disconnect(ui->pushButton_lType_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateLType()));

    QObject::disconnect(ui->pushButton_remove_lType, SIGNAL(clicked()),
                     this, SLOT(removeLType()));

    QObject::disconnect(ui->pushButton_save_lType, SIGNAL(clicked()),
                     this, SLOT(saveLType()));

    //COATING CONNECTIONS
    QObject::disconnect(ui->lineEdit_coating_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCoatName(QString)));

    QObject::disconnect(ui->pushButton_new_coating, SIGNAL(clicked()),
                     this, SLOT(newCoat()));

    QObject::disconnect(ui->pushButton_coat_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateCoat()));

    QObject::disconnect(ui->pushButton_remove_coating, SIGNAL(clicked()),
                     this, SLOT(removeCoat()));

    QObject::disconnect(ui->pushButton_save_coating, SIGNAL(clicked()),
                     this, SLOT(saveCoat()));

    //ENERG CONNECTIONS
    QObject::disconnect(ui->comboBox_energizations_frequency, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeEnerFreq(QString)));

    QObject::disconnect(ui->lineEdit_energization_identification, SIGNAL(textChanged(QString)),
                     this, SLOT(changeEnerIdent(QString)));

    QObject::disconnect(ui->lineEdit_energization_type, SIGNAL(textChanged(QString)),
                     this, SLOT(changeEnerType(QString)));

    QObject::disconnect(ui->spinBox_energization_magnitude, SIGNAL(valueChanged(int)),
                     this, SLOT(changeEnerMag(int)));

    QObject::disconnect(ui->doubleSpinBox_energization_angle, SIGNAL(valueChanged(double)),
                     this, SLOT(changeEnerAng(double)));

    QObject::disconnect(ui->pushButton_new_energization, SIGNAL(clicked()),
                     this, SLOT(newEner()));

    QObject::disconnect(ui->pushButton_ener_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateEner()));

    QObject::disconnect(ui->pushButton_remove_energization, SIGNAL(clicked()),
                     this, SLOT(removeEner()));

    QObject::disconnect(ui->pushButton_save_energization, SIGNAL(clicked()),
                     this, SLOT(saveEner()));

    //CTYPE CONNECTIONS
    QObject::disconnect(ui->lineEdit_cType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCTypeName(QString)));

    QObject::disconnect(ui->lineEdit_cType_type, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCTypeType(QString)));

    QObject::disconnect(ui->doubleSpinBox_cType_permeability, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCTypePerm(double)));

    QObject::disconnect(ui->doubleSpinBox_cType_resistivity, SIGNAL(valueChanged(double)),
                     this, SLOT(changeCTypeRes(double)));

    QObject::disconnect(ui->pushButton_new_cType, SIGNAL(clicked()),
                     this, SLOT(newCType()));

    QObject::disconnect(ui->pushButton_cType_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateCType()));

    QObject::disconnect(ui->pushButton_remove_cType, SIGNAL(clicked()),
                     this, SLOT(removeCType()));

    QObject::disconnect(ui->pushButton_save_cType, SIGNAL(clicked()),
                     this, SLOT(saveCType()));

    //CBTYPE CONNECTIONS
    QObject::disconnect(ui->lineEdit_cbType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCbTypeName(QString)));

    QObject::disconnect(ui->pushButton_new_cbType, SIGNAL(clicked()),
                     this, SLOT(newCbType()));

    QObject::disconnect(ui->pushButton_cbType_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicateCbType()));

    QObject::disconnect(ui->pushButton_remove_cbType, SIGNAL(clicked()),
                     this, SLOT(removeCbType()));

    QObject::disconnect(ui->pushButton_save_cbType, SIGNAL(clicked()),
                     this, SLOT(saveCbType()));

    //PROFILE CONNECTIONS
    QObject::disconnect(ui->spinBox_number_points, SIGNAL(valueChanged(int)),
                     this, SLOT(changeProNumPt(int)));

    QObject::disconnect(ui->spinBox_number_profiles, SIGNAL(valueChanged(int)),
                     this, SLOT(changeProNumPr(int)));

    QObject::disconnect(ui->doubleSpinBox_point_step_x, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPtStepX(double)));

    QObject::disconnect(ui->doubleSpinBox_point_step_y, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPtStepY(double)));

    QObject::disconnect(ui->doubleSpinBox_point_step_z, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPtStepZ(double)));

    QObject::disconnect(ui->doubleSpinBox_profile_start_x, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProStartX(double)));

    QObject::disconnect(ui->doubleSpinBox_profile_start_y, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProStartY(double)));

    QObject::disconnect(ui->doubleSpinBox_profile_start_z, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProStartZ(double)));

    QObject::disconnect(ui->doubleSpinBox_profile_step_x, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPrStepX(double)));

    QObject::disconnect(ui->doubleSpinBox_profile_step_y, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPrStepY(double)));

    QObject::disconnect(ui->doubleSpinBox_profile_step_z, SIGNAL(valueChanged(double)),
                     this, SLOT(changeProPrStepZ(double)));

    QObject::disconnect(ui->pushButton_new_profile, SIGNAL(clicked()),
                     this, SLOT(newPro()));

    QObject::disconnect(ui->pushButton_pro_duplicate, SIGNAL(clicked()),
                     this, SLOT(duplicatePro()));

    QObject::disconnect(ui->pushButton_remove_profile, SIGNAL(clicked()),
                     this, SLOT(removePro()));

    QObject::disconnect(ui->pushButton_save_profile, SIGNAL(clicked()),
                     this, SLOT(savePro()));

    QObject::disconnect(ui->radioButton_profile_endPts, SIGNAL(clicked()),
                     this, SLOT(refreshProfile()));

    QObject::disconnect(ui->radioButton_profile_steps, SIGNAL(clicked()),
                     this, SLOT(refreshProfile()));

    //COMPUTATION CONNECTIONS

    QObject::connect(ui->checkBox_comp_ELECTRIC, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));

    QObject::connect(ui->checkBox_comp_GPR, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));

    QObject::connect(ui->checkBox_comp_GRADIENT_SCALAR, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));

    QObject::connect(ui->checkBox_comp_MAGNETIC, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));

    QObject::connect(ui->checkBox_comp_POTENTIAL_SCALAR, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));

    QObject::connect(ui->checkBox_comp_VECTOR_POTENTIAL, SIGNAL(stateChanged(int)),
                     this, SLOT(changeComputations(int)));
}

/*!
 \brief

 \fn configuration_widget::getConfig
 \return Configuration
*/
std::shared_ptr<Configuration> configuration_widget::getConfig(){
    return configuration;
}

QString const& configuration_widget::getName() const{
    return m_name;
}

/*!
 \brief

 \fn configuration_widget::~configuration_widget
*/
configuration_widget::~configuration_widget()
{
    delete ui;
    configuration.reset();
    lType.reset();
    coat.reset();
    ener.reset();
    cType.reset();
    cbType.reset();
    pro.reset();
}

/*!
 \brief

 \fn configuration_widget::refresh
*/
void configuration_widget::refresh(){
    disconnectSlots();
    refreshConfSettings();
    refreshLType();
    refreshCoating();
    refreshEnergization();
    refreshCType();
    refreshCbType();
    refreshProfile();
    refreshConductor();
    refreshBuilding();
    refreshPlot();
    m_name = QString::fromStdString(configuration->getIdentifier());
    connectSlots();
    if(configuration->isModified()){
        QString newName = m_name;
        newName.append("*");
        defParent->modifyProject();
        defParent->changeTabName(this, newName);
    }
    else{
        defParent->changeTabName(this, m_name);
    }
    defParent->refresh();
}

//COMBOBOX CONNECTIONS

void configuration_widget::populateFields(){
    populateLTypes();
    populateCoatings();
    populateEnergizations();
    populateCTypes();
    populateCbTypes();
    populateComputations();
    populateProfiles();
    populateConductors();
    populateBuildings();
}

void configuration_widget::populateLTypes(){
    ui->comboBox_lTypes_chooser->clear();
    for(unsigned int i = 0; i < configuration->getLeadTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getLeadTypes().at(i)->getName());
        ui->comboBox_lTypes_chooser->addItem(text);
    }
    fetchLType(ui->comboBox_lTypes_chooser->currentText());
}

void configuration_widget::fetchLType(QString id){
    if(!id.isEmpty()){
        id.truncate(id.indexOf(" "));
        int index = id.toInt();
        lType.reset(new LeadType(configuration->getLeadTypes().at(index).get()));
        refresh();
    }
    else{
        lType.reset();
        refresh();
    }
}

void configuration_widget::populateCoatings(){
    ui->comboBox_coatings_chooser->clear();
    for(unsigned int i = 0; i < configuration->getCoatings().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getCoatings().at(i)->getName());
        ui->comboBox_coatings_chooser->addItem(text);
    }
    fetchCoating(ui->comboBox_coatings_chooser->currentText());
}

void configuration_widget::fetchCoating(QString id){
    if(!id.isEmpty()){
        id.truncate(id.indexOf(" "));
        int index = id.toInt();
        coat.reset(new Coating(configuration->getCoatings().at(index).get()));
        refresh();
    }
    else{
        coat.reset();
        refresh();
    }
}

void configuration_widget::populateEnergizations(){
    ui->comboBox_energizations_chooser->clear();
    for(unsigned int i = 0; i < configuration->getEnergizations().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getEnergizations().at(i)->getIdentification());
        ui->comboBox_energizations_chooser->addItem(text);
    }
    fetchEnergization(ui->comboBox_energizations_chooser->currentText());
}

void configuration_widget::fetchEnergization(QString id){
    if(!id.isEmpty()){
        id.truncate(id.indexOf(" "));
        int index = id.toInt();
        ener.reset(new Energization(configuration->getEnergizations().at(index).get()));
        refresh();
    }
    else{
        ener.reset();
        refresh();
    }
}

void configuration_widget::populateCTypes(){
    ui->comboBox_cTypes_chooser->clear();
    for(unsigned int i = 0; i < configuration->getConductorTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getConductorTypes().at(i)->getName());
        ui->comboBox_cTypes_chooser->addItem(text);
    }
    fetchCType(ui->comboBox_cTypes_chooser->currentText());
}

void configuration_widget::fetchCType(QString id){
    if(!id.isEmpty()){
        id.truncate(id.indexOf(" "));
        int index = id.toInt();
        cType.reset(new ConductorType(configuration->getConductorTypes().at(index).get()));
        refresh();
    }
    else{
        cType.reset();
        refresh();
    }
}

void configuration_widget::populateCbTypes(){
    ui->comboBox_cbTypes_chooser->clear();
    for(unsigned int i = 0; i < configuration->getCableTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getCableTypes().at(i)->getName());
        ui->comboBox_cbTypes_chooser->addItem(text);
    }
    fetchCbType(ui->comboBox_cbTypes_chooser->currentText());
}

void configuration_widget::fetchCbType(QString id){
    if(!id.isEmpty()){
        id.truncate(id.indexOf(" "));
        int index = id.toInt();
        cbType.reset(new CableType(configuration->getCableTypes().at(index).get()));
        refresh();
    }
    else{
        cbType.reset();
        refresh();
    }
}

void configuration_widget::populateComputations(){
    ui->checkBox_comp_GPR->setChecked(configuration->getComputations().GPR);
    ui->checkBox_comp_POTENTIAL_SCALAR->setChecked(configuration->getComputations().POTENTIAL_SCALAR);
    ui->checkBox_comp_ELECTRIC->setChecked(configuration->getComputations().ELECTRIC);
    ui->checkBox_comp_GRADIENT_SCALAR->setChecked(configuration->getComputations().GRADIENT_SCALAR);
    ui->checkBox_comp_MAGNETIC->setChecked(configuration->getComputations().MAGNETIC);
    ui->checkBox_comp_VECTOR_POTENTIAL->setChecked(configuration->getComputations().VECTOR_POTENTIAL);
}

void configuration_widget::populateProfiles(){
    ui->comboBox_profiles_chooser->clear();
    for(unsigned int i = 0; i < configuration->getProfiles().size(); i++){
        profile* p = configuration->getProfiles().at(i).get();
        QString text = QString::number(i) + " - Profile(X:" + QString::number(p->start.x) + ", Y:" + QString::number(p->start.y) + ", Z:" + QString::number(p->start.z) + ")";
        ui->comboBox_profiles_chooser->addItem(text);
    }
    fetchProfile(ui->comboBox_profiles_chooser->currentText());
}

void configuration_widget::fetchProfile(QString id){
    if(!id.isEmpty()){
        id.truncate(id.indexOf(" "));
        int index = id.toInt();
        pro.reset(new profile(configuration->getProfiles().at(index).get()));
        refresh();
    }
    else{
        pro.reset();
        refresh();
    }
}

void configuration_widget::refreshLType(){
    if(lType){
        ui->lineEdit_lType_name->setText(QString::fromStdString(lType->getName()));
        if(lType->isLocked()){
            ui->pushButton_remove_lType->setDisabled(true);
            ui->pushButton_lType_duplicate->setEnabled(false);
            ui->lineEdit_lType_name->setDisabled(true);
        }
        else{
            ui->pushButton_remove_lType->setEnabled(true);
            ui->pushButton_lType_duplicate->setEnabled(true);
            ui->lineEdit_lType_name->setEnabled(true);
        }
    }
    else{
        ui->pushButton_remove_lType->setDisabled(true);
        ui->pushButton_lType_duplicate->setEnabled(false);
        ui->lineEdit_lType_name->setDisabled(true);
    }
}

void configuration_widget::refreshCoating(){
    if(coat){
        ui->lineEdit_coating_name->setText(QString::fromStdString(coat->getName()));
        if(!coat->isLocked()){
            ui->pushButton_remove_coating->setEnabled(true);
            ui->pushButton_coat_duplicate->setEnabled(true);
            ui->lineEdit_coating_name->setEnabled(true);
        }
        else{
            ui->pushButton_remove_coating->setDisabled(true);
            ui->pushButton_coat_duplicate->setEnabled(false);
            ui->lineEdit_coating_name->setDisabled(true);
        }
    }
    else{
        ui->pushButton_remove_coating->setDisabled(true);
        ui->pushButton_coat_duplicate->setEnabled(false);
        ui->lineEdit_coating_name->setDisabled(true);
    }
}

void configuration_widget::refreshEnergization(){
    if(ener){
        ui->comboBox_energizations_frequency->setCurrentText(QString::fromStdString(ener->getFrequency()));
        ui->lineEdit_energization_identification->setText(QString::fromStdString(ener->getIdentification()));
        ui->lineEdit_energization_type->setText(QString::fromStdString(ener->getType()));
        ui->spinBox_energization_magnitude->setValue(ener->getMagnitude());
        ui->doubleSpinBox_energization_angle->setValue(ener->getAngle());
        if(!ener->isLocked()){
            ui->pushButton_remove_energization->setEnabled(true);
            ui->pushButton_ener_duplicate->setEnabled(true);
            ui->comboBox_energizations_frequency->setEnabled(true);
            ui->lineEdit_energization_identification->setEnabled(true);
            ui->lineEdit_energization_type->setEnabled(true);
            ui->spinBox_energization_magnitude->setEnabled(true);
            ui->doubleSpinBox_energization_angle->setEnabled(true);
        }
        else{
            ui->pushButton_remove_energization->setDisabled(true);
            ui->pushButton_ener_duplicate->setEnabled(false);
            ui->comboBox_energizations_frequency->setDisabled(true);
            ui->lineEdit_energization_identification->setDisabled(true);
            ui->lineEdit_energization_type->setDisabled(true);
            ui->spinBox_energization_magnitude->setDisabled(true);
            ui->doubleSpinBox_energization_angle->setDisabled(true);
        }
    }
    else{
        ui->pushButton_remove_energization->setDisabled(true);
        ui->pushButton_ener_duplicate->setEnabled(false);
        ui->comboBox_energizations_frequency->setDisabled(true);
        ui->lineEdit_energization_identification->setDisabled(true);
        ui->lineEdit_energization_type->setDisabled(true);
        ui->spinBox_energization_magnitude->setDisabled(true);
        ui->doubleSpinBox_energization_angle->setDisabled(true);
    }
}

void configuration_widget::refreshCType(){
    if(cType){
        ui->lineEdit_cType_name->setText(QString::fromStdString(cType->getName()));
        ui->lineEdit_cType_type->setText(QString::fromStdString(cType->getType()));
        ui->doubleSpinBox_cType_permeability->setValue(cType->getPermeability());
        ui->doubleSpinBox_cType_resistivity->setValue(cType->getResistivity());
        if(!cType->isLocked()){
            ui->pushButton_remove_cType->setEnabled(true);
            ui->pushButton_cType_duplicate->setEnabled(true);
            ui->lineEdit_cType_name->setEnabled(true);
            ui->lineEdit_cType_type->setEnabled(true);
            ui->doubleSpinBox_cType_permeability->setEnabled(true);
            ui->doubleSpinBox_cType_resistivity->setEnabled(true);
        }
        else{
            ui->pushButton_remove_cType->setDisabled(true);
            ui->pushButton_cType_duplicate->setEnabled(false);
            ui->lineEdit_cType_name->setDisabled(true);
            ui->lineEdit_cType_type->setDisabled(true);
            ui->doubleSpinBox_cType_permeability->setDisabled(true);
            ui->doubleSpinBox_cType_resistivity->setDisabled(true);
        }
    }
    else{
        ui->pushButton_cType_duplicate->setEnabled(false);
        ui->pushButton_remove_cType->setDisabled(true);
        ui->lineEdit_cType_name->setDisabled(true);
        ui->lineEdit_cType_type->setDisabled(true);
        ui->doubleSpinBox_cType_permeability->setDisabled(true);
        ui->doubleSpinBox_cType_resistivity->setDisabled(true);
    }
}

void configuration_widget::refreshCbType(){
    if(cbType){
        ui->lineEdit_cbType_name->setText(QString::fromStdString(cbType->getName()));
        if(!cbType->isLocked()){
            ui->pushButton_remove_cbType->setEnabled(true);
            ui->pushButton_cbType_duplicate->setEnabled(true);
            ui->lineEdit_cbType_name->setEnabled(true);
        }
        else{
            ui->pushButton_remove_cbType->setDisabled(true);
            ui->pushButton_cbType_duplicate->setEnabled(false);
            ui->lineEdit_cbType_name->setDisabled(true);
        }
    }
    else{
        ui->pushButton_remove_cbType->setDisabled(true);
        ui->pushButton_cbType_duplicate->setEnabled(false);
        ui->lineEdit_cbType_name->setDisabled(true);
    }
}

void configuration_widget::refreshProfile(){
    if(pro){
        ui->pushButton_new_profile->setEnabled(false);
        ui->pushButton_remove_profile->setEnabled(true);
        ui->pushButton_pro_duplicate->setEnabled(false);
        if(ui->radioButton_profile_endPts->isChecked()){
            ui->doubleSpinBox_profile_dist_pros->setEnabled(true);
            ui->doubleSpinBox_profile_dist_pts->setEnabled(true);
            ui->groupBox_profile_ptA->setEnabled(true);
            ui->groupBox_profile_ptB->setEnabled(true);
            ui->groupBox_profile_ptC->setEnabled(true);

            ui->spinBox_number_points->setEnabled(false);
            ui->spinBox_number_profiles->setEnabled(false);
            ui->groupBox_profile_prStart->setEnabled(false);
            ui->groupBox_profile_prStep->setEnabled(false);
            ui->groupBox_profile_ptStep->setEnabled(false);
        }
        else if(ui->radioButton_profile_steps->isChecked()){
            ui->spinBox_number_points->setEnabled(true);
            ui->spinBox_number_profiles->setEnabled(true);
            ui->groupBox_profile_prStart->setEnabled(true);
            ui->groupBox_profile_prStep->setEnabled(true);
            ui->groupBox_profile_ptStep->setEnabled(true);

            ui->doubleSpinBox_profile_dist_pros->setEnabled(false);
            ui->doubleSpinBox_profile_dist_pts->setEnabled(false);
            ui->groupBox_profile_ptA->setEnabled(false);
            ui->groupBox_profile_ptB->setEnabled(false);
            ui->groupBox_profile_ptC->setEnabled(false);
        }
        std::vector<coords> prPts;

        prPts = pro->toCoords();

        ui->doubleSpinBox_profile_ptA_x->setValue(prPts[0].x);
        ui->doubleSpinBox_profile_ptA_y->setValue(prPts[0].y);
        ui->doubleSpinBox_profile_ptA_z->setValue(prPts[0].z);
        ui->doubleSpinBox_profile_ptB_x->setValue(prPts[1].x);
        ui->doubleSpinBox_profile_ptB_y->setValue(prPts[1].y);
        ui->doubleSpinBox_profile_ptB_z->setValue(prPts[1].z);
        ui->doubleSpinBox_profile_ptC_x->setValue(prPts[2].x);
        ui->doubleSpinBox_profile_ptC_y->setValue(prPts[2].y);
        ui->doubleSpinBox_profile_ptC_z->setValue(prPts[2].z);

        ui->spinBox_number_points->setValue(pro->ptNum);
        ui->spinBox_number_profiles->setValue(pro->prNum);
        ui->doubleSpinBox_point_step_x->setValue(pro->ptStep.x);
        ui->doubleSpinBox_point_step_y->setValue(pro->ptStep.y);
        ui->doubleSpinBox_point_step_z->setValue(pro->ptStep.z);
        ui->doubleSpinBox_profile_start_x->setValue(pro->start.x);
        ui->doubleSpinBox_profile_start_y->setValue(pro->start.y);
        ui->doubleSpinBox_profile_start_z->setValue(pro->start.z);
        ui->doubleSpinBox_profile_step_x->setValue(pro->prStep.x);
        ui->doubleSpinBox_profile_step_y->setValue(pro->prStep.y);
        ui->doubleSpinBox_profile_step_z->setValue(pro->prStep.z);
    }
    else{
        ui->pushButton_new_profile->setEnabled(true);
        ui->pushButton_remove_profile->setDisabled(true);
        ui->pushButton_pro_duplicate->setEnabled(false);

        ui->spinBox_number_points->setEnabled(false);
        ui->spinBox_number_profiles->setEnabled(false);
        ui->groupBox_profile_prStart->setEnabled(false);
        ui->groupBox_profile_prStep->setEnabled(false);
        ui->groupBox_profile_ptStep->setEnabled(false);

        ui->doubleSpinBox_profile_dist_pros->setEnabled(false);
        ui->doubleSpinBox_profile_dist_pts->setEnabled(false);
        ui->groupBox_profile_ptA->setEnabled(false);
        ui->groupBox_profile_ptB->setEnabled(false);
        ui->groupBox_profile_ptC->setEnabled(false);
    }
}

void configuration_widget::populateConductors(){
    ui->comboBox_conductors->clear();
    for(unsigned int i = 0; i <configuration->getConductors().size(); i++){
        QString text = QString::number(i) + " - Conductor(X:" + QString::number(configuration->getConductors().at(i)->getStartCoords().x) + ", Y:" + QString::number(configuration->getConductors().at(i)->getStartCoords().y) + ", Z:" + QString::number(configuration->getConductors().at(i)->getStartCoords().z) + ")";
        ui->comboBox_conductors->addItem(text);
    }

    ui->comboBox_cond_lType->clear();
    ui->comboBox_cond_lType->addItem("None");
    for(unsigned int i = 0; i < configuration->getLeadTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getLeadTypes().at(i)->getName());
        ui->comboBox_cond_lType->addItem(text);
    }

    ui->comboBox_cond_coating->clear();
    ui->comboBox_cond_coating->addItem("None");
    for(unsigned int i = 0; i < configuration->getCoatings().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getCoatings().at(i)->getName());
        ui->comboBox_cond_coating->addItem(text);
    }

    ui->comboBox_cond_energization->clear();
    ui->comboBox_cond_energization->addItem("None");
    for(unsigned int i = 0; i < configuration->getEnergizations().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getEnergizations().at(i)->getIdentification());
        ui->comboBox_cond_energization->addItem(text);
    }

    ui->comboBox_cond_cType->clear();
    ui->comboBox_cond_cType->addItem("None");
    for(unsigned int i = 0; i < configuration->getConductorTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getConductorTypes().at(i)->getName());
        ui->comboBox_cond_cType->addItem(text);
    }

    ui->comboBox_cond_cbType->clear();
    ui->comboBox_cond_cbType->addItem("None");
    for(unsigned int i = 0; i < configuration->getCableTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getCableTypes().at(i)->getName());
        ui->comboBox_cond_cbType->addItem(text);
    }

    fetchConductor(ui->comboBox_conductors->currentText());
}

void configuration_widget::fetchConductor(QString id){
    if(!id.isEmpty()){
        id.truncate(id.indexOf(" "));
        int index = id.toInt();
        conductor.reset(new Conductor(configuration->getConductors().at(index).get()));
        refresh();
    }
    else{
        conductor.reset();
        refresh();
    }
}

void configuration_widget::refreshConductor(){
    if(conductor){
        ui->pushButton_cond_remove->setEnabled(true);
        ui->pushButton_cond_save->setEnabled(true);
        ui->pushButton_cond_duplicate->setEnabled(true);
        ui->comboBox_cond_cbType->setEnabled(true);
        ui->comboBox_cond_coating->setEnabled(true);
        ui->comboBox_cond_cType->setEnabled(true);
        ui->comboBox_cond_energization->setEnabled(true);
        ui->comboBox_cond_lType->setEnabled(true);
        ui->doubleSpinBox_cond_radius->setEnabled(true);
        ui->doubleSpinBox_cond_startX->setEnabled(true);
        ui->doubleSpinBox_cond_startY->setEnabled(true);
        ui->doubleSpinBox_cond_startZ->setEnabled(true);

        if(ui->checkBox_cond_advanced->isChecked()){
            ui->doubleSpinBox_cond_endX->setEnabled(true);
            ui->doubleSpinBox_cond_endY->setEnabled(true);
            ui->doubleSpinBox_cond_endZ->setEnabled(true);
        }
        else{
            ui->doubleSpinBox_cond_endX->setEnabled(false);
            ui->doubleSpinBox_cond_endY->setEnabled(false);
            ui->doubleSpinBox_cond_endZ->setEnabled(false);
        }

        ui->doubleSpinBox_cond_endX->setValue(conductor->getEndCoords().x);
        ui->doubleSpinBox_cond_endY->setValue(conductor->getEndCoords().y);
        ui->doubleSpinBox_cond_endZ->setValue(conductor->getEndCoords().z);
        ui->doubleSpinBox_cond_startX->setValue(conductor->getStartCoords().x);
        ui->doubleSpinBox_cond_startY->setValue(conductor->getStartCoords().y);
        ui->doubleSpinBox_cond_startZ->setValue(conductor->getStartCoords().z);
        ui->doubleSpinBox_cond_radius->setValue(conductor->getRadius());
        ui->cond_plot->setEnabled(true);

        if(conductor->getLeadType()){
            ui->comboBox_cond_lType->setCurrentIndex(ui->comboBox_cond_lType->findText(QString::fromStdString(conductor->getLeadType()->getName()), Qt::MatchEndsWith));
        }
        else{
            ui->comboBox_cond_lType->setCurrentIndex(0);
        }

        if(conductor->getCoating()){
            ui->comboBox_cond_coating->setCurrentIndex(ui->comboBox_cond_coating->findText(QString::fromStdString(conductor->getCoating()->getName()), Qt::MatchEndsWith));
        }
        else{
            ui->comboBox_cond_coating->setCurrentIndex(0);
        }

        if(conductor->getEnergization()){
            ui->comboBox_cond_energization->setCurrentIndex(ui->comboBox_cond_energization->findText(QString::fromStdString(conductor->getEnergization()->getIdentification()), Qt::MatchEndsWith));
        }
        else{
            ui->comboBox_cond_energization->setCurrentIndex(0);
        }

        if(conductor->getConductorType()){
            ui->comboBox_cond_cType->setCurrentIndex(ui->comboBox_cond_cType->findText(QString::fromStdString(conductor->getConductorType()->getName()), Qt::MatchEndsWith));
        }
        else{
            ui->comboBox_cond_cType->setCurrentIndex(0);
        }

        if(conductor->getCableType()){
            ui->comboBox_cond_cbType->setCurrentIndex(ui->comboBox_cond_cbType->findText(QString::fromStdString(conductor->getCableType()->getName()), Qt::MatchEndsWith));
        }
        else{
            ui->comboBox_cond_cbType->setCurrentIndex(0);
        }
    }
    else{
        ui->pushButton_cond_remove->setEnabled(false);
        ui->pushButton_cond_save->setEnabled(false);
        ui->pushButton_cond_duplicate->setEnabled(false);
        ui->comboBox_cond_cbType->setEnabled(false);
        ui->comboBox_cond_coating->setEnabled(false);
        ui->comboBox_cond_cType->setEnabled(false);
        ui->comboBox_cond_energization->setEnabled(false);
        ui->comboBox_cond_lType->setEnabled(false);
        ui->doubleSpinBox_cond_endX->setEnabled(false);
        ui->doubleSpinBox_cond_endY->setEnabled(false);
        ui->doubleSpinBox_cond_endZ->setEnabled(false);
        ui->doubleSpinBox_cond_radius->setEnabled(false);
        ui->doubleSpinBox_cond_startX->setEnabled(false);
        ui->doubleSpinBox_cond_startY->setEnabled(false);
        ui->doubleSpinBox_cond_startZ->setEnabled(false);
        ui->cond_plot->setEnabled(false);
        ui->comboBox_cond_lType->setCurrentIndex(0);
        ui->comboBox_cond_coating->setCurrentIndex(0);
        ui->comboBox_cond_energization->setCurrentIndex(0);
        ui->comboBox_cond_cType->setCurrentIndex(0);
        ui->comboBox_cond_cbType->setCurrentIndex(0);
        ui->doubleSpinBox_cond_endX->setValue(0);
        ui->doubleSpinBox_cond_endY->setValue(0);
        ui->doubleSpinBox_cond_endZ->setValue(0);
        ui->doubleSpinBox_cond_startX->setValue(0);
        ui->doubleSpinBox_cond_startY->setValue(0);
        ui->doubleSpinBox_cond_startZ->setValue(0);
        ui->doubleSpinBox_cond_radius->setValue(0);
    }
}

void configuration_widget::populateBuildings(){
    ui->comboBox_buildings->clear();

    for(unsigned int i = 0; i < configuration->getBuildings().size(); i++){
        QString text = QString::number(i) + " - Building( HB: " + QString::number(configuration->getBuildings().at(i)->getHeight()) + " DB: " + QString::number(configuration->getBuildings().at(i)->getDistance()) + " )";
        ui->comboBox_buildings->addItem(text);
    }

    ui->comboBox_building_lType->clear();
    for(unsigned int i = 0; i < configuration->getLeadTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getLeadTypes().at(i)->getName());
        ui->comboBox_building_lType->addItem(text);
    }

    ui->comboBox_building_coat->clear();
    for(unsigned int i = 0; i < configuration->getCoatings().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getCoatings().at(i)->getName());
        ui->comboBox_building_coat->addItem(text);
    }

    ui->comboBox_building_ener->clear();
    for(unsigned int i = 0; i < configuration->getEnergizations().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getEnergizations().at(i)->getIdentification());
        ui->comboBox_building_ener->addItem(text);
    }

    ui->comboBox_building_cType->clear();
    for(unsigned int i = 0; i < configuration->getConductorTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getConductorTypes().at(i)->getName());
        ui->comboBox_building_cType->addItem(text);
    }

    ui->comboBox_building_cbType->clear();
    for(unsigned int i = 0; i < configuration->getCableTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getCableTypes().at(i)->getName());
        ui->comboBox_building_cbType->addItem(text);
    }

    fetchBuilding(ui->comboBox_buildings->currentText());
}

void configuration_widget::fetchBuilding(QString id){
    if(!id.isEmpty()){
        id.truncate(id.indexOf(" "));
        int index = id.toInt();
        building.reset(new Building(configuration->getBuildings().at(index).get()));
        refresh();
    }
    else{
        building.reset();
        refresh();
    }
}

void configuration_widget::refreshBuilding(){
    if(building){
        ui->comboBox_building_cbType->setEnabled(false);
        ui->comboBox_building_coat->setEnabled(false);
        ui->comboBox_building_cType->setEnabled(true);
        ui->comboBox_building_ener->setEnabled(false);
        ui->comboBox_building_lType->setEnabled(false);
        ui->comboBox_building_sides->setEnabled(true);
        ui->spinBox_building_height->setEnabled(true);
        ui->doubleSpinBox_building_radius->setEnabled(true);
        ui->comboBox_building_step->setEnabled(true);
        ui->spinBox_building_distance->setEnabled(true);
        ui->spinBox_building_length->setEnabled(true);
        ui->spinBox_building_width->setEnabled(true);
        ui->pushButton_add_building->setEnabled(false);
        ui->pushButton_build_duplicate->setEnabled(true);
        ui->pushButton_remove_building->setEnabled(true);
        ui->pushButton_save_building->setEnabled(true);
        ui->pushButton_building_generate->setEnabled(true);
        ui->pushButton_building_clear->setEnabled(true);

        if(!configuration->getBuildingConductors().empty()){
            ui->lineEdit_building_status->setText("Building in config: Yes");
        }
        else{
            ui->lineEdit_building_status->setText("Building in config: No");
        }

        ui->spinBox_building_distance->setValue(building->getDistance());
        ui->spinBox_building_length->setValue(building->getLength());
        ui->spinBox_building_width->setValue(building->getWidth());
        ui->spinBox_building_height->setValue(building->getHeight());
        ui->doubleSpinBox_building_radius->setValue(building->getRadius());

        QString stepString = QString::number(building->getStep());
        stepString.replace(".", ",");
        int key = ui->comboBox_building_step->findText(stepString, Qt::MatchStartsWith);

        if(key != -1){
            ui->comboBox_building_step->setCurrentIndex(key);
        }
        else{
            ui->comboBox_building_step->setCurrentIndex(0);
        }

        key = ui->comboBox_building_sides->findText(QString::number(building->getFaces()), Qt::MatchStartsWith);
        if(key != -1){
            ui->comboBox_building_sides->setCurrentIndex(key);
        }
        else{
            ui->comboBox_building_sides->setCurrentIndex(0);
        }


        if(building->getLeadType()){
            ui->comboBox_building_lType->setCurrentIndex(ui->comboBox_building_lType->findText(QString::fromStdString(building->getLeadType()->getName()), Qt::MatchEndsWith));
        }
        else{
            ui->comboBox_building_lType->setCurrentIndex(0);
        }

        if(building->getCoating()){
            ui->comboBox_building_coat->setCurrentIndex(ui->comboBox_building_coat->findText(QString::fromStdString(building->getCoating()->getName()), Qt::MatchEndsWith));
        }
        else{
            ui->comboBox_building_coat->setCurrentIndex(0);
        }

        if(building->getEnergization()){
            ui->comboBox_building_ener->setCurrentIndex(ui->comboBox_building_ener->findText(QString::fromStdString(building->getEnergization()->getIdentification()), Qt::MatchEndsWith));
        }
        else{
            ui->comboBox_building_ener->setCurrentIndex(0);
        }

        if(building->getConductorType()){
            ui->comboBox_building_cType->setCurrentIndex(ui->comboBox_building_cType->findText(QString::fromStdString(building->getConductorType()->getName()), Qt::MatchEndsWith));
        }
        else{
            ui->comboBox_building_cType->setCurrentIndex(0);
        }

        if(building->getCableType()){
            ui->comboBox_building_cbType->setCurrentIndex(ui->comboBox_building_cbType->findText(QString::fromStdString(building->getCableType()->getName()), Qt::MatchEndsWith));
        }
        else{
            ui->comboBox_building_cbType->setCurrentIndex(0);
        }
    }
    else{
        ui->comboBox_building_cbType->setEnabled(false);
        ui->comboBox_building_coat->setEnabled(false);
        ui->comboBox_building_cType->setEnabled(false);
        ui->comboBox_building_ener->setEnabled(false);
        ui->comboBox_building_lType->setEnabled(false);
        ui->comboBox_building_sides->setEnabled(false);
        ui->spinBox_building_height->setEnabled(false);
        ui->doubleSpinBox_building_radius->setEnabled(false);
        ui->comboBox_building_step->setEnabled(false);
        ui->spinBox_building_distance->setEnabled(false);
        ui->spinBox_building_length->setEnabled(false);
        ui->spinBox_building_width->setEnabled(false);
        ui->pushButton_add_building->setEnabled(true);
        ui->pushButton_remove_building->setEnabled(false);
        ui->pushButton_save_building->setEnabled(false);
        ui->pushButton_building_generate->setEnabled(false);
        ui->pushButton_building_clear->setEnabled(true);
        ui->pushButton_build_duplicate->setEnabled(false);
    }
}

void configuration_widget::refreshPlot(){
    QVector<double> keys, values, keySelected, valueSelected;
    int lowX = -4;
    int lowY = -9;
    int highX = 4;
    int highY = 4;
    for(std::shared_ptr<Conductor> cond : configuration->getConductors()){
        if(cond->getStartCoords().y < lowX) lowX = cond->getStartCoords().y;
        if(cond->getStartCoords().z < lowY) lowY = cond->getStartCoords().z;
        if(cond->getEndCoords().y > highX) highX = cond->getEndCoords().y;
        if(cond->getEndCoords().z > highY) highY = cond->getEndCoords().z;
        keys.push_back(cond->getStartCoords().y);
        values.push_back(cond->getStartCoords().z);
    }
    if(conductor){
        keySelected.push_back(conductor->getStartCoords().y);
        valueSelected.push_back(conductor->getStartCoords().z);
    }
    ui->cond_plot->xAxis->setRange((lowX - 1), (highX + 1));
    ui->cond_plot->yAxis->setRange((lowY - 1), (highY + 1));
    ui->cond_plot->yAxis->setRangeReversed(true);
    ui->cond_plot->graph(0)->setData(keys, values);
    ui->cond_plot->graph(1)->setData(keySelected, valueSelected);
    ui->cond_plot->replot();
}

//CONF CONNECTIONS
void configuration_widget::changeConfIdentifier(QString ident){
    configuration->setIdentifier(ident.toStdString());
    configuration->setModified(true);
    refresh();
}

void configuration_widget::changeConfUnits(QString units){
    configuration->setUnits(units.toStdString());
    configuration->setModified(true);
    refresh();
}

void configuration_widget::changeConfFrequency(QString frequency){
    configuration->setFrequency(frequency.toStdString());
    configuration->setModified(true);
    refresh();
}

void configuration_widget::saveConfig(){
    defParent->saveConfig();
}

//COND CONNECTIONS
void configuration_widget::newCond(){
    conductor.reset(new Conductor());
    if(conductor->getId() < 0){
        conductor->setId(configuration->componentIdGenerator());
    }
    configuration->addConductor(conductor);
    configuration->setModified(true);
    populateConductors();
}

void configuration_widget::duplicateCond(){
    if(conductor){
        std::shared_ptr<Conductor> cond;
        cond.reset(new Conductor(conductor.get()));
        cond->setId(configuration->componentIdGenerator());
        configuration->addConductor(cond);
        configuration->setModified(true);
        populateConductors();
    }
}

void configuration_widget::removeCond(){
    configuration->removeConductor(conductor);
    configuration->setModified(true);
    conductor.reset();
    populateConductors();
}

void configuration_widget::saveCond(){
    int result = configuration->replaceConductor(conductor);
    if(result == 1){
        if(conductor->getId() < 0) conductor->setId(configuration->componentIdGenerator());
        configuration->addConductor(conductor);
    }
    configuration->setModified(true);
    populateConductors();
}

void configuration_widget::changeCondCbType(int index){
    if(conductor && index > 0){
        conductor->setCableType(configuration->getCableTypes().at(index-1));
        refresh();
        configuration->setModified(true);
    }
}

void configuration_widget::changeCondCoat(int index){
    if(conductor && index > 0){
        conductor->setCoating(configuration->getCoatings().at(index-1));
        refresh();
        configuration->setModified(true);
    }
}

void configuration_widget::changeCondCType(int index){
    if(conductor && index > 0){
        conductor->setConductorType(configuration->getConductorTypes().at(index-1));
        refresh();
        configuration->setModified(true);
    }
}

void configuration_widget::changeCondEner(int index){
    if(conductor && index > 0){
        conductor->setEnergization(configuration->getEnergizations().at(index-1));
        refresh();
        configuration->setModified(true);
    }
}

void configuration_widget::changeCondLType(int index){
    if(conductor && index > 0){
        conductor->setLeadType(configuration->getLeadTypes().at(index-1));
        refresh();
        configuration->setModified(true);
    }
}

void configuration_widget::changeCondRadius(double value){
    if(conductor){
        conductor->setRadius(value);
        configuration->setModified(true);
    }
}

void configuration_widget::changeCondStartX(double value){
    if(conductor){
        coords start;
        start = conductor->getStartCoords();
        start.x = value;
        conductor->setStartCoords(start);

        if(!ui->checkBox_cond_advanced->isChecked()){
            coords end;
            end = conductor->getEndCoords();
            end.x = -(start.x);
            conductor->setEndCoords(end);
            ui->doubleSpinBox_cond_endX->setValue(end.x);
        }

        configuration->setModified(true);
    }
}

void configuration_widget::changeCondStartY(double value){
    if(conductor){
        coords start;
        start = conductor->getStartCoords();
        start.y = value;
        conductor->setStartCoords(start);

        if(!ui->checkBox_cond_advanced->isChecked()){
            coords end;
            end = conductor->getEndCoords();
            end.y = start.y;
            conductor->setEndCoords(end);
            ui->doubleSpinBox_cond_endY->setValue(end.y);
        }

        configuration->setModified(true);
    }
}

void configuration_widget::changeCondStartZ(double value){
    if(conductor){
        coords start;
        start = conductor->getStartCoords();
        start.z = value;
        conductor->setStartCoords(start);

        if(!ui->checkBox_cond_advanced->isChecked()){
            coords end;
            end = conductor->getEndCoords();
            end.z = start.z;
            conductor->setEndCoords(end);
            ui->doubleSpinBox_cond_endZ->setValue(end.z);
        }

        configuration->setModified(true);
    }
}

void configuration_widget::changeCondEndX(double value){
    if(conductor){
        coords end;
        end = conductor->getEndCoords();
        end.x = value;
        conductor->setEndCoords(end);
        configuration->setModified(true);
    }
}

void configuration_widget::changeCondEndY(double value){
    if(conductor){
        coords end;
        end = conductor->getEndCoords();
        end.y = value;
        conductor->setEndCoords(end);
        configuration->setModified(true);
    }
}

void configuration_widget::changeCondEndZ(double value){
    if(conductor){
        coords end;
        end = conductor->getEndCoords();
        end.z = value;
        conductor->setEndCoords(end);
        configuration->setModified(true);
    }
}

//BUILD CONNECTIONS

void configuration_widget::newBuilding(){
    if(!configuration->getLeadTypes().empty() && !configuration->getCoatings().empty() && !configuration->getEnergizations().empty() && !configuration->getConductorTypes().empty() && !configuration->getCableTypes().empty()){
        building.reset(new Building());
        configuration->setModified(true);
        building->setLeadType(configuration->getLeadTypes().at(0));
        building->setCoating(configuration->getCoatings().at(0));
        building->setEnergization(configuration->getEnergizations().at(0));
        building->setCableType(configuration->getCableTypes().at(0));
        building->setConductorType(configuration->getConductorTypes().at(0));
        if(building->getId() < 0){
            building->setId(configuration->componentIdGenerator());
        }
        configuration->addBuilding(building);
        populateBuildings();
    }
    else{
        QMessageBox::critical(this, "Failure", "There are missing default components in the configuration.");
    }
}

void configuration_widget::duplicateBuilding(){
    if(building){
        std::shared_ptr<Building> build;
        build.reset(new Building(building.get()));
        build->setId(configuration->componentIdGenerator());
        configuration->addBuilding(build);
        configuration->setModified(true);
        populateBuildings();
    }
}

void configuration_widget::removeBuilding(){
    configuration->removeBuilding(building);
    configuration->setModified(true);
    building.reset();
    populateBuildings();
}

void configuration_widget::saveBuilding(){
    int result = configuration->replaceBuilding(building);
    if(result == 1){
        if(building->getId() < 0) building->setId(configuration->componentIdGenerator());
        configuration->addBuilding(building);
    }
    configuration->setModified(true);
    populateBuildings();
}

void configuration_widget::changeBuildFaces(QString index){
    if(building){
        int faces = index.toInt();
        building->setFaces(faces);
        configuration->setModified(true);
    }
}

void configuration_widget::changeBuildHeight(int value){
    if(building){
        building->setHeight(value);
        configuration->setModified(true);
    }
}

void configuration_widget::changeBuildStep(QString index){
    if(building){
        double step = index.toDouble();
        building->setStep(step);
        configuration->setModified(true);
    }
}

void configuration_widget::changeBuildDistance(int value){
    if(building){
        building->setDistance(value);
        configuration->setModified(true);
    }
}

void configuration_widget::changeBuildLength(int value){
    if(building){
        building->setLength(value);
        configuration->setModified(true);
    }
}

void configuration_widget::changeBuildWidth(int value){
    if(building){
        building->setWidth(value);
        configuration->setModified(true);
    }
}

void configuration_widget::changeBuildRadius(double value){
    if(building){
        building->setRadius(value);
        configuration->setModified(true);
    }
}

void configuration_widget::changeBuildCbType(int index){
    if(building && index >= 0){
        building->setCableType(configuration->getCableTypes().at(index));
        configuration->setModified(true);
    }
}

void configuration_widget::changeBuildCoat(int index){
    if(building && index >= 0){
        building->setCoating(configuration->getCoatings().at(index));
        configuration->setModified(true);
    }
}

void configuration_widget::changeBuildCType(int index){
    if(building && index >= 0){
        building->setConductorType(configuration->getConductorTypes().at(index));
        configuration->setModified(true);
    }
}

void configuration_widget::changeBuildEner(int index){
    if(building && index >= 0){
        building->setEnergization(configuration->getEnergizations().at(index));
        configuration->setModified(true);
    }
}

void configuration_widget::changeBuildLType(int index){
    if(building && index >= 0){
        building->setLeadType(configuration->getLeadTypes().at(index));
        configuration->setModified(true);
    }
}

void configuration_widget::generateBuildingConductors(){
    if(building){
        configuration->updateBuildingConductors(building);
        configuration->setModified(true);
    }
}

void configuration_widget::clearBuildingConductors(){
    if(building){
        configuration->clearBuildingConductors();
        configuration->setModified(true);
    }
}

//LTYPE CONNECTIONS
void configuration_widget::changeLTypeName(QString text){
    if(lType){
        lType->setName(text.toStdString());
        configuration->setModified(true);
    }
}

void configuration_widget::newLType(){
    lType.reset(new LeadType());
    if(lType->getId() < 0) lType->setId(configuration->componentIdGenerator());
    configuration->addLeadType(lType);
    configuration->setModified(true);
    populateLTypes();
    populateConductors();
}

void configuration_widget::duplicateLType(){
    if(lType){
        std::shared_ptr<LeadType> lt;
        lt.reset(new LeadType(lType.get()));
        lt->setId(configuration->componentIdGenerator());
        configuration->addLeadType(lt);
        configuration->setModified(true);
        populateLTypes();
    }
}

void configuration_widget::removeLType(){
    int result = configuration->removeLeadType(lType);
    if(result == 1){
        QMessageBox::critical(this, "Failure", "This LeadType is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration.");
    }
    else{
        configuration->setModified(true);
        lType.reset();
        populateLTypes();
    }
}

void configuration_widget::saveLType(){
    int result = configuration->replaceLeadType(lType);
    if(result == 1){
        if(lType->getId() < 0) lType->setId(configuration->componentIdGenerator());
        configuration->addLeadType(lType);
    }
    configuration->setModified(true);
    populateLTypes();
}

//COATING CONNECTIONS
void configuration_widget::changeCoatName(QString text){
    if(coat){
        coat->setName(text.toStdString());
        configuration->setModified(true);
    }
}

void configuration_widget::newCoat(){
    coat.reset(new Coating());
    if(coat->getId() < 0) coat->setId(configuration->componentIdGenerator());
    configuration->addCoating(coat);
    configuration->setModified(true);
    populateCoatings();
    populateConductors();
}

void configuration_widget::duplicateCoat(){
    if(coat){
        std::shared_ptr<Coating> co;
        co.reset(new Coating(coat.get()));
        co->setId(configuration->componentIdGenerator());
        configuration->addCoating(co);
        configuration->setModified(true);
        populateCoatings();
    }
}

void configuration_widget::removeCoat(){
    int result = configuration->removeCoating(coat);
    if(result == 1){
        QMessageBox::critical(this, "Failure", "This Coating is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration.");
    }
    else{
        configuration->setModified(true);
        coat.reset();
        populateCoatings();
    }
}

void configuration_widget::saveCoat(){
    int result = configuration->replaceCoating(coat);
    if(result == 1){
        if(coat->getId() < 0) coat->setId(configuration->componentIdGenerator());
        configuration->addCoating(coat);
    }
    configuration->setModified(true);
    populateCoatings();
}

//ENERG CONNECTIONS
void configuration_widget::changeEnerFreq(QString text){
    if(ener){
        ener->setFrequency(text.toStdString());
        configuration->setModified(true);
    }
}

void configuration_widget::changeEnerIdent(QString text){
    if(ener){
        ener->setIdentification(text.toStdString());
        configuration->setModified(true);
    }
}

void configuration_widget::changeEnerType(QString text){
    if(ener){
        ener->setType(text.toStdString());
        configuration->setModified(true);
    }
}

void configuration_widget::changeEnerMag(int i){
    if(ener){
        ener->setMagnitude(i);
        configuration->setModified(true);
    }
}

void configuration_widget::changeEnerAng(double d){
    if(ener){
        ener->setAngle(d);
        configuration->setModified(true);
    }
}

void configuration_widget::newEner(){
    ener.reset(new Energization());
    if(ener->getId() < 0) ener->setId(configuration->componentIdGenerator());
    configuration->addEnergization(ener);
    configuration->setModified(true);
    populateEnergizations();
    populateConductors();
}

void configuration_widget::duplicateEner(){
    if(ener){
        std::shared_ptr<Energization> en;
        en.reset(new Energization(ener.get()));
        en->setId(configuration->componentIdGenerator());
        configuration->addEnergization(en);
        configuration->setModified(true);
        populateEnergizations();
    }
}

void configuration_widget::removeEner(){
    int result = configuration->removeEnergization(ener);
    if(result == 1){
        QMessageBox::critical(this, "Failure", "This Energization is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration.");
    }
    else{
        configuration->setModified(true);
        ener.reset();
        populateEnergizations();
    }
}

void configuration_widget::saveEner(){
    int result = configuration->replaceEnergization(ener);
    if(result == 1){
        if(ener->getId() < 0) ener->setId(configuration->componentIdGenerator());
        configuration->addEnergization(ener);
    }
    configuration->setModified(true);
    populateEnergizations();
}

//CTYPE CONNECTIONS
void configuration_widget::changeCTypeName(QString text){
    if(cType){
        cType->setName(text.toStdString());
        configuration->setModified(true);
    }
}

void configuration_widget::changeCTypeType(QString text){
    if(cType){
        cType->setType(text.toStdString());
        configuration->setModified(true);
    }
}

void configuration_widget::changeCTypePerm(double d){
    if(cType){
        cType->setPermeability(d);
        configuration->setModified(true);
    }
}

void configuration_widget::changeCTypeRes(double d){
    if(cType){
        cType->setResistivity(d);
        configuration->setModified(true);
    }
}

void configuration_widget::newCType(){
    cType.reset(new ConductorType());
    if(cType->getId() < 0) cType->setId(configuration->componentIdGenerator());
    configuration->addConductorType(cType);
    configuration->setModified(true);
    populateCTypes();
    populateConductors();
}

void configuration_widget::duplicateCType(){
    if(cType){
        std::shared_ptr<ConductorType> ct;
        ct.reset(new ConductorType(cType.get()));
        ct->setId(configuration->componentIdGenerator());
        configuration->addConductorType(ct);
        configuration->setModified(true);
        populateCTypes();
    }
}

void configuration_widget::removeCType(){
    int result = configuration->removeConductorType(cType);
    if(result == 1){
        QMessageBox::critical(this, "Failure", "This ConductorType is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration.");
    }
    else{
        configuration->setModified(true);
        cType.reset();
        populateCTypes();
    }
}

void configuration_widget::saveCType(){
    int result = configuration->replaceConductorType(cType);
    if(result == 1){
        if(cType->getId() < 0) cType->setId(configuration->componentIdGenerator());
        configuration->addConductorType(cType);
    }
    configuration->setModified(true);
    populateCTypes();
}

//CBTYPE CONNECTIONS
void configuration_widget::changeCbTypeName(QString text){
    if(cbType){
        cbType->setName(text.toStdString());
        configuration->setModified(true);
    }
}

void configuration_widget::newCbType(){
    cbType.reset(new CableType());
    if(cbType->getId() < 0) cbType->setId(configuration->componentIdGenerator());
    configuration->addCableType(cbType);
    configuration->setModified(true);
    populateCbTypes();
    populateConductors();
}

void configuration_widget::duplicateCbType(){
    if(cbType){
        std::shared_ptr<CableType> cb;
        cb.reset(new CableType(cbType.get()));
        cb->setId(configuration->componentIdGenerator());
        configuration->addCableType(cb);
        configuration->setModified(true);
        populateCbTypes();
    }
}

void configuration_widget::removeCbType(){
    int result = configuration->removeCableType(cbType);
    if(result == 1){
        QMessageBox::critical(this, "Failure", "This CableType is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration.");
    }
    else{
        configuration->setModified(true);
        cbType.reset();
        populateCbTypes();
    }
}

void configuration_widget::saveCbType(){
    int result = configuration->replaceCableType(cbType);
    if(result == 1){
        if(cbType->getId() < 0) cbType->setId(configuration->componentIdGenerator());
        configuration->addCableType(cbType);
        configuration->setModified(true);
    }
    populateCbTypes();
}

//PROFILE CONNECTIONS
void configuration_widget::changeProNumPt(int i){
    if(pro){
        pro->ptNum = i;
        configuration->setModified(true);
    }
}

void configuration_widget::changeProNumPr(int i){
    if(pro){
        pro->prNum = i;
        configuration->setModified(true);
    }
}

void configuration_widget::changeProPtStepX(double d){
    if(pro){
        pro->ptStep.x = d;
        configuration->setModified(true);
    }
}

void configuration_widget::changeProPtStepY(double d){
    if(pro){
        pro->ptStep.y = d;
        configuration->setModified(true);
    }
}

void configuration_widget::changeProPtStepZ(double d){
    if(pro){
        pro->ptStep.z = d;
        configuration->setModified(true);
    }
}

void configuration_widget::changeProStartX(double d){
    if(pro){
        pro->start.x = d;
        configuration->setModified(true);
    }
}

void configuration_widget::changeProStartY(double d){
    if(pro){
        pro->start.y = d;
        configuration->setModified(true);
    }
}

void configuration_widget::changeProStartZ(double d){
    if(pro){
        pro->start.z = d;
        configuration->setModified(true);
    }
}

void configuration_widget::changeProPrStepX(double d){
    if(pro){
        pro->prStep.x = d;
        configuration->setModified(true);
    }
}

void configuration_widget::changeProPrStepY(double d){
    if(pro){
        pro->prStep.y = d;
        configuration->setModified(true);
    }
}

void configuration_widget::changeProPrStepZ(double d){
    if(pro){
        pro->prStep.z = d;
        configuration->setModified(true);
    }
}

void configuration_widget::newPro(){
    pro.reset(new profile());
    if(pro->id < 0) cbType->setId(configuration->componentIdGenerator());
    configuration->addProfile(pro);
    configuration->setModified(true);
    populateProfiles();
}

void configuration_widget::duplicatePro(){
    if(pro){
        std::shared_ptr<profile> p;
        p.reset(new profile(pro.get()));
        p->id = configuration->componentIdGenerator();
        configuration->addProfile(p);
        configuration->setModified(true);
        populateProfiles();
    }
}

void configuration_widget::removePro(){
    configuration->removeProfile(pro);
    configuration->setModified(true);
    pro.reset();
    populateProfiles();
}

void configuration_widget::savePro(){
    if(pro->id < 0) cbType->setId(configuration->componentIdGenerator());
    configuration->removeProfile(pro);
    configuration->addProfile(pro);
    configuration->setModified(true);
    populateProfiles();
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void configuration_widget::changeComputations(int i){
    if(configuration){
        configuration->setComputations().ELECTRIC = ui->checkBox_comp_ELECTRIC->isChecked();
        configuration->setComputations().GPR = ui->checkBox_comp_GPR->isChecked();
        configuration->setComputations().GRADIENT_SCALAR = ui->checkBox_comp_GRADIENT_SCALAR->isChecked();
        configuration->setComputations().MAGNETIC = ui->checkBox_comp_MAGNETIC->isChecked();
        configuration->setComputations().POTENTIAL_SCALAR = ui->checkBox_comp_POTENTIAL_SCALAR->isChecked();
        configuration->setComputations().VECTOR_POTENTIAL = ui->checkBox_comp_VECTOR_POTENTIAL->isChecked();
        configuration->setModified(true);
        refresh();
    }
}
#pragma GCC diagnostic pop

void configuration_widget::refreshConfSettings(){
    ui->lineEdit_settings_identifier->setText(QString::fromStdString(configuration->getIdentifier()));

    if(configuration->getUnits() == "Metric") ui->comboBox_settings_units->setCurrentIndex(0);
    else ui->comboBox_settings_units->setCurrentIndex(1);

    if(configuration->getFrequency() == "AC") ui->comboBox_settings_frequency->setCurrentIndex(0);
    else ui->comboBox_settings_frequency->setCurrentIndex(1);

    ui->lineEdit_settings_lTypes->setText(QString::number(configuration->getLeadTypes().size()));
    ui->lineEdit_settings_coatings->setText(QString::number(configuration->getCoatings().size()));
    ui->lineEdit_settings_energizations->setText(QString::number(configuration->getEnergizations().size()));
    ui->lineEdit_settings_cTypes->setText(QString::number(configuration->getConductorTypes().size()));
    ui->lineEdit_settings_cbTypes->setText(QString::number(configuration->getCableTypes().size()));
    ui->lineEdit_settings_profiles->setText(QString::number(configuration->getProfiles().size()));
}
