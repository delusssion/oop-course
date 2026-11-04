#include <iostream>
#include <limits>
#include "body_collection.h"
#include "moon.h"
#include "planet.h"
#include "star.h"

void show_details(const CelestialBody& body) {
    const Star* star = dynamic_cast<const Star*>(&body);
    if (star != nullptr) {
        std::cout << "   спектральный класс: " << star->stellarClass() << std::endl;
    }
    const Planet* planet = dynamic_cast<const Planet*>(&body);
    if (planet != nullptr) {
        std::cout << "   обитаемая: " << (planet->isHabitable() ? "да" : "нет") << std::endl;
    }
    const Moon* moon = dynamic_cast<const Moon*>(&body);
    if (moon != nullptr) {
        std::cout << "   приливной захват: " << (moon->tidallyLocked() ? "да" : "нет") << std::endl;
    }
}

void clear_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    BodyCollection bodies;
    bodies.add(new Star(1.989e30, 6.957e8, 5778));
    bodies.add(new Planet(5.972e24, 6.371e6, 288));
    bodies.add(new Moon(7.342e22, 1.737e6, 2360591.5, 2360591.5));

    while (true) {
        std::cout << std::endl;
        std::cout << "1. Добавить звезду (M R T)" << std::endl;
        std::cout << "2. Добавить планету (M R T)" << std::endl;
        std::cout << "3. Добавить спутник (M R T_orbit T_rot)" << std::endl;
        std::cout << "4. Показать все тела" << std::endl;
        std::cout << "5. Суммарная метрика" << std::endl;
        std::cout << "6. Удалить тело по номеру" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "> ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                break;
            }
            clear_input();
            std::cout << "Ошибка ввода" << std::endl;
            continue;
        }

        if (choice == 0) {
            break;
        } else if (choice >= 1 && choice <= 3) {
            CelestialBody* body = nullptr;
            if (choice == 1) {
                body = new Star();
            } else if (choice == 2) {
                body = new Planet();
            } else {
                body = new Moon();
            }
            std::cout << "Введите параметры: ";
            if (std::cin >> *body) {
                bodies.add(body);
                std::cout << "Добавлено: " << *body << std::endl;
            } else {
                delete body;
                clear_input();
                std::cout << "Некорректные данные (все значения должны быть > 0)" << std::endl;
            }
        } else if (choice == 4) {
            if (bodies.empty()) {
                std::cout << "Коллекция пуста" << std::endl;
            }
            for (std::size_t i = 0; i < bodies.size(); i++) {
                std::cout << i << ") " << bodies[i] << std::endl;
                show_details(bodies[i]);
            }
        } else if (choice == 5) {
            std::cout << "Сумма g = " << bodies.totalMetric() << " m/s^2" << std::endl;
        } else if (choice == 6) {
            std::size_t index = 0;
            std::cout << "Номер: ";
            if (!(std::cin >> index)) {
                clear_input();
                std::cout << "Ошибка ввода" << std::endl;
            } else if (bodies.remove(index)) {
                std::cout << "Удалено" << std::endl;
            } else {
                std::cout << "Нет такого номера" << std::endl;
            }
        } else {
            std::cout << "Нет такого пункта" << std::endl;
        }
    }
    return 0;
}
