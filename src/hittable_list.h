#ifndef _RTIAW_HITTABLE_LIST_H
#define _RTIAW_HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.h"

class HittableList : public Hittable
{
   public:
    HittableList() = default;

    HittableList(std::shared_ptr<Hittable> &object) { add(object); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

    bool hit(const Ray &r, double tMin, double tMax,
             HitRecord &rec) const override;

   public:
    std::vector<std::shared_ptr<Hittable>> objects;
};

#endif  // _RTIAW_HITTABLE_LIST_H
