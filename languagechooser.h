#ifndef MODEL_LANGUAGECHOOSER_H
#define MODEL_LANGUAGECHOOSER_H

#include <QDialog>

namespace model
{

class LanguageChooser : public QDialog
{
    Q_OBJECT
public:
    explicit LanguageChooser(QWidget *parent = 0);

private:
    void closeEvent(QCloseEvent* _ev);

private slots:
    void languageChoosed();

};

} // namespace model

#endif // MODEL_LANGUAGECHOOSER_H
