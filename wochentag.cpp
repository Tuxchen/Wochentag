#include <iostream>
#include <string>
#include <regex>

enum class Wochentag {
    Sonntag = 0,
    Montag,
    Dienstag,
    Mittwoch,
    Donnerstag,
    Freitag,
    Samstag
};

std::string enumToWochentag(Wochentag tag) {
    switch(tag) {
        case Wochentag::Sonntag:
            return "Sonntag";
        case Wochentag::Montag:
            return "Montag";
        case Wochentag::Dienstag:
            return "Dienstag";
        case Wochentag::Mittwoch:
            return "Mittwoch";
        case Wochentag::Donnerstag:
            return "Donnerstag";
        case Wochentag::Freitag:
            return "Freitag";
        case Wochentag::Samstag:
            return "Samstag";
        default:
            return "Ungültiger Wert";
    }
}

Wochentag calc_day(int t, int m, int j) {
    if(m <= 2) {
        m += 10;
        j--;
    }
    else {
        m -= 2;
    }

    int c = j / 100;
    int y = j % 100;

    int h = (((26 * m - 2) / 10) + t + y + y/4 + c/4 - 2 * c) % 7;

    if(h < 0) {
        h += 7;
    }

    return static_cast<Wochentag>(h);
}

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " dd.mm.yyyy" << std::endl;
        return 1;
    }

    std::regex expr(R"(^(\d{2})\.(\d{2})\.(\d{4})$)");
    std::smatch match;
    std::string text(argv[1]);

    int day{0}, month{0}, year{0};

    if(std::regex_match(text, match, expr)) {
        day = std::stoi(match[1].str());
        month = std::stoi(match[2].str());
        year = std::stoi(match[3].str());
    }
    else {
        std::cerr << "Ungültige Eingabe!" << std::endl;
        std::cerr << "Usage: " << argv[0] << " dd.mm.yyyy" << std::endl;
        return 1;
    }

    Wochentag tag = calc_day(day, month, year);

    std::cout << "Der " << day << "." << month << "." << year << " ist ein " << enumToWochentag(tag) << std::endl;

    return 0;
}