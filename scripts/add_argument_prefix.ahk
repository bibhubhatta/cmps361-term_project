#Requires AutoHotkey v2.0
#SingleInstance Force

^j:: {

    Send '+{F6}'
    Sleep 50

    Send '^a'
    Sleep 50

    Send '^x'
    Sleep 50

    Send "a_"
    Sleep 50

    Send '^v'
    Sleep 50

    Send '{Enter}'

}

^l:: {

    Send '+{F6}'
    Sleep 300

    A_Clipboard := ""
    Send '^x'
    Sleep 50
    ClipWait

    char_1 := SubStr(A_Clipboard, 1, 1)
    upper_char_1 := StrUpper(char_1)

    str_upper := upper_char_1 . SubStr(A_Clipboard, 2)

    Send str_upper
    Sleep 50

    Send '{Enter}'

    return

}