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
#include <fstream>
#include <sstream>
#include <QDate>
#include <exception>
#include "ui/cdegs_main.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    AppUtils::getInstance().generateDefaultConfig();

    AppUtils::getInstance().setDefaultConfig();

    AppUtils::getInstance().loadStylesheets();

    cdegs_main maine;

    maine.show();

    return app.exec();

}

    /*std::shared_ptr<Project> p, p2, p3;

    std::cout << p.get() << std::endl;

    p.reset();

    std::cout << NULL << std::endl;

    p.reset(new Project());

    p2 = p;

    p3 = p;

    std::cout << p.use_count() << std::endl;

    std::cout << p3->getId() << std::endl;

    std::cout << p.get() << " " << p2.get() << " " << p3.get() << std::endl;

    std::cout << p.use_count() << std::endl;

    std::cout << p.get() << " " << p.get()->getId() << std::endl;

    p.reset();

    std::cout << p3.use_count() << std::endl;

    std::cout << p3->getId() << std::endl;

    p2.reset();

    std::cout << p3.use_count() << std::endl;

    do{
        std::shared_ptr<Project> p4;
        p4 = p3;
        std::cout << p3.use_count() << std::endl;
    }while(0 != 0);

    std::weak_ptr<Project> wp;

    std::cout << p3.use_count() << std::endl;

    wp = p3;

    std::cout << p3.use_count() << std::endl;

    std::cout << p3.get() << std::endl;

    std::cout << wp.lock().get() << std::endl;

    std::cout << p3.use_count() << std::endl;

    std::cout << p2.get() << std::endl;

    std::cout << "last line before main return" << std::endl;

    return 0;
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
    Project* p = new Project("Test", "great escape.cdp", QDate::currentDate(), "Dudebro", "test please");

    AppUtils::getInstance().generateDefaultConfig();
    AppUtils::getInstance().setDefaultConfig();

    Configuration* c = new Configuration(AppUtils::getInstance().getDefaultConfig());

    Conductor* cd1;
    Conductor* cd2;
    Conductor* cd3;

    cd1 = new Conductor(*c, 0, 1, 0, 1, 0, 0.0191);
    cd2 = new Conductor(*c, 0, 1, 0, 2, 0, 0.0191);
    cd3 = new Conductor(*c, 0, 1, 0, 3, 0, 0.0191);

    cd1->setSubDivision(1);
    cd2->setSubDivision(1);
    cd3->setSubDivision(1);

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

    c->addConductor(cd1, true).addConductor(cd2, true).addConductor(cd3, true);

    profile* pro = new profile;

    pro->start.x = 0;
    pro->start.y = -50;
    pro->start.z = 0;
    pro->ptStep.x = 0;
    pro->ptStep.y = 0;
    pro->ptStep.z = -0.25;
    pro->prStep.x = 0.0;
    pro->prStep.y = 0.25;
    pro->prStep.z = 0.0;
    pro->ptNum = 181;
    pro->prNum = 401;

    profile* pro2 = new profile;

    pro2->fromCoordsToStep(0, -50, 0, 0, -50, -45, 0, 50, 0, 181, 401);

    std::cout << "Profile 1: " << std::endl
              << "Start X: " << pro->start.x << std::endl
              << "Start Y: " << pro->start.y << std::endl
              << "Start Z: " << pro->start.z << std::endl
              << "Point Step Dx: " << pro->ptStep.x << std::endl
              << "Point Step Dy: " << pro->ptStep.y << std::endl
              << "Point Step Dz: " << pro->ptStep.z << std::endl
              << "Profile Step Dx: " << pro->prStep.x << std::endl
              << "Profile Step Dy: " << pro->prStep.y << std::endl
              << "Profile Step Dz: " << pro->prStep.z << std::endl
              << "Number of Points: " << pro->ptNum << std::endl
              << "Number of Profiles: " << pro->prNum << std::endl;

    std::cout << "Profile 2: " << std::endl
              << "Start X: " << pro2->start.x << std::endl
              << "Start Y: " << pro2->start.y << std::endl
              << "Start Z: " << pro2->start.z << std::endl
              << "Point Step Dx: " << pro2->ptStep.x << std::endl
              << "Point Step Dy: " << pro2->ptStep.y << std::endl
              << "Point Step Dz: " << pro2->ptStep.z << std::endl
              << "Profile Step Dx: " << pro2->prStep.x << std::endl
              << "Profile Step Dy: " << pro2->prStep.y << std::endl
              << "Profile Step Dz: " << pro2->prStep.z << std::endl
              << "Number of Points: " << pro2->ptNum << std::endl
              << "Number of Profiles: " << pro2->prNum << std::endl;

    for(auto& coord : pro->toCoords()){
        std::cout << "Point:" << std::endl
                  << "X: " << coord.x << std::endl
                  << "Y: " << coord.y << std::endl
                  << "Z: " << coord.z << std::endl;
    }

    for(auto& coord : pro2->toCoords()){
        std::cout << "Point:" << std::endl
                  << "X: " << coord.x << std::endl
                  << "Y: " << coord.y << std::endl
                  << "Z: " << coord.z << std::endl;
    }

    delete(pro);
    delete(pro2);

    /*c->addProfile(pro, true);

    p->addConfiguration(c);

    std::string path = "D:/test";

    AppUtils::getInstance().saveProject(*p, path);

    for(auto& conf : p->getConfigurations()){
        std::string fullPath = p->getAbsPath() + "/hi_" + conf.second->getIdentifier() + ".f05";
        AppUtils::getInstance().exportConfiguration(conf.second, fullPath);
    }

    delete(p);

    std::string filename = "greatescape.cdp";

    p = AppUtils::getInstance().loadProject(QString::fromStdString(path), QString::fromStdString(filename));
    p->setFileName("fuckere.cdp");
    AppUtils::getInstance().saveProject(*p, path);

    return 1337;
}

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
