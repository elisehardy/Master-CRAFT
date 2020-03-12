//
// Created by ehardy on 3/8/20.
//

#ifndef MASTERCRAFT_C3GATOOLS_HPP
#define MASTERCRAFT_C3GATOOLS_HPP
template<typename T>
c3ga::Mvec<T> point(const T &x, const T &y, const T &z){

    c3ga::Mvec<T> mv;
    mv[c3ga::E1] = x;
    mv[c3ga::E2] = y;
    mv[c3ga::E3] = z;
    mv[c3ga::Ei] = 0.5 * (x*x + y*y + z*z);
    mv[c3ga::E0] = 1.0;

    return mv;
}

template<typename T>
c3ga::Mvec<T> dualSphere(const T &centerX, const T &centerY, const T &centerZ, const T &radius){
    c3ga::Mvec<T> dualSphere = point(centerX,centerY,centerZ);
    dualSphere[c3ga::Ei] -= 0.5*radius;
    return dualSphere;
}


template<typename T>
c3ga::Mvec<T> vector(const T &x, const T &y, const T &z){

    c3ga::Mvec<T> mv;
    mv[c3ga::E1] = x;
    mv[c3ga::E2] = y;
    mv[c3ga::E3] = z;
    return mv;
}


template<typename T>
c3ga::Mvec<T> translation(c3ga::Mvec<T> t){

    c3ga::Mvec<T> mv = (1.0 + (-1.0 / 2.0) * t * c3ga::ei<double>());

    return mv;
}



template<typename T>
c3ga::Mvec<T> scale(T t){

    c3ga::Mvec<T> mv = ( 1-(1.0 - t/ (1.0 + t)) * -c3ga::e0i<double>());

    return mv;
}

template<typename T>
void radiusAndCenterFromDualSphere(const c3ga::Mvec<T> &dualSphere, T &radius, c3ga::Mvec<T> &center){
    radius = (dualSphere | dualSphere) / dualSphere[c3ga::E0];
    center = dualSphere / dualSphere[c3ga::E0];
}



#endif //MASTERCRAFT_C3GATOOLS_HPP
