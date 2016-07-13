#include "locale.h"

#include <FL/fl_utf8.h>

#include "constants.h"
#include "util.h"
#include "os_specific.h"

#define KEY_LANGUAGE "lang"
#define KEY_LANGUAGE_INDEX "lang_index"

using namespace std;

static Language* languages[] = {
    new Language("System Default", ""),
    new Language("Čeština", "cs.UTF-8"),
    new Language("Deutsch", "de.UTF-8"),
    new Language("ελληνικά", "el.UTF-8"),
    new Language("English", "en.UTF-8"),
    new Language("Español", "es.UTF-8"),
    new Language("Italiano", "it.UTF-8"),
    new Language("Português (Brasil)", "pt_BR.UTF-8"),
    NULL
};

void Locale::init(Dao* dao)
{
    this->dao = dao;

#ifdef WIN32
    string language = dao->open_get_key(KEY_LANGUAGE);

    setenv("LC_ALL", language.c_str(), 1);
    bindtextdomain("kissplayer", ".\\locale");
    bind_textdomain_codeset("kissplayer", "UTF-8");
#elif __linux__
    bindtextdomain("kissplayer", LOCALEDIR);
    setlocale(LC_ALL, "");
#endif

    textdomain("kissplayer");
}

void Locale::setLanguage(int index)
{
    const char* choice = languages[index]->locale_name.c_str();

    dao->open_db();
    dao->set_key(KEY_LANGUAGE, choice);
    dao->set_key_int(KEY_LANGUAGE_INDEX, index);
    dao->close_db();
}

Language** Locale::getDefinedLanguages()
{
    return languages;
}
