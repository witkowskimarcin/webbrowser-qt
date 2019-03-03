#ifndef HTMLHIGHTLIGHTER_H
#define HTMLHIGHTLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>

class HtmlHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    HtmlHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};

#endif // HTMLHIGHTLIGHTER_H
