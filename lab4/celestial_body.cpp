#include "celestial_body.h"
#include <cmath>
#include <stdexcept>

CelestialBody::CelestialBody() : mass_(1.0), radius_(1.0) {}

CelestialBody::CelestialBody(double mass, double radius) : mass_(1.0), radius_(1.0) {
    set_mass_and_radius(mass, radius);
}

void CelestialBody::set_mass_and_radius(double mass, double radius) {
    if (mass <= 0 || radius <= 0) {
        throw std::invalid_argument("mass and radius must be positive");
    }
    mass_ = mass;
    radius_ = radius;
}

double CelestialBody::mass() const {
    return mass_;
}

double CelestialBody::radius() const {
    return radius_;
}

double CelestialBody::metric() const {
    return G * mass_ / (radius_ * radius_);
}

CelestialBody::operator double() const {
    return metric();
}

bool CelestialBody::operator==(const CelestialBody& other) const {
    return std::fabs(metric() - other.metric()) < EPS;
}

bool CelestialBody::operator!=(const CelestialBody& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
    body.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, CelestialBody& body) {
    body.read(in);
    return in;
}
