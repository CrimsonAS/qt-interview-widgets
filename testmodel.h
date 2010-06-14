/*
 * Copyright (C) 2010 Collabora Ltd. <http://www.collabora.co.uk/>
 * Copyright (C) 2010 Robin Burchell <robin.burchell@collabora.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef TESTMODEL_H
#define TESTMODEL_H

#include <QAbstractListModel>

/** A regular Qt model subclass.
  */
class TestModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TestModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
signals:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
private:
    QList<QString> m_strings;
};

#endif // TESTMODEL_H
