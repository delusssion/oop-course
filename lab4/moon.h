#pragma once
#include "celestial_body.h"

class Moon : public CelestialBody {
public:
    Moon();
    Moon(double mass, double radius, double orbit_period, double rotation_period);
    Moon(const Moon& other) = default;

    double orbitPeriod() const;
    double rotationPeriod() const;
    bool tidallyLocked() const;

    const char* name() const override;
    void print(std::ostream& out) const override;
    void read(std::istream& in) override;
    CelestialBody* clone() const override;

private:
    double orbit_period_;
    double rotation_period_;
};
