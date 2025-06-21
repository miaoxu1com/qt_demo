#include "stdafx.h"
#include <QDomDocument>
#include "xmindparser.h"
#include <QProcess>
#include <QDir>
#include <QDebug>
#include <QFile>

QString XmindParser::extractXmindToTempDir(const QString& filePath) {
    QDir tempDir(QDir::tempPath() + "/xmind_extracted");
    if (tempDir.exists()) {
        tempDir.removeRecursively(); // 清空旧目录
    }
    tempDir.mkpath(".");

    QProcess process;
    process.start("7z", QStringList() << "x" << filePath << "-o" + tempDir.path() << "-y");
    process.waitForFinished(-1);

    return tempDir.path();
}

QList<TestCase> XmindParser::parseXmindFile(const QString& filePath) {
    QString tempPath = extractXmindToTempDir(filePath);
    QString contentXmlPath = tempPath + "/content.xml"; // 根据实际路径调整
    return parseContentXml(contentXmlPath);
}

QList<TestCase> XmindParser::parseContentXml(const QString& xmlPath) {
    QFile file(xmlPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "无法打开 XML 文件：" << xmlPath;
        return {};
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "无法解析 XML 内容：" << xmlPath;
        return {};
    }
    file.close();

    QList<TestCase> cases;

    QDomElement root = doc.documentElement();
    QDomNodeList topics = root.elementsByTagName("topic");

    for (int i = 0; i < topics.size(); ++i) {
        QDomElement topic = topics.at(i).toElement();
        if (topic.isNull()) continue;

        QString name = topic.attribute("text");
        if (name.isEmpty()) continue;

        TestCase t;
        t.caseName = name;

        QStringList steps;
        QString expected;

        QDomNode child = topic.firstChild();
        while (!child.isNull()) {
            QDomElement e = child.toElement();
            if (e.tagName() == "topic") {
                QString title = e.attribute("text");
                QDomNode gChild = e.firstChild();
                bool hasChildren = false;
                while (!gChild.isNull()) {
                    if (gChild.toElement().tagName() == "topic") {
                        hasChildren = true;
                        break;
                    }
                    gChild = gChild.nextSibling();
                }

                if (hasChildren) {
                    steps << title;
                }
                else {
                    expected = title;
                }
            }
            child = child.nextSibling();
        }

        t.testSteps = steps.join("\n");
        t.expectedResult = expected;

        cases.append(t);
    }

    return cases;
}