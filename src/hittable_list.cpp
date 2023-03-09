#include "hittable_list.h"

#include "hittable.h"

bool HittableList::hit(const Ray &r, double tMin, double tMax,
                       HitRecord &rec) const
{
    HitRecord tempRec;
    bool hitAnything  = false;
    auto closestSoFar = tMax;

    for (const auto &object : objects)
    {
        if (object->hit(r, tMin, closestSoFar, tempRec))
        {
            hitAnything  = true;
            closestSoFar = tempRec.t;
            rec          = tempRec;
        }
    }

    return hitAnything;
}
