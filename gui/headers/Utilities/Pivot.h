#pragma once

class Pivot
{
public:

    Pivot(float x, float y);

    void SetPivot(float x, float y);

    void SetXPivot(float value);
    void SetYPivot(float value);

    [[nodiscard]] float GetXPivot() const;
    [[nodiscard]] float GetYPivot() const;

private:

    float _x;
    float _y;
};