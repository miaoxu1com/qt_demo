#include "stdafx.h"
#include "excelwriter.h"
#include "QXlsx/header/xlsxdocument.h"
#include <QDebug>
using namespace QXlsx;

bool ExcelWriter::writeTestCasesToExcel(const QList<TestCase>& cases, const QString& outputPath) {

    Document xlsx;

    xlsx.write("A1", "用例名称");
    xlsx.write("B1", "测试步骤");
    xlsx.write("C1", "预期结果");

    int row = 2;
    for (const auto& t : cases) {
        xlsx.write("A" + QString::number(row), t.caseName);
        xlsx.write("B" + QString::number(row), t.testSteps);
        xlsx.write("C" + QString::number(row), t.expectedResult);
        row++;
    }

    return xlsx.saveAs(outputPath);
}