# `formeditorgraphicsview.h`
Contains the code for painting the CheckerBoard background in the designer

# `formeditoritem.h`
Contains the code that draws the QML controls into the designer
* `void FormEditorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)`
is the function that does the drawing of the QML control in the designer.
these are the lines that do all the heavy lifting:
```
//            if (m_blurContent)
//                painter->drawPixmap(m_paintedBoundingRect.topLeft(), qmlItemNode().instanceBlurredRenderPixmap());
//            else
//                painter->drawPixmap(m_paintedBoundingRect.topLeft(), qmlItemNode().instanceRenderPixmap());
```

# `plugins/qmldesigner/designercore/include/nodeinstanceview.h`
the function `void NodeInstanceView::pixmapChanged(const PixmapChangedCommand &command)` is what updates the control image so that the designer can draw it.

# qml2puppet
this executable is what creates and runs the qml files and is what provides the designer with the renders of the QML previews. it looks like it was done like this (separated from the QtCreator executable) to prevent QtCreator from crashing if the QML emulation ran into problems. 
the data exchange between QtCreator and the qml2puppet executable is done via QSharedMemory.
* this line: `new QmlDesigner::Qt5NodeInstanceClientProxy(application);` inside the `share/qtcreator/qml/qmlpuppet/qml2puppet/qml2puppetmain.cpp` > `internalMain()` function is the heart of the qml2puppet executable
* the function `Qt5NodeInstanceClientProxy(QObject *parent = nullptr)` inside the file `share/qtcreator/qml/qmlpuppet/qml2puppet/instances/qt5nodeinstanceclientproxy.h` is responsible for executing the taks requested from the `qml2puppet` executable through the cmmand line arguments.
* the function `QImage QuickItemNodeInstance::renderPreviewImage(const QSize &previewImageSize)` inside the file `share/qtcreator/qml/qmlpuppet/qml2puppet/instances/quickitemnodeinstance.h` is what renders any QML control into a QImage that is then sent to the designer to be displayed.
    **Note:** this function depends on the calss `QQuickDesignerSupport` which is found in `QtQuick/private/qquickdesignersupport_p.h` under the Qt SDK Header files Dir. this file isn't part of the SDK and looks like it's been removed in Qt 6.
