#include <iostream>
#include <random>
#include <cmath>

// defining normal cdf
double N(double x);

// European option expiration taken to be 252 trading days / 1 year
// Black-Scholes price
double B_S(double S, double K, double r, double sigma);

// initialising multipliactive random walk function with current price S, strike price K, risk-free interest rate r, annual volatility sigma
void M_C_pricer(double S, double K, double r, double sigma, std::mt19937& gen);

int main() {
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    M_C_pricer(100.0, 100.0, 0.05, 0.20, gen);

    return 0;
}

double N(double x) {
    return 0.5*(1.0 +std::erf(x/std::sqrt(2.0)));
}

double B_S(double S, double K, double r, double sigma) {
    double d_1 = (std::log(S/K) + (r + (sigma * sigma / 2))) / sigma;
    double d_2 = d_1 - sigma;

    return S*N(d_1) - K*std::exp(-r)*N(d_2);
}

void M_C_pricer(double S, double K, double r, double sigma, std::mt19937& gen) {
    int walks = 1000000;
    double S_0 = S;

    // rescaling annual volatility and risk-free interest rate to daily values
    double s = sigma / std::sqrt(252);
    double r_daily = std::exp(r/252) - 1;

    // initialising rolling average and rolling square average
    double r_a = 0;
    double r_s_a = 0;

    std::lognormal_distribution<double> dist(r_daily, s);
    for (int j = 0; j < walks; j++) {
        S = S_0;
        for (int i = 0; i < 252; i++) {
            double L = dist(gen);
            S *= L;
            }
        
        double payoff = (S > K) ? S - K : 0.0;

        // updating averages avoiding overflow error
        r_a = (static_cast<double>(j) / (j + 1)) * r_a +  payoff / (j + 1);
        r_s_a = (static_cast<double>(j) / (j + 1)) * r_s_a +  payoff * payoff / (j + 1);
    }

    // calcuations for standard error using the sample standard deviation, given r_a as the sample mean
    double s_v = (walks / (walks - 1)) * (r_s_a - r_a * r_a);
    double s_s_d = std::sqrt(s_v);
    double se = s_s_d / std::sqrt(walks);

    double B_S_price = B_S(S_0, K, r, sigma);
    double M_C_price = std::exp(-r)*r_a;
    double upper_bound = std::exp(-r)*(r_a + 1.96*se);
    double lower_bound = std::exp(-r)*(r_a - 1.96*se);
    // constructing a 95% confidence interval around the mean option price

    std::cout << "The Black-Scholes price is " << B_S_price << "\n";
    std::cout << "The Monte-Carlo price is " << r_a << " With 95% confidence interval [" << lower_bound << ", " << upper_bound << "] \n";
    std::cout << ((lower_bound <= B_S_price && B_S_price <= upper_bound) 
        ? "So the Black-Scholes lies in this range \n" 
        : "So the Black-Scholes does not lie in this range \n");
}
