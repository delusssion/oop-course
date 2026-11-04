#include "moon.h"
#include <cmath>
#include <stdexcept>

Moon::Moon() : CelestialBody(), orbit_period_(1.0), rotation_period_(1.0) {}

Moon::Moon(double mass, double radius, double orbit_period, double rotation_period)
    : CelestialBody(mass, radius), orbit_period_(orbit_period), rotation_period_(rotation_period) {
    if (orbit_period <= 0 || rotation_period <= 0) {
        throw std::invalid_argument("periods must be positive");
    }
}

double Moon::orbitPeriod() const {
    return orbit_period_;
}

double Moon::rotationPeriod() const {
    return rotation_period_;
}

bool Moon::tidallyLocked() const {
    return std::fabs(orbit_period_ - rotation_period_) < EPS * orbit_period_;
}

const char* Moon::name() const {
    return "Moon";
}

void Moon::print(std::ostream& out) const {
    out << "Moon: M=" << mass_ << " kg R=" << radius_ << " m T_orbit=" << orbit_period_
        << " s T_rot=" << rotation_period_ << " s g=" << metric() << " m/s^2";
}

void Moon::read(std::istream& in) {
    double m = 0;
    double r = 0;
    double t_orbit = 0;
    double t_rot = 0;
    if (!(in >> m >> r >> t_orbit >> t_rot) || m <= 0 || r <= 0 || t_orbit <= 0 || t_rot <= 0) {
        in.setstate(std::ios::failbit);
        return;
    }
    mass_ = m;
    radius_ = r;
    orbit_period_ = t_orbit;
    rotation_period_ = t_rot;
}

CelestialBody* Moon::clone() const {
    return new Moon(*this);
}
