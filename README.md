# עברי++ | Ivri++

ספריית לימוד לכתיבת C++17 עם מילות מפתח, טיפוסים ופעולות בעברית. הספרייה כוללת קובצי כותרת בלבד ופועלת עם מהדר C++ רגיל.

## הדגמה בדפדפן

[ה־Playground](playground/) מציג את הקוד בעברית לצד אותו קוד לאחר החלפת מילות המפתח של C++. אפשר להריץ מיון וסכום, או להזין פקודות למסוף העברי. שתי הדוגמאות נבנות מקוד המקור שבתיקיית `examples/` ומורצות בדפדפן כ־WebAssembly.

## מתחילים

הורידו את הפרויקט כ־ZIP דרך **Code → Download ZIP** ב־GitHub וחלצו את התיקייה. פתחו מסוף בתיקייה שבה נמצא `CMakeLists.txt`. נדרשים CMake ‏3.16 ומעלה ומהדר שתומך ב־C++17. ב־Windows אפשר להשתמש ב־WSL עם GCC או ב־Visual Studio עם כלי הפיתוח ל־C++.

```sh
cmake -S . -B build
cmake --build build --config Release
cmake -E chdir build ctest -C Release --output-on-failure
```

להרצת המסוף העברי ב־Linux או WSL:

```sh
./build/03_hebrew_terminal
```

ב־PowerShell עם Visual Studio, הריצו `.\build\Release\03_hebrew_terminal.exe`. ראו את [מדריך המסוף](docs/TERMINAL_HE.md) להגדרות קידוד ותצוגה.

## שימוש בפרויקט אחר

מקמו את `include/ivri/` תחת תיקיית ה־include של הפרויקט, או חברו את הספרייה דרך CMake לפי [המדריך בעברית](docs/GUIDE_HE.md).

```cpp
#include <ivri/ivri.hpp>

שלם ראשי() {
    עברי::וקטור<שלם> מספרים = {4, 2, 8};
    עברי::מיין(מספרים);
    עברי::הדפס_וקטור(מספרים);
    החזר 0;
}
```

## דוגמאות

| דוגמה | מה לומדים | איפה מריצים |
| --- | --- | --- |
| [מיון וסכום](examples/01_basics.cpp) | וקטור, הוספה, מיון וסכימה | דפדפן או CMake |
| [ציוני תלמיד](examples/02_student_grades.cpp) | מחלקה, בדיקת ציון וחישוב ממוצע | CMake |
| [מסוף עברי](examples/03_hebrew_terminal.cpp) | קלט, תנאים, פקודות וטיפול בקלט שגוי | דפדפן או CMake |
| [הדוגמה המקיפה](legacy/) | מפות, אלגוריתמים, מתמטיקה וקבצים באב־הטיפוס | GCC |

ראו את [תוכנית ההמשך](docs/ROADMAP_HE.md).

## רישיון

[MIT](LICENSE)
