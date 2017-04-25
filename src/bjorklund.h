//
//  bjorklund.h
//  pointersonterries
//
//  Created by gustaf svenungsson on 10/01/2017.
//
//
//modified from https://bitbucket.org/sjcastroe/bjorklunds-algorithm
// EUCLIDEAN RHYTHM ALGORITHM, RETURNS A VECTOR OF BOOLS THAT IS USED AS INPUT FOR OUR STEPSEQUENCER

#ifndef bjorklund_h
#define bjorklund_h
template<typename T, typename T2>
vector<T> bjorklund(T2 beats, T2 steps)
{
    vector<T> x;
    x.push_back(1);
    vector<T> y;
    y.push_back(0);
    T2 x_amount = beats;
    T2 y_amount = steps - beats;
    do
    {
        T2 x_temp = x_amount;
        T2 y_temp = y_amount;
        vector<T> y_copy = y;
        if (x_temp >= y_temp)
        {
            x_amount = y_temp;
            y_amount = x_temp - y_temp;
            y = x;
        }
        else
        {
            x_amount = x_temp;
            y_amount = y_temp - x_temp;
        }
        for (int i = 0; i < y_copy.size(); i++){
            x.push_back(y_copy[i]);
        }
    } while (x_amount > 1 && y_amount > 1);
    vector<T> r;
    for (int i =0; i < x_amount; i++){
        for (int i = 0; i < x.size(); i++) r.push_back(x[i]);
    }
    
    for (int i = 0; i < y_amount; i++){
        for (int i = 0; i < y.size(); i++) r.push_back(y[i]);
    }
    return r;
}

#endif /* bjorklund_h */
