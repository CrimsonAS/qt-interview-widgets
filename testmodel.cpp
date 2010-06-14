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

#include "testmodel.h"

TestModel::TestModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_strings.append("hi");
    m_strings.append("there");
    m_strings.append("my");
    m_strings.append("name");
    m_strings.append("is");
    m_strings.append("jeb");
    m_strings.append("test");
    m_strings.append("test");
    m_strings.append("test");
    m_strings.append("test");
}

int TestModel::rowCount(const QModelIndex &parent) const
{
    return m_strings.count();
}

QVariant TestModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    return m_strings.at(index.row());
}

bool TestModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::DisplayRole)
        return false;

    m_strings[index.row()] = value.toString();
    emit dataChanged(index, index);
    return true;
}
