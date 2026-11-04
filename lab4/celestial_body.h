#pragma once
#include <iostream>

const double G = 6.674e-11;
const double EPS = 1e-6;

class CelestialBody {
public:
    CelestialBody();
    CelestialBody(double mass, double radius);
    virtual ~CelestialBody() = default;

    CelestialBody& operator=(const CelestialBody&) = delete;

    double mass() const;
    double radius() const;

    virtual double metric() const;
    virtual const char* name() const = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void read(std::istream& in) = 0;
    virtual CelestialBody* clone() const = 0;

    explicit operator double() const;
    bool operator==(const CelestialBody& other) const;
    bool operator!=(const CelestialBody& other) const;

protected:
    CelestialBody(const CelestialBody&) = default;

    void set_mass_and_radius(double mass, double radius);

    double mass_;
    double radius_;
};

std::ostream& operator<<(std::ostream& out, const CelestialBody& body);
std::istream& operator>>(std::istream& in, CelestialBody& body);
