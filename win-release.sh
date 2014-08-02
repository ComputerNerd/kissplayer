#!/bin/bash

MINGW_PATH=C:/MinGW/bin/
OUTPUT=kissplayer

containsElement() {
  local e
  for e in "${@:2}"; do [[ "$e" == "$1" ]] && return 1; done
  return 0
}

win_dlls=(advapi32.dll comctl32.dll gdi32.dll kernel32.dll msvcrt.dll ole32.dll shell32.dll user32.dll)

mkdir -p $OUTPUT

cd po

find . -type f -iname "*.gmo" -print0 | while IFS= read -r -d $'\0' file; do
    lang=`echo "$file" | cut -d'.' -f2 |cut -d'/' -f2`
    mkdir -p ../$OUTPUT/locale/$lang/LC_MESSAGES
    cp "$file" ../$OUTPUT/locale/$lang/LC_MESSAGES/kissplayer.mo
done

cd ..

objdump -p kissplayer.exe | grep "DLL Name:" | while read -r dll; do
    dll=`echo $dll | cut -d' ' -f3`
    containsElement $dll "${win_dlls[@]}"
    if [ "$?" -eq "1" ]; then
        continue
    fi
    cp $MINGW_PATH$dll $OUTPUT
done

strip kissplayer.exe
cp kissplayer.exe $OUTPUT
cp LICENSE.txt $OUTPUT
cp CHANGELOG.txt $OUTPUT
cp README.txt $OUTPUT

7z a -tzip kissplayer kissplayer