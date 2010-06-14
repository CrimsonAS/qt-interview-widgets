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

#include <QStyledItemDelegate>

#include "qtwidgetlistview.h"
#include "qtmodelwidget.h"

class QtWidgetListDelegate : public QStyledItemDelegate
{
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        // Remove selected state
        QStyleOptionViewItemV4 opt(option);
        initStyleOption(&opt, index);

        opt.state &= ~QStyle::State_Selected;

        QStyledItemDelegate::paint(painter, opt, index);
    }
};

QtWidgetListView::QtWidgetListView(QWidget *parent) :
    QListWidget(parent),
    m_metaObject(0)
{
    setItemDelegate(new QtWidgetListDelegate);
}

void QtWidgetListView::setMetaObject(const QMetaObject *metaObject)
{
    m_metaObject = metaObject;
}

void QtWidgetListView::setModel(QAbstractItemModel *model)
{
    // TODO: disconnect signals from old model

    // connect signals to new model
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onDataChanged(QModelIndex,QModelIndex)));
    connect(model, SIGNAL(layoutChanged()), this, SLOT(populateModel())); // cheat: just redo the whole view if layout changes
    connect(model, SIGNAL(modelReset()), this, SLOT(populateModel())); // not sure precisely what this is supposed to do; so we cheat
    connect(model, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(populateModel())); // this won't perform great. we should do it properly.
    connect(model, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(populateModel())); // this won't perform great. we should do it properly.

    m_model = model;
    populateModel();
}

void QtWidgetListView::populateModel()
{
    // clear old widget list
    while (!m_widgets.empty())
        m_widgets.takeFirst()->deleteLater();

    // remove all rows from the view
    clear();

    for (int i = 0; i != m_model->rowCount(); ++i) {
        QtModelWidget *widget = static_cast<QtModelWidget *>(m_metaObject->newInstance
                                                 (
                                                  Q_ARG(QAbstractItemModel*, m_model),
                                                  Q_ARG(QModelIndex, m_model->index(i, 0))
                                                 ));
        // if this asserts, you either:
        // 1) have the wrong constructor arguments
        // 2) forgot to mark it Q_INVOKABLE.
        Q_ASSERT(widget);

        m_widgets.append(widget);

        QListWidgetItem *item = new QListWidgetItem(this);
        insertItem(i, item);
        setItemWidget(item, widget);
    }

    // Populate the UI for the first time
    if (m_widgets.count())
        onDataChanged(m_model->index(0, 0), m_model->index(m_widgets.count() - 1, 0));
}

void QtWidgetListView::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    // send notifications to all the widgets that their data changed
    int bottomRow = bottomRight.row() + 1;
    for (int i = topLeft.row(); i != bottomRow; ++i) {
        QtModelWidget *widget = m_widgets.at(i);

        // tell it its data changed so it can reposition UI
        widget->dataChanged();

        // get the new sizehint from it
        QSize size = widget->sizeHint();

        // cap at our own width
        if (size.width() > viewport()->geometry().width())
            size.setWidth(viewport()->geometry().width());

        // change sizehint on the item.
        item(i)->setSizeHint(size);
    }
}
