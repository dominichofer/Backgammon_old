#pragma once
#include <algorithm>
#include <numeric>
#include <memory>
#include <string>
#include <vector>

class ProbDist
{
    double E = 0;
    std::vector<double> m{};
public:
    constexpr ProbDist() noexcept = default;
    explicit ProbDist(std::vector<double> pd) : m(std::move(pd))
    {
        E = 0;
        for (std::size_t i = 0; i < m.size(); i++)
            E += m[i] * i;
    }

    [[nodiscard]] bool operator< (const ProbDist& o) const noexcept { return E <  o.E; }
    [[nodiscard]] bool operator> (const ProbDist& o) const noexcept { return E >  o.E; }
    [[nodiscard]] bool operator<=(const ProbDist& o) const noexcept { return E <= o.E; }
    [[nodiscard]] bool operator>=(const ProbDist& o) const noexcept { return E >= o.E; }

    [[nodiscard]] double& operator[](std::size_t i)       noexcept { return m[i]; }
    [[nodiscard]] double  operator[](std::size_t i) const noexcept { return m[i]; }

    [[nodiscard]] std::size_t size() const noexcept { return m.size(); }
    [[nodiscard]] double ExpectationValue() const noexcept { return E; }

    ProbDist& operator+=(const ProbDist& o) // denormalizes
    {
        if (o.size() > m.size())
            m.resize(o.size());
        for (std::size_t i = 0; i < o.size(); i++)
            m[i] += o[i];
        return *this;
    }

    void Normalize() {
        double sum = std::accumulate(m.begin(), m.end(), 0.0);
        E = 0;
        for (std::size_t i = 0; i < m.size(); i++)
        {
            m[i] /= sum;
            E += m[i] * i;
        }
    }

    void ShiftOneUp() { m.insert(m.begin(), 1, 0); }
};

std::string to_string(const ProbDist&);
