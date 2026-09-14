# Monte_Carlo_option_pricer
1-year European call option pricer with Monte-Carlo methods 

## Model

The underlying asset price dynamics were modelled as a multiplicative random walk with lognormal daily returns using risk-neutral drift and volatility. Taking the trading year to be 252 days, the lognormal distribution parameters were created as follows:

$$s = \frac{\sigma}{\sqrt{252}}$$

$$X \sim \text{LogN}(\mu, s^2) \Rightarrow E[X] = \exp \left(\mu + \frac{s^2}{2} \right)$$
where we want the expected daily multiplier under the risk-neutral measure to be:
$$E[X] = \exp \left(\frac{r}{252} \right) $$
Hence $$\frac{r}{252} = \mu + \frac{s^2}{2} \Rightarrow \mu = \frac{r - \frac{\sigma^2}{2}}{252} $$

Therefore, $$S_{t+1} = R S_t$$ 
where $$R \sim \text{LogN}(\mu, s^2) $$

where r is the continuous risk-free interest rate, $$\sigma$$ is the realised annual volatility of the stock, $$S_t$$ is the price of the stock on day t

Expiration payoffs for each simulation were calculated for strike price K as below:

$$p = \text{max}(S_{252} - K, 0)$$

n = 1 million simulations were then ran, computing the rolling average and rolling square average in order to calculate the mean and standard error option payoff. These values were then discounted back to present value and a 95% confidence interval was constructed as follows:

$$p_{discounted} = \frac{\exp(\text{-}r)}{n} \sum_{i=1}^{n} p_i$$
$$\text{Standard Error} = \sqrt{\frac{1}{n-1} \left(\frac{\sum_{i=1}^{n} p_i^2}{n} - \left(\frac{\sum_{i=1}^{n} p_i}{n} \right)^2 \right)} $$
$$SE_{discounted} = \exp(\text{-}r) \text{ SE} $$

$$\text{CI} = [p_{disc}-1.96SE_{disc},p_{disc}+1.96SE_{disc}] $$

In order to valid the accuracy of this model, the Monte Carlo option prices were compared to the analytical Black-Scholes price of the same option by testing if the Black-Scholes price given below lied in the 95% confidence interval of the Monte Carlo price in at least 95% of trials.

$$d_1 = \frac{\log \left(\frac{S}{K} \right) + r + \frac{\sigma^2}{2}}{\sigma} $$
$$d_2 = d_1 - \sigma $$
$$\text{Black-Scholes price} = SN(d_1) - K \exp(\text{-}r) N(d_2) $$

where N(x) is the normal distribution cdf. Note these formulae hold for an expiration time of 1 year.

## Example output

Output for S = 100.0, K = 90.0, r = 0.03, sigma = 0.20:

The Black-Scholes price is 10.4506

The Monte-Carlo price is 10.3921 with 95% confidence interval [10.1067, 10.6776] 

So the Black-Scholes lies in this range 

## Build and Run

### Requirements

- A C++17-compatible compiler
- CMake 3.15 or later

### Build

Clone the repository and navigate to the project directory:

```bash
git clone <repository-url>
cd Monte_Carlo_option_pricer
```

Replace `<repository-url>` with the URL of this GitHub repository.

Configure and build the project using CMake:

```bash
cmake -S . -B build
cmake --build build
```

### Run

On macOS/Linux:

```bash
./build/Monte_Carlo_option_pricer
```

On Windows:

```powershell
.\build\Debug\Monte_Carlo_option_pricer.exe
```

## Results

### Summary

No. trials: 30

Simulations per trial: 1000000

Overall Black-Scholes coverage: 29/30

ITM coverage: 10/10

ATM coverage: 10/10

OTM coverage: 9/10

Table of trial results without Black-Scholes parameters (full table can be found in results.csv):

| Trial | MC Price | 95% CI Lower | 95% CI Upper | BS Price | BS in CI? |
| ----: | -------: | -----------: | -----------: | -------: | :-------: |
|     1 |  10.3921 |      10.1067 |      10.6776 |  10.4506 |    Yes    |
|     2 |  10.2287 |      9.94314 |      10.5143 |  10.4506 |    Yes    |
|     3 |  13.2463 |      13.2137 |      13.2788 |  13.2423 |    Yes    |
|     4 |  21.6429 |      21.5883 |      21.6975 |  21.6641 |    Yes    |
|     5 |  14.5539 |      14.5242 |      14.5836 |  14.5573 |    Yes    |
|     6 |  16.8424 |      16.7908 |      16.8940 |  16.8550 |    Yes    |
|     7 |  24.3591 |      24.3057 |      24.4124 |  24.3543 |    Yes    |
|     8 |  36.5190 |      36.4169 |      36.6211 |  36.5437 |    Yes    |
|     9 |  13.2758 |      13.2485 |      13.3030 |  13.2656 |    Yes    |
|    10 |  43.6782 |      43.5755 |      43.7809 |  43.6700 |    Yes    |
|    11 |  10.4287 |      10.3999 |      10.4575 |  10.4506 |    Yes    |
|    12 |  13.2740 |      13.2311 |      13.3169 |  13.2833 |    Yes    |
|    13 |  9.77723 |      9.75428 |      9.80018 |  9.77309 |    Yes    |
|    14 |  12.4385 |      12.4010 |      12.4759 |  12.4289 |    Yes    |
|    15 |  15.8604 |      15.8038 |      15.9169 |  15.8692 |    Yes    |
|    16 |  13.1701 |      13.1348 |      13.2054 |  13.1875 |    Yes    |
|    17 |  16.7486 |      16.6848 |      16.8124 |  16.7692 |    Yes    |
|    18 |  10.2053 |      10.1826 |      10.2280 |  10.2074 |    Yes    |
|    19 |  31.3197 |      31.2160 |      31.4234 |  31.3363 |    Yes    |
|    20 |  7.26916 |      7.24546 |      7.29286 |  7.28248 |    Yes    |
|    21 |  5.27848 |      5.25706 |      5.29989 |   5.2934 |    Yes    |
|    22 |   4.9884 |      4.96406 |      5.01274 |  5.02541 |     No    |
|    23 |  10.2789 |      10.2391 |      10.3187 |  10.2852 |    Yes    |
|    24 |  10.6927 |      10.6458 |      10.7396 |  10.6708 |    Yes    |
|    25 |  2.14072 |      2.12557 |      2.15586 |  2.14105 |    Yes    |
|    26 |  10.7757 |      10.7273 |      10.8241 |  10.7808 |    Yes    |
|    27 |  4.30774 |      4.28955 |      4.32593 |   4.3076 |    Yes    |
|    28 |   9.9235 |      9.87588 |      9.97112 |  9.88849 |    Yes    |
|    29 |  2.59696 |      2.58110 |      2.61282 |  2.59068 |    Yes    |
|    30 |  11.1002 |      11.0563 |      11.1441 |  11.1339 |    Yes    |
