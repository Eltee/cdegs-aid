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
        explicit configuration_widget(QWidget *parent = 0, project_tab_widget* dp = NULL, std::shared_ptr<Configuration> config = std::make_shared<Configuration>());
        std::shared_ptr<Configuration> getConfig();
        void refresh();
        ~configuration_widget();

    signals:
        void dataModified(QWidget* widget);

    private:
        Ui::configuration_widget *ui;
        std::shared_ptr<Configuration> configuration, configOrig;
        project_tab_widget* defParent;
};

#endif // CONFIGURATION_WIDGET_H
