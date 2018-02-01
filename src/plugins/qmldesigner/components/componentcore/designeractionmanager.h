/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include <qmldesignercorelib_global.h>
#include "actioninterface.h"

#include <coreplugin/actionmanager/command.h>
#include <utils/styledbar.h>

#include <QToolBar>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
class QGraphicsWidget;
QT_END_NAMESPACE

namespace QmlDesigner {

class DesignerActionManagerView;

typedef std::function<bool (const QString &filename, const QString &targetDirectory)> AddResourceOperation;

struct AddResourceHandler
{
public:
    AddResourceHandler( const QString &_category,
                        const QString &_filter,
                        AddResourceOperation _operation)
        : category(_category)
        ,filter(_filter)
        ,operation(_operation)
    {
    }

    QString category;
    QString filter;
    AddResourceOperation operation;
};

class DesignerActionToolBar : public Utils::StyledBar
{
public:
    DesignerActionToolBar(QWidget *parentWidget);
    void registerAction(ActionInterface *action);
    void addSeparator();

private:
    QToolBar *m_toolBar;
};

class QMLDESIGNERCORE_EXPORT DesignerActionManager {
public:
    DesignerActionManager(DesignerActionManagerView *designerActionManagerView);
    ~DesignerActionManager();

    void addDesignerAction(ActionInterface *newAction);
    void addCreatorCommand(Core::Command *command, const QByteArray &category, int priority,
                           const QIcon &overrideIcon = QIcon());
    QList<ActionInterface* > designerActions() const;

    void createDefaultDesignerActions();
    void createDefaultAddResourceHandler();
    DesignerActionManagerView *view();

    DesignerActionToolBar *createToolBar(QWidget *parent = 0) const;
    void polishActions() const;
    QGraphicsWidget *createFormEditorToolBar(QGraphicsItem *parent);

    static DesignerActionManager &instance();
    void setupContext();

    DesignerActionManager(const DesignerActionManager&) = delete;
    DesignerActionManager & operator=(const DesignerActionManager&) = delete;

    QList<AddResourceHandler> addResourceHandler() const;
    void registerAddResourceHandler(const AddResourceHandler &handler);

private:
    QList<QSharedPointer<ActionInterface> > m_designerActions;
    DesignerActionManagerView *m_designerActionManagerView;
    QList<AddResourceHandler> m_addResourceHandler;
};

} //QmlDesigner
