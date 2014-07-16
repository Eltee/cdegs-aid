/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    apputils.cpp
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

#include "apputils.h"

/*!
 \brief

 \fn AppUtils::drange
 \param start
 \param end
 \param step
 \return std::vector<double>
*/
std::vector<double> AppUtils::drange(double start, double end, double step){
    std::vector<double> range;

    for(double i=start; i<=end; i+=step){
        range.push_back(i);
    }

    return range;
}

/*!
 \brief

 \fn AppUtils::getOsName
 \return std::string
*/
std::string AppUtils::getOsName(){
    #ifdef _WIN64
        return "Windows 64-bit";
    #elif _WIN32
        return "Windows 32-bit";
    #elif __unix || __unix__
        return "Unix";
    #elif __APPLE__ || __MACH__
        return "Mac OSX";
    #elif __linux__
        return "Linux";
    #elif __FreeBSD__
        return "FreeBSD";
    #else
        return "Other";
    #endif
}

/*!
 \brief

 \fn AppUtils::BoolToString
 \param b
 \return const char
*/
inline const char* AppUtils::BoolToString(const bool b) const{
  return b ? "True" : "False";
}

/*!
 \brief

 \fn AppUtils::readXML
 \param toIter
 \param iteration
*/
void AppUtils::readXML(const pugi::xml_node& toIter, int iteration){
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

/*!
 \brief

 \fn AppUtils::loadStylesheets
*/
void AppUtils::loadStylesheets(){
    QDir directory(QString::fromStdString(getAppData()));

    directory.setFilter(QDir::Files);

    m_styleSheets.emplace("Default", "");

    for(QString file : directory.entryList()){
        if(file.endsWith(".css")){
            QString style;
            std::ifstream infile(directory.absoluteFilePath(file).toStdString());
            std::string line;
            while (std::getline(infile, line))
            {
                style.append(QString::fromStdString(line)).append("\n");
            }
            m_styleSheets.emplace(file.remove(file.size()-4, 4).toStdString(), style);
        }
    }
}

std::unordered_map<std::string, QString> const& AppUtils::getStyleSheets() const{
    return m_styleSheets;
}

const QString AppUtils::getStyle(std::string name) const{
    return m_styleSheets.at(name);
}

/*!
 \brief

 \fn AppUtils::getAppData
 \return std::string
*/
std::string AppUtils::getAppData(){
    std::string pathToFolder = qgetenv("APPDATA").constData();
    pathToFolder += "\\CDEGS-AID";
    return pathToFolder;
}

/*!
 \brief

 \fn AppUtils::getPath
 \param folderPath
 \param filename
 \return std::string
*/
std::string AppUtils::getPath(const QString folderPath, const QString filename){
    QDir appFolder(folderPath);
    std::string path = appFolder.absoluteFilePath(filename).toStdString();
    return path;
}

/*!
 \brief

 \fn AppUtils::getPath
 \param filename
 \return std::string
*/
std::string AppUtils::getPath(const QString filename){
    QString pathToFolder = qgetenv("APPDATA").constData();
    pathToFolder += "/CDEGS-AID";
    QDir appFolder(pathToFolder);
    std::string path = appFolder.absoluteFilePath(filename).toStdString();
    return path;
}

/*!
 \brief

 \fn AppUtils::setDefaultConfig
*/
void AppUtils::setDefaultConfig(){
    if(0 == access(getPath("default_values.cdp").c_str(), 0)){ //Exists
        loadDefaultConfig();
    }
    else{ //Does not exist
        generateDefaultConfig();
        loadDefaultConfig();
    }
}

/*!
 \brief

 \fn AppUtils::loadDefaultConfig
*/
void AppUtils::loadDefaultConfig(){
    m_defaultConfig = new Configuration();

    pugi::xml_document doc;

    QString filename = "default_values.cdp";
    if (!doc.load_file(QString::fromStdString(getPath(filename)).toStdWString().c_str())){
        std::cout << "Failure" << std::endl;
    }

    pugi::xml_node node = doc.first_child().first_child();

    m_defaultConfig->setId(node.first_attribute().as_int());

    m_defaultConfig->setIdentifier(node.child("Identifier").first_attribute().value());

    m_defaultConfig->setUnits(node.child("Units").first_attribute().value());

    m_defaultConfig->setFrequency(node.child("Frequency").first_attribute().value());

    for(pugi::xml_node_iterator it = node.child("LeadTypes").children().begin(); it != node.child("LeadTypes").children().end(); it++){
        LeadType* lt = new LeadType(it->attribute("Name").value());
        lt->setId(it->attribute("Id").as_double());
        lt->setLocked(it->attribute("Locked").as_bool());
        std::shared_ptr<LeadType> ptr(lt);
        m_defaultConfig->addLeadType(ptr);
    }

    for(pugi::xml_node_iterator it = node.child("Coatings").children().begin(); it != node.child("Coatings").children().end(); it++){
        Coating* co = new Coating(it->attribute("Name").value());
        co->setId(it->attribute("Id").as_double());
        co->setLocked(it->attribute("Locked").as_bool());
        std::shared_ptr<Coating> ptr(co);
        m_defaultConfig->addCoating(ptr);
    }

    for(pugi::xml_node_iterator it = node.child("Energizations").children().begin(); it != node.child("Energizations").children().end(); it++){
        Energization* en = new Energization(it->attribute("Identification").value(), it->attribute("Type").value(), it->attribute("Frequency").value(), it->attribute("Magnitude").as_double(), it->attribute("Angle").as_double());
        en->setId(it->attribute("Id").as_double());
        en->setLocked(it->attribute("Locked").as_bool());
        std::shared_ptr<Energization> ptr(en);
        m_defaultConfig->addEnergization(ptr);
    }

    for(pugi::xml_node_iterator it = node.child("Tolerances").children().begin(); it != node.child("Tolerances").children().end(); it++){
        m_defaultConfig->addTolerance(it->attribute("Value").as_double());
    }

    for(pugi::xml_node_iterator it = node.child("ConductorTypes").children().begin(); it != node.child("ConductorTypes").children().end(); it++){
        ConductorType* ct = new ConductorType(it->attribute("Type").value(), it->attribute("Name").value(), it->attribute("Resistivity").as_double(), it->attribute("Permeability").as_double());
        ct->setId(it->attribute("Id").as_double());
        ct->setLocked(it->attribute("Locked").as_bool());
        std::shared_ptr<ConductorType> ptr(ct);
        m_defaultConfig->addConductorType(ptr);
    }

    for(pugi::xml_node_iterator it = node.child("CableTypes").children().begin(); it != node.child("CableTypes").children().end(); it++){
        CableType* cbt = new CableType(it->attribute("Name").value());
        cbt->setId(it->attribute("Id").as_double());
        cbt->setLocked(it->attribute("Locked").as_bool());
        std::shared_ptr<CableType> ptr(cbt);
        m_defaultConfig->addCableType(ptr);
    }

    m_defaultConfig->setComputations().GPR = node.child("Computations").child("GPR").first_attribute().as_bool();
    m_defaultConfig->setComputations().POTENTIAL_SCALAR = node.child("Computations").child("POTENTIAL-SCALAR").first_attribute().as_bool();
    m_defaultConfig->setComputations().ELECTRIC = node.child("Computations").child("ELECTRIC").first_attribute().as_bool();
    m_defaultConfig->setComputations().MAGNETIC = node.child("Computations").child("MAGNETIC").first_attribute().as_bool();
    m_defaultConfig->setComputations().VECTOR_POTENTIAL = node.child("Computations").child("VECTOR-POTENTIAL").first_attribute().as_bool();
    m_defaultConfig->setComputations().GRADIENT_SCALAR = node.child("Computations").child("GRADIENT-SCALAR ").first_attribute().as_bool();

}

/*!
 \brief

 \fn AppUtils::generateDefaultConfig
*/
void AppUtils::generateDefaultConfig(){
    pugi::xml_document doc;

    pugi::xml_node defaultNode = doc.append_child("Default");
    pugi::xml_node configNode = defaultNode.append_child("Configuration");

    pugi::xml_node node;

    //Configuration node-------------------------------------------------------

    configNode.append_attribute("Id").set_value(0);

    //Identifier node
    node = configNode.append_child("Identifier");
    node.append_attribute("Value").set_value("Default");

    //Units node
    node = configNode.append_child("Units");
    node.append_attribute("Value").set_value("Metric");

    //Frequency node
    node = configNode.append_child("Frequency");
    node.append_attribute("Value").set_value("AC");

    //LeadTypes node-----------------------------------------------------------
    pugi::xml_node leadTypesNode = configNode.append_child("LeadTypes");

    node = leadTypesNode.append_child("LeadType");
    node.append_attribute("Id").set_value("1");
    node.append_attribute("Name").set_value("Unconnected");
    node.append_attribute("Locked").set_value("1");

    node = leadTypesNode.append_child("LeadType");
    node.append_attribute("Id").set_value("2");
    node.append_attribute("Name").set_value("Default Impedance");
    node.append_attribute("Locked").set_value("1");

    //LeadTypes end------------------------------------------------------------

    //ConductorTypes node-----------------------------------------------------------
    pugi::xml_node conductorTypesNode = configNode.append_child("ConductorTypes");

    node = conductorTypesNode.append_child("ConductorType");
    node.append_attribute("Id").set_value("3");
    node.append_attribute("Type").set_value("Plastic");
    node.append_attribute("Name").set_value("Plastic");
    node.append_attribute("Resistivity").set_value("0.0");
    node.append_attribute("Permeability").set_value("1.0");
    node.append_attribute("Locked").set_value("1");

    node = conductorTypesNode.append_child("ConductorType");
    node.append_attribute("Id").set_value("4");
    node.append_attribute("Type").set_value("Default");
    node.append_attribute("Name").set_value("Default (Copper)");
    node.append_attribute("Resistivity").set_value("1.0");
    node.append_attribute("Permeability").set_value("1.0");
    node.append_attribute("Locked").set_value("1");

    node = conductorTypesNode.append_child("ConductorType");
    node.append_attribute("Id").set_value("5");
    node.append_attribute("Type").set_value("Computed");
    node.append_attribute("Name").set_value("Aluminium");
    node.append_attribute("Resistivity").set_value("1.64");
    node.append_attribute("Permeability").set_value("1.0");
    node.append_attribute("Locked").set_value("0");

    node = conductorTypesNode.append_child("ConductorType");
    node.append_attribute("Id").set_value("6");
    node.append_attribute("Type").set_value("Computed");
    node.append_attribute("Name").set_value("Steel");
    node.append_attribute("Resistivity").set_value("12.0");
    node.append_attribute("Permeability").set_value("250.0");
    node.append_attribute("Locked").set_value("0");

    //ConductorTypes end------------------------------------------------------------

    //Coatings node-----------------------------------------------------------
    pugi::xml_node coatingsNode = configNode.append_child("Coatings");

    node = coatingsNode.append_child("Coating");
    node.append_attribute("Id").set_value("7");
    node.append_attribute("Name").set_value("Insulated");
    node.append_attribute("Locked").set_value("1");

    node = coatingsNode.append_child("Coating");
    node.append_attribute("Id").set_value("8");
    node.append_attribute("Name").set_value("Default Coating");
    node.append_attribute("Locked").set_value("1");

    //Coatings end------------------------------------------------------------

    //Energizations node-----------------------------------------------------------
    pugi::xml_node energizationsNode = configNode.append_child("Energizations");

    node = energizationsNode.append_child("Energization");
    node.append_attribute("Id").set_value("9");
    node.append_attribute("Identification").set_value("(No Energization)");
    node.append_attribute("Type").set_value("GPR-Potential");
    node.append_attribute("Frequency").set_value("Both");
    node.append_attribute("Angle").set_value("0");
    node.append_attribute("Magnitude").set_value("0");
    node.append_attribute("Locked").set_value("1");

    node = energizationsNode.append_child("Energization");
    node.append_attribute("Id").set_value("10");
    node.append_attribute("Identification").set_value("GND");
    node.append_attribute("Type").set_value("GPR-Potential");
    node.append_attribute("Frequency").set_value("Both");
    node.append_attribute("Angle").set_value("0");
    node.append_attribute("Magnitude").set_value("0");
    node.append_attribute("Locked").set_value("1");

    node = energizationsNode.append_child("Energization");
    node.append_attribute("Id").set_value("11");
    node.append_attribute("Identification").set_value("PhaseA");
    node.append_attribute("Type").set_value("GPR-Potential");
    node.append_attribute("Frequency").set_value("AC");
    node.append_attribute("Angle").set_value("0");
    node.append_attribute("Magnitude").set_value("190500");
    node.append_attribute("Locked").set_value("0");

    node = energizationsNode.append_child("Energization");
    node.append_attribute("Id").set_value("12");
    node.append_attribute("Identification").set_value("PhaseB");
    node.append_attribute("Type").set_value("GPR-Potential");
    node.append_attribute("Frequency").set_value("AC");
    node.append_attribute("Angle").set_value("-120");
    node.append_attribute("Magnitude").set_value("190500");
    node.append_attribute("Locked").set_value("0");

    node = energizationsNode.append_child("Energization");
    node.append_attribute("Id").set_value("13");
    node.append_attribute("Identification").set_value("PhaseC");
    node.append_attribute("Type").set_value("GPR-Potential");
    node.append_attribute("Frequency").set_value("AC");
    node.append_attribute("Angle").set_value("120");
    node.append_attribute("Magnitude").set_value("190500");
    node.append_attribute("Locked").set_value("0");

    //Energizations end------------------------------------------------------------

    //CableTypes node-----------------------------------------------------------
    pugi::xml_node cableTypesNode = configNode.append_child("CableTypes");

    node = cableTypesNode.append_child("CableType");
    node.append_attribute("Id").set_value("16");
    node.append_attribute("Name").set_value("(Not a Cable)");
    node.append_attribute("Locked").set_value("1");

    //CableTypes end------------------------------------------------------------

    //Tolerances node-----------------------------------------------------------
    pugi::xml_node tolerancesNode = configNode.append_child("Tolerances");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.001");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("1");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.005");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.00005");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.001");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.0");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.0");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.0");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.5");

    //Tolerances end------------------------------------------------------------

    node = configNode.append_child("Conductors");
    node = configNode.append_child("BuildingConductors");
    node = configNode.append_child("Buildings");

    //Computations node----------------------------------------------------------------
    pugi::xml_node computationsNode = configNode.append_child("Computations");

    node = computationsNode.append_child("GPR");
    node.append_attribute("Value").set_value("False");

    node = computationsNode.append_child("POTENTIAL-SCALAR");
    node.append_attribute("Value").set_value("False");

    node = computationsNode.append_child("ELECTRIC");
    node.append_attribute("Value").set_value("True");

    node = computationsNode.append_child("MAGNETIC");
    node.append_attribute("Value").set_value("False");

    node = computationsNode.append_child("VECTOR-POTENTIAL");
    node.append_attribute("Value").set_value("False");

    node = computationsNode.append_child("GRADIENT-SCALAR");
    node.append_attribute("Value").set_value("False");

    //Computations end-----------------------------------------------------------------

    node = configNode.append_child("Profiles");

    QString filename = "default_values.cdp";

    doc.save_file(QString::fromStdString(getPath(filename)).toStdWString().c_str());
}

/*!
 \brief

 \fn AppUtils::getDefaultConfig
 \return const Configuration
*/
Configuration const* AppUtils::getDefaultConfig() const{
    return m_defaultConfig;
}

/*!
 \brief

 \fn AppUtils::loadConfig
 \param configNode
 \return Configuration
*/
Configuration* AppUtils::loadConfig(pugi::xml_node configNode) const{
    Configuration* config = new Configuration();

    config->setId(configNode.first_attribute().as_int());

    config->setIdentifier(configNode.child("Identifier").first_attribute().value());

    config->setUnits(configNode.child("Units").first_attribute().value());

    config->setFrequency(configNode.child("Frequency").first_attribute().value());

    for(pugi::xml_node_iterator it = configNode.child("LeadTypes").children().begin(); it != configNode.child("LeadTypes").children().end(); it++){
        LeadType* lt = new LeadType(it->attribute("Name").value());
        lt->setId(it->attribute("Id").as_int());
        lt->setLocked(it->attribute("Locked").as_bool());
        std::shared_ptr<LeadType> ptr(lt);
        config->addLeadType(ptr);
    }

    for(pugi::xml_node_iterator it = configNode.child("Coatings").children().begin(); it != configNode.child("Coatings").children().end(); it++){
        Coating* co = new Coating(it->attribute("Name").value());
        co->setId(it->attribute("Id").as_int());
        co->setLocked(it->attribute("Locked").as_bool());
        std::shared_ptr<Coating> ptr(co);
        config->addCoating(ptr);
    }

    for(pugi::xml_node_iterator it = configNode.child("Energizations").children().begin(); it != configNode.child("Energizations").children().end(); it++){
        Energization* en = new Energization(it->attribute("Identification").value(), it->attribute("Type").value(), it->attribute("Frequency").value(), it->attribute("Magnitude").as_int(), it->attribute("Angle").as_double());
        en->setId(it->attribute("Id").as_int());
        en->setLocked(it->attribute("Locked").as_bool());
        std::shared_ptr<Energization> ptr(en);
        config->addEnergization(ptr);
    }

    for(pugi::xml_node_iterator it = configNode.child("Tolerances").children().begin(); it != configNode.child("Tolerances").children().end(); it++){
        config->addTolerance(it->attribute("Value").as_double());
    }

    for(pugi::xml_node_iterator it = configNode.child("ConductorTypes").children().begin(); it != configNode.child("ConductorTypes").children().end(); it++){
        ConductorType* ct = new ConductorType(it->attribute("Type").value(), it->attribute("Name").value(), it->attribute("Resistivity").as_double(), it->attribute("Permeability").as_double());
        ct->setId(it->attribute("Id").as_int());
        ct->setLocked(it->attribute("Locked").as_bool());
        std::shared_ptr<ConductorType> ptr(ct);
        config->addConductorType(ptr);
    }

    for(pugi::xml_node_iterator it = configNode.child("CableTypes").children().begin(); it != configNode.child("CableTypes").children().end(); it++){
        CableType* cbt = new CableType(it->attribute("Name").value());
        cbt->setId(it->attribute("Id").as_int());
        cbt->setLocked(it->attribute("Locked").as_bool());
        std::shared_ptr<CableType> ptr(cbt);
        config->addCableType(ptr);
    }



    for(pugi::xml_node_iterator it = configNode.child("Conductors").children().begin(); it != configNode.child("Conductors").children().end(); it++){
        std::shared_ptr<Conductor> cd;
        cd.reset(new Conductor());
        int key;
        cd->setId(it->attribute("Id").as_int());

        key = it->child("LeadTypeId").first_attribute().as_int();
        cd->setLeadType(config->getLeadType(key));

        key = it->child("CoatingId").first_attribute().as_int();
        cd->setCoating(config->getCoating(key));

        key = it->child("ConductorTypeId").first_attribute().as_int();
        cd->setConductorType(config->getConductorType(key));

        key = it->child("EnergizationId").first_attribute().as_int();
        cd->setEnergization(config->getEnergization(key));

        key = it->child("CableTypeId").first_attribute().as_int();
        cd->setCableType(config->getCableType(key));

        cd->setRadius(it->child("Radius").first_attribute().as_double());
        coords start, end;
        start.x = it->child("CoordsStart").attribute("X").as_double();
        start.y = it->child("CoordsStart").attribute("Y").as_double();
        start.z = it->child("CoordsStart").attribute("Z").as_double();
        end.x = it->child("CoordsEnd").attribute("X").as_double();
        end.y = it->child("CoordsEnd").attribute("Y").as_double();
        end.z = it->child("CoordsEnd").attribute("Z").as_double();
        cd->setCoords(start, end);
        config->addConductor(cd);
    }

    for(pugi::xml_node_iterator it = configNode.child("BuildingConductors").children().begin(); it != configNode.child("BuildingConductors").children().end(); it++){
        std::shared_ptr<Conductor> cd;
        cd.reset(new Conductor());
        int key;
        cd->setId(it->attribute("Id").as_int());

        key = it->child("LeadTypeId").first_attribute().as_int();
        cd->setLeadType(config->getLeadType(key));

        key = it->child("CoatingId").first_attribute().as_int();
        cd->setCoating(config->getCoating(key));

        key = it->child("ConductorTypeId").first_attribute().as_int();
        cd->setConductorType(config->getConductorType(key));

        key = it->child("EnergizationId").first_attribute().as_int();
        cd->setEnergization(config->getEnergization(key));

        key = it->child("CableTypeId").first_attribute().as_int();
        cd->setCableType(config->getCableType(key));

        cd->setRadius(it->child("Radius").first_attribute().as_int());
        coords start, end;
        start.x = it->child("CoordsStart").attribute("X").as_double();
        start.y = it->child("CoordsStart").attribute("Y").as_double();
        start.z = it->child("CoordsStart").attribute("Z").as_double();
        end.x = it->child("CoordsEnd").attribute("X").as_double();
        end.y = it->child("CoordsEnd").attribute("Y").as_double();
        end.z = it->child("CoordsEnd").attribute("Z").as_double();
        cd->setCoords(start, end);
        config->addBuildingConductor(cd);
    }

    for(pugi::xml_node_iterator it = configNode.child("Buildings").children().begin(); it != configNode.child("Buildings").children().end(); it++){
        Building* b = new Building();
        b->setDistance(it->child("Distance").first_attribute().as_int());
        b->setFaces(it->child("Faces").first_attribute().as_int());
        b->setHeight(it->child("Height").first_attribute().as_int());
        b->setLength(it->child("Length").first_attribute().as_int());
        b->setRadius(it->child("Radius").first_attribute().as_double());
        b->setWidth(it->child("Width").first_attribute().as_int());
        b->setStep(it->child("Step").first_attribute().as_double());
        b->setId(it->attribute("Id").as_int());

        int key;

        key = it->child("LeadTypeId").first_attribute().as_int();
        b->setLeadType(config->getLeadType(key));

        key = it->child("CoatingId").first_attribute().as_int();
        b->setCoating(config->getCoating(key));

        key = it->child("ConductorTypeId").first_attribute().as_int();
        b->setConductorType(config->getConductorType(key));

        key = it->child("EnergizationId").first_attribute().as_int();
        b->setEnergization(config->getEnergization(key));

        key = it->child("CableTypeId").first_attribute().as_int();
        b->setCableType(config->getCableType(key));

        std::shared_ptr<Building> ptr(b);
        config->addBuilding(ptr);
    }

    config->setComputations().GPR = configNode.child("Computations").child("GPR").first_attribute().as_bool();
    config->setComputations().POTENTIAL_SCALAR = configNode.child("Computations").child("POTENTIAL-SCALAR").first_attribute().as_bool();
    config->setComputations().ELECTRIC = configNode.child("Computations").child("ELECTRIC").first_attribute().as_bool();
    config->setComputations().MAGNETIC = configNode.child("Computations").child("MAGNETIC").first_attribute().as_bool();
    config->setComputations().VECTOR_POTENTIAL = configNode.child("Computations").child("VECTOR-POTENTIAL").first_attribute().as_bool();
    config->setComputations().GRADIENT_SCALAR = configNode.child("Computations").child("GRADIENT-SCALAR ").first_attribute().as_bool();

    for(pugi::xml_node_iterator it = configNode.child("Profiles").children().begin(); it != configNode.child("Profiles").children().end(); it++){
        profile* p = new profile();
        p->id = it->attribute("Id").as_int();
        p->start.x = it->child("ProfileStart").attribute("X").as_double();
        p->start.y = it->child("ProfileStart").attribute("Y").as_double();
        p->start.z = it->child("ProfileStart").attribute("Z").as_double();
        p->ptStep.x = it->child("PointStep").attribute("Dx").as_double();
        p->ptStep.y = it->child("PointStep").attribute("Dy").as_double();
        p->ptStep.z = it->child("PointStep").attribute("Dz").as_double();
        p->prStep.x = it->child("ProfileStep").attribute("Dx").as_double();
        p->prStep.y = it->child("ProfileStep").attribute("Dy").as_double();
        p->prStep.z = it->child("ProfileStep").attribute("Dz").as_double();
        p->ptNum = it->child("NumberPoints").attribute("Value").as_int();
        p->prNum = it->child("NumberProfiles").attribute("Value").as_int();
        std::shared_ptr<profile> ptr(p);
        config->addProfile(ptr);
    }

    return config;
}

/*!
 \brief

 \fn AppUtils::loadProject
 \param folder
 \param filename
 \return Project
*/
Project* AppUtils::loadProject(const QString folder, const QString filename){
    Project* project = new Project();

    pugi::xml_document doc;

    doc.load_file(QString::fromStdString(getPath(folder, filename)).toStdWString().c_str());

    pugi::xml_node node = doc.first_child();

    project->setId(node.attribute("Id").value());

    project->setAbsPath(node.child("AbsPath").attribute("Value").value());

    project->setRelPath(node.child("RelPath").attribute("Value").value());

    project->setFileName(node.child("FileName").attribute("Value").value());

    project->setDefaultWindow(node.child("DefaultWindow").attribute("Value").value());

    project->setLastWindow(node.child("LastWindow").attribute("Value").value());

    project->setMetaAuthor(node.child("Metadata").child("Author").text().as_string());

    project->setMetaName(node.child("Metadata").child("Name").text().as_string());

    project->setMetaDescription(node.child("Metadata").child("Description").text().as_string());

    project->setMetaDate(QDate::fromString(node.child("Metadata").child("Date").text().as_string()));

    project->setProjSet1(node.child("ProjectSettings").child("Set1").text().as_string());

    project->setProjSet2(node.child("ProjectSettings").child("Set2").text().as_string());

    project->setProjSet3(node.child("ProjectSettings").child("Set3").text().as_string());

    project->setProjSet4(node.child("ProjectSettings").child("Set4").text().as_string());

    node = doc.last_child();

    for(pugi::xml_node_iterator it = node.children().begin(); it != node.children().end(); it++){
        std::shared_ptr<Configuration> ptr(loadConfig(*it));
        project->addConfiguration(ptr);
    }

    int key;

    node = doc.first_child();

    key = node.child("DefaultConfig").first_attribute().as_int();
    if(key != 0) project->setDefaultConfig(project->getConfigurations().at(key));

    key = node.child("LastConfig").first_attribute().as_int();
    if(key != 0) project->setLastConfig(project->getConfigurations().at(key));

    return project;
}

/*!
 \brief

 \fn AppUtils::loadProject
 \param fullPath
 \return Project
*/
Project* AppUtils::loadProject(const wchar_t* fullPath){
    Project* project = new Project();

    pugi::xml_document doc;

    doc.load_file(fullPath);

    pugi::xml_node node = doc.first_child();

    project->setId(node.attribute("Id").value());

    project->setAbsPath(node.child("AbsPath").attribute("Value").value());

    project->setRelPath(node.child("RelPath").attribute("Value").value());

    project->setFileName(node.child("FileName").attribute("Value").value());

    project->setDefaultWindow(node.child("DefaultWindow").attribute("Value").value());

    project->setLastWindow(node.child("LastWindow").attribute("Value").value());

    project->setMetaAuthor(node.child("Metadata").child("Author").text().as_string());

    project->setMetaName(node.child("Metadata").child("Name").text().as_string());

    project->setMetaDescription(node.child("Metadata").child("Description").text().as_string());

    project->setMetaDate(QDate::fromString(node.child("Metadata").child("Date").text().as_string()));

    project->setProjSet1(node.child("ProjectSettings").child("Set1").text().as_string());

    project->setProjSet2(node.child("ProjectSettings").child("Set2").text().as_string());

    project->setProjSet3(node.child("ProjectSettings").child("Set3").text().as_string());

    project->setProjSet4(node.child("ProjectSettings").child("Set4").text().as_string());

    node = doc.last_child();

    for(pugi::xml_node_iterator it = node.children().begin(); it != node.children().end(); it++){
        std::shared_ptr<Configuration> ptr(loadConfig(*it));
        project->addConfiguration(ptr);
    }

    int key;

    node = doc.first_child();

    key = node.child("DefaultConfig").first_attribute().as_int();
    if(key != 0) project->setDefaultConfig(project->getConfigurations().at(key));

    key = node.child("LastConfig").first_attribute().as_int();
    if(key != 0) project->setLastConfig(project->getConfigurations().at(key));

    return project;
}

/*!
 \brief

 \fn AppUtils::radians
 \param d
 \return double
*/
double AppUtils::radians(const double d) {
return d * pi() / 180;
}

/*!
 \brief

 \fn AppUtils::degrees
 \param r
 \return double
*/
double AppUtils::degrees(const double r) {
return r * 180/ pi();
}

/*!
 \brief

 \fn AppUtils::stringToUpper
 \param strToConvert
 \return std::string
*/
std::string AppUtils::stringToUpper(std::string strToConvert){
    std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

    return strToConvert;
}

/*!
 \brief

 \fn AppUtils::exportConfiguration
 \param config
 \param fullPath
*/
void AppUtils::exportConfiguration(const Configuration* config, const std::string fullPath){
    std::ofstream configFile;
    std::string tolerances = "";
    std::unordered_multimap<std::string, std::shared_ptr<Energization>> enerMap;

    configFile.open(fullPath);
    configFile << "HIFREQ\n";
    configFile << "OPTIONS\n";
    configFile << "  RUN-IDENTIFI, " + config->getIdentifier() + "\n";
    configFile << "  UNITS, " + stringToUpper(config->getUnits()) + "\n";
    configFile << "  PRINTOUT, DETAILED\n";
    configFile << "SYSTEM\n";
    configFile << "    TOLERANCE,";

    for(double tolerance : config->getTolerances()){
        tolerances.append(dbl2str(tolerance, true, false)).append(",");
    }
    tolerances.pop_back();

    configFile << tolerances << "\n";

    for(unsigned int i=1; i<config->getEnergizations().size(); i++){

        if(config->getEnergizations().at(i)->getFrequency() == config->getFrequency() || config->getEnergizations().at(i)->getFrequency() == "Both"){
            double realPart, imagPart;
            realPart = config->getEnergizations().at(i)->getRealPart();
            imagPart = config->getEnergizations().at(i)->getImaginaryPart();

            configFile << "  ENERGIZATION, " << stringToUpper(config->getEnergizations().at(i)->getType()) << "," << dbl2str(round(realPart, 1), false, true) << "," << dbl2str(round(imagPart, 1), false, true) << ",,,,,," << config->getEnergizations().at(i)->getIdentification();

            configFile << enerMap.count(config->getEnergizations().at(i)->getIdentification()) << "\n";

            enerMap.emplace(config->getEnergizations().at(i)->getIdentification(), config->getEnergizations().at(i));
        }

    }

    configFile << "  CHARACTERISTICS\n";

    for(unsigned int i=2; i<config->getConductorTypes().size(); i++){
        configFile << "    CONDUCTOR-TYPE," << config->getConductorTypes().at(i)->getType() << "," << dbl2str(config->getConductorTypes().at(i)->getResistivity()) << "," << dbl2str(config->getConductorTypes().at(i)->getPermeability()) << ",,,,,,," << config->getConductorTypes().at(i)->getName() << "\n";
    }

    //COATING TYPES HERE

    //CABLE TYPES HERE

    configFile << "\n";
    configFile << "    SUBDIVISION,YES,\n";
    configFile << "  NETWORK\n";
    configFile << "    MAIN-GROUND\n";
    configFile << "\n";

    //TEMP ID ATTRIBUTION CENTER

    for(unsigned int i=0; i<config->getLeadTypes().size(); i++){
        config->getLeadTypes().at(i)->setTempId(i-1);
    }

    for(unsigned int i=0; i<config->getCoatings().size(); i++){
        config->getCoatings().at(i)->setTempId(i-1);
    }

    for(unsigned int i=0; i<config->getConductorTypes().size(); i++){
        config->getConductorTypes().at(i)->setTempId(i-1);
    }

    for(unsigned int i=0; i<config->getEnergizations().size(); i++){
        config->getEnergizations().at(i)->setTempId(i);
    }

    for(unsigned int i=0; i<config->getCableTypes().size(); i++){
        config->getCableTypes().at(i)->setTempId(i);
    }

    for(unsigned int i=0; i<config->getConductors().size(); i++){
        configFile << "      CONDUCTOR, " << std::to_string(config->getConductors().at(i)->getLeadType()->getTempId()) << ", " << std::to_string(config->getConductors().at(i)->getConductorType()->getTempId()) << ", " << std::to_string(config->getConductors().at(i)->getCoating()->getTempId()) << ", " << std::to_string(config->getConductors().at(i)->getEnergization()->getTempId()) << "," << dbl2str(config->getConductors().at(i)->getStartCoords().x, true, false) << "," << dbl2str(config->getConductors().at(i)->getStartCoords().y, true, true) << "," << dbl2str(config->getConductors().at(i)->getStartCoords().z, true, true) << "," << dbl2str(config->getConductors().at(i)->getEndCoords().x, true, false) << "," << dbl2str(config->getConductors().at(i)->getEndCoords().y, true, true) << "," << dbl2str(config->getConductors().at(i)->getEndCoords().z, true, true) << "," << dbl2str(config->getConductors().at(i)->getRadius(), true, true) << "," << std::to_string(config->getConductors().at(i)->getSubDivision()) << ",0\n";
    }

    configFile << "\n";

    for(unsigned int i=0; i<config->getBuildingConductors().size(); i++){
        configFile << "      CONDUCTOR, " << std::to_string(config->getBuildingConductors().at(i)->getLeadType()->getTempId()) << ", " << std::to_string(config->getBuildingConductors().at(i)->getConductorType()->getTempId()) << ", " << std::to_string(config->getBuildingConductors().at(i)->getCoating()->getTempId()) << ", " << std::to_string(config->getBuildingConductors().at(i)->getEnergization()->getTempId()) << "," << dbl2str(config->getBuildingConductors().at(i)->getStartCoords().x, true, false) << "," << dbl2str(config->getBuildingConductors().at(i)->getStartCoords().y, true, true) << "," << dbl2str(config->getBuildingConductors().at(i)->getStartCoords().z, true, true) << "," << dbl2str(config->getBuildingConductors().at(i)->getEndCoords().x, true, false) << "," << dbl2str(config->getBuildingConductors().at(i)->getEndCoords().y, true, true) << "," << dbl2str(config->getBuildingConductors().at(i)->getEndCoords().z, true, true) << "," << dbl2str(config->getBuildingConductors().at(i)->getRadius(), true, true) << "," << std::to_string(config->getBuildingConductors().at(i)->getSubDivision()) << ",0\n";
    }

    configFile << "\n\n";
    configFile << "COMPUTATIONS\n";
    configFile << "  DETERMINE\n";
    configFile << "    GPR, ";
    if(config->getComputations().GPR){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }
    configFile << "    POTENTIAL-SCALAR, ";
    if(config->getComputations().POTENTIAL_SCALAR){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }
    configFile << "    ELECTRIC, ";
    if(config->getComputations().ELECTRIC){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }
    configFile << "    MAGNETIC, ";
    if(config->getComputations().MAGNETIC){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }
    configFile << "    VECTOR-POTENTIAL, ";
    if(config->getComputations().VECTOR_POTENTIAL){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }
    configFile << "    GRADIENT-SCALAR, ";
    if(config->getComputations().GRADIENT_SCALAR){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }
    configFile << "    CURRENTS, COMPUTED\n";

    configFile << "  OBSERVATION\n";

    for(unsigned int i=0; i<config->getProfiles().size(); i++){
        configFile << "    PROFILE, " << std::to_string(config->getProfiles().at(i)->ptNum)
                   << "," << dbl2str(config->getProfiles().at(i)->start.x)
                   << "," << dbl2str(config->getProfiles().at(i)->start.y)
                   << "," << dbl2str(config->getProfiles().at(i)->start.z)
                   << "," << dbl2str(config->getProfiles().at(i)->ptStep.x)
                   << "," << dbl2str(config->getProfiles().at(i)->ptStep.y)
                   << "," << dbl2str(config->getProfiles().at(i)->ptStep.z)
                   << ",0\n";
        configFile << "      SURFACE," << std::to_string(config->getProfiles().at(i)->prNum)
                   << "," << dbl2str(config->getProfiles().at(i)->prStep.x)
                   << "," << dbl2str(config->getProfiles().at(i)->prStep.y)
                   << "," << dbl2str(config->getProfiles().at(i)->prStep.z)
                   << ",0\n";
    }

    configFile << "  FREQUENCY,60.,\n";
    configFile << "\n";
    configFile << "ENDPROGRAM";

    configFile.close();
}

double AppUtils::round(double value, int precision)
{
    const int adjustment = pow((double)10, precision);
    return floor(value * (adjustment) + 0.5) / adjustment;
}

/*!
 \brief

 \fn AppUtils::dbl2str
 \param d
 \return std::string
*/
std::string AppUtils::dbl2str(const double d, bool zeroFront, bool zeroBack)
{
    if(d == 0.0) return "0";
    size_t len = std::snprintf(0, 0, "%.10f", d);
    std::string s(len+1, 0);
    // technically non-portable, see below
    std::snprintf(&s[0], len+1, "%.10f", d);
    // remove nul terminator
    s.pop_back();
    // remove trailing zeros
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    // remove trailing point
    if(s.back() == '.') {
        if(!zeroBack){
            s.pop_back();
        }
        else{
            s.push_back('0');
        }
    }
    // remove front zero
    if(s.front() == '0' && !zeroFront){
        s.erase(s.begin());
    }
    return s;
}

/*!
 \brief

 \fn AppUtils::append_dbl2str
 \param s
 \param d
*/
void AppUtils::append_dbl2str(std::string s, const double d) {
    size_t len = std::snprintf(0, 0, "%.10f", d);
    size_t oldsize = s.size();
    s.resize(oldsize + len + 1);
    // technically non-portable
    std::snprintf(&s[oldsize], len+1, "%.10f", d);
    // remove nul terminator
    s.pop_back();
    // remove trailing zeros
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    // remove trailing point
    if(s.back() == '.') {
        s.pop_back();
    }
    // remove front zero
    if(s.front() == '0'){
        s.erase(s.begin());
    }
}

/*!
 \brief

 \fn AppUtils::uniqueIdGenerator
 \return std::string
*/
std::string AppUtils::uniqueIdGenerator(){
    std::string result = "failure";

    result = "P";
    append_dbl2str(result, m_projectId+1);
    m_projectId += 1;

    return result;
}

double AppUtils::componentIdGenerator(){
    if(m_currentConfig){
        return m_currentConfig->componentIdGenerator();
    }
    else{
        return -1;
    }
}

void AppUtils::setCurrentConfig(std::shared_ptr<Configuration> config){
    if(config){
        m_currentConfig = config;
    }
    else{
        m_currentConfig.reset();
    }
}

/*!
 \brief

 \fn AppUtils::saveProject
 \param project
 \param path
*/
void AppUtils::saveProject(const Project &project, std::string path){
    pugi::xml_document doc;

    pugi::xml_node projectNode = doc.append_child("Project");

    pugi::xml_node node;

    //Project node-------------------------------------------------------

    //Project attribute
    projectNode.append_attribute("Id").set_value(project.getId().c_str());

    //AbsPath node
    node = projectNode.append_child("AbsPath");
    node.append_attribute("Os").set_value(getOsName().c_str());
    node.append_attribute("Value").set_value(project.getAbsPath().c_str());

    //RelPath node
    node = projectNode.append_child("RelPath");
    node.append_attribute("Os").set_value(getOsName().c_str());
    node.append_attribute("Value").set_value(project.getRelPath().c_str());

    //FileName node
    node = projectNode.append_child("FileName");
    node.append_attribute("Value").set_value(project.getFileName().c_str());

    //DefaultConfig node
    node = projectNode.append_child("DefaultConfig");
    if(project.getDefaultConfig().lock().get() != NULL){
        node.append_attribute("Value").set_value(project.getDefaultConfig().lock()->getIdentifier().c_str());
    }

    //LastConfig node
    node = projectNode.append_child("LastConfig");
    if(project.getLastConfig().lock().get() != NULL){
        node.append_attribute("Value").set_value(project.getLastConfig().lock()->getIdentifier().c_str());
    }

    //DefaultWindow node
    node = projectNode.append_child("DefaultWindow");
    node.append_attribute("Value").set_value(project.getDefaultWindow().c_str());

    //LastWindow node
    node = projectNode.append_child("LastWindow");
    node.append_attribute("Value").set_value(project.getLastWindow().c_str());

    //Metadata node------------------------------------------------------------
    pugi::xml_node metadataNode = projectNode.append_child("Metadata");

    //Name node
    node = metadataNode.append_child("Name");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().name.c_str());

    //Date node
    node = metadataNode.append_child("Date");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().date.toString().toStdString().c_str());

    //Author node
    node = metadataNode.append_child("Author");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().author.c_str());

    //Description node
    node = metadataNode.append_child("Description");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().description.toPlainText().toStdString().c_str());

    //Metadata node end---------------------------------------------------------

    //ProjectSettings node------------------------------------------------------------
    pugi::xml_node projectSettingsNode = projectNode.append_child("ProjectSettings");

    //Set1 node
    node = projectSettingsNode.append_child("Set1");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set1.c_str());

    //Set2 node
    node = projectSettingsNode.append_child("Set2");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set2.c_str());

    //Set3 node
    node = projectSettingsNode.append_child("Set3");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set3.c_str());

    //Set4 node
    node = projectSettingsNode.append_child("Set4");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set4.c_str());

    //ProjectSettings node end---------------------------------------------------------

    //Project node end-----------------------------------------------------------------

    //Configurations
    pugi::xml_node configNode = doc.append_child("Configurations");

    for(auto& config : project.getConfigurations()){
        saveConfiguration(config.second.get(), configNode);
    }

    if(path == ""){
        path = getAppData();
    }

    QString filename = QString::fromStdString(project.getFileName());

    doc.save_file(QString::fromStdString(getPath(QString::fromStdString(path), filename)).toStdWString().c_str());
}

/*!
 \brief

 \fn AppUtils::saveProject
 \param project
*/
void AppUtils::saveProject(const Project &project){
    pugi::xml_document doc;

    pugi::xml_node projectNode = doc.append_child("Project");

    pugi::xml_node node;

    //Project node-------------------------------------------------------

    //Project attribute
    projectNode.append_attribute("Id").set_value(project.getId().c_str());

    //AbsPath node
    node = projectNode.append_child("AbsPath");
    node.append_attribute("Os").set_value(getOsName().c_str());
    node.append_attribute("Value").set_value(project.getAbsPath().c_str());

    //RelPath node
    node = projectNode.append_child("RelPath");
    node.append_attribute("Os").set_value(getOsName().c_str());
    node.append_attribute("Value").set_value(project.getRelPath().c_str());

    //FileName node
    node = projectNode.append_child("FileName");
    node.append_attribute("Value").set_value(project.getFileName().c_str());

    //DefaultConfig node
    node = projectNode.append_child("DefaultConfig");
    if(project.getDefaultConfig().lock().get() != NULL){
        node.append_attribute("Value").set_value(project.getDefaultConfig().lock()->getIdentifier().c_str());
    }

    //LastConfig node
    node = projectNode.append_child("LastConfig");
    if(project.getLastConfig().lock().get() != NULL){
        node.append_attribute("Value").set_value(project.getLastConfig().lock()->getIdentifier().c_str());
    }

    //DefaultWindow node
    node = projectNode.append_child("DefaultWindow");
    node.append_attribute("Value").set_value(project.getDefaultWindow().c_str());

    //LastWindow node
    node = projectNode.append_child("LastWindow");
    node.append_attribute("Value").set_value(project.getLastWindow().c_str());

    //Metadata node------------------------------------------------------------
    pugi::xml_node metadataNode = projectNode.append_child("Metadata");

    //Name node
    node = metadataNode.append_child("Name");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().name.c_str());

    //Date node
    node = metadataNode.append_child("Date");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().date.toString().toStdString().c_str());

    //Author node
    node = metadataNode.append_child("Author");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().author.c_str());

    //Description node
    node = metadataNode.append_child("Description");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().description.toPlainText().toStdString().c_str());

    //Metadata node end---------------------------------------------------------

    //ProjectSettings node------------------------------------------------------------
    pugi::xml_node projectSettingsNode = projectNode.append_child("ProjectSettings");

    //Set1 node
    node = projectSettingsNode.append_child("Set1");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set1.c_str());

    //Set2 node
    node = projectSettingsNode.append_child("Set2");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set2.c_str());

    //Set3 node
    node = projectSettingsNode.append_child("Set3");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set3.c_str());

    //Set4 node
    node = projectSettingsNode.append_child("Set4");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set4.c_str());

    //ProjectSettings node end---------------------------------------------------------

    //Project node end-----------------------------------------------------------------

    //Configurations
    pugi::xml_node configNode = doc.append_child("Configurations");

    for(auto& config : project.getConfigurations()){
        saveConfiguration(config.second.get(), configNode);
    }

    QString folder = QString::fromStdString(project.getAbsPath());
    QString filename = QString::fromStdString(project.getFileName());

    doc.save_file(QString::fromStdString(getPath(folder, filename)).toStdWString().c_str());

}

/*!
 \brief

 \fn AppUtils::saveConfiguration
 \param config
 \param parent
*/
void AppUtils::saveConfiguration(const Configuration* config, pugi::xml_node &parent){
    pugi::xml_node configNode = parent.append_child("Configuration");

    pugi::xml_node node;

    //Configuration node-------------------------------------------------------

    configNode.append_attribute("Id").set_value(config->getId());

    //Identifier node
    node = configNode.append_child("Identifier");
    node.append_attribute("Value").set_value(config->getIdentifier().c_str());

    //Units node
    node = configNode.append_child("Units");
    node.append_attribute("Value").set_value(config->getUnits().c_str());

    //Frequency node
    node = configNode.append_child("Frequency");
    node.append_attribute("Value").set_value(config->getFrequency().c_str());

    //LeadTypes node-----------------------------------------------------------
    pugi::xml_node leadTypesNode = configNode.append_child("LeadTypes");

    for(unsigned int i=0; i<config->getLeadTypes().size(); i++){
        node = leadTypesNode.append_child("LeadType");
        node.append_attribute("Id").set_value(config->getLeadTypes().at(i)->getId());
        node.append_attribute("Name").set_value(config->getLeadTypes().at(i)->getName().c_str());
        node.append_attribute("Locked").set_value(config->getLeadTypes().at(i)->isLocked());
    }

    //LeadTypes end------------------------------------------------------------

    //Coatings node-----------------------------------------------------------
    pugi::xml_node coatingsNode = configNode.append_child("Coatings");

    for(unsigned int i=0; i<config->getCoatings().size(); i++){
        node = coatingsNode.append_child("Coating");
        node.append_attribute("Id").set_value(config->getCoatings().at(i)->getId());
        node.append_attribute("Name").set_value(config->getCoatings().at(i)->getName().c_str());
        node.append_attribute("Locked").set_value(config->getCoatings().at(i)->isLocked());
    }

    //Coatings end------------------------------------------------------------

    //Energizations node-----------------------------------------------------------
    pugi::xml_node energizationsNode = configNode.append_child("Energizations");

    for(unsigned int i=0; i<config->getEnergizations().size(); i++){
        node = energizationsNode.append_child("Energization");
        node.append_attribute("Id").set_value(config->getEnergizations().at(i)->getId());
        node.append_attribute("Identification").set_value(config->getEnergizations().at(i)->getIdentification().c_str());
        node.append_attribute("Type").set_value(config->getEnergizations().at(i)->getType().c_str());
        node.append_attribute("Frequency").set_value(config->getEnergizations().at(i)->getFrequency().c_str());
        node.append_attribute("Angle").set_value(dbl2str(config->getEnergizations().at(i)->getAngle(), true, false).c_str());
        node.append_attribute("Magnitude").set_value(config->getEnergizations().at(i)->getMagnitude());
        node.append_attribute("Locked").set_value(config->getEnergizations().at(i)->isLocked());
    }

    //Energizations end------------------------------------------------------------

    //Tolerances node-----------------------------------------------------------
    pugi::xml_node tolerancesNode = configNode.append_child("Tolerances");

    for(double i_tolerance : config->getTolerances()){
        node = tolerancesNode.append_child("Tolerance");
        node.append_attribute("Value").set_value(dbl2str(i_tolerance).c_str());
    }

    //Tolerances end------------------------------------------------------------

    //ConductorTypes node-----------------------------------------------------------
    pugi::xml_node conductorTypesNode = configNode.append_child("ConductorTypes");

    for(unsigned int i=0; i<config->getConductorTypes().size(); i++){
        node = conductorTypesNode.append_child("ConductorType");
        node.append_attribute("Id").set_value(config->getConductorTypes().at(i)->getId());
        node.append_attribute("Type").set_value(config->getConductorTypes().at(i)->getType().c_str());
        node.append_attribute("Name").set_value(config->getConductorTypes().at(i)->getName().c_str());
        node.append_attribute("Resistivity").set_value(dbl2str(config->getConductorTypes().at(i)->getResistivity()).c_str());
        node.append_attribute("Permeability").set_value(dbl2str(config->getConductorTypes().at(i)->getPermeability()).c_str());
        node.append_attribute("Locked").set_value(config->getConductorTypes().at(i)->isLocked());
    }

    //ConductorTypes end------------------------------------------------------------

    //CableTypes node-----------------------------------------------------------
    pugi::xml_node cableTypesNode = configNode.append_child("CableTypes");

    for(unsigned int i=0; i<config->getCableTypes().size(); i++){
        node = cableTypesNode.append_child("CableType");
        node.append_attribute("Id").set_value(config->getCableTypes().at(i)->getId());
        node.append_attribute("Name").set_value(config->getCableTypes().at(i)->getName().c_str());
        node.append_attribute("Locked").set_value(config->getCableTypes().at(i)->isLocked());
    }

    //CableTypes end------------------------------------------------------------

    //Conductors node----------------------------------------------------------------
    pugi::xml_node conductorsNode = configNode.append_child("Conductors");
    pugi::xml_node conductorNode;

    for(unsigned int i=0; i<config->getConductors().size(); i++){
        conductorNode = conductorsNode.append_child("Conductor");
        conductorNode.append_attribute("Id").set_value(config->getConductors().at(i)->getId());
        conductorNode.append_attribute("Type").set_value("Conductor");

        node = conductorNode.append_child("LeadTypeId");
        if(config->getConductors().at(i)->getLeadType() != NULL){
            node.append_attribute("Value").set_value(config->getConductors().at(i)->getLeadType()->getId());
        }

        node = conductorNode.append_child("ConductorTypeId");
        if(config->getConductors().at(i)->getConductorType() != NULL){
            node.append_attribute("Value").set_value(config->getConductors().at(i)->getConductorType()->getId());
        }

        node = conductorNode.append_child("CoatingId");
        if(config->getConductors().at(i)->getCoating() != NULL){
            node.append_attribute("Value").set_value(config->getConductors().at(i)->getCoating()->getId());
        }

        node = conductorNode.append_child("EnergizationId");
        if(config->getConductors().at(i)->getEnergization() != NULL){
            node.append_attribute("Value").set_value(config->getConductors().at(i)->getEnergization()->getId());
        }

        node = conductorNode.append_child("CableTypeId");
        if(config->getConductors().at(i)->getCableType() != NULL){
            node.append_attribute("Value").set_value(config->getConductors().at(i)->getCableType()->getId());
        }

        node = conductorNode.append_child("CoordsStart");
        node.append_attribute("X").set_value(dbl2str(config->getConductors().at(i)->getStartCoords().x, true, true).c_str());
        node.append_attribute("Y").set_value(dbl2str(config->getConductors().at(i)->getStartCoords().y, true, true).c_str());
        node.append_attribute("Z").set_value(dbl2str(config->getConductors().at(i)->getStartCoords().z, true, true).c_str());

        node = conductorNode.append_child("CoordsEnd");
        node.append_attribute("X").set_value(dbl2str(config->getConductors().at(i)->getEndCoords().x, true, true).c_str());
        node.append_attribute("Y").set_value(dbl2str(config->getConductors().at(i)->getEndCoords().y, true, true).c_str());
        node.append_attribute("Z").set_value(dbl2str(config->getConductors().at(i)->getEndCoords().z, true, true).c_str());

        node = conductorNode.append_child("Radius");
        node.append_attribute("Value").set_value(dbl2str(config->getConductors().at(i)->getRadius(), true, true).c_str());
    }

    //Conductors end-----------------------------------------------------------------

    //Building Conductors node----------------------------------------------------------------
        conductorsNode = configNode.append_child("BuildingConductors");

    for(unsigned int i=0; i<config->getBuildingConductors().size(); i++){
        conductorNode = conductorsNode.append_child("Conductor");
        conductorNode.append_attribute("Id").set_value(config->getBuildingConductors().at(i)->getId());
        conductorNode.append_attribute("Type").set_value("BuildingConductor");

        node = conductorNode.append_child("LeadTypeId");
        if(config->getBuildingConductors().at(i)->getLeadType() != NULL){
            node.append_attribute("Value").set_value(config->getBuildingConductors().at(i)->getLeadType()->getId());
        }

        node = conductorNode.append_child("ConductorTypeId");
        if(config->getBuildingConductors().at(i)->getConductorType() != NULL){
            node.append_attribute("Value").set_value(config->getBuildingConductors().at(i)->getConductorType()->getId());
        }

        node = conductorNode.append_child("CoatingId");
        if(config->getBuildingConductors().at(i)->getCoating() != NULL){
            node.append_attribute("Value").set_value(config->getBuildingConductors().at(i)->getCoating()->getId());
        }

        node = conductorNode.append_child("EnergizationId");
        if(config->getBuildingConductors().at(i)->getEnergization() != NULL){
            node.append_attribute("Value").set_value(config->getBuildingConductors().at(i)->getEnergization()->getId());
        }

        node = conductorNode.append_child("CableTypeId");
        if(config->getBuildingConductors().at(i)->getCableType() != NULL){
            node.append_attribute("Value").set_value(config->getBuildingConductors().at(i)->getCableType()->getId());
        }

        node = conductorNode.append_child("CoordsStart");
        node.append_attribute("X").set_value(dbl2str(config->getBuildingConductors().at(i)->getStartCoords().x).c_str());
        node.append_attribute("Y").set_value(dbl2str(config->getBuildingConductors().at(i)->getStartCoords().y).c_str());
        node.append_attribute("Z").set_value(dbl2str(config->getBuildingConductors().at(i)->getStartCoords().z).c_str());

        node = conductorNode.append_child("CoordsEnd");
        node.append_attribute("X").set_value(dbl2str(config->getBuildingConductors().at(i)->getEndCoords().x).c_str());
        node.append_attribute("Y").set_value(dbl2str(config->getBuildingConductors().at(i)->getEndCoords().y).c_str());
        node.append_attribute("Z").set_value(dbl2str(config->getBuildingConductors().at(i)->getEndCoords().z).c_str());

        node = conductorNode.append_child("Radius");
        node.append_attribute("Value").set_value(dbl2str(config->getBuildingConductors().at(i)->getRadius()).c_str());
    }

    //Building Conductors end-----------------------------------------------------------------

    //Buildings node----------------------------------------------------------------
    pugi::xml_node buildingsNode = configNode.append_child("Buildings");
    pugi::xml_node buildingNode;

    for(unsigned int i=0; i<config->getBuildings().size(); i++){
        buildingNode = buildingsNode.append_child("Building");
        buildingNode.append_attribute("Id").set_value(config->getBuildings().at(i)->getId());

        node = buildingNode.append_child("Faces");
        node.append_attribute("Value").set_value(std::to_string(config->getBuildings().at(i)->getFaces()).c_str());

        node = buildingNode.append_child("Height");
        node.append_attribute("Value").set_value(std::to_string(config->getBuildings().at(i)->getHeight()).c_str());

        node = buildingNode.append_child("Step");
        node.append_attribute("Value").set_value(dbl2str(config->getBuildings().at(i)->getStep()).c_str());

        node = buildingNode.append_child("Distance");
        node.append_attribute("Value").set_value(std::to_string(config->getBuildings().at(i)->getDistance()).c_str());

        node = buildingNode.append_child("Length");
        node.append_attribute("Value").set_value(std::to_string(config->getBuildings().at(i)->getLength()).c_str());

        node = buildingNode.append_child("Width");
        node.append_attribute("Value").set_value(std::to_string(config->getBuildings().at(i)->getWidth()).c_str());

        node = buildingNode.append_child("Radius");
        node.append_attribute("Value").set_value(dbl2str(config->getBuildings().at(i)->getRadius()).c_str());

        node = buildingNode.append_child("LeadTypeId");
        if(config->getBuildings().at(i)->getLeadType() != NULL){
            node.append_attribute("Value").set_value(config->getBuildings().at(i)->getLeadType()->getId());
        }

        node = buildingNode.append_child("ConductorTypeId");
        if(config->getBuildings().at(i)->getConductorType() != NULL){
            node.append_attribute("Value").set_value(config->getBuildings().at(i)->getConductorType()->getId());
        }

        node = buildingNode.append_child("CoatingId");
        if(config->getBuildings().at(i)->getCoating() != NULL){
            node.append_attribute("Value").set_value(config->getBuildings().at(i)->getCoating()->getId());
        }

        node = buildingNode.append_child("EnergizationId");
        if(config->getBuildings().at(i)->getEnergization() != NULL){
            node.append_attribute("Value").set_value(config->getBuildings().at(i)->getEnergization()->getId());
        }

        node = buildingNode.append_child("CableTypeId");
        if(config->getBuildings().at(i)->getCableType() != NULL){
            node.append_attribute("Value").set_value(config->getBuildings().at(i)->getCableType()->getId());
        }
    }

    //Buildings end-----------------------------------------------------------------

    //Computations node----------------------------------------------------------------
    pugi::xml_node computationsNode = configNode.append_child("Computations");

    node = computationsNode.append_child("GPR");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().GPR));

    node = computationsNode.append_child("POTENTIAL-SCALAR");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().POTENTIAL_SCALAR));

    node = computationsNode.append_child("ELECTRIC");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().ELECTRIC));

    node = computationsNode.append_child("MAGNETIC");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().MAGNETIC));

    node = computationsNode.append_child("VECTOR-POTENTIAL");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().VECTOR_POTENTIAL));

    node = computationsNode.append_child("GRADIENT-SCALAR");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().GRADIENT_SCALAR));

    //Computations end-----------------------------------------------------------------

    //Profiles node----------------------------------------------------------------
    pugi::xml_node profilesNode = configNode.append_child("Profiles");
    pugi::xml_node profileNode;

    for(unsigned int i=0; i<config->getProfiles().size(); i++){
        profileNode = profilesNode.append_child("Profile");
        profileNode.append_attribute("Id").set_value(config->getProfiles().at(i)->id);

        node = profileNode.append_child("ProfileStart");
        node.append_attribute("X").set_value(dbl2str(config->getProfiles().at(i)->start.x).c_str());
        node.append_attribute("Y").set_value(dbl2str(config->getProfiles().at(i)->start.y).c_str());
        node.append_attribute("Z").set_value(dbl2str(config->getProfiles().at(i)->start.z).c_str());

        node = profileNode.append_child("PointStep");
        node.append_attribute("Dx").set_value(dbl2str(config->getProfiles().at(i)->ptStep.x).c_str());
        node.append_attribute("Dy").set_value(dbl2str(config->getProfiles().at(i)->ptStep.y).c_str());
        node.append_attribute("Dz").set_value(dbl2str(config->getProfiles().at(i)->ptStep.z).c_str());

        node = profileNode.append_child("ProfileStep");
        node.append_attribute("Dx").set_value(dbl2str(config->getProfiles().at(i)->prStep.x).c_str());
        node.append_attribute("Dy").set_value(dbl2str(config->getProfiles().at(i)->prStep.y).c_str());
        node.append_attribute("Dz").set_value(dbl2str(config->getProfiles().at(i)->prStep.z).c_str());

        node = profileNode.append_child("NumberPoints");
        node.append_attribute("Value").set_value(dbl2str(config->getProfiles().at(i)->ptNum).c_str());

        node = profileNode.append_child("NumberProfiles");
        node.append_attribute("Value").set_value(dbl2str(config->getProfiles().at(i)->prNum).c_str());
    }

    //Profiles end-----------------------------------------------------------------
}
