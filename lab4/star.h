#pragma once
#include "celestial_body.h"

class Star : public CelestialBody {
public:
    Star();
    Star(double mass, double radius, double temperature);
    Star(const Star& other) = default;

    double temperature() const;
    const char* stellarClass() const;

    const char* name() const override;
    void print(std::ostream& out) const override;
    void read(std::istream& in) override;
    CelestialBody* clone() const override;

private:
    double temperature_;
};
