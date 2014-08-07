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
#include <QCloseEvent>
#include <QInputDialog>
#include <QTranslator>
#include <memory>
#include "configuration_widget.h"
#include "project_tab_widget.h"
#include "project_widget.h"
#include "style_dialog.h"
#include "configuration_chooser_dialog.h"
#include "classes/configuration.h"
#include "classes/project.h"

class Configuration;
class Project;

namespace Ui {
    class cdegs_main;
}

/*!
 \brief Classe représentant la fenêtre principale du logiciel.

 Cette classe représente la fenêtre mère du logiciel. C'est aussi le contrôleur principal,
 compte-tenu de la mentalité M-VC de Qt (Un modèle et un hybride View/Controller)

 \class cdegs_main cdegs_main.h "ui/cdegs_main.h"
*/
class cdegs_main : public QMainWindow
{
        Q_OBJECT

    public:
        explicit cdegs_main(QWidget *parent = 0, QTranslator* translator = 0);
        ~cdegs_main();
        void connectSlots();
        void updateTitle();
        void updateActions();
        void updateProject();
        void updateConfig();
        void updateTab();
        void changeTabName(QWidget* widget, QString name);
        void closeEvent(QCloseEvent* event);

    public slots:
        void refresh();
        void saveConfig();
        void saveAllConfigs();

    private slots:
        void newProject();
        void openProject();
        void saveProject();
        void saveProjectAs();
        void closeProject();
        void closeProject(int index);
        void changeTab();
        void changeProject(int index);
        void newConfig();
        void openConfig(std::shared_ptr<Configuration> config);
        void closeConfig();
        void duplicateConfig();
        void exportConfig();
        void exportConfigAs();
        void deleteConfig();
        void openStyleDialog();
        void changeStyle(std::string style);
        void openConfigDialog();
        void about();
        void langEng();
        void langFr();

    signals:
        void saveOccurred();

    private:
        Ui::cdegs_main *ui;
        std::shared_ptr<Project> project;
        std::shared_ptr<Configuration> config;
        QTranslator* m_translator;
};

#endif // CDEGS_MAIN_H
