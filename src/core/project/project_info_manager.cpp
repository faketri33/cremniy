#include "project_info_manager.h"
#include "core/file/filemanager.h"
#include "core/file/filecontext.h"


QString ProjectInfoManager::projectInfoFilePath(const QString &projectPath) {

    QDir dir(projectPath);
    QString fullPath = dir.filePath(m_projectInfoFileName);
    return fullPath;

}


bool ProjectInfoManager::loadProjectInfo(const QString &projectPath, ProjectInfo &outInfo){

    FileContext fctx(projectInfoFilePath(projectPath));
    QJsonObject jsonObj = FileManager::loadJson(fctx);

    if (jsonObj.isEmpty()) {
        return false;
    }

    outInfo = ProjectInfo::fromJson(jsonObj);
    return true;

}


void ProjectInfoManager::saveProjectInfo(const ProjectInfo &projInfo){

    FileContext fctx(projectInfoFilePath(projInfo.path));
    FileManager::saveJson(fctx, projInfo.toJson());

}
