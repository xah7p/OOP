#include "TransformArgs.h"

ScaleArgs::ScaleArgs(double k, double centerX, double centerY, double centerZ) noexcept:
    k(k), centerX(centerX), centerY(centerY), centerZ(centerZ)
{ }

double ScaleArgs::getK() const noexcept { return k; }
double ScaleArgs::getCenterX() const noexcept { return centerX; }
double ScaleArgs::getCenterY() const noexcept { return centerY; }
double ScaleArgs::getCenterZ() const noexcept { return centerZ; }

RotateArgs::RotateArgs(double angleX, double angleY, double angleZ,
                       double centerX, double centerY, double centerZ) noexcept:
    angleX(angleX), angleY(angleY), angleZ(angleZ),
    centerX(centerX), centerY(centerY), centerZ(centerZ)
{ }

double RotateArgs::getAngleX() const noexcept { return angleX; }
double RotateArgs::getAngleY() const noexcept { return angleY; }
double RotateArgs::getAngleZ() const noexcept { return angleZ; }
double RotateArgs::getCenterX() const noexcept { return centerX; }
double RotateArgs::getCenterY() const noexcept { return centerY; }
double RotateArgs::getCenterZ() const noexcept { return centerZ; }

MoveArgs::MoveArgs(double dX, double dY, double dZ) noexcept:
    dX(dX), dY(dY), dZ(dZ)
{ }

double MoveArgs::getOffsetX() const noexcept { return dX; }
double MoveArgs::getOffsetY() const noexcept { return dY; }
double MoveArgs::getOffsetZ() const noexcept { return dZ; }
