#include <QApplication>
#include <QCloseEvent>
#include <QPushButton>
#include <QBoxLayout>
#include <QDir>
#include <QTranslator>

#include "languagechooser.h"

namespace model
{

LanguageChooser::LanguageChooser(QWidget *parent)
    : QDialog(parent)
{    
    setMinimumWidth(200);

    QDir dir;
    QFileInfoList translations = dir.entryInfoList(QStringList("*.qm"), QDir::Files);

    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);

    QList<QPushButton*> languages;
    QFont defaultFont = font();
    defaultFont.setPixelSize(20);
    foreach (QFileInfo inf, translations)
    {
        QPushButton* aLanguage = new QPushButton(inf.baseName());
        layout->addWidget(aLanguage);
        languages << aLanguage;
        aLanguage->setFont(defaultFont);
    }
    QPushButton* defaultLang = new QPushButton("русский");
    layout->addWidget(defaultLang);
    defaultLang->setFont(defaultFont);
    languages << defaultLang;

    foreach (QPushButton* aLang, languages)
        connect(aLang, SIGNAL(clicked()), SLOT(languageChoosed()));
}

void LanguageChooser::closeEvent(QCloseEvent *_ev)
{
    _ev->ignore();
}

void LanguageChooser::languageChoosed()
{
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    Q_ASSERT(button);
    if(!button)
        return;

    // check for mem leak
    QTranslator* translator = new QTranslator();
    QString language = button->text();
    bool success = translator->load(language);
    if(!success)
    {
        done(1);
        return;
    }
    Q_ASSERT(success);
    success = qApp->installTranslator(translator);
    Q_ASSERT(success);
    done(1);
}

} // namespace model
