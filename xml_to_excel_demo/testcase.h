// testcase.h
#pragma once
#include <QString>

struct TestCase {
    QString caseName;
    QString testSteps;
    QString expectedResult;

    TestCase() = default;
    TestCase(const QString& name, const QString& steps, const QString& result)
        : caseName(name), testSteps(steps), expectedResult(result) {
    }
};
