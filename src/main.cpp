/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    main.cpp
*
* Description: CDEGS-Aid est un logiciel d'aide pour la génération de fichiers
*              de simulation compatibles avec SESCad et CDEGS-HiFreq pour des
*              simulations de champ électrics, d'affichage et d'analyse de
*              résultat de simulations CDEGS-HiFreq.
*
* Auteur:      Renaud Bigras, Hydro-Québec Transénergie
*  /Author
*
* Créé:        12-05-2014
*  /Created
*
* Copyright:   (c) Renaud Bigras 2014
*
*   This file is part of CDEGS-Aid.
*
*   CDEGS-Aid is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   CDEGS-Aid is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with CDEGS-Aid. If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#include <QApplication>
#include <QtWidgets>
#include "classes/project.h"
#include "util/apputils.h"
#include <iostream>
#include <limits>
#include "lib/pugixml.hpp"
#include <QDir>
#include <QtGlobal>
#include <memory>


/*int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Dialog_Welcome diag;

    return diag.exec();
}*/

/*

extern char **environ;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    pugi::xml_document doc;
    if (!doc.load_file("XML Template Project.xml")){
        std::cout << "Failure";
        return -1;
    }

    readXML(doc);

    std::cout << qgetenv("APPDATA").constData() << std::endl;

    std::cout << qgetenv("LANG").constData() << std::endl;

    std::cout << qgetenv("USERNAME").constData() << " " << qgetenv("NAME").constData() << " " << qgetenv("NOMUSAGER").constData() << std::endl;

    std::cout << getOsName() << std::endl;

    char *s = *environ;

    for(int i=0; s; i++){
        std::cout << s << std::endl;
        s = *(environ+i);
    }

    return 0;
}*/

/*int main(int argc, char* argv[])
{
    std::vector<double> range;

    range = utils::drange(-60.0, 60.0, 2.5);

    for(double i : range){
        std::cout << i << " ";
    }

    std::cout << std::endl << std::endl << "Length: " << range.size() << std::endl;

    return 0;
}*/

int main(int argc, char* argv[]){
    Project* p = new Project("Test", "1999-04-18", "Dudebro", "test please");

    qDebug() << p->getMetadata().date.toString();

    //AppUtils::getInstance().saveProject(*p);

    delete(p);

    return 0;
}
