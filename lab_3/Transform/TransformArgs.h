#pragma once

class ScaleArgs{
private:
    double k;
    double centerX, centerY, centerZ;
public:
    ScaleArgs() noexcept = default;
    ScaleArgs(double k, double centerX, double centerY, double centerZ) noexcept;

    double getK() const noexcept;
    double getCenterX() const noexcept;
    double getCenterY() const noexcept;
    double getCenterZ() const noexcept;
};

class RotateArgs{
private:
    double angleX, angleY, angleZ;
    double centerX, centerY, centerZ;
public:
    RotateArgs() noexcept = default;
    RotateArgs(double angleX, double angleY, double angleZ, 
        double centerX, double centerY, double centerZ) noexcept;

    double getAngleX() const noexcept;
    double getAngleY() const noexcept;
    double getAngleZ() const noexcept;

    double getCenterX() const noexcept;
    double getCenterY() const noexcept;
    double getCenterZ() const noexcept;
};

class MoveArgs{
private:
    double dX, dY, dZ;

public:
    MoveArgs() noexcept = default;
    MoveArgs(double dX, double dY, double dZ) noexcept;

    double getOffsetX() const noexcept;
    double getOffsetY() const noexcept;
    double getOffsetZ() const noexcept;
};