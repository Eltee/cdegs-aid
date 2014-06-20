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
    populateFields();
    ui->stackedWidget_config->setCurrentIndex(0);
    connectSlots();
    initPlot();
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

    ui->cond_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->cond_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QColor(0, 102, 255), 10));
    ui->cond_plot->graph(0)->setPen(QPen(QColor(120, 120, 120), 2));
    ui->cond_plot->graph(0)->setName("Conductors");
    ui->cond_plot->graph(0)->setAntialiased(true);

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
    ui->cond_plot->yAxis->setRange(0, 10);
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

    //COND CONNECTIONS
    QObject::connect(ui->pushButton_cond_add, SIGNAL(clicked()),
                     this, SLOT(newCond()));

    QObject::connect(ui->pushButton_cond_remove, SIGNAL(clicked()),
                     this, SLOT(removeCond()));


    //BUILD CONNECTIONS

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

    QObject::connect(ui->pushButton_remove_lType, SIGNAL(clicked()),
                     this, SLOT(removeLType()));

    QObject::connect(ui->pushButton_save_lType, SIGNAL(clicked()),
                     this, SLOT(saveLType()));

    //COATING CONNECTIONS
    QObject::connect(ui->lineEdit_coating_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCoatName(QString)));

    QObject::connect(ui->pushButton_new_coating, SIGNAL(clicked()),
                     this, SLOT(newCoat()));

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

    QObject::connect(ui->pushButton_remove_cType, SIGNAL(clicked()),
                     this, SLOT(removeCType()));

    QObject::connect(ui->pushButton_save_cType, SIGNAL(clicked()),
                     this, SLOT(saveCType()));

    //CBTYPE CONNECTIONS
    QObject::connect(ui->lineEdit_cbType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCbTypeName(QString)));

    QObject::connect(ui->pushButton_new_cbType, SIGNAL(clicked()),
                     this, SLOT(newCbType()));

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

    QObject::connect(ui->pushButton_remove_profile, SIGNAL(clicked()),
                     this, SLOT(removePro()));

    QObject::connect(ui->pushButton_save_profile, SIGNAL(clicked()),
                     this, SLOT(savePro()));

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

    //COND CONNECTIONS
    QObject::disconnect(ui->pushButton_cond_add, SIGNAL(clicked()),
                     this, SLOT(newCond()));

    QObject::disconnect(ui->pushButton_cond_remove, SIGNAL(clicked()),
                     this, SLOT(removeCond()));

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

    QObject::disconnect(ui->pushButton_remove_lType, SIGNAL(clicked()),
                     this, SLOT(removeLType()));

    QObject::disconnect(ui->pushButton_save_lType, SIGNAL(clicked()),
                     this, SLOT(saveLType()));

    //COATING CONNECTIONS
    QObject::disconnect(ui->lineEdit_coating_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCoatName(QString)));

    QObject::disconnect(ui->pushButton_new_coating, SIGNAL(clicked()),
                     this, SLOT(newCoat()));

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

    QObject::disconnect(ui->pushButton_remove_cType, SIGNAL(clicked()),
                     this, SLOT(removeCType()));

    QObject::disconnect(ui->pushButton_save_cType, SIGNAL(clicked()),
                     this, SLOT(saveCType()));

    //CBTYPE CONNECTIONS
    QObject::disconnect(ui->lineEdit_cbType_name, SIGNAL(textChanged(QString)),
                     this, SLOT(changeCbTypeName(QString)));

    QObject::disconnect(ui->pushButton_new_cbType, SIGNAL(clicked()),
                     this, SLOT(newCbType()));

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

    QObject::disconnect(ui->pushButton_remove_profile, SIGNAL(clicked()),
                     this, SLOT(removePro()));

    QObject::disconnect(ui->pushButton_save_profile, SIGNAL(clicked()),
                     this, SLOT(savePro()));

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
}

void configuration_widget::populateLTypes(){
    ui->comboBox_lTypes_chooser->clear();
    for(int i = 0; i < configuration->getLeadTypes().size(); i++){
        QString text = QString::number(i-1) + " - " + QString::fromStdString(configuration->getLeadTypes().at(i-1)->getName());
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
}

void configuration_widget::populateCoatings(){
    ui->comboBox_coatings_chooser->clear();
    for(int i = 0; i < configuration->getCoatings().size(); i++){
        QString text = QString::number(i-1) + " - " + QString::fromStdString(configuration->getCoatings().at(i-1)->getName());
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
}

void configuration_widget::populateEnergizations(){
    ui->comboBox_energizations_chooser->clear();
    for(int i = 0; i < configuration->getEnergizations().size(); i++){
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
}

void configuration_widget::populateCTypes(){
    ui->comboBox_cTypes_chooser->clear();
    for(int i = 0; i < configuration->getConductorTypes().size(); i++){
        QString text = QString::number(i-1) + " - " + QString::fromStdString(configuration->getConductorTypes().at(i-1)->getName());
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
}

void configuration_widget::populateCbTypes(){
    ui->comboBox_cbTypes_chooser->clear();
    for(int i = 0; i < configuration->getCableTypes().size(); i++){
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
    for(int i = 1; i <= configuration->getProfiles().size(); i++){
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
}

void configuration_widget::refreshLType(){
    if(lType){
        ui->lineEdit_lType_name->setText(QString::fromStdString(lType->getName()));
        if(lType->isLocked()){
            ui->pushButton_remove_lType->setDisabled(true);
            ui->lineEdit_lType_name->setDisabled(true);
        }
        else{
            ui->pushButton_remove_lType->setEnabled(true);
            ui->lineEdit_lType_name->setEnabled(true);
        }
    }
    else{
        ui->pushButton_remove_lType->setDisabled(true);
        ui->lineEdit_lType_name->setDisabled(true);
    }
}

void configuration_widget::refreshCoating(){
    if(coat){
        ui->lineEdit_coating_name->setText(QString::fromStdString(coat->getName()));
        if(!coat->isLocked()){
            ui->pushButton_remove_coating->setEnabled(true);
            ui->lineEdit_coating_name->setEnabled(true);
        }
        else{
            ui->pushButton_remove_coating->setDisabled(true);
            ui->lineEdit_coating_name->setDisabled(true);
        }
    }
    else{
        ui->pushButton_remove_coating->setDisabled(true);
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
            ui->comboBox_energizations_frequency->setEnabled(true);
            ui->lineEdit_energization_identification->setEnabled(true);
            ui->lineEdit_energization_type->setEnabled(true);
            ui->spinBox_energization_magnitude->setEnabled(true);
            ui->doubleSpinBox_energization_angle->setEnabled(true);
        }
        else{
            ui->pushButton_remove_energization->setDisabled(true);
            ui->comboBox_energizations_frequency->setDisabled(true);
            ui->lineEdit_energization_identification->setDisabled(true);
            ui->lineEdit_energization_type->setDisabled(true);
            ui->spinBox_energization_magnitude->setDisabled(true);
            ui->doubleSpinBox_energization_angle->setDisabled(true);
        }
    }
    else{
        ui->pushButton_remove_energization->setDisabled(true);
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
            ui->lineEdit_cType_name->setEnabled(true);
            ui->lineEdit_cType_type->setEnabled(true);
            ui->doubleSpinBox_cType_permeability->setEnabled(true);
            ui->doubleSpinBox_cType_resistivity->setEnabled(true);
        }
        else{
            ui->pushButton_remove_cType->setDisabled(true);
            ui->lineEdit_cType_name->setDisabled(true);
            ui->lineEdit_cType_type->setDisabled(true);
            ui->doubleSpinBox_cType_permeability->setDisabled(true);
            ui->doubleSpinBox_cType_resistivity->setDisabled(true);
        }
    }
    else{
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
            ui->lineEdit_cbType_name->setEnabled(true);
        }
        else{
            ui->pushButton_remove_cbType->setDisabled(true);
            ui->lineEdit_cbType_name->setDisabled(true);
        }
    }
    else{
        ui->pushButton_remove_cbType->setDisabled(true);
        ui->lineEdit_cbType_name->setDisabled(true);
    }
}

void configuration_widget::refreshProfile(){
    if(pro){
        ui->pushButton_remove_profile->setEnabled(true);
        ui->spinBox_number_points->setEnabled(true);
        ui->spinBox_number_profiles->setEnabled(true);
        ui->doubleSpinBox_point_step_x->setEnabled(true);
        ui->doubleSpinBox_point_step_y->setEnabled(true);
        ui->doubleSpinBox_point_step_z->setEnabled(true);
        ui->doubleSpinBox_profile_start_x->setEnabled(true);
        ui->doubleSpinBox_profile_start_y->setEnabled(true);
        ui->doubleSpinBox_profile_start_z->setEnabled(true);
        ui->doubleSpinBox_profile_step_x->setEnabled(true);
        ui->doubleSpinBox_profile_step_y->setEnabled(true);
        ui->doubleSpinBox_profile_step_z->setEnabled(true);
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
        ui->pushButton_remove_profile->setDisabled(true);
        ui->spinBox_number_points->setDisabled(true);
        ui->spinBox_number_profiles->setDisabled(true);
        ui->doubleSpinBox_point_step_x->setDisabled(true);
        ui->doubleSpinBox_point_step_y->setDisabled(true);
        ui->doubleSpinBox_point_step_z->setDisabled(true);
        ui->doubleSpinBox_profile_start_x->setDisabled(true);
        ui->doubleSpinBox_profile_start_y->setDisabled(true);
        ui->doubleSpinBox_profile_start_z->setDisabled(true);
        ui->doubleSpinBox_profile_step_x->setDisabled(true);
        ui->doubleSpinBox_profile_step_y->setDisabled(true);
        ui->doubleSpinBox_profile_step_z->setDisabled(true);
    }
}

void configuration_widget::populateConductors(){
    ui->comboBox_conductors->clear();
    for(int i = 1; i <= configuration->getConductors().size(); i++){
        QString text = QString::number(i) + " - Conductor(X:" + QString::number(configuration->getConductors().at(i)->getStartCoords().x) + ", Y:" + QString::number(configuration->
        (i)->getStartCoords().y) + ", Z:" + QString::number(configuration->getConductors().at(i)->getStartCoords().z) + ")";
        ui->comboBox_conductors->addItem(text);
    }

    ui->comboBox_cond_lType->clear();
    ui->comboBox_cond_lType->addItem("None");
    for(int i = 0; i < configuration->getLeadTypes().size(); i++){
        QString text = QString::number(i-1) + " - " + QString::fromStdString(configuration->getLeadTypes().at(i-1)->getName());
        ui->comboBox_cond_lType->addItem(text);
    }

    ui->comboBox_cond_coating->clear();
    ui->comboBox_cond_coating->addItem("None");
    for(int i = 0; i < configuration->getCoatings().size(); i++){
        QString text = QString::number(i-1) + " - " + QString::fromStdString(configuration->getCoatings().at(i-1)->getName());
        ui->comboBox_cond_coating->addItem(text);
    }

    ui->comboBox_cond_energization->clear();
    ui->comboBox_cond_energization->addItem("None");
    for(int i = 0; i < configuration->getEnergizations().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getEnergizations().at(i)->getIdentification());
        ui->comboBox_cond_energization->addItem(text);
    }

    ui->comboBox_cond_cType->clear();
    ui->comboBox_cond_cType->addItem("None");
    for(int i = 0; i < configuration->getConductorTypes().size(); i++){
        QString text = QString::number(i-1) + " - " + QString::fromStdString(configuration->getConductorTypes().at(i-1)->getName());
        ui->comboBox_cond_cType->addItem(text);
    }

    ui->comboBox_cond_cbType->clear();
    ui->comboBox_cond_cbType->addItem("None");
    for(int i = 0; i < configuration->getCableTypes().size(); i++){
        QString text = QString::number(i) + " - " + QString::fromStdString(configuration->getCableTypes().at(i)->getName());
        ui->comboBox_cond_cbType->addItem(text);
    }

    fetchConductor(ui->comboBox_conductors->currentText());
}

void configuration_widget::fetchConductor(QString id){
    if(!id.isEmpty()){
        id.truncate(id.indexOf(" "));
        int index = id.toInt();
        cond.reset(new Conductor(configuration->getConductors().at(index)));
        refresh();
    }
}

void configuration_widget::refreshConductor(){
    if(cond){
        ui->pushButton_cond_remove->setEnabled(true);
        ui->comboBox_cond_cbType->setEnabled(true);
        ui->comboBox_cond_coating->setEnabled(true);
        ui->comboBox_cond_cType->setEnabled(true);
        ui->comboBox_cond_energization->setEnabled(true);
        ui->comboBox_cond_lType->setEnabled(true);
        ui->doubleSpinBox_cond_endX->setEnabled(true);
        ui->doubleSpinBox_cond_endY->setEnabled(true);
        ui->doubleSpinBox_cond_endZ->setEnabled(true);
        ui->doubleSpinBox_cond_radius->setEnabled(true);
        ui->doubleSpinBox_cond_startX->setEnabled(true);
        ui->doubleSpinBox_cond_startY->setEnabled(true);
        ui->doubleSpinBox_cond_startZ->setEnabled(true);
        ui->doubleSpinBox_cond_endX->setValue(cond->getEndCoords().x);
        ui->doubleSpinBox_cond_endY->setValue(cond->getEndCoords().y);
        ui->doubleSpinBox_cond_endZ->setValue(cond->getEndCoords().z);
        ui->doubleSpinBox_cond_startX->setValue(cond->getStartCoords().x);
        ui->doubleSpinBox_cond_startY->setValue(cond->getStartCoords().y);
        ui->doubleSpinBox_cond_startZ->setValue(cond->getStartCoords().z);
        ui->doubleSpinBox_cond_radius->setValue(cond->getRadius());
        ui->cond_plot->setEnabled(true);

        if(cond->getLeadType()){
            ui->comboBox_cond_lType->setCurrentIndex(ui->comboBox_cond_lType->findText(QString::number(cond->getLeadType()->getId()), Qt::MatchStartsWith));
        }
        else{
            ui->comboBox_cond_lType->setCurrentIndex(0);
        }


        if(cond->getCoating()){
            ui->comboBox_cond_coating->setCurrentIndex(ui->comboBox_cond_coating->findText(QString::number(cond->getCoating()->getId()), Qt::MatchStartsWith));
        }
        else{
            ui->comboBox_cond_coating->setCurrentIndex(0);
        }

        if(cond->getEnergization()){
            ui->comboBox_cond_energization->setCurrentIndex(ui->comboBox_cond_energization->findText(QString::number(cond->getEnergization()->getId()), Qt::MatchStartsWith));
        }
        else{
            ui->comboBox_cond_energization->setCurrentIndex(0);
        }

        if(cond->getConductorType()){
            ui->comboBox_cond_cType->setCurrentIndex(ui->comboBox_cond_cType->findText(QString::number(cond->getConductorType()->getId()), Qt::MatchStartsWith));
        }
        else{
            ui->comboBox_cond_cType->setCurrentIndex(0);
        }

        if(cond->getCableType()){
            ui->comboBox_cond_cbType->setCurrentIndex(ui->comboBox_cond_cbType->findText(QString::number(cond->getCableType()->getId()), Qt::MatchStartsWith));
        }
        else{
            ui->comboBox_cond_cbType->setCurrentIndex(0);
        }
    }
    else{
        ui->pushButton_cond_remove->setEnabled(false);
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

}

void configuration_widget::fetchBuilding(QString id){

}

void configuration_widget::refreshBuilding(){

}

void configuration_widget::refreshPlot(){

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
    cond.reset(new Conductor());
    configuration->addConductor(cond.get(), true);
    populateConductors();
}

void configuration_widget::removeCond(){
    configuration->removeConductor(cond.get());
    cond.reset();
    populateConductors();
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
    configuration->addLeadType(lType, true);
    populateLTypes();
    populateConductors();
}

void configuration_widget::removeLType(){
    int result = configuration->removeLeadType(lType);
    if(result == 1){
        QMessageBox::critical(this, "Failure", "This LeadType is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration.");
    }
    else{
        lType.reset();
        populateLTypes();
    }
}

void configuration_widget::saveLType(){
    if(configuration->getLeadTypes().count(lType->getId()) > 0){
        configuration->replaceLeadType(lType);
    }
    else{
        configuration->addLeadType(lType, true);
    }
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
    configuration->addCoating(coat, true);
    populateCoatings();
    populateConductors();
}

void configuration_widget::removeCoat(){
    int result = configuration->removeCoating(coat);
    if(result == 1){
        QMessageBox::critical(this, "Failure", "This Coating is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration.");
    }
    else{
        coat.reset();
        populateCoatings();
    }
}

void configuration_widget::saveCoat(){
    if(configuration->getCoatings().count(coat->getId()) > 0){
        configuration->replaceCoating(coat);
    }
    else{
        configuration->addCoating(coat, true);
    }
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
    configuration->addEnergization(ener, true);
    populateEnergizations();
    populateConductors();
}

void configuration_widget::removeEner(){
    int result = configuration->removeEnergization(ener);
    if(result == 1){
        QMessageBox::critical(this, "Failure", "This Energization is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration.");
    }
    else{
        ener.reset();
        populateEnergizations();
    }
}

void configuration_widget::saveEner(){
    if(configuration->getEnergizations().count(ener->getId()) > 0){
        configuration->replaceEnergization(ener);
    }
    else{
        configuration->addEnergization(ener, true);
    }
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
    configuration->addConductorType(cType, true);
    populateCTypes();
    populateConductors();
}

void configuration_widget::removeCType(){
    int result = configuration->removeConductorType(cType);
    if(result == 1){
        QMessageBox::critical(this, "Failure", "This ConductorType is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration.");
    }
    else{
        cType.reset();
        populateCTypes();
    }
}

void configuration_widget::saveCType(){
    if(configuration->getConductorTypes().count(cType->getId()) > 0){
        configuration->replaceConductorType(cType);
    }
    else{
        configuration->addConductorType(cType, true);
    }
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
    configuration->addCableType(cbType, true);
    populateCbTypes();
    populateConductors();
}

void configuration_widget::removeCbType(){
    int result = configuration->removeCableType(cbType);
    if(result == 1){
        QMessageBox::critical(this, "Failure", "This CableType is currently used by a conductor. Remove it from the conductor before trying to remove it from the configuration.");
    }
    else{
        cbType.reset();
        populateCbTypes();
    }
}

void configuration_widget::saveCbType(){
    if(configuration->getCableTypes().count(cbType->getId()) > 0){
        configuration->replaceCableType(cbType);
    }
    else{
        configuration->addCableType(cbType, true);
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
    configuration->addProfile(pro, true);
    populateProfiles();
}

void configuration_widget::removePro(){
    configuration->removeProfile(pro);
    pro.reset();
    populateProfiles();
}

void configuration_widget::savePro(){
    if(configuration->getProfiles().count(pro->id) > 0){
        configuration->removeProfile(pro).addProfile(pro);
    }
    else{
        configuration->addProfile(pro, true);
    }
    populateEnergizations();
}

void configuration_widget::changeComputations(int i){
    if(configuration){
        configuration->setComputations().ELECTRIC = ui->checkBox_comp_ELECTRIC->isChecked();
        configuration->setComputations().GPR = ui->checkBox_comp_GPR->isChecked();
        configuration->setComputations().GRADIENT_SCALAR = ui->checkBox_comp_GRADIENT_SCALAR->isChecked();
        configuration->setComputations().MAGNETIC = ui->checkBox_comp_MAGNETIC->isChecked();
        configuration->setComputations().POTENTIAL_SCALAR = ui->checkBox_comp_POTENTIAL_SCALAR->isChecked();
        configuration->setComputations().VECTOR_POTENTIAL = ui->checkBox_comp_VECTOR_POTENTIAL->isChecked();
        refresh();
    }
}

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
