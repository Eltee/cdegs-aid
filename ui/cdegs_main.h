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

#ifndef CDEGS_MAIN_H
#define CDEGS_MAIN_H

#include <QMainWindow>
#include <stdio.h>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QtUiTools/QUiLoader>
#include <iostream>
#include <QFileInfo>
#include "ui/configuration_widget.h"
#include "ui/project_tab_widget.h"
#include "ui/project_widget.h"
#include "classes/configuration.h"
#include "classes/project.h"

namespace Ui {
    class cdegs_main;
}

class cdegs_main : public QMainWindow
{
        Q_OBJECT

    public:
        explicit cdegs_main(QWidget *parent = 0);
        ~cdegs_main();
        void connectSlots();
        void updateTitle();
        void updateActions();
        void updateProject();
        void updateConfig();
        void updateTab();
        void refresh();

    private slots:
        void newProject();
        void openProject();
        void saveProject();
        void saveProjectAs();
        void closeProject();
        void closeProject(int index);
        void changeProject(int index);
        void newConfig();
        void openConfig();
        void saveConfig();
        void closeConfig();
        void exportConfig();
        void exportConfigAs();
        void about();

    private:
        Ui::cdegs_main *ui;
        Project* project = NULL;
        Configuration* config = NULL;
};

#endif // CDEGS_MAIN_H
