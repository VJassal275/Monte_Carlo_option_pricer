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

$$\text{payoff} = \text{max}(S_{252} - K, 0)$$

1 million simulations were then ran, computing the rolling average and rolling square average in order to calculate the mean and standard error option payoff. These values were then discounted back to present value and a 95% confidence interval was constructed as follows:

$$\text{discounted payoff} = \frac{\exp(\text{-}r)}{n} \sum_{i=1}^{n} \text{payoff}_i$$
$$\text{standard error} = \sqrt{\frac{1}{n-1} \left(\frac{\sum_{i=1}^{n} \text{payoff}_i^2}{n} - \left(\frac{\sum_{i=1}^{n} \text{payoff}_i}{n} \right)^2     \right)} $$
$$\text{discounted SE} = \exp(\text{-}r) \text{ SE} $$

$$\text{CI} = [d_{payoff}-1.96d_{SE},d_{payoff}+1.96d_{SE}] $$

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
./build/option_pricer
```

On Windows:

```powershell
.\build\Debug\option_pricer.exe
```

