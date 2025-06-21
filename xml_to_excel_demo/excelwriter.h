#pragma once
// excelwriter.h
#include <QString>
#include <QList>
#include "testcase.h"

class ExcelWriter {
public:
    static bool writeTestCasesToExcel(const QList<TestCase>& cases, const QString& outputPath);
};
