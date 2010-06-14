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

#ifndef AWIDGETLISTVIEW_H
#define AWIDGETLISTVIEW_H

#include <QListWidget>
class QtModelWidget;

/** QtWidgetListView is a list view, powered by Qt's Interview framework.
  * Unlike a traditional listview, it allows for full, easy customisation of the UI, by presenting items
  * as regular widgets, which may be created through Qt Designer or other means.
  */
class QtWidgetListView : public QListWidget
{
    Q_OBJECT
public:
    /** Create a view instance.
      * @param metaObject The meta object of the AWidget class you wish this listview to use.
      *                   e.g. MyClass::staticMetaObject
      * @param parent A regular QObject parent.
      */
    explicit QtWidgetListView(const QMetaObject *metaObject, QWidget *parent = 0);

    /** Sets the model of this view.
      * @param model A subclass of QAbstractItemModel.
      */
    void setModel(QAbstractItemModel *model);

private slots:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void populateModel();
private:
    const QMetaObject *m_metaObject;
    QList<QtModelWidget *> m_widgets;
    QAbstractItemModel *m_model;
};

#endif // AWIDGETLISTVIEW_H
