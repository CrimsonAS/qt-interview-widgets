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

#include "qtmodelwidget.h"

QtModelWidget::QtModelWidget(QAbstractItemModel *model, QModelIndex index) :
    QWidget(0),
    m_model(model),
    m_index(index)
{
}

QModelIndex QtModelWidget::index() const
{
    return m_index;
}

QAbstractItemModel *QtModelWidget::model() const
{
    return m_model;
}

void QtModelWidget::dataChanged()
{
    // must be reimplemented by an inheriting class
    abort();
}
