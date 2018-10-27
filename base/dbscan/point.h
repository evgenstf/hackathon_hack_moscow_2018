#pragma once

class Point {
public:
  virtual double distance_to(const Point& other) const = 0;
};
