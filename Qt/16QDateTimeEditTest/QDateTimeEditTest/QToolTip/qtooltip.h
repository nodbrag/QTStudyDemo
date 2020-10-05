/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtWidgets module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
 * 说明：此QToolTip模块修改子QT库中的源码，原因是由于tootip与QDateTimeEdit一起使用时，点击上下箭头，弹出的
 * 提示，一下就消失了。点击QDateTimeEdit调节时间时，触发了QEvent::wheel鼠标滚轮消息，以至于tip被隐藏。
 * 此模块修复了这个问题。
*/

#ifndef QTOOLTIP_H
#define QTOOLTIP_H

#include <QtWidgets/qwidget.h>

#define MY_BEGIN_NAMESPACE namespace MY_NAMESPACE {
#define MY_END_NAMESPACE }

MY_BEGIN_NAMESPACE


#ifndef QT_NO_TOOLTIP

class /*Q_WIDGETS_EXPORT*/ QToolTip
{
    QToolTip() Q_DECL_EQ_DELETE;
public:
    // ### Qt 6 - merge the three showText functions below
    static void showText(const QPoint &pos, const QString &text, QWidget *w = 0);
    static void showText(const QPoint &pos, const QString &text, QWidget *w, const QRect &rect);
    static void showText(const QPoint &pos, const QString &text, QWidget *w, const QRect &rect, int msecShowTime);
    static inline void hideText() { showText(QPoint(), QString()); }

    static bool isVisible();
    static QString text();

    static QPalette palette();
    static void setPalette(const QPalette &);
    static QFont font();
    static void setFont(const QFont &);
};

#endif // QT_NO_TOOLTIP

MY_END_NAMESPACE

#endif // QTOOLTIP_H
