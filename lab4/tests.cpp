#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include "body_collection.h"
#include "moon.h"
#include "planet.h"
#include "star.h"

TEST(Metric, Star) {
    Star sun(1.989e30, 6.957e8, 5778);
    EXPECT_NEAR(sun.metric(), 274.27, 0.01);
}

TEST(Metric, Planet) {
    Planet earth(5.972e24, 6.371e6, 288);
    EXPECT_NEAR(earth.metric(), 9.82, 0.01);
}

TEST(Metric, Moon) {
    Moon moon(7.342e22, 1.737e6, 2360591.5, 2360591.5);
    EXPECT_NEAR(moon.metric(), 1.624, 0.001);
}

TEST(Metric, SimpleNumbers) {
    Planet p(1.0 / G, 1.0, 300);
    EXPECT_NEAR(p.metric(), 1.0, 1e-9);
}

TEST(TypeSpecific, StellarClass) {
    EXPECT_STREQ(Star(1e30, 1e8, 40000).stellarClass(), "O");
    EXPECT_STREQ(Star(1e30, 1e8, 20000).stellarClass(), "B");
    EXPECT_STREQ(Star(1e30, 1e8, 8000).stellarClass(), "A");
    EXPECT_STREQ(Star(1e30, 1e8, 6500).stellarClass(), "F");
    EXPECT_STREQ(Star(1e30, 1e8, 5778).stellarClass(), "G");
    EXPECT_STREQ(Star(1e30, 1e8, 4000).stellarClass(), "K");
    EXPECT_STREQ(Star(1e30, 1e8, 3000).stellarClass(), "M");
}

TEST(TypeSpecific, IsHabitable) {
    Planet earth(5.972e24, 6.371e6, 288);
    EXPECT_TRUE(earth.isHabitable());
    Planet hot(5.972e24, 6.371e6, 700);
    EXPECT_FALSE(hot.isHabitable());
    Planet mars(6.39e23, 3.3895e6, 280);
    EXPECT_FALSE(mars.isHabitable());
}

TEST(TypeSpecific, TidallyLocked) {
    Moon locked(7.342e22, 1.737e6, 2360591.5, 2360591.5);
    EXPECT_TRUE(locked.tidallyLocked());
    Moon free(1e20, 1e5, 1000.0, 500.0);
    EXPECT_FALSE(free.tidallyLocked());
}

TEST(DynamicCast, RightAndWrongType) {
    CelestialBody* body = new Planet(5.972e24, 6.371e6, 288);
    EXPECT_NE(dynamic_cast<Planet*>(body), nullptr);
    EXPECT_EQ(dynamic_cast<Star*>(body), nullptr);
    EXPECT_EQ(dynamic_cast<Moon*>(body), nullptr);
    delete body;
}

TEST(Collection, TotalMetric) {
    BodyCollection bodies;
    bodies.add(new Planet(1.0 / G, 1.0, 300));
    bodies.add(new Star(2.0 / G, 1.0, 6000));
    bodies.add(new Moon(3.0 / G, 1.0, 10, 10));
    EXPECT_EQ(bodies.size(), 3u);
    EXPECT_NEAR(bodies.totalMetric(), 6.0, 1e-9);
}

TEST(Collection, Empty) {
    BodyCollection bodies;
    EXPECT_TRUE(bodies.empty());
    EXPECT_DOUBLE_EQ(bodies.totalMetric(), 0.0);
    EXPECT_FALSE(bodies.remove(0));
    EXPECT_THROW(bodies[0], std::out_of_range);
}

TEST(Collection, CopyIsDeepAndMoveWorks) {
    BodyCollection a;
    a.add(new Star(1e30, 1e8, 5000));
    a.add(new Moon(1e20, 1e5, 10, 10));
    BodyCollection b(a);
    EXPECT_NE(&a[0], &b[0]);
    EXPECT_TRUE(a[0] == b[0]);
    EXPECT_NE(dynamic_cast<Moon*>(&b[1]), nullptr);

    b.remove(0);
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 1u);

    BodyCollection c(std::move(a));
    EXPECT_EQ(c.size(), 2u);
    EXPECT_TRUE(a.empty());

    b = c;
    EXPECT_EQ(b.size(), 2u);
}

TEST(Collection, CountTypesThroughDynamicCast) {
    BodyCollection bodies;
    bodies.add(new Star());
    bodies.add(new Planet());
    bodies.add(new Planet());
    bodies.add(new Moon());
    int planets = 0;
    for (std::size_t i = 0; i < bodies.size(); i++) {
        if (dynamic_cast<Planet*>(&bodies[i]) != nullptr) {
            planets++;
        }
    }
    EXPECT_EQ(planets, 2);
}

TEST(Stream, OutputContainsNameAndFields) {
    Star s(2e30, 7e8, 6000);
    std::ostringstream out;
    out << s;
    std::string text = out.str();
    EXPECT_NE(text.find("Star:"), std::string::npos);
    EXPECT_NE(text.find("M=2e+30 kg"), std::string::npos);
    EXPECT_NE(text.find("R=7e+08 m"), std::string::npos);
    EXPECT_NE(text.find("T=6000 K"), std::string::npos);

    Moon m(1e20, 1e5, 100, 200);
    std::ostringstream moon_out;
    moon_out << m;
    EXPECT_NE(moon_out.str().find("Moon:"), std::string::npos);
    EXPECT_NE(moon_out.str().find("T_rot=200 s"), std::string::npos);
}

TEST(Stream, InputGivesExpectedMetric) {
    std::istringstream in("5.972e24 6.371e6 288");
    Planet p;
    in >> p;
    EXPECT_FALSE(in.fail());
    EXPECT_NEAR(p.metric(), 9.82, 0.01);
    EXPECT_NEAR(p.temperature(), 288.0, 1e-9);

    std::istringstream moon_in("7.342e22 1.737e6 100 100");
    Moon m;
    CelestialBody& ref = m;
    moon_in >> ref;
    EXPECT_FALSE(moon_in.fail());
    EXPECT_TRUE(m.tidallyLocked());
}

TEST(Stream, BadInputSetsFail) {
    std::istringstream in("-5 10 300");
    Star s;
    in >> s;
    EXPECT_TRUE(in.fail());
    EXPECT_DOUBLE_EQ(s.mass(), 1.0);
}

TEST(Operators, EqualityByMetric) {
    Planet a(1.0 / G, 1.0, 300);
    Star b(1.0 / G, 1.0, 6000);
    Moon c(2.0 / G, 1.0, 10, 10);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
}

TEST(Operators, CastToDouble) {
    Planet earth(5.972e24, 6.371e6, 288);
    double g = static_cast<double>(earth);
    EXPECT_DOUBLE_EQ(g, earth.metric());
}

TEST(EdgeCases, InvalidSizesThrow) {
    EXPECT_THROW(Star(0, 1e8, 5000), std::invalid_argument);
    EXPECT_THROW(Planet(1e24, -1, 300), std::invalid_argument);
    EXPECT_THROW(Planet(1e24, 1e6, 0), std::invalid_argument);
    EXPECT_THROW(Moon(1e20, 1e5, -1, 10), std::invalid_argument);
}

TEST(Memory, DeleteThroughBasePointer) {
    CelestialBody* bodies[3] = {new Star(), new Planet(), new Moon()};
    for (int i = 0; i < 3; i++) {
        delete bodies[i];
    }
    BodyCollection collection;
    for (int i = 0; i < 100; i++) {
        collection.add(new Moon());
    }
    collection.clear();
    EXPECT_TRUE(collection.empty());
}
