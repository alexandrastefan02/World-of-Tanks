//
// Created by Alexandra Stefan on 12.12.2023.
//

#ifndef GFXFRAMEWORK_BUILDING_H
#define GFXFRAMEWORK_BUILDING_H


class Building {
private:
    float bx;
    float by;
    float bz;
    float width;
public:
    float getBx() const;

    void setBx(float bx);

    float getBy() const;

    void setBy(float by);

    float getBz() const;

    void setBz(float bz);

    float getWidth() const;

    void setWidth(float width);

    explicit Building(float width, float bx, float by, float bz);
};


#endif //GFXFRAMEWORK_BUILDING_H
