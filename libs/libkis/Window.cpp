/*
 *  Copyright (c) 2016 Boudewijn Rempt <boud@valdyas.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include "Window.h"

#include <KisMainWindow.h>
#include <KisPart.h>
#include <KisDocument.h>

#include <Document.h>
#include <View.h>


struct Window::Private {
    Private() {}

    QPointer<KisMainWindow> window;
};

Window::Window(KisMainWindow *window, QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->window = window;
    connect(window, SIGNAL(destroyed(QObject*)), SIGNAL(windowClosed()));
}

Window::~Window()
{
    delete d;
}

QMainWindow *Window::qwindow() const
{
    return d->window;
}

QList<View*> Window::views() const
{
    QList<View *> ret;
    if (d->window) {
        foreach(QPointer<KisView> view, KisPart::instance()->views()) {
            if (view->mainWindow() == d->window) {
                ret << new View(view);
            }
        }
    }
    return ret;

}

View *Window::addView(Document *document)
{
    if (d->window) {
        KisView *view = KisPart::instance()->createView(document->document(),
                                                    d->window->resourceManager(),
                                                    d->window->actionCollection(),
                                                    d->window);
        d->window->addView(view);
        return new View(view);
    }
    return 0;
}

void Window::showView(View *view)
{
    if (views().contains(view)) {
        KisView *v = view->view();
        d->window->showView(v);
    }
}

void Window::activate()
{
    if (d->window) {
        d->window->activateWindow();
    }
}

void Window::close()
{
    if (d->window) {
        KisPart::instance()->removeMainWindow(d->window);
        d->window->close();
    }
}



