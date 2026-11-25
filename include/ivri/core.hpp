#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <utility>
#include <memory>

// Language keywords: intentionally opt-in through this header.
#define ראשי main
#define שלם int
#define שלם_ארוך_ארוך long long
#define ממשי float
#define כפול double
#define תו char
#define לוגי bool
#define ריק void
#define אוטומטי auto
#define קבוע const
#define אם if
#define אחרת else
#define עבור for
#define כלעוד while
#define החזר return
#define עצור break
#define המשך continue
#define אמת true
#define שקר false
#define מחלקה class
#define מבנה struct
#define ציבורי public
#define פרטי private
#define מוגן protected
#define זה this
#define חדש new
#define מחק delete
#define אין nullptr

// Container aliases via template aliases, avoiding macro replacement of std tokens.
namespace עברי {
    using מחרוזת = std::string;
    template<class T> using וקטור = std::vector<T>;
    template<class K, class V> using מפה = std::map<K,V>;
    template<class T> void הדפס_וקטור(const וקטור<T>& values) {
        std::cout << "[";
        bool first = true;
        for (const auto& value : values) {
            if (!first) std::cout << ", ";
            std::cout << value;
            first = false;
        }
        std::cout << "]\n";
    }
    template<class T> void הוסף(וקטור<T>& values, const T& value) { values.push_back(value); }
    template<class T> std::size_t גודל(const וקטור<T>& values) { return values.size(); }
    template<class T> void מיין(וקטור<T>& values) { std::sort(values.begin(), values.end()); }
    template<class T> T סכום(const וקטור<T>& values, T initial = T{}) {
        return std::accumulate(values.begin(), values.end(), initial);
    }
    inline void הדפס(const std::string& text) { std::cout << text << '\n'; }
}
