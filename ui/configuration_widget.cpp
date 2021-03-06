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
    //connectSlots();
}

/*!
 \brief

 \fn configuration_widget::initPlot
*/
void configuration_widget::initPlot(){
    ui->cond_plot->plotLayout()->insertRow(0);
    QCPPlotTitle* title = new QCPPlotTitle(ui->cond_plot, tr("Position of Conductors"));
    title->setTextColor(Qt::white);
    title->setAntialiased(true);
    ui->cond_plot->plotLayout()->addElement(0, 0, title);
    ui->cond_plot->legend->setVisible(false);
    ui->cond_plot->legend->setAntialiased(true);

    ui->cond_plot->addGraph();
    ui->cond_plot->addGraph();
    ui->cond_plot->addGraph();

    ui->cond_plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->cond_plot->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->cond_plot->graph(0)->setPen(QPen(QColor(141, 95, 0), 3));
    ui->cond_plot->graph(0)->setName("Ground");
    ui->cond_plot->graph(0)->setAntialiased(true);

    ui->cond_plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->cond_plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QColor(0, 102, 255), 10));
    ui->cond_plot->graph(1)->setPen(QPen(QColor(120, 120, 120), 1));
    ui->cond_plot->graph(1)->setName("Conductors");
    ui->cond_plot->graph(1)->setAntialiased(true);

    ui->cond_plot->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->cond_plot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QColor(220, 0, 0), 10));
    ui->cond_plot->graph(2)->setPen(QPen(QColor(120, 120, 120), 1));
    ui->cond_plot->graph(2)->setName("Selected Conductor");
    ui->cond_plot->graph(2)->setAntialiased(true);

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

    ui->cond_plot->xAxis->setLabel(tr("Y - Distance from Line Center (m)"));
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

    ui->cond_plot->yAxis->setLabel(tr("Z - Height (m)"));
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

/*!
 \brief

 \fn configuration_widget::connectSlots
*/
void configuration_widget::connectSlots(){
    QObject::connect(ui->comboBox_page, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(fetchPage(int)));


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
    QObject::connect(ui->pushButton_cond_add, SIGNAL(released()),
                     this, SLOT(newCond()));

    QObject::connect(ui->pushButton_cond_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateCond()));

    QObject::connect(ui->pushButton_cond_remove, SIGNAL(released()),
                     this, SLOT(removeCond()));

    QObject::connect(ui->pushButton_cond_save, SIGNAL(released()),
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

    QObject::connect(ui->checkBox_cond_advanced, SIGNAL(released()),
                     this, SLOT(refreshConductor()));

    QObject::connect(ui->pushButton_cond_batchHeight, SIGNAL(released()),
                     this, SLOT(batchChangeCondHeight()));

    QObject::connect(ui->pushButton_cond_addMultiple, SIGNAL(released()),
                     this, SLOT(multiCondDialog()));

    //BUILD CONNECTIONS
    QObject::connect(ui->pushButton_add_building, SIGNAL(released()),
                     this, SLOT(newBuilding()));

    QObject::connect(ui->pushButton_build_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateBuilding()));

    QObject::connect(ui->pushButton_remove_building, SIGNAL(released()),
                     this, SLOT(removeBuilding()));

    QObject::connect(ui->pushButton_save_building, SIGNAL(released()),
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

    QObject::connect(ui->pushButton_building_generate, SIGNAL(released()),
                     this, SLOT(generateBuildingConductors()));

    QObject::connect(ui->pushButton_building_clear, SIGNAL(released()),
                     this, SLOT(clearBuildingConductors()));

    //CONF CONNECTIONS

    QObject::connect(ui->lineEdit_settings_identifier, SIGNAL(textChanged(QString)),
                     this, SLOT(changeConfIdentifier(QString)));

    QObject::connect(ui->comboBox_settings_units, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeConfUnits(QString)));

    QObject::connect(ui->comboBox_settings_frequency, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeConfFrequency(QString)));

    QObject::connect(ui->pushButton_save_conf, SIGNAL(released()),
                     this, SLOT(saveConfig()));

    //LTYPE CONNECTIONS
    QObject::connect(ui->lineEdit_lType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeLTypeName(QString)));

    QObject::connect(ui->pushButton_new_lType, SIGNAL(released()),
                     this, SLOT(newLType()));

    QObject::connect(ui->pushButton_lType_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateLType()));

    QObject::connect(ui->pushButton_remove_lType, SIGNAL(released()),
                     this, SLOT(removeLType()));

    QObject::connect(ui->pushButton_save_lType, SIGNAL(released()),
                     this, SLOT(saveLType()));

    //COATING CONNECTIONS
    QObject::connect(ui->lineEdit_coating_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCoatName(QString)));

    QObject::connect(ui->pushButton_new_coating, SIGNAL(released()),
                     this, SLOT(newCoat()));

    QObject::connect(ui->pushButton_coat_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateCoat()));

    QObject::connect(ui->pushButton_remove_coating, SIGNAL(released()),
                     this, SLOT(removeCoat()));

    QObject::connect(ui->pushButton_save_coating, SIGNAL(released()),
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

    QObject::connect(ui->pushButton_new_energization, SIGNAL(released()),
                     this, SLOT(newEner()));

    QObject::connect(ui->pushButton_ener_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateEner()));

    QObject::connect(ui->pushButton_remove_energization, SIGNAL(released()),
                     this, SLOT(removeEner()));

    QObject::connect(ui->pushButton_save_energization, SIGNAL(released()),
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

    QObject::connect(ui->pushButton_new_cType, SIGNAL(released()),
                     this, SLOT(newCType()));

    QObject::connect(ui->pushButton_cType_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateCType()));

    QObject::connect(ui->pushButton_remove_cType, SIGNAL(released()),
                     this, SLOT(removeCType()));

    QObject::connect(ui->pushButton_save_cType, SIGNAL(released()),
                     this, SLOT(saveCType()));

    //CBTYPE CONNECTIONS
    QObject::connect(ui->lineEdit_cbType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCbTypeName(QString)));

    QObject::connect(ui->pushButton_new_cbType, SIGNAL(released()),
                     this, SLOT(newCbType()));

    QObject::connect(ui->pushButton_cbType_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateCbType()));

    QObject::connect(ui->pushButton_remove_cbType, SIGNAL(released()),
                     this, SLOT(removeCbType()));

    QObject::connect(ui->pushButton_save_cbType, SIGNAL(released()),
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

    QObject::connect(ui->pushButton_reset_profile, SIGNAL(released()),
                     this, SLOT(resetPro()));

    QObject::connect(ui->pushButton_save_profile, SIGNAL(released()),
                     this, SLOT(savePro()));

    QObject::connect(ui->radioButton_pro_surface, SIGNAL(clicked()),
                     this, SLOT(changeProSetup()));

    QObject::connect(ui->radioButton_pro_line, SIGNAL(clicked()),
                     this, SLOT(changeProSetup()));

    QObject::connect(ui->radioButton_profile_endPts, SIGNAL(released()),
                     this, SLOT(refreshProfile()));

    QObject::connect(ui->radioButton_profile_steps, SIGNAL(released()),
                     this, SLOT(refreshProfile()));

    QObject::connect(ui->pushButton_profile_genRight, SIGNAL(released()),
                     this, SLOT(generateProRight()));

    QObject::connect(ui->pushButton_profile_genLeft, SIGNAL(released()),
                     this, SLOT(generateProLeft()));

    QObject::connect(ui->pushButton_profile_genTwo, SIGNAL(released()),
                     this, SLOT(generateProTwo()));

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

 \fn configuration_widget::disconnectSlots
*/
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
    QObject::disconnect(ui->pushButton_cond_add, SIGNAL(released()),
                     this, SLOT(newCond()));

    QObject::disconnect(ui->pushButton_cond_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateCond()));

    QObject::disconnect(ui->pushButton_cond_remove, SIGNAL(released()),
                     this, SLOT(removeCond()));

    QObject::disconnect(ui->pushButton_cond_save, SIGNAL(released()),
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

    QObject::disconnect(ui->checkBox_cond_advanced, SIGNAL(released()),
                     this, SLOT(refreshConductor()));

    QObject::disconnect(ui->pushButton_cond_batchHeight, SIGNAL(released()),
                     this, SLOT(batchChangeCondHeight()));

    QObject::disconnect(ui->pushButton_cond_addMultiple, SIGNAL(released()),
                     this, SLOT(multiCondDialog()));

    //BUILD CONNECTIONS
    QObject::disconnect(ui->pushButton_add_building, SIGNAL(released()),
                     this, SLOT(newBuilding()));

    QObject::disconnect(ui->pushButton_build_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateBuilding()));

    QObject::disconnect(ui->pushButton_remove_building, SIGNAL(released()),
                     this, SLOT(removeBuilding()));

    QObject::disconnect(ui->pushButton_save_building, SIGNAL(released()),
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

    QObject::disconnect(ui->pushButton_building_generate, SIGNAL(released()),
                     this, SLOT(generateBuildingConductors()));

    QObject::disconnect(ui->pushButton_building_clear, SIGNAL(released()),
                     this, SLOT(clearBuildingConductors()));

    //CONF CONNECTIONS

    QObject::disconnect(ui->lineEdit_settings_identifier, SIGNAL(textChanged(QString)),
                     this, SLOT(changeConfIdentifier(QString)));

    QObject::disconnect(ui->comboBox_settings_units, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeConfUnits(QString)));

    QObject::disconnect(ui->comboBox_settings_frequency, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(changeConfFrequency(QString)));

    QObject::disconnect(ui->pushButton_save_conf, SIGNAL(released()),
                     this, SLOT(saveConfig()));

    //LTYPE CONNECTIONS
    QObject::disconnect(ui->lineEdit_lType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeLTypeName(QString)));

    QObject::disconnect(ui->pushButton_new_lType, SIGNAL(released()),
                     this, SLOT(newLType()));

    QObject::disconnect(ui->pushButton_lType_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateLType()));

    QObject::disconnect(ui->pushButton_remove_lType, SIGNAL(released()),
                     this, SLOT(removeLType()));

    QObject::disconnect(ui->pushButton_save_lType, SIGNAL(released()),
                     this, SLOT(saveLType()));

    //COATING CONNECTIONS
    QObject::disconnect(ui->lineEdit_coating_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCoatName(QString)));

    QObject::disconnect(ui->pushButton_new_coating, SIGNAL(released()),
                     this, SLOT(newCoat()));

    QObject::disconnect(ui->pushButton_coat_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateCoat()));

    QObject::disconnect(ui->pushButton_remove_coating, SIGNAL(released()),
                     this, SLOT(removeCoat()));

    QObject::disconnect(ui->pushButton_save_coating, SIGNAL(released()),
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

    QObject::disconnect(ui->pushButton_new_energization, SIGNAL(released()),
                     this, SLOT(newEner()));

    QObject::disconnect(ui->pushButton_ener_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateEner()));

    QObject::disconnect(ui->pushButton_remove_energization, SIGNAL(released()),
                     this, SLOT(removeEner()));

    QObject::disconnect(ui->pushButton_save_energization, SIGNAL(released()),
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

    QObject::disconnect(ui->pushButton_new_cType, SIGNAL(released()),
                     this, SLOT(newCType()));

    QObject::disconnect(ui->pushButton_cType_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateCType()));

    QObject::disconnect(ui->pushButton_remove_cType, SIGNAL(released()),
                     this, SLOT(removeCType()));

    QObject::disconnect(ui->pushButton_save_cType, SIGNAL(released()),
                     this, SLOT(saveCType()));

    //CBTYPE CONNECTIONS
    QObject::disconnect(ui->lineEdit_cbType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCbTypeName(QString)));

    QObject::disconnect(ui->pushButton_new_cbType, SIGNAL(released()),
                     this, SLOT(newCbType()));

    QObject::disconnect(ui->pushButton_cbType_duplicate, SIGNAL(released()),
                     this, SLOT(duplicateCbType()));

    QObject::disconnect(ui->pushButton_remove_cbType, SIGNAL(released()),
                     this, SLOT(removeCbType()));

    QObject::disconnect(ui->pushButton_save_cbType, SIGNAL(released()),
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

    QObject::disconnect(ui->pushButton_reset_profile, SIGNAL(released()),
                     this, SLOT(resetPro()));

    QObject::disconnect(ui->pushButton_save_profile, SIGNAL(released()),
                     this, SLOT(savePro()));

    QObject::disconnect(ui->radioButton_pro_surface, SIGNAL(clicked()),
                     this, SLOT(changeProSetup()));

    QObject::disconnect(ui->radioButton_pro_line, SIGNAL(clicked()),
                     this, SLOT(changeProSetup()));

    QObject::disconnect(ui->radioButton_profile_endPts, SIGNAL(released()),
                     this, SLOT(refreshProfile()));

    QObject::disconnect(ui->radioButton_profile_steps, SIGNAL(released()),
                     this, SLOT(refreshProfile()));

    QObject::disconnect(ui->pushButton_profile_genRight, SIGNAL(released()),
                     this, SLOT(generateProRight()));

    QObject::disconnect(ui->pushButton_profile_genLeft, SIGNAL(released()),
                     this, SLOT(generateProLeft()));

    QObject::disconnect(ui->pushButton_profile_genTwo, SIGNAL(released()),
                     this, SLOT(generateProTwo()));

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

/*!
 \brief

 \fn configuration_widget::getName
 \return const QString
*/
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

/*!
 \brief

 \fn configuration_widget::populateFields
*/
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

/*!
 \brief

 \fn configuration_widget::populateLTypes
 \param action
*/
void configuration_widget::populateLTypes(int action){
    int currentIndex = ui->comboBox_lTypes_chooser->currentIndex();
    QString currentText = ui->comboBox_lTypes_chooser->currentText();

    ui->comboBox_lTypes_chooser->clear();
    for(unsigned int i = 0; i < configuration->getLeadTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getLeadTypes().at(i)->getName());
        ui->comboBox_lTypes_chooser->addItem(text);
    }

    if(action == 1){ //save or add
        ui->comboBox_lTypes_chooser->setCurrentIndex(currentIndex);
    }
    else if(action == 2){ //remove
        int index = ui->comboBox_lTypes_chooser->findText(currentText);

        if(index > -1){
            ui->comboBox_lTypes_chooser->setCurrentIndex(index);
        }
        else if(currentIndex < ui->comboBox_lTypes_chooser->count()){
            ui->comboBox_lTypes_chooser->setCurrentIndex(currentIndex);
        }
    }

    fetchLType(ui->comboBox_lTypes_chooser->currentText());
}

/*!
 \brief

 \fn configuration_widget::fetchLType
 \param id
*/
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

/*!
 \brief

 \fn configuration_widget::populateCoatings
 \param action
*/
void configuration_widget::populateCoatings(int action){
    int currentIndex = ui->comboBox_coatings_chooser->currentIndex();
    QString currentText = ui->comboBox_coatings_chooser->currentText();

    ui->comboBox_coatings_chooser->clear();
    for(unsigned int i = 0; i < configuration->getCoatings().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getCoatings().at(i)->getName());
        ui->comboBox_coatings_chooser->addItem(text);
    }

    if(action == 1){ //save or add
        ui->comboBox_coatings_chooser->setCurrentIndex(currentIndex);
    }
    else if(action == 2){ //remove
        int index = ui->comboBox_coatings_chooser->findText(currentText);

        if(index > -1){
            ui->comboBox_coatings_chooser->setCurrentIndex(index);
        }
        else if(currentIndex < ui->comboBox_coatings_chooser->count()){
            ui->comboBox_coatings_chooser->setCurrentIndex(currentIndex);
        }
    }

    fetchCoating(ui->comboBox_coatings_chooser->currentText());
}

/*!
 \brief

 \fn configuration_widget::fetchCoating
 \param id
*/
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

/*!
 \brief

 \fn configuration_widget::populateEnergizations
 \param action
*/
void configuration_widget::populateEnergizations(int action){
    int currentIndex = ui->comboBox_energizations_chooser->currentIndex();
    QString currentText = ui->comboBox_energizations_chooser->currentText();

    ui->comboBox_energizations_chooser->clear();
    for(unsigned int i = 0; i < configuration->getEnergizations().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getEnergizations().at(i)->getIdentification());
        ui->comboBox_energizations_chooser->addItem(text);
    }

    if(action == 1){ //save or add
        ui->comboBox_energizations_chooser->setCurrentIndex(currentIndex);
    }
    else if(action == 2){ //remove
        int index = ui->comboBox_energizations_chooser->findText(currentText);

        if(index > -1){
            ui->comboBox_energizations_chooser->setCurrentIndex(index);
        }
        else if(currentIndex < ui->comboBox_energizations_chooser->count()){
            ui->comboBox_energizations_chooser->setCurrentIndex(currentIndex);
        }
    }

    fetchEnergization(ui->comboBox_energizations_chooser->currentText());
}

/*!
 \brief

 \fn configuration_widget::fetchEnergization
 \param id
*/
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

/*!
 \brief

 \fn configuration_widget::populateCTypes
 \param action
*/
void configuration_widget::populateCTypes(int action){
    int currentIndex = ui->comboBox_cTypes_chooser->currentIndex();
    QString currentText = ui->comboBox_cTypes_chooser->currentText();

    ui->comboBox_cTypes_chooser->clear();
    for(unsigned int i = 0; i < configuration->getConductorTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getConductorTypes().at(i)->getName());
        ui->comboBox_cTypes_chooser->addItem(text);
    }

    if(action == 1){ //save or add
        ui->comboBox_cTypes_chooser->setCurrentIndex(currentIndex);
    }
    else if(action == 2){ //remove
        int index = ui->comboBox_cTypes_chooser->findText(currentText);

        if(index > -1){
            ui->comboBox_cTypes_chooser->setCurrentIndex(index);
        }
        else if(currentIndex < ui->comboBox_cTypes_chooser->count()){
            ui->comboBox_cTypes_chooser->setCurrentIndex(currentIndex);
        }
    }

    fetchCType(ui->comboBox_cTypes_chooser->currentText());
}

/*!
 \brief

 \fn configuration_widget::fetchCType
 \param id
*/
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

/*!
 \brief

 \fn configuration_widget::populateCbTypes
 \param action
*/
void configuration_widget::populateCbTypes(int action){
    int currentIndex = ui->comboBox_cbTypes_chooser->currentIndex();
    QString currentText = ui->comboBox_cbTypes_chooser->currentText();

    ui->comboBox_cbTypes_chooser->clear();
    for(unsigned int i = 0; i < configuration->getCableTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getCableTypes().at(i)->getName());
        ui->comboBox_cbTypes_chooser->addItem(text);
    }

    if(action == 1){ //save or add
        ui->comboBox_cbTypes_chooser->setCurrentIndex(currentIndex);
    }
    else if(action == 2){ //remove
        int index = ui->comboBox_cbTypes_chooser->findText(currentText);

        if(index > -1){
            ui->comboBox_cbTypes_chooser->setCurrentIndex(index);
        }
        else if(currentIndex < ui->comboBox_cbTypes_chooser->count()){
            ui->comboBox_cbTypes_chooser->setCurrentIndex(currentIndex);
        }
    }

    fetchCbType(ui->comboBox_cbTypes_chooser->currentText());
}

/*!
 \brief

 \fn configuration_widget::fetchCbType
 \param id
*/
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

/*!
 \brief

 \fn configuration_widget::populateComputations
*/
void configuration_widget::populateComputations(){
    ui->checkBox_comp_GPR->setChecked(configuration->getComputations().GPR);
    ui->checkBox_comp_POTENTIAL_SCALAR->setChecked(configuration->getComputations().POTENTIAL_SCALAR);
    ui->checkBox_comp_ELECTRIC->setChecked(configuration->getComputations().ELECTRIC);
    ui->checkBox_comp_GRADIENT_SCALAR->setChecked(configuration->getComputations().GRADIENT_SCALAR);
    ui->checkBox_comp_MAGNETIC->setChecked(configuration->getComputations().MAGNETIC);
    ui->checkBox_comp_VECTOR_POTENTIAL->setChecked(configuration->getComputations().VECTOR_POTENTIAL);
}

/*!
 \brief

 \fn configuration_widget::populateProfiles
 \param action
*/
void configuration_widget::populateProfiles(int action){
    int currentIndex = ui->comboBox_profiles_chooser->currentIndex();
    QString currentText = ui->comboBox_profiles_chooser->currentText();

    ui->comboBox_profiles_chooser->clear();
    for(unsigned int i = 0; i < configuration->getProfiles().size(); i++){
        profile* p = configuration->getProfiles().at(i).get();
        QString text = QString::number(i) + " - Profile(X:" + QString::number(p->start.x) + ", Y:" + QString::number(p->start.y) + ", Z:" + QString::number(p->start.z) + ")";
        ui->comboBox_profiles_chooser->addItem(text);
    }

    if(action == 1){ //save or add
        ui->comboBox_profiles_chooser->setCurrentIndex(currentIndex);
    }
    else if(action == 2){ //remove
        int index = ui->comboBox_profiles_chooser->findText(currentText);

        if(index > -1){
            ui->comboBox_profiles_chooser->setCurrentIndex(index);
        }
        else if(currentIndex < ui->comboBox_profiles_chooser->count()){
            ui->comboBox_profiles_chooser->setCurrentIndex(currentIndex);
        }
    }

    fetchProfile(ui->comboBox_profiles_chooser->currentText());
}

/*!
 \brief

 \fn configuration_widget::fetchProfile
 \param id
*/
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

/*!
 \brief

 \fn configuration_widget::refreshLType
*/
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

/*!
 \brief

 \fn configuration_widget::refreshCoating
*/
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

/*!
 \brief

 \fn configuration_widget::refreshEnergization
*/
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

/*!
 \brief

 \fn configuration_widget::refreshCType
*/
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

/*!
 \brief

 \fn configuration_widget::refreshCbType
*/
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

/*!
 \brief

 \fn configuration_widget::refreshProfile
*/
void configuration_widget::refreshProfile(){
    if(pro){
        ui->pushButton_reset_profile->setEnabled(true);
        if(ui->radioButton_profile_endPts->isChecked()){
            ui->doubleSpinBox_profile_pts_prStep->setEnabled(true);
            ui->doubleSpinBox_profile_pts_ptStep->setEnabled(true);
            ui->groupBox_profile_ptA->setEnabled(true);
            ui->groupBox_profile_ptB->setEnabled(true);
            ui->groupBox_profile_ptC->setEnabled(true);

            //ui->spinBox_number_points->setEnabled(false);
            ui->spinBox_number_profiles->setEnabled(false);
            ui->groupBox_profile_prStart->setEnabled(false);
            ui->groupBox_profile_prStep->setEnabled(false);
            //ui->groupBox_profile_ptStep->setEnabled(false);
        }
        else if(ui->radioButton_profile_steps->isChecked()){
            //ui->spinBox_number_points->setEnabled(true);
            ui->spinBox_number_profiles->setEnabled(true);
            ui->groupBox_profile_prStart->setEnabled(true);
            ui->groupBox_profile_prStep->setEnabled(true);
            //ui->groupBox_profile_ptStep->setEnabled(true);

            ui->doubleSpinBox_profile_pts_prStep->setEnabled(false);
            ui->doubleSpinBox_profile_pts_ptStep->setEnabled(false);
            ui->groupBox_profile_ptA->setEnabled(false);
            ui->groupBox_profile_ptB->setEnabled(false);
            ui->groupBox_profile_ptC->setEnabled(false);
        }
        std::vector<coords> prPts;

        prPts = pro->toCoords();

        if(pro->surface){
            ui->radioButton_pro_surface->setChecked(true);
            ui->radioButton_pro_line->setChecked(false);
            ui->pushButton_profile_genLeft->setText(tr("Generate profile as surface (left-sided)"));
            ui->pushButton_profile_genRight->setText(tr("Generate profile as surface (right-sided)"));
            ui->pushButton_profile_genTwo->setText(tr("Generate profile as surface (two-sided)"));
            ui->groupBox_profile_ptStep->setEnabled(true);
            ui->spinBox_number_points->setEnabled(true);
        }
        else{
            ui->radioButton_pro_surface->setChecked(false);
            ui->radioButton_pro_line->setChecked(true);
            ui->pushButton_profile_genLeft->setText(tr("Generate profile as line (left-sided)"));
            ui->pushButton_profile_genRight->setText(tr("Generate profile as line (right-sided)"));
            ui->pushButton_profile_genTwo->setText(tr("Generate profile as line (two-sided)"));
            ui->groupBox_profile_ptStep->setEnabled(false);
            ui->spinBox_number_points->setEnabled(false);
        }

        ui->doubleSpinBox_profile_ptA_x->setValue(prPts[0].x);
        ui->doubleSpinBox_profile_ptA_y->setValue(prPts[0].y);
        ui->doubleSpinBox_profile_ptA_z->setValue(prPts[0].z);
        ui->doubleSpinBox_profile_ptB_x->setValue(prPts[1].x);
        ui->doubleSpinBox_profile_ptB_y->setValue(prPts[1].y);
        ui->doubleSpinBox_profile_ptB_z->setValue(prPts[1].z);
        ui->doubleSpinBox_profile_ptC_x->setValue(prPts[2].x);
        ui->doubleSpinBox_profile_ptC_y->setValue(prPts[2].y);
        ui->doubleSpinBox_profile_ptC_z->setValue(prPts[2].z);

        ui->doubleSpinBox_profile_pts_ptStep->setValue(pro->ptStep.z);
        ui->doubleSpinBox_profile_pts_prStep->setValue(pro->prStep.y);

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
        ui->pushButton_reset_profile->setEnabled(false);

        ui->spinBox_number_points->setEnabled(false);
        ui->spinBox_number_profiles->setEnabled(false);
        ui->groupBox_profile_prStart->setEnabled(false);
        ui->groupBox_profile_prStep->setEnabled(false);
        ui->groupBox_profile_ptStep->setEnabled(false);

        ui->doubleSpinBox_profile_pts_ptStep->setEnabled(false);
        ui->doubleSpinBox_profile_pts_prStep->setEnabled(false);
        ui->groupBox_profile_ptA->setEnabled(false);
        ui->groupBox_profile_ptB->setEnabled(false);
        ui->groupBox_profile_ptC->setEnabled(false);
    }
}

/*!
 \brief

 \fn configuration_widget::populateConductors
 \param action
*/
void configuration_widget::populateConductors(int action){
    int currentIndex = ui->comboBox_conductors->currentIndex();
    QString currentText = ui->comboBox_conductors->currentText();

    ui->comboBox_conductors->clear();
    for(unsigned int i = 0; i <configuration->getConductors().size(); i++){
        QString text = QString::number(i) + " - Conductor(X:" + QString::number(configuration->getConductors().at(i)->getStartCoords().x) + ", Y:" + QString::number(configuration->getConductors().at(i)->getStartCoords().y) + ", Z:" + QString::number(configuration->getConductors().at(i)->getStartCoords().z) + ")";
        ui->comboBox_conductors->addItem(text);
    }

    if(action == 1){ //save or add
        ui->comboBox_conductors->setCurrentIndex(currentIndex);
    }
    else if(action == 2){ //remove
        int index = ui->comboBox_conductors->findText(currentText);

        if(index > -1){
            ui->comboBox_conductors->setCurrentIndex(index);
        }
        else if(currentIndex < ui->comboBox_conductors->count()){
            ui->comboBox_conductors->setCurrentIndex(currentIndex);
        }
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

/*!
 \brief

 \fn configuration_widget::fetchConductor
 \param id
*/
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

/*!
 \brief

 \fn configuration_widget::refreshConductor
*/
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

/*!
 \brief

 \fn configuration_widget::populateBuildings
 \param action
*/
void configuration_widget::populateBuildings(int action){
    int currentIndex = ui->comboBox_buildings->currentIndex();
    QString currentText = ui->comboBox_buildings->currentText();

    ui->comboBox_buildings->clear();
    for(unsigned int i = 0; i < configuration->getBuildings().size(); i++){
        QString text = QString::number(i) + " - Building( HB: " + QString::number(configuration->getBuildings().at(i)->getHeight()) + " DB: " + QString::number(configuration->getBuildings().at(i)->getDistance()) + " )";
        ui->comboBox_buildings->addItem(text);
    }

    if(action == 1){ //save or add
        ui->comboBox_buildings->setCurrentIndex(currentIndex);
    }
    else if(action == 2){ //remove
        int index = ui->comboBox_buildings->findText(currentText);

        if(index > -1){
            ui->comboBox_buildings->setCurrentIndex(index);
        }
        else if(currentIndex < ui->comboBox_buildings->count()){
            ui->comboBox_buildings->setCurrentIndex(currentIndex);
        }
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

/*!
 \brief

 \fn configuration_widget::fetchBuilding
 \param id
*/
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

/*!
 \brief

 \fn configuration_widget::refreshBuilding
*/
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
        ui->pushButton_add_building->setEnabled(true);
        ui->pushButton_build_duplicate->setEnabled(true);
        ui->pushButton_remove_building->setEnabled(true);
        ui->pushButton_save_building->setEnabled(true);
        ui->pushButton_building_generate->setEnabled(true);
        ui->pushButton_building_clear->setEnabled(true);

        if(!configuration->getBuildingConductors().empty()){
            ui->lineEdit_building_status->setText(tr("Building in config: Yes"));
        }
        else{
            ui->lineEdit_building_status->setText(tr("Building in config: No"));
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

/*!
 \brief

 \fn configuration_widget::refreshPlot
*/
void configuration_widget::refreshPlot(){
    QVector<double> keys, values, keySelected, valueSelected, groundKeys, groundValues;
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
    for(double i = lowX - 1; i <= highX + 1; i+= 0.5){
        groundKeys.push_back(i);
        groundValues.push_back(0);
    }
    ui->cond_plot->xAxis->setRange((lowX - 1), (highX + 1));
    ui->cond_plot->yAxis->setRange((lowY - 1), (highY + 1));
    ui->cond_plot->yAxis->setRangeReversed(true);
    ui->cond_plot->graph(0)->setData(groundKeys, groundValues);
    ui->cond_plot->graph(1)->setData(keys, values);
    ui->cond_plot->graph(2)->setData(keySelected, valueSelected);
    ui->cond_plot->replot();
}

//CONF CONNECTIONS
/*!
 \brief

 \fn configuration_widget::changeConfIdentifier
 \param ident
*/
void configuration_widget::changeConfIdentifier(QString ident){
    configuration->setIdentifier(ident.toStdString());
    configuration->setModified(true);
    refresh();
}

/*!
 \brief

 \fn configuration_widget::changeConfUnits
 \param units
*/
void configuration_widget::changeConfUnits(QString units){
    configuration->setUnits(units.toStdString());
    configuration->setModified(true);
    refresh();
}

/*!
 \brief

 \fn configuration_widget::changeConfFrequency
 \param frequency
*/
void configuration_widget::changeConfFrequency(QString frequency){
    configuration->setFrequency(frequency.toStdString());
    configuration->setModified(true);
    refresh();
}

/*!
 \brief

 \fn configuration_widget::saveConfig
*/
void configuration_widget::saveConfig(){
    defParent->saveConfig();
}

//COND CONNECTIONS
/*!
 \brief

 \fn configuration_widget::newCond
*/
void configuration_widget::newCond(){
    conductor.reset(new Conductor());
    if(conductor->getId() < 0){
        conductor->setId(configuration->componentIdGenerator());
    }
    configuration->addConductor(conductor);
    configuration->setModified(true);
    populateConductors();
}

/*!
 \brief

 \fn configuration_widget::duplicateCond
*/
void configuration_widget::duplicateCond(){
    if(conductor){
        std::shared_ptr<Conductor> cond;
        cond.reset(new Conductor(conductor.get()));
        cond->setId(configuration->componentIdGenerator());
        configuration->addConductor(cond);
        configuration->setModified(true);
        populateConductors(1);
    }
}

/*!
 \brief

 \fn configuration_widget::removeCond
*/
void configuration_widget::removeCond(){
    configuration->removeConductor(conductor);
    configuration->setModified(true);
    conductor.reset();
    populateConductors(2);
}

/*!
 \brief

 \fn configuration_widget::saveCond
*/
void configuration_widget::saveCond(){
    int result = configuration->replaceConductor(conductor);
    if(result == 1){
        if(conductor->getId() < 0) conductor->setId(configuration->componentIdGenerator());
        configuration->addConductor(conductor);
    }
    configuration->setModified(true);
    populateConductors(1);
}

/*!
 \brief

 \fn configuration_widget::changeCondCbType
 \param index
*/
void configuration_widget::changeCondCbType(int index){
    if(conductor && index > 0){
        conductor->setCableType(configuration->getCableTypes().at(index-1));
        refresh();
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeCondCoat
 \param index
*/
void configuration_widget::changeCondCoat(int index){
    if(conductor && index > 0){
        conductor->setCoating(configuration->getCoatings().at(index-1));
        refresh();
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeCondCType
 \param index
*/
void configuration_widget::changeCondCType(int index){
    if(conductor && index > 0){
        conductor->setConductorType(configuration->getConductorTypes().at(index-1));
        refresh();
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeCondEner
 \param index
*/
void configuration_widget::changeCondEner(int index){
    if(conductor && index > 0){
        conductor->setEnergization(configuration->getEnergizations().at(index-1));
        refresh();
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeCondLType
 \param index
*/
void configuration_widget::changeCondLType(int index){
    if(conductor && index > 0){
        conductor->setLeadType(configuration->getLeadTypes().at(index-1));
        refresh();
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeCondRadius
 \param value
*/
void configuration_widget::changeCondRadius(double value){
    if(conductor){
        conductor->setRadius(value);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeCondStartX
 \param value
*/
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

/*!
 \brief

 \fn configuration_widget::changeCondStartY
 \param value
*/
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

/*!
 \brief

 \fn configuration_widget::changeCondStartZ
 \param value
*/
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

/*!
 \brief

 \fn configuration_widget::changeCondEndX
 \param value
*/
void configuration_widget::changeCondEndX(double value){
    if(conductor){
        coords end;
        end = conductor->getEndCoords();
        end.x = value;
        conductor->setEndCoords(end);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeCondEndY
 \param value
*/
void configuration_widget::changeCondEndY(double value){
    if(conductor){
        coords end;
        end = conductor->getEndCoords();
        end.y = value;
        conductor->setEndCoords(end);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeCondEndZ
 \param value
*/
void configuration_widget::changeCondEndZ(double value){
    if(conductor){
        coords end;
        end = conductor->getEndCoords();
        end.z = value;
        conductor->setEndCoords(end);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::batchChangeCondHeight
*/
void configuration_widget::batchChangeCondHeight(){
    double newHeight = QInputDialog::getDouble(this, tr("Change height by.."), tr("Input height difference (-/+)"), 0, -9999.0, 9999.0, 2);
    for(std::shared_ptr<Conductor> cond : configuration->getConductors()){
        coords start, end;
        start = cond->getStartCoords();
        end = cond->getEndCoords();
        start.z += newHeight;
        end.z += newHeight;
        cond->setCoords(start, end);
    }
    configuration->setModified(true);
    populateConductors(1);
}

/*!
 \brief

 \fn configuration_widget::multiCondDialog
*/
void configuration_widget::multiCondDialog(){
    if(configuration){
        MultiConductorDialog* multiDiag = new MultiConductorDialog(this, configuration);
        multiDiag->exec();
        if(multiDiag->isComplete()){
            for(std::shared_ptr<Conductor> cond : multiDiag->getConductors()){
                cond->setId(configuration->componentIdGenerator());
                configuration->addConductor(cond);
            }
            populateConductors(1);
        }
    }
}

//BUILD CONNECTIONS

/*!
 \brief

 \fn configuration_widget::newBuilding
*/
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
        QMessageBox::critical(this, tr("Failure"), tr("There are missing default components in the configuration."));
    }
}

/*!
 \brief

 \fn configuration_widget::duplicateBuilding
*/
void configuration_widget::duplicateBuilding(){
    if(building){
        std::shared_ptr<Building> build;
        build.reset(new Building(building.get()));
        build->setId(configuration->componentIdGenerator());
        configuration->addBuilding(build);
        configuration->setModified(true);
        populateBuildings(1);
    }
}

/*!
 \brief

 \fn configuration_widget::removeBuilding
*/
void configuration_widget::removeBuilding(){
    configuration->removeBuilding(building);
    configuration->setModified(true);
    building.reset();
    populateBuildings(2);
}

/*!
 \brief

 \fn configuration_widget::saveBuilding
*/
void configuration_widget::saveBuilding(){
    int result = configuration->replaceBuilding(building);
    if(result == 1){
        if(building->getId() < 0) building->setId(configuration->componentIdGenerator());
        configuration->addBuilding(building);
    }
    configuration->setModified(true);
    populateBuildings(1);
}

/*!
 \brief

 \fn configuration_widget::changeBuildFaces
 \param index
*/
void configuration_widget::changeBuildFaces(QString index){
    if(building){
        int faces = index.toInt();
        building->setFaces(faces);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeBuildHeight
 \param value
*/
void configuration_widget::changeBuildHeight(int value){
    if(building){
        building->setHeight(value);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeBuildStep
 \param index
*/
void configuration_widget::changeBuildStep(QString index){
    if(building){
        index.truncate(index.indexOf(" "));
        index.replace(",", ".");
        double step = index.toDouble();
        building->setStep(step);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeBuildDistance
 \param value
*/
void configuration_widget::changeBuildDistance(int value){
    if(building){
        building->setDistance(value);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeBuildLength
 \param value
*/
void configuration_widget::changeBuildLength(int value){
    if(building){
        building->setLength(value);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeBuildWidth
 \param value
*/
void configuration_widget::changeBuildWidth(int value){
    if(building){
        building->setWidth(value);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeBuildRadius
 \param value
*/
void configuration_widget::changeBuildRadius(double value){
    if(building){
        building->setRadius(value);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeBuildCbType
 \param index
*/
void configuration_widget::changeBuildCbType(int index){
    if(building && index >= 0){
        building->setCableType(configuration->getCableTypes().at(index));
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeBuildCoat
 \param index
*/
void configuration_widget::changeBuildCoat(int index){
    if(building && index >= 0){
        building->setCoating(configuration->getCoatings().at(index));
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeBuildCType
 \param index
*/
void configuration_widget::changeBuildCType(int index){
    if(building && index >= 0){
        building->setConductorType(configuration->getConductorTypes().at(index));
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeBuildEner
 \param index
*/
void configuration_widget::changeBuildEner(int index){
    if(building && index >= 0){
        building->setEnergization(configuration->getEnergizations().at(index));
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeBuildLType
 \param index
*/
void configuration_widget::changeBuildLType(int index){
    if(building && index >= 0){
        building->setLeadType(configuration->getLeadTypes().at(index));
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::generateBuildingConductors
*/
void configuration_widget::generateBuildingConductors(){
    if(building){
        configuration->updateBuildingConductors(building);
        QMessageBox::about(this, tr("Success"), tr("Building conductors generated in configuration. You might want to update your profile."));
        populateBuildings(1);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::clearBuildingConductors
*/
void configuration_widget::clearBuildingConductors(){
    if(building){
        configuration->clearBuildingConductors();
        QMessageBox::about(this, tr("Success"), tr("Building conductors removed from configuration. You might want to update your profile."));
        populateBuildings(1);
        configuration->setModified(true);
    }
}

//LTYPE CONNECTIONS
/*!
 \brief

 \fn configuration_widget::changeLTypeName
 \param text
*/
void configuration_widget::changeLTypeName(QString text){
    if(lType){
        lType->setName(text.toStdString());
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::newLType
*/
void configuration_widget::newLType(){
    lType.reset(new LeadType());
    if(lType->getId() < 0) lType->setId(configuration->componentIdGenerator());
    configuration->addLeadType(lType);
    configuration->setModified(true);
    populateLTypes();
    populateConductors();
}

/*!
 \brief

 \fn configuration_widget::duplicateLType
*/
void configuration_widget::duplicateLType(){
    if(lType){
        std::shared_ptr<LeadType> lt;
        lt.reset(new LeadType(lType.get()));
        lt->setId(configuration->componentIdGenerator());
        configuration->addLeadType(lt);
        configuration->setModified(true);
        populateLTypes(1);
    }
}

/*!
 \brief

 \fn configuration_widget::removeLType
*/
void configuration_widget::removeLType(){
    int result = configuration->removeLeadType(lType);
    if(result == 1){
        QMessageBox::critical(this, tr("Failure"), tr("This LeadType is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration."));
    }
    else{
        configuration->setModified(true);
        lType.reset();
        populateLTypes(2);
    }
}

/*!
 \brief

 \fn configuration_widget::saveLType
*/
void configuration_widget::saveLType(){
    int result = configuration->replaceLeadType(lType);
    if(result == 1){
        if(lType->getId() < 0) lType->setId(configuration->componentIdGenerator());
        configuration->addLeadType(lType);
    }
    configuration->setModified(true);
    populateLTypes(1);
}

//COATING CONNECTIONS
/*!
 \brief

 \fn configuration_widget::changeCoatName
 \param text
*/
void configuration_widget::changeCoatName(QString text){
    if(coat){
        coat->setName(text.toStdString());
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::newCoat
*/
void configuration_widget::newCoat(){
    coat.reset(new Coating());
    if(coat->getId() < 0) coat->setId(configuration->componentIdGenerator());
    configuration->addCoating(coat);
    configuration->setModified(true);
    populateCoatings();
    populateConductors();
}

/*!
 \brief

 \fn configuration_widget::duplicateCoat
*/
void configuration_widget::duplicateCoat(){
    if(coat){
        std::shared_ptr<Coating> co;
        co.reset(new Coating(coat.get()));
        co->setId(configuration->componentIdGenerator());
        configuration->addCoating(co);
        configuration->setModified(true);
        populateCoatings(1);
    }
}

/*!
 \brief

 \fn configuration_widget::removeCoat
*/
void configuration_widget::removeCoat(){
    int result = configuration->removeCoating(coat);
    if(result == 1){
        QMessageBox::critical(this, tr("Failure"), tr("This Coating is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration."));
    }
    else{
        configuration->setModified(true);
        coat.reset();
        populateCoatings(2);
    }
}

/*!
 \brief

 \fn configuration_widget::saveCoat
*/
void configuration_widget::saveCoat(){
    int result = configuration->replaceCoating(coat);
    if(result == 1){
        if(coat->getId() < 0) coat->setId(configuration->componentIdGenerator());
        configuration->addCoating(coat);
    }
    configuration->setModified(true);
    populateCoatings(1);
}

//ENERG CONNECTIONS
/*!
 \brief

 \fn configuration_widget::changeEnerFreq
 \param text
*/
void configuration_widget::changeEnerFreq(QString text){
    if(ener){
        ener->setFrequency(text.toStdString());
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeEnerIdent
 \param text
*/
void configuration_widget::changeEnerIdent(QString text){
    if(ener){
        ener->setIdentification(text.toStdString());
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeEnerType
 \param text
*/
void configuration_widget::changeEnerType(QString text){
    if(ener){
        ener->setType(text.toStdString());
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeEnerMag
 \param i
*/
void configuration_widget::changeEnerMag(int i){
    if(ener){
        ener->setMagnitude(i);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeEnerAng
 \param d
*/
void configuration_widget::changeEnerAng(double d){
    if(ener){
        ener->setAngle(d);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::newEner
*/
void configuration_widget::newEner(){
    ener.reset(new Energization());
    if(ener->getId() < 0) ener->setId(configuration->componentIdGenerator());
    configuration->addEnergization(ener);
    configuration->setModified(true);
    populateEnergizations();
    populateConductors();
}

/*!
 \brief

 \fn configuration_widget::duplicateEner
*/
void configuration_widget::duplicateEner(){
    if(ener){
        std::shared_ptr<Energization> en;
        en.reset(new Energization(ener.get()));
        en->setId(configuration->componentIdGenerator());
        configuration->addEnergization(en);
        configuration->setModified(true);
        populateEnergizations(1);
    }
}

/*!
 \brief

 \fn configuration_widget::removeEner
*/
void configuration_widget::removeEner(){
    int result = configuration->removeEnergization(ener);
    if(result == 1){
        QMessageBox::critical(this, tr("Failure"), tr("This Energization is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration."));
    }
    else{
        configuration->setModified(true);
        ener.reset();
        populateEnergizations(2);
    }
}

/*!
 \brief

 \fn configuration_widget::saveEner
*/
void configuration_widget::saveEner(){
    int result = configuration->replaceEnergization(ener);
    if(result == 1){
        if(ener->getId() < 0) ener->setId(configuration->componentIdGenerator());
        configuration->addEnergization(ener);
    }
    configuration->setModified(true);
    populateEnergizations(1);
}

//CTYPE CONNECTIONS
/*!
 \brief

 \fn configuration_widget::changeCTypeName
 \param text
*/
void configuration_widget::changeCTypeName(QString text){
    if(cType){
        cType->setName(text.toStdString());
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeCTypeType
 \param text
*/
void configuration_widget::changeCTypeType(QString text){
    if(cType){
        cType->setType(text.toStdString());
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeCTypePerm
 \param d
*/
void configuration_widget::changeCTypePerm(double d){
    if(cType){
        cType->setPermeability(d);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeCTypeRes
 \param d
*/
void configuration_widget::changeCTypeRes(double d){
    if(cType){
        cType->setResistivity(d);
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::newCType
*/
void configuration_widget::newCType(){
    cType.reset(new ConductorType());
    if(cType->getId() < 0) cType->setId(configuration->componentIdGenerator());
    configuration->addConductorType(cType);
    configuration->setModified(true);
    populateCTypes();
    populateConductors();
}

/*!
 \brief

 \fn configuration_widget::duplicateCType
*/
void configuration_widget::duplicateCType(){
    if(cType){
        std::shared_ptr<ConductorType> ct;
        ct.reset(new ConductorType(cType.get()));
        ct->setId(configuration->componentIdGenerator());
        configuration->addConductorType(ct);
        configuration->setModified(true);
        populateCTypes(1);
    }
}

/*!
 \brief

 \fn configuration_widget::removeCType
*/
void configuration_widget::removeCType(){
    int result = configuration->removeConductorType(cType);
    if(result == 1){
        QMessageBox::critical(this, tr("Failure"), tr("This ConductorType is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration."));
    }
    else{
        configuration->setModified(true);
        cType.reset();
        populateCTypes(2);
    }
}

/*!
 \brief

 \fn configuration_widget::saveCType
*/
void configuration_widget::saveCType(){
    int result = configuration->replaceConductorType(cType);
    if(result == 1){
        if(cType->getId() < 0) cType->setId(configuration->componentIdGenerator());
        configuration->addConductorType(cType);
    }
    configuration->setModified(true);
    populateCTypes(1);
}

//CBTYPE CONNECTIONS
/*!
 \brief

 \fn configuration_widget::changeCbTypeName
 \param text
*/
void configuration_widget::changeCbTypeName(QString text){
    if(cbType){
        cbType->setName(text.toStdString());
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::newCbType
*/
void configuration_widget::newCbType(){
    cbType.reset(new CableType());
    if(cbType->getId() < 0) cbType->setId(configuration->componentIdGenerator());
    configuration->addCableType(cbType);
    configuration->setModified(true);
    populateCbTypes();
    populateConductors();
}

/*!
 \brief

 \fn configuration_widget::duplicateCbType
*/
void configuration_widget::duplicateCbType(){
    if(cbType){
        std::shared_ptr<CableType> cb;
        cb.reset(new CableType(cbType.get()));
        cb->setId(configuration->componentIdGenerator());
        configuration->addCableType(cb);
        configuration->setModified(true);
        populateCbTypes(1);
    }
}

/*!
 \brief

 \fn configuration_widget::removeCbType
*/
void configuration_widget::removeCbType(){
    int result = configuration->removeCableType(cbType);
    if(result == 1){
        QMessageBox::critical(this, tr("Failure"), tr("This CableType is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration."));
    }
    else{
        configuration->setModified(true);
        cbType.reset();
        populateCbTypes(2);
    }
}

/*!
 \brief

 \fn configuration_widget::saveCbType
*/
void configuration_widget::saveCbType(){
    int result = configuration->replaceCableType(cbType);
    if(result == 1){
        if(cbType->getId() < 0) cbType->setId(configuration->componentIdGenerator());
        configuration->addCableType(cbType);
        configuration->setModified(true);
    }
    populateCbTypes(1);
}

//PROFILE CONNECTIONS
/*!
 \brief

 \fn configuration_widget::changeProNumPt
 \param i
*/
void configuration_widget::changeProNumPt(int i){
    if(pro){
        pro->ptNum = i;
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeProNumPr
 \param i
*/
void configuration_widget::changeProNumPr(int i){
    if(pro){
        pro->prNum = i;
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeProPtStepX
 \param d
*/
void configuration_widget::changeProPtStepX(double d){
    if(pro){
        pro->ptStep.x = d;
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeProPtStepY
 \param d
*/
void configuration_widget::changeProPtStepY(double d){
    if(pro){
        pro->ptStep.y = d;
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeProPtStepZ
 \param d
*/
void configuration_widget::changeProPtStepZ(double d){
    if(pro){
        pro->ptStep.z = d;
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeProStartX
 \param d
*/
void configuration_widget::changeProStartX(double d){
    if(pro){
        pro->start.x = d;
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeProStartY
 \param d
*/
void configuration_widget::changeProStartY(double d){
    if(pro){
        pro->start.y = d;
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeProStartZ
 \param d
*/
void configuration_widget::changeProStartZ(double d){
    if(pro){
        pro->start.z = d;
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeProPrStepX
 \param d
*/
void configuration_widget::changeProPrStepX(double d){
    if(pro){
        pro->prStep.x = d;
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeProPrStepY
 \param d
*/
void configuration_widget::changeProPrStepY(double d){
    if(pro){
        pro->prStep.y = d;
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::changeProPrStepZ
 \param d
*/
void configuration_widget::changeProPrStepZ(double d){
    if(pro){
        pro->prStep.z = d;
        configuration->setModified(true);
    }
}

/*!
 \brief

 \fn configuration_widget::removePro
*/
void configuration_widget::resetPro(){
    configuration->setModified(true);
    pro.reset(new profile());
    if(pro->id < 0) pro->id = configuration->componentIdGenerator();
    configuration->replaceProfile(pro);
    populateProfiles();
}

void configuration_widget::changeProSetup(){
    if(ui->radioButton_pro_surface->isChecked()){
        if(!pro->surface){
            pro->surface = true;
            ui->pushButton_profile_genLeft->setText(tr("Generate profile as surface (left-sided)"));
            ui->pushButton_profile_genRight->setText(tr("Generate profile as surface (right-sided)"));
            ui->pushButton_profile_genTwo->setText(tr("Generate profile as surface (two-sided)"));
            ui->groupBox_profile_ptStep->setEnabled(true);
            ui->spinBox_number_points->setEnabled(true);
        }
    }
    else if(ui->radioButton_pro_line->isChecked()){
        if(pro->surface){
            pro->surface = false;
            ui->pushButton_profile_genLeft->setText(tr("Generate profile as line (left-sided)"));
            ui->pushButton_profile_genRight->setText(tr("Generate profile as line (right-sided)"));
            ui->pushButton_profile_genTwo->setText(tr("Generate profile as line (two-sided)"));
            ui->groupBox_profile_ptStep->setEnabled(false);
            ui->spinBox_number_points->setEnabled(false);
        }
    }
}

/*!
 \brief

 \fn configuration_widget::savePro
*/
void configuration_widget::savePro(){
    if(pro->id < 0) pro->id = configuration->componentIdGenerator();
    if(ui->radioButton_profile_steps->isChecked()){
        //configuration->removeProfile(pro);
        //configuration->addProfile(pro);
        configuration->replaceProfile(pro);
        configuration->setModified(true);
    }
    else if(ui->radioButton_profile_endPts->isChecked()){
        coords ptA, ptB, ptC;
        double prStep, ptStep;
        ptA.x = ui->doubleSpinBox_profile_ptA_x->value();
        ptA.y = ui->doubleSpinBox_profile_ptA_y->value();
        ptA.z = ui->doubleSpinBox_profile_ptA_z->value();
        ptB.x = ui->doubleSpinBox_profile_ptB_x->value();
        ptB.y = ui->doubleSpinBox_profile_ptB_y->value();
        ptB.z = ui->doubleSpinBox_profile_ptB_z->value();
        ptC.x = ui->doubleSpinBox_profile_ptC_x->value();
        ptC.y = ui->doubleSpinBox_profile_ptC_y->value();
        ptC.z = ui->doubleSpinBox_profile_ptC_z->value();
        prStep = ui->doubleSpinBox_profile_pts_prStep->value();
        ptStep = ui->doubleSpinBox_profile_pts_ptStep->value();

        pro->fromCoords(ptA, ptB, ptC, ptStep, prStep);

        configuration->removeProfile(pro);
        configuration->addProfile(pro);
        configuration->setModified(true);
    }
    populateProfiles(1);
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
/*!
 \brief

 \fn configuration_widget::changeComputations
 \param i
*/
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

/*!
 \brief

 \fn configuration_widget::refreshConfSettings
*/
void configuration_widget::refreshConfSettings(){
    ui->lineEdit_settings_identifier->setText(QString::fromStdString(configuration->getIdentifier()));

    if(configuration->getUnits() == "Metric") ui->comboBox_settings_units->setCurrentIndex(0);
    else ui->comboBox_settings_units->setCurrentIndex(1);

    if(configuration->getFrequency() == "AC") ui->comboBox_settings_frequency->setCurrentIndex(0);
    else ui->comboBox_settings_frequency->setCurrentIndex(1);
}

/*!
 \brief

 \fn configuration_widget::generateProRight
*/
void configuration_widget::generateProRight(){
    double step = QInputDialog::getDouble(this, tr("Input profile step value"), tr("Input the step value for the generated profile."), 0.25, -50, 50, 2);
    double height = 1;
    if(!pro->surface){
        height = QInputDialog::getDouble(this, tr("Input line height value"), tr("Input the line height value for the generated profile."), -1, -5000, 5000, 2);
    }
    int result = configuration->generateProfile(false, true, step, pro->surface, height);
    populateProfiles(0);

    switch(result){
        case 0:
            QMessageBox::about(this, tr("Success"), tr("Profile generated."));
            break;
        case 1:
            QMessageBox::critical(this, tr("Failure"), tr("No conductors."));
            break;
        case 2:
            QMessageBox::critical(this, tr("Failure"), tr("Invalid building placement."));
            break;
        case 3:
            QMessageBox::critical(this, tr("Failure"), tr("Conductors too close to building."));
            break;
        default:
            QMessageBox::critical(this, tr("Failure"), tr("Something went wrong."));
            break;
    }
}

/*!
 \brief

 \fn configuration_widget::generateProLeft
*/
void configuration_widget::generateProLeft(){
    double step = QInputDialog::getDouble(this, tr("Input profile step value"), tr("Input the step value for the generated profile."), 0.25, -50, 50, 2);
    double height = 1;
    if(!pro->surface){
        height = QInputDialog::getDouble(this, tr("Input line height value"), tr("Input the line height value for the generated profile."), -1, -5000, 5000, 2);
    }
    int result = configuration->generateProfile(false, false, step, pro->surface, height);
    populateProfiles(0);

    switch(result){
        case 0:
            QMessageBox::about(this, tr("Success"), tr("Profile generated."));
            break;
        case 1:
            QMessageBox::critical(this, tr("Failure"), tr("No conductors."));
            break;
        case 2:
            QMessageBox::critical(this, tr("Failure"), tr("Invalid building placement."));
            break;
        case 3:
            QMessageBox::critical(this, tr("Failure"), tr("Conductors too close to building."));
            break;
        default:
            QMessageBox::critical(this, tr("Failure"), tr("Something went wrong."));
            break;
    }
}

/*!
 \brief

 \fn configuration_widget::generateProTwo
*/
void configuration_widget::generateProTwo(){
    double step = QInputDialog::getDouble(this, tr("Input profile step value"), tr("Input the step value for the generated profile."), 0.25, -50, 50, 2);
    double height = 1;
    if(!pro->surface){
        height = QInputDialog::getDouble(this, tr("Input line height value"), tr("Input the line height value for the generated profile."), -1, -5000, 5000, 2);
    }
    int result = configuration->generateProfile(true, true, step, pro->surface, height);
    populateProfiles(0);

    switch(result){
        case 0:
            QMessageBox::about(this, tr("Success"), tr("Profile generated."));
            break;
        case 1:
            QMessageBox::critical(this, tr("Failure"), tr("No conductors."));
            break;
        case 2:
            QMessageBox::critical(this, tr("Failure"), tr("Invalid building placement."));
            break;
        case 3:
            QMessageBox::critical(this, tr("Failure"), tr("Conductors too close to building."));
            break;
        default:
            QMessageBox::critical(this, tr("Failure"), tr("Something went wrong."));
            break;
    }
}

void configuration_widget::fetchPage(int i){
    switch(i){
        case 0:
            ui->stackedWidget_config->setCurrentIndex(0);
            break;
        case 1:
            ui->stackedWidget_config->setCurrentIndex(5);
            break;
        case 2:
            ui->stackedWidget_config->setCurrentIndex(6);
            break;
        case 3:
            ui->stackedWidget_config->setCurrentIndex(1);
            break;
        case 4:
            ui->stackedWidget_config->setCurrentIndex(2);
            break;
        case 5:
            ui->stackedWidget_config->setCurrentIndex(9);
            break;
        case 6:
            ui->stackedWidget_config->setCurrentIndex(8);
            break;
        case 7:
            ui->stackedWidget_config->setCurrentIndex(3);
            break;
        case 8:
            ui->stackedWidget_config->setCurrentIndex(4);
            break;
        case 9:
            ui->stackedWidget_config->setCurrentIndex(7);
            break;
    }
}
