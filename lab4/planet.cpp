#include "planet.h"
#include <cmath>
#include <stdexcept>

Planet::Planet() : CelestialBody(), temperature_(288.0) {}

Planet::Planet(double mass, double radius, double temperature)
    : CelestialBody(mass, radius), temperature_(temperature) {
    if (temperature <= 0) {
        throw std::invalid_argument("temperature must be positive");
    }
}

double Planet::temperature() const {
    return temperature_;
}

bool Planet::isHabitable() const {
    double g = metric();
    return std::fabs(temperature_ - 290.0) < 60.0 && g >= 5.0 && g <= 15.0;
}

const char* Planet::name() const {
    return "Planet";
}

void Planet::print(std::ostream& out) const {
    out << "Planet: M=" << mass_ << " kg R=" << radius_ << " m T=" << temperature_
        << " K g=" << metric() << " m/s^2";
}

void Planet::read(std::istream& in) {
    double m = 0;
    double r = 0;
    double t = 0;
    if (!(in >> m >> r >> t) || m <= 0 || r <= 0 || t <= 0) {
        in.setstate(std::ios::failbit);
        return;
    }
    mass_ = m;
    radius_ = r;
    temperature_ = t;
}

CelestialBody* Planet::clone() const {
    return new Planet(*this);
}
