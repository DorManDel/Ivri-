#pragma once

/*
    ================================================================
    עברי++ / Ivri++
    ================================================================

    קובץ בסיס לכתיבת C++ בסגנון עברי.

    הרעיון:
    --------
    הקובץ הזה משתמש ב־#define וב־aliasים כדי לאפשר כתיבה
    של קוד C++ עם מילים בעברית.

    חשוב לדעת:
    -----------
    1. זה עדיין C++ רגיל מאחורי הקלעים.
    2. ה־preprocessor מחליף את המילים בעברית לפני הקומפילציה.
    3. לא ניתן לתרגם directive כמו #include ל־#כלול.
    4. מומלץ להשתמש בזה כניסוי לימודי / פרויקט כיפי.

    דוגמה:
    -------
        שלם ראשי()
        {
            הדפס << "שלום עברי++" << סוף_שורה;
            החזר 0;
        }

    ================================================================
*/

// ================================================================
//  ספריות בסיס שנייבא כברירת מחדל
// ================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <fstream>
#include <sstream>
#include <utility>
#include <tuple>
#include <optional>
#include <variant>
#include <functional>
#include <stdexcept>
#include <limits>

// ================================================================
//  Namespace Alias
// ================================================================

namespace ספרייה = std;

// ================================================================
//  מבנה תוכנית בסיסי
// ================================================================

#define ראשי main
#define החזר return
#define יציאה std::exit

// ================================================================
//  מילות בקרה / Control Flow
// ================================================================

#define אם if
#define אחרת else
#define אחרת_אם else if
#define עבור for
#define כלעוד while
#define עשה do
#define שבור break
#define המשך continue
#define החלף switch
#define מקרה case
#define ברירת_מחדל default
#define לך_אל goto

// ================================================================
//  ערכים לוגיים
// ================================================================

#define אמת true
#define שקר false

// ================================================================
//  טיפוסים בסיסיים
// ================================================================

#define ריק void
#define שלם int
#define שלם_קצר short
#define שלם_ארוך long
#define שלם_ארוך_ארוך long long
#define ללא_סימן unsigned
#define תו char
#define תו_רחב wchar_t
#define בוליאני bool
#define ממשי float
#define ממשי_כפול double
#define ממשי_ארוך long double
#define אוטומטי auto

// ================================================================
//  קבועים והרשאות משתנים
// ================================================================

#define קבוע const
#define סטטי static
#define חיצוני extern
#define ניתן_לשינוי mutable
#define נדיף volatile
#define מפורש explicit
#define וירטואלי virtual
#define דריסה override
#define סופי final
#define חבר friend
#define פנימי inline

// ================================================================
//  מחלקות / Structs / Access Modifiers
// ================================================================

#define מחלקה class
#define מבנה struct
#define ציבורי public
#define פרטי private
#define מוגן protected
#define תבנית template
#define שם_טיפוס typename
#define שימוש using
#define מרחב_שמות namespace

// ================================================================
//  זיכרון ומצביעים
// ================================================================

#define חדש new
#define מחק delete
#define מצביע_יחיד std::unique_ptr
#define מצביע_משותף std::shared_ptr
#define מצביע_חלש std::weak_ptr
#define צור_יחיד std::make_unique
#define צור_משותף std::make_shared
#define זה this
#define כלום nullptr

// ================================================================
//  המרות וטיפוסים
// ================================================================

#define גודל_של sizeof
#define סוג_של decltype
#define המרה_סטטית static_cast
#define המרה_דינמית dynamic_cast
#define המרה_קבועה const_cast
#define המרה_מחדש reinterpret_cast

// ================================================================
//  חריגות / Exceptions
// ================================================================

#define נסה try
#define תפוס catch
#define זרוק throw
#define חריגה std::exception
#define שגיאת_ריצה std::runtime_error
#define שגיאת_טווח std::out_of_range
#define שגיאת_ארגומנט std::invalid_argument

// ================================================================
//  קלט / פלט
// ================================================================

#define הדפס std::cout
#define קלט std::cin
#define שגיאה std::cerr
#define יומן std::clog
#define סוף_שורה std::endl
#define שטיפה std::flush
#define רווח " "

// ================================================================
//  מחרוזות
// ================================================================

#define מחרוזת std::string
#define זרם_מחרוזת std::stringstream
#define זרם_קלט_מחרוזת std::istringstream
#define זרם_פלט_מחרוזת std::ostringstream

#define אורך length
#define גודל size
#define ריק_האם empty
#define נקה clear
#define הוסף_תו push_back
#define מצא find
#define תת_מחרוזת substr
#define החלף_טקסט replace
#define הכנס insert
#define מחק_טקסט erase

// ================================================================
//  מכולות STL
// ================================================================

#define וקטור std::vector
#define מערך std::array
#define תור_דו_צדדי std::deque
#define רשימה std::list
#define רשימה_קדמית std::forward_list
#define מחסנית std::stack
#define תור std::queue
#define תור_עדיפויות std::priority_queue
#define מפה std::map
#define מפה_מהירה std::unordered_map
#define קבוצה std::set
#define קבוצה_מהירה std::unordered_set
#define זוג std::pair
#define שלשה std::tuple
#define אופציונלי std::optional
#define וריאנט std::variant

// ================================================================
//  פעולות נפוצות על מכולות
// ================================================================

#define הוסף push_back
#define הוסף_קדימה push_front
#define מחק_אחרון pop_back
#define מחק_ראשון pop_front
#define ראשון front
#define אחרון back
#define התחלה begin
#define סוף end
#define התחלה_קבועה cbegin
#define סוף_קבוע cend
#define הכנס_אל insert
#define מחק_ממ erase
#define מנה count
#if __cplusplus >= 202002L || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
#define מכיל contains
#endif
#define מצא_ב find
#define במקום emplace
#define במקום_אחורה emplace_back
#define שנה_גודל resize
#define שמור_מקום reserve
#define קיבולת capacity

// ================================================================
//  אלגוריתמים STL
// ================================================================

#define מיין std::sort
#define מיין_יציב std::stable_sort
#define הפוך std::reverse
#define ערבב std::shuffle
#define חפש std::find
#define חפש_אם std::find_if
#define ספור std::count
#define ספור_אם std::count_if
#define עבור_כל std::for_each
#define העתק std::copy
#define העבר std::move
#define החלף_ערכים std::swap
#define מינימום std::min
#define מקסימום std::max
#define מינמקס std::minmax
#define צבור std::accumulate
#define מלא std::fill
#define הכל_מתקיים std::all_of
#define יש_מתקיים std::any_of
#define אין_מתקיים std::none_of
#define חיפוש_בינארי std::binary_search
#define גבול_תחתון std::lower_bound
#define גבול_עליון std::upper_bound

// ================================================================
//  מתמטיקה
// ================================================================

#define שורש std::sqrt
#define חזקה std::pow
#define ערך_מוחלט std::abs
#define רצפה std::floor
#define תקרה std::ceil
#define עיגול std::round
#define סינוס std::sin
#define קוסינוס std::cos
#define טנגנס std::tan
#define לוגריתם std::log
#define לוגריתם10 std::log10
#define אקספוננט std::exp

// ================================================================
//  קבצים
// ================================================================

#define קובץ_קלט std::ifstream
#define קובץ_פלט std::ofstream
#define קובץ std::fstream
#define פתח open
#define סגור close
#define פתוח_האם is_open
#define קרא_שורה std::getline

// ================================================================
//  מספרים אקראיים בסיסיים בסגנון C
// ================================================================

#define אקראי std::rand
#define זרע_אקראי std::srand
#define זמן std::time

// ================================================================
//  גבולות מספריים
// ================================================================

#define גבולות std::numeric_limits

// ================================================================
//  פונקציות עזר עבריות קטנות
// ================================================================

namespace עברי
{
    inline void קו()
    {
        std::cout << "----------------------------------------" << std::endl;
    }

    inline void כותרת(const std::string& טקסט)
    {
        קו();
        std::cout << טקסט << std::endl;
        קו();
    }

    template <typename T>
    inline void הדפס_וקטור(const std::vector<T>& איברים)
    {
        std::cout << "[ ";

        for (const auto& איבר : איברים)
        {
            std::cout << איבר << " ";
        }

        std::cout << "]" << std::endl;
    }
}
