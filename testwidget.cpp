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

#include "testwidget.h"
#include "ui_testwidget.h"

TestWidget::TestWidget(QAbstractItemModel *model, QModelIndex index) :
    AWidget(model, index),
    ui(new Ui::TestWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onUpdate()));
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TestWidget::onUpdate()
{
    model()->setData(index(), ui->lineEdit->text(), Qt::DisplayRole);
}

void TestWidget::dataChanged()
{
    ui->label->setText(model()->data(index(), Qt::DisplayRole).toString());
}
