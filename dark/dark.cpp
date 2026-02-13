#include <bits/stdc++.h>
using namespace std;

void rot90(double &x, double &y) {
    const double opp = -x;
    x = y;
    y = opp;
}

pair<double,double> solutions(double a, double b, double c) {
    double determinant = b*b-4*a*c;
    if (determinant < 0)
        return {INFINITY, INFINITY};

    double sol1 = (-b-sqrt(determinant)) / (2*a);
    double sol2 = (-b+sqrt(determinant)) / (2*a);

    return {sol1, sol2};
}

int main() {

    auto leq = [](double a, double b) {
        return a < b || fabs(a-b) < 1e-6;
    };
    auto geq = [](double a, double b) {
        return a > b || fabs(a-b) < 1e-6;
    };

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    vector<pair<double,double>> dark_zones;
    for (int i=0;i<n;++i) {
        double x,y;
        cin>>x>>y;
        dark_zones.push_back({x,y});
    }

    double xe, ye, xp, yp;
    cin>>xe>>ye>>xp>>yp;
    if (xe == xp) {
        rot90(xe,ye);
        rot90(xp,yp);
        for (auto &[xi, yi]: dark_zones)
            rot90(xi, yi);
    }
    double m = (yp-ye)*1.0 / (xp-xe);


    double l = 0, r = 1e14;
    while (fabs(r-l) > 1e-5) {
        double radius = (l+r)/2;

        vector<pair<double,double>> intervals;
        for (auto &[xi,yi]: dark_zones) {
            double a = 1 + m*m;
            double b = -2*xi + 2*m*ye - 2*m*m*xe - 2*m*yi;
            double c = xi*xi + ye*ye - 2*m*xe*ye - 2*yi*ye + m*m*xe*xe + 2*m*xe*yi + yi*yi - radius*radius;
            auto [sol1, sol2] = solutions(a,b,c);
            if (sol1 == INFINITY && sol2 == INFINITY) continue;

            intervals.push_back({sol1, sol2});
        }

        if (intervals.empty()) {
            l = radius;
            continue;
        }

        sort(intervals.begin(),intervals.end());
        double last = min(xe,xp);
        for (size_t i=0; i<intervals.size(); ++i) {
            if (leq(intervals[i].first, last) && leq(last, intervals[i].second))
                last = intervals[i].second;
        }

        if (geq(last, max(xe,xp)))
            r = radius;
        else
            l = radius;

    }

    printf("%.10lf\n", l);
}