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
#include <QStyleFactory>
#include <QDate>
#include <exception>
#include "ui/cdegs_main.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    app.setStyle("gtk");

    cdegs_main maine;

    maine.show();

    return app.exec();
}

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

/*int main(int argc, char* argv[]){
    Project* p = new Project("Test", QDate::currentDate(), "Dudebro", "test please");

    AppUtils::getInstance().setDefaultConfig();

    Configuration* c = new Configuration(AppUtils::getInstance().getDefaultConfig());

    Conductor* cd1;
    Conductor* cd2;
    Conductor* cd3;

    cd1 = new Conductor(*c, "LT0", "CT3", "CO0", "E2", "CBT0", 0.0191);
    cd2 = new Conductor(*c, "LT0", "CT3", "CO0", "E3", "CBT0", 0.0191);
    cd3 = new Conductor(*c, "LT0", "CT3", "CO0", "E4", "CBT0", 0.0191);

    subDivision subD;

    subD.method = "Explicit";
    subD.number = 1;

    cd1->setSubDivision(subD);
    cd2->setSubDivision(subD);
    cd3->setSubDivision(subD);

    coords start, end;

    start.x = -800.0;
    start.y = 0.0;
    start.z = -10.0;
    end.x = 800.0;
    end.y = 0.0;
    end.z = -10.0;

    cd1->setCoords(start, end);

    start.y = 10.0;
    end.y = 10.0;

    cd2->setCoords(start, end);

    start.y = -10.0;
    end.y = -10.0;

    cd3->setCoords(start, end);

    c->addConductor(cd1).addConductor(cd2).addConductor(cd3);

    profile* pro = new profile;

    pro->id = AppUtils::getInstance().uniqueIdGenerator("ProfileId");

    pro->xCoords.start = -50.0;
    pro->xCoords.step = 0.25;
    pro->yCoords.start = -0.0;
    pro->yCoords.step = -0.25;
    pro->NLine = 181.0;
    pro->MCol = 401.0;

    c->addProfile(pro);

    p->addConfiguration(c);

    AppUtils::getInstance().saveProject(*p, "D:/test/", "attempt1.cdp");

    for(auto& conf : p->getConfigurations()){
        std::string fullPath = p->getAbsPath() + "/hi_" + conf.second->getIdentifier() + ".f05";
        AppUtils::getInstance().exportConfiguration(conf.second, fullPath);
    }

    delete(p);

    Project* p;

    try{
        p = AppUtils::getInstance().loadProject("D:/test/", "okay.cdp");
        AppUtils::getInstance().saveProject(*p, "D:/test/", "not okay.cdp");
    }
    catch (std::exception e){
        std::cout << "An exception occurred. Exception: " << e.what() << std::endl;
    }

    return 1337;
}*/

/*
 * std::cout << p->getConfigurations().size() << std::endl;

    Configuration* c = new Configuration();
    Configuration* d = new Configuration();

    p->addConfiguration(c).addConfiguration(d);

    std::cout << p->getConfigurations().size() << std::endl;

    std::cout << p->getId() << std::endl;

    std::cout << p->getConfigurations().front()->getId() << std::endl;

    std::cout << c << std::endl;

    std::cout << d << std::endl;

    std::cout << p->getConfigurations().front() << std::endl;

    std::cout << p->getConfigurations().back() << std::endl;

    std::cout << c->getId() << std::endl;

    std::cout << p->getConfigurations().front()->getId() << std::endl;

    for(Configuration* config : p->getConfigurations()){
        std::cout << config->getId() << std::endl;
    }
    */
