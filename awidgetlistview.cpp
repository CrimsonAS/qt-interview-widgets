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

#include "awidgetlistview.h"
#include "awidget.h"

AWidgetListView::AWidgetListView(const QMetaObject *metaObject, QWidget *parent) :
    QListWidget(parent),
    m_metaObject(metaObject)
{
}

void AWidgetListView::setModel(QAbstractItemModel *model)
{
    // TODO: disconnect signals from old model

    // connect signals to new model
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onDataChanged(QModelIndex,QModelIndex)));
    connect(model, SIGNAL(layoutChanged()), this, SLOT(populateModel())); // cheat: just redo the whole view if layout changes
    connect(model, SIGNAL(modelReset()), this, SLOT(populateModel())); // not sure precisely what this is supposed to do; so we cheat
    connect(model, SIGNAL(rowsInserted()), this, SLOT(populateModel())); // this won't perform great. we should do it properly.
    connect(model, SIGNAL(rowsMoved()), this, SLOT(populateModel())); // this won't perform great. we should do it properly.
    connect(model, SIGNAL(rowsRemoved()), this, SLOT(populateModel())); // this won't perform great. we should do it properly.

    m_model = model;
    populateModel();
}

void AWidgetListView::populateModel()
{
    // clear old widget list
    while (!m_widgets.empty())
        m_widgets.takeFirst()->deleteLater();

    for (int i = 0; i != m_model->rowCount(); ++i) {
        AWidget *widget = static_cast<AWidget *>(m_metaObject->newInstance
                                                 (
                                                  Q_ARG(QAbstractItemModel*, m_model),
                                                  Q_ARG(QModelIndex, m_model->index(i, 0))
                                                 ));

        m_widgets.append(widget);

        QListWidgetItem *item = new QListWidgetItem(this);
        insertItem(i, item);
        setItemWidget(item, widget);
    }

    // Populate the UI for the first time
    onDataChanged(m_model->index(0, 0), m_model->index(m_widgets.count() - 1, 0));
}

void AWidgetListView::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    // send notifications to all the widgets that their data changed
    int bottomRow = bottomRight.row() + 1;
    for (int i = topLeft.row(); i != bottomRow; ++i) {
        m_widgets.at(i)->dataChanged();

        // Alter sizehints for this item also
        item(i)->setSizeHint(m_widgets.at(i)->sizeHint());
    }
}
