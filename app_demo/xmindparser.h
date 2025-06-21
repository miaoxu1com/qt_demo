#pragma once
#include <QString>
#include <QList>
#include "testcase.h"

class XmindParser {
public:
	static QList<TestCase> parseXmindFile(const QString& filePath);
	static QString extractXmindToTempDir(const QString& filePath);

private:
	static QList<TestCase> parseContentXml(const QString& xmlPath);
};