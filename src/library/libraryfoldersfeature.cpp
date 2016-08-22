#include <QAbstractItemModel>
#include <QAction>
#include <QMenu>

#include "library/libraryfoldersfeature.h"

#include "library/libraryfoldermodel.h"
#include "widget/wlibrarysidebar.h"

LibraryFoldersFeature::LibraryFoldersFeature(UserSettingsPointer pConfig,
                                             Library* pLibrary,
                                             QObject* parent,
                                             TrackCollection* pTrackCollection)
        : MixxxLibraryFeature(pConfig, pLibrary, parent, pTrackCollection) {
    
    setChildModel(new LibraryFolderModel(this, m_pTrackCollection, m_pConfig));
}

QVariant LibraryFoldersFeature::title() {
    return "Folders";
}

QString LibraryFoldersFeature::getIconPath() {
    return ":/images/library/ic_library_folder.png";
}

QString LibraryFoldersFeature::getSettingsName() const {
    return "LibraryFoldersFeature";
}

QWidget* LibraryFoldersFeature::createInnerSidebarWidget(KeyboardEventFilter* pKeyboard) {
    return createLibrarySidebarWidget(pKeyboard);
}

void LibraryFoldersFeature::onRightClickChild(const QPoint&pos, 
                                              const QModelIndex&) {
    
    bool recursive = m_pChildModel->data(QModelIndex(), 
                                         TreeItemModel::RoleSettings).toBool();
    
    QMenu menu;
    QAction* showRecursive = menu.addAction(tr("Show recursive view in folders"));
    showRecursive->setCheckable(true);
    showRecursive->setChecked(recursive);
    
    QAction* selected = menu.exec(pos);
    
    if (selected == showRecursive) {
        m_pChildModel->setData(QModelIndex(), selected->isChecked(), 
                               TreeItemModel::RoleSettings);
    } else {
        // Menu rejected
        return;
    }
    
    m_pChildModel->reloadTree();
}