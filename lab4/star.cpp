#include "star.h"
#include <stdexcept>

Star::Star() : CelestialBody(), temperature_(5778.0) {}

Star::Star(double mass, double radius, double temperature)
    : CelestialBody(mass, radius), temperature_(temperature) {
    if (temperature <= 0) {
        throw std::invalid_argument("temperature must be positive");
    }
}

double Star::temperature() const {
    return temperature_;
}

const char* Star::stellarClass() const {
    if (temperature_ >= 30000) {
        return "O";
    }
    if (temperature_ >= 10000) {
        return "B";
    }
    if (temperature_ >= 7500) {
        return "A";
    }
    if (temperature_ >= 6000) {
        return "F";
    }
    if (temperature_ >= 5200) {
        return "G";
    }
    if (temperature_ >= 3700) {
        return "K";
    }
    return "M";
}

const char* Star::name() const {
    return "Star";
}

void Star::print(std::ostream& out) const {
    out << "Star: M=" << mass_ << " kg R=" << radius_ << " m T=" << temperature_
        << " K g=" << metric() << " m/s^2";
}

void Star::read(std::istream& in) {
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

CelestialBody* Star::clone() const {
    return new Star(*this);
}
