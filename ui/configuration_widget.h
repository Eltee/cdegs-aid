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

#ifndef CONFIGURATION_WIDGET_H
#define CONFIGURATION_WIDGET_H

#include <QWidget>
#include <memory>
#include <QMessageBox>
#include "project_tab_widget.h"
#include "classes/configuration.h"

class project_tab_widget;
class Configuration;

namespace Ui {
    class configuration_widget;
}

/*!
 \brief Classe qui représente une fenêtre contenant une configuration.

 Cette fenêtre GUI représente une fenêtre/onglet contenant une configuration et ses options de modification.

 \class configuration_widget configuration_widget.h "ui/configuration_widget.h"
*/
class configuration_widget : public QWidget
{
        Q_OBJECT

    public:
        explicit configuration_widget(QWidget *parent = 0, project_tab_widget* dp = NULL, std::shared_ptr<Configuration> config = std::make_shared<Configuration>(), QString name = "");
        std::shared_ptr<Configuration> getConfig();
        QString const& getName() const;
        ~configuration_widget();
        void initPlot();
        void populateFields();
        void populateLTypes();
        void populateCoatings();
        void populateEnergizations();
        void populateCTypes();
        void populateCbTypes();
        void populateComputations();
        void populateProfiles();
        void populateConductors();
        void populateBuildings();
        void connectSlots();
        void disconnectSlots();
        void refreshConfSettings();
        void refreshLType();
        void refreshCoating();
        void refreshEnergization();
        void refreshCType();
        void refreshCbType();
        void refreshProfile();
        void refreshConductor();
        void refreshBuilding();
        void refreshPlot();

    public slots:
        void refresh();

    private slots:
        //COMBOBOX CONNECTIONS
        void fetchLType(QString id);
        void fetchCoating(QString id);
        void fetchEnergization(QString id);
        void fetchCType(QString id);
        void fetchCbType(QString id);
        void fetchProfile(QString id);
        void fetchConductor(QString id);
        void fetchBuilding(QString id);

        //CONF CONNECTIONS
        void changeConfIdentifier(QString ident);
        void changeConfUnits(QString units);
        void changeConfFrequency(QString frequency);
        void saveConfig();

        //COND CONNECTIONS
        void newCond();
        void removeCond();

        //BUILD CONNECTIONS

        //LTYPE CONNECTIONS
        void changeLTypeName(QString text);
        void newLType();
        void removeLType();
        void saveLType();

        //COATING CONNECTIONS
        void changeCoatName(QString text);
        void newCoat();
        void removeCoat();
        void saveCoat();

        //ENERG CONNECTIONS
        void changeEnerFreq(QString text);
        void changeEnerIdent(QString text);
        void changeEnerType(QString text);
        void changeEnerMag(int i);
        void changeEnerAng(double i);
        void newEner();
        void removeEner();
        void saveEner();

        //CTYPE CONNECTIONS
        void changeCTypeName(QString text);
        void changeCTypeType(QString text);
        void changeCTypePerm(double d);
        void changeCTypeRes(double d);
        void newCType();
        void removeCType();
        void saveCType();

        //CBTYPE CONNECTIONS
        void changeCbTypeName(QString text);
        void newCbType();
        void removeCbType();
        void saveCbType();

        //PROFILE CONNECTIONS
        void changeProNumPt(int i);
        void changeProNumPr(int i);
        void changeProPtStepX(double d);
        void changeProPtStepY(double d);
        void changeProPtStepZ(double d);
        void changeProStartX(double d);
        void changeProStartY(double d);
        void changeProStartZ(double d);
        void changeProPrStepX(double d);
        void changeProPrStepY(double d);
        void changeProPrStepZ(double d);
        void newPro();
        void removePro();
        void savePro();

        //COMPUTATION CONNECTIONS
        void changeComputations(int i);


    private:
        Ui::configuration_widget *ui;
        std::shared_ptr<Configuration> configuration;
        project_tab_widget* defParent;
        QString m_name;
        std::shared_ptr<LeadType> lType;
        std::shared_ptr<Coating> coat;
        std::shared_ptr<Energization> ener;
        std::shared_ptr<ConductorType> cType;
        std::shared_ptr<CableType> cbType;
        std::shared_ptr<profile> pro;
        std::shared_ptr<Conductor> cond;
};

#endif // CONFIGURATION_WIDGET_H
