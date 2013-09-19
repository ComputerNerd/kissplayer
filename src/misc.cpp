#include "misc.h"

/**
* This is a place for general purpose functions.
*/

/**
* Parses the arguments to check if there are music files to play
*/
vector<Music> *parseArgs(int argc, char **argv)
{
    vector<Music> *list = new vector<Music>();
    for(int i = 1; i < argc; i++)
    {
        string arg(argv[i]);

        //List of supported file formats
        if(strstr(arg.c_str(), ".mp3") != NULL ||
                strstr(arg.c_str(), ".wma") != NULL ||
                strstr(arg.c_str(), ".ogg") != NULL ||
                strstr(arg.c_str(), ".wav") != NULL ||
                strstr(arg.c_str(), ".flac") != NULL)
        {
            Music m;
            TagLib::FileRef *f = new TagLib::FileRef(arg.c_str());
            m.title = f->tag()->title().to8Bit();
            m.artist = f->tag()->artist().to8Bit();
            m.album = f->tag()->album().to8Bit();
            m.filepath = arg;
            delete(f);
            list->push_back(m);
        }
    }

    return list;
}

/**
* Removes whitespaces at the beginning and end of a string
*/
void trim(string &str)
{
    string::size_type pos = str.find_last_not_of(" \f\n\r\t\v");
    str.erase(pos + 1);

    pos = str.find_first_not_of(" \f\n\r\t\v");
    str.erase(0, pos);
}

/**
* Takes a time value in miliseconds and returns formated in mm:ss.
* Ex: 123 secs -> 02:03 |  799 secs -> 13:19
*/
const char *formatTime (int time)
{
    stringstream stream;

    time = (int) time / 1000;

    int minutes = (int) (time / 60);
    int seconds = (int) (time % 60);

    stream << (minutes <= 9 ? "0" : "") << minutes << ":" << (seconds <= 9 ? "0" : "") << seconds;

    return stream.str().c_str();
}

/**
* Generates random numbers
*/
ptrdiff_t myrandom (ptrdiff_t i) { return rand()%i;}

/**
* Generates a vector filled with unique random numbers
*/
void randomize(vector<int> **listRandom, int max)
{
    ptrdiff_t (*p_myrandom)(ptrdiff_t) = myrandom;
    srand((int)time(NULL));
    *listRandom = new vector<int>();
    for(int i = 0; i < max; i++)
        (*listRandom)->push_back(i);

    random_shuffle((*listRandom)->begin(), (*listRandom)->end(), p_myrandom);
}

/**
* Seeks directories for music files and adds them to the DB.
*/
void misc_sync_library()
{
    vector<NameCod *> *listDir = getAllDirectories();

    if(listDir->size() == 0) {
        fl_beep();
        fl_message_title("Warning");
        fl_message("Please, add at least one directory on the Settings Window.");
        delete listDir;
        return;
    }

    Fl_Window *window = make_window_loading();
    progress_bar_dir->maximum(listDir->size());
    window->show();

    deleteAllMusics();
    beginTransaction();

    for(int i = 0; i < listDir->size(); i++)
    {
        Fl::check();
#ifdef WIN32
        deque<wstring> listFiles;
        wchar_t dir[4096];
        fl_utf8towc(listDir->at(i)->name.c_str(), listDir->at(i)->name.size(), dir, 4096);
#else
        deque<string> listFiles;
        const char* dir = listDir->at(i)->name.c_str();
#endif

        os_specific_scanfolder(dir, listFiles);

        progress_bar_file->maximum(listFiles.size());
        for(int j = 0; j < listFiles.size(); j++)
        {
            //cout<<"Dir: "<<i+1<<"/"<<listDir->size()<<" - File: "<<j+1<<"/"<<listFiles.size()<< endl;
            if(FLAG_CANCEL_SYNC) break;

#ifdef WIN32
            const wchar_t* filepath = listFiles.at(j).c_str();
#else
            const char* filepath = listFiles.at(j).c_str();
#endif

            string title = "";
            string artist = "";
            string album = "";

            TagLib::FileRef* f = new TagLib::FileRef(filepath);

            title = f->tag()->title().toCString(true);
            artist = f->tag()->artist().toCString(true);
            album = f->tag()->album().toCString(true);
            delete(f);

#ifdef WIN32
            char path[4096];
            fl_utf8fromwc(path, 4096, filepath, lstrlenW(filepath));
#else
            const char* path = filepath;
#endif

            insertMusic(title, artist, album, path);
            progress_bar_file->value(j+1);
            Fl::check();
        }
        listFiles.clear();
        if(FLAG_CANCEL_SYNC) break;

        progress_bar_dir->value(i+1);
    }
    delete listDir;
    Fl::delete_widget(window);

    commitTransaction();
    FLAG_CANCEL_SYNC = false;
}

int stringToInt(string value)
{
    if(value.empty()) return -1;
    return atoi (value.c_str());
}

string intToString(int value)
{
    stringstream out;
    out << value;
    return out.str();
}

float stringToFloat(string value)
{
    if(value.empty()) return -1;
    return atof (value.c_str());
}

string floatToString(float value)
{
    stringstream out;
    out << value;
    return out.str();
}
