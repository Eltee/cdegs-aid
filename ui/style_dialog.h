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

#ifndef STYLE_DIALOG_H
#define STYLE_DIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QStringList>
#include "../util/apputils.h"

namespace Ui {
    class style_dialog;
}

/*!
 \brief

 \class style_dialog style_dialog.h "ui/style_dialog.h"
*/
class style_dialog : public QDialog
{
        Q_OBJECT

    public:
        explicit style_dialog(QWidget *parent = 0);
        void populateModel();
        void connectSlots();
        ~style_dialog();

    public slots:
        void buttonOk();

    private slots:
        void selectStyle(QModelIndex index);

    signals:
        std::string returnStyle(std::string style);

    private:
        Ui::style_dialog *ui;
        QStringListModel* m_model;
        std::string m_style;
};

#endif // STYLE_DIALOG_H
