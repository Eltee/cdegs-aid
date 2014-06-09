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
    configOrig = config;
    m_name = name;
    configuration.reset(new Configuration(config.get()));
    ui->setupUi(this);
    defParent = dp;
    configModified = configuration->isModified();
    populateFields();
    connectSlots();
}

void configuration_widget::connectSlots(){
    QObject::connect(ui->comboBox_page, SIGNAL(currentIndexChanged(int)),
                     ui->stackedWidget_config, SLOT(setCurrentIndex(int)));
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
}

/*!
 \brief

 \fn configuration_widget::refresh
*/
void configuration_widget::refresh(){
    defParent->refresh();
    if(configuration->isModified() != configModified){
        configModified = configuration->isModified();
        QString newName = m_name;
        if(configuration->isModified()) newName.append("*");
        defParent->changeTabName(this, newName);
    }
}

void configuration_widget::populateFields(){
    populateConfSettings();
    populateLTypes();
}

void configuration_widget::populateConfSettings(){
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

void configuration_widget::populateLTypes(){
    std::cout << "GUH" << std::endl;
    for(int i = 0; i < configuration->getLeadTypes().size(); i++){
        QString text = QString::number(i-1) + " - " + QString::fromStdString(configuration->getLeadTypes().at(i-1)->getName());
        std::cout << "Entry: " << text.toStdString() << std::endl;
        ui->comboBox_lTypes_chooser->addItem(text);
    }
}
