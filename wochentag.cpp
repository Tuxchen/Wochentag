#include <iostream>
#include <string>

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
    if(argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <Tag> <Monat> <Jahr>" << std::endl;
        return 1;
    }

    int day{0}, month{0}, year{0};

    try {
        day = std::stoi(argv[1]);
        month = std::stoi(argv[2]);
        year = std::stoi(argv[3]);
    } catch(std::invalid_argument &e) {
        std::cerr << "Tag, Monat oder Jahr müssen numerische Werte sein!\n";
        return 1;
    } catch(std::out_of_range &e) {
        std::cerr << "Tag, Monat oder Jahr hat einen zu großen Wert.\n";
        return 1;
    }

    Wochentag tag = calc_day(day, month, year);

    std::cout << "Der " << day << "." << month << "." << year << " ist ein " << enumToWochentag(tag) << std::endl;

    return 0;
}