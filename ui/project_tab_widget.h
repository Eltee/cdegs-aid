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

#ifndef PROJECT_TAB_WIDGET_H
#define PROJECT_TAB_WIDGET_H

#include <QWidget>
#include <memory>
#include "classes/project.h"
#include "classes/configuration.h"
#include "project_widget.h"
#include "configuration_widget.h"
#include "cdegs_main.h"

class cdegs_main;
class Project;
class Configuration;

namespace Ui {
    class project_tab_widget;
}

/*!
 \brief Classe représentant une fenêtre à onglet contenant les données et configurations du projet courant.

 Cette classe représente une fenêtre à onglets contenu dans la fenêtre à onglet principale de la fenêtre mère.
 Celle-ci contient un onglet pour les données et un onglet pour chaque configuration ouverte provenant du projet.

 \class project_tab_widget project_tab_widget.h "ui/project_tab_widget.h"
*/
class project_tab_widget : public QWidget
{
        Q_OBJECT

    public:
        explicit project_tab_widget(QWidget *parent = 0, cdegs_main* dp = NULL, std::shared_ptr<Project> p = std::make_shared<Project>(), QString name = "");
        std::shared_ptr<Project> getProject();
        std::shared_ptr<Configuration> getConfig();
        QString const& getName() const;
        void addConfig(std::shared_ptr<Configuration> config);
        void connectSlots();
        ~project_tab_widget();
        void changeTabName(QWidget* widget, QString name);

    public slots:
        void refresh();

    private slots:
        void changeTab();
        void closeConfig(int index);

    private:
        Ui::project_tab_widget *ui;
        std::shared_ptr<Project> project, projectOrig;
        cdegs_main* defParent;
        QString m_name;
        bool m_projectModified;
};

#endif // PROJECT_TAB_WIDGET_H
