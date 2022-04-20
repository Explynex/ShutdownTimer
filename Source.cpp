#include "devattribute.h"

BOOL ShowConsoleCursor(BOOL bShow)
{
    CONSOLE_CURSOR_INFO cci;
    HANDLE hStdOut;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return FALSE;
    if (!GetConsoleCursorInfo(hStdOut, &cci))
        return FALSE;
    cci.bVisible = bShow;
    if (!SetConsoleCursorInfo(hStdOut, &cci))
        return FALSE;
    return TRUE;
}

int main() {
    utf.setUtfLocale();
    system("mode con cols=42 lines=7");
    std::string info, command;
    bool condition = 0;
    int time;
    sheetGenerator(0, 0, 1, 1, 40, 5);
    GotoXY(10, 1, "Таймер выключения ПК",BROWN,BLACK);
    GotoXY(2, 3, "Время до завершения работы: ");
    GotoXY(2, 4, "/s - сек. /m - мин.:",DARKGRAY,BLACK);
    do {
        cleaning(30, 3, 1, 7);
        GotoXY(30, 3);
        info = printFilter(30, 3, 2,"str","/","s");
        if (info != "/s" && info != "/m") {
            GotoXY(30, 3, "/s 3600", DARKGRAY, BLACK);
            Sleep(1200);
        }
    } while (info != "/s" && info != "/m");
    GotoXY(33, 3);
    time = stoi(printFilter(33, 3, 5, "digit", "0", "9", 1));
    ShowConsoleCursor(FALSE);
    if (info == "/m") time *= 60;
    command = "shutdown /s /t " + std::to_string(time) + " /f";
    system(data(command));
    GotoXY(2, 3, "Осталось до выключения:            ");
    GotoXY(2, 4, "Чтобы отменить выключение нажмите ESC",DARKGRAY,BLACK);
    for (; 0 <= time; time--) {
        GotoXY(27, 3, std::to_string(time)+" с    ",LIGHTRED,BLACK);
        if (GetAsyncKeyState(VK_ESCAPE) != 0) {
            system("shutdown /a");
            GotoXY(26, 3, "Отменено!     ", LIGHTRED, BLACK);
            break;
        }
        Sleep(999);
    }
    Sleep(1500);
}


//system("mode con cols=60 lines=4");
//system("shutdown /s /t 10 /c \"Вы долбоеб! Мои поздравления!\" /f");