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

#ifndef PROJECT_WIDGET_H
#define PROJECT_WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include "project_tab_widget.h"
#include "classes/project.h"

class project_tab_widget;
class Project;

namespace Ui {
    class project_widget;
}

/*!
 \brief Classe qui représente une fenêtre contenant les métadonnées/paramètres d'un projet.

 Cette fenêtre GUI représente une fenêtre/onglet contenant un projet et ses options de modification.

 \class project_widget project_widget.h "ui/project_widget.h"
*/
class project_widget : public QWidget
{
        Q_OBJECT

    public:
        explicit project_widget(QWidget *parent = 0, project_tab_widget* dp = NULL, Project* p = NULL);
        Project* getProject();
        void connectSlots();
        void disconnectSlots();
        void refresh();
        ~project_widget();

    private slots:
        void changeDate(QDate date);
        void changeName(QString name);
        void changeAuthor(QString author);
        void changeDescription();
        void changeFilepath(QString path);
        void openFilepath();

    private:
        Ui::project_widget *ui;
        Project* project;
        project_tab_widget* defParent;
};

#endif // PROJECT_WIDGET_H
