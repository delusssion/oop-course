#pragma once
#include "celestial_body.h"

class Planet : public CelestialBody {
public:
    Planet();
    Planet(double mass, double radius, double temperature);
    Planet(const Planet& other) = default;

    double temperature() const;
    bool isHabitable() const;

    const char* name() const override;
    void print(std::ostream& out) const override;
    void read(std::istream& in) override;
    CelestialBody* clone() const override;

private:
    double temperature_;
};
