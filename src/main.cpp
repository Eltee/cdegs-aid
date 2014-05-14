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
#include "ui/dialog_welcome.h"


/*int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Dialog_Welcome diag;

    return diag.exec();
}*/


#include "pugixml.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <QtGlobal>

void readXML(pugi::xml_node toIter, int iteration=0){
    std::string whitespace = "";

    for(int i=0; i<iteration; i++){
        whitespace += "    ";
    }

    for(pugi::xml_node_iterator it = toIter.children().begin(); it != toIter.children().end(); it++){
        std::cout << whitespace << it->name();

        for(pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ait++){
            std::cout <<  "(" << ait->name() << " = " << ait->value() << ")";
        }



        if(it->text()){
            std::cout << " Text: " << it->first_child().value() << std::endl;
        }
        else if(it->first_child()){ //has children
            std::cout << std::endl;
            readXML(*it, iteration+1);
        }
        else{
            std::cout << std::endl;
        }

    }

}

std::string getOsName()
{
    #ifdef _WIN64
    return "Windows 64-bit";
    #elif _WIN32
    return "Windows 32-bit";
    #elif __unix || __unix__
    return "Unix";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    reutnr "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #else
    return "Other";
    #endif
}

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
}


// vim:et

