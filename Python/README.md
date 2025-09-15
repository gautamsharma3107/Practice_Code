# Trading Bot

A comprehensive Python trading bot implementation with multiple strategies, risk management, and backtesting capabilities.

## Features

### Core Components
- **Market Data Provider**: Simulates real-time market data for testing
- **Trading Strategies**: Multiple built-in strategies
- **Portfolio Management**: Track positions, cash, and P&L
- **Risk Management**: Position sizing, stop losses, and risk controls
- **Backtesting**: Historical simulation capabilities

### Included Strategies
1. **Moving Average Crossover**: Buy when short MA crosses above long MA, sell when it crosses below
2. **RSI (Relative Strength Index)**: Buy when oversold (RSI < 30), sell when overbought (RSI > 70)

### Risk Management Features
- Maximum position size limits (default: 10% of portfolio)
- Stop loss protection (default: 5% loss)
- Cash management and validation
- Daily loss limits

## Quick Start

### Basic Usage
```python
from trading_bot import TradingBot, MovingAverageStrategy, RSIStrategy

# Create trading bot with $100,000 initial capital
bot = TradingBot(initial_cash=100000.0)

# Add trading strategies
bot.add_strategy(MovingAverageStrategy(short_period=5, long_period=20))
bot.add_strategy(RSIStrategy(period=14, oversold=30, overbought=70))

# Run backtest
results = bot.run_backtest(iterations=100)

# View results
print(f"Final Portfolio Value: ${results['final_summary']['portfolio_value']:,.2f}")
print(f"Total Return: {results['final_summary']['return_pct']:.2f}%")
```

### Running the Demo
```bash
cd Python
python3 trading_bot.py
```

## File Structure

- `trading_bot.py` - Main trading bot implementation
- `trading_bot_config.json` - Configuration file for bot parameters
- `requirements.txt` - Python dependencies (all optional)
- `README.md` - This documentation file

## Configuration

Edit `trading_bot_config.json` to customize:
- Initial cash amount
- Risk management parameters
- Strategy settings
- Symbols to trade
- Backtesting parameters

## Classes Overview

### TradingBot
Main bot class that orchestrates all components.

### MarketDataProvider
Simulates market data with realistic price movements.

### TradingStrategy (Base Class)
- `MovingAverageStrategy`: Implements MA crossover signals
- `RSIStrategy`: Implements RSI overbought/oversold signals

### Portfolio
Manages cash, positions, and trade history.

### RiskManager
Enforces risk limits and generates stop-loss orders.

### Order & Position
Data classes for tracking trades and holdings.

## Example Output

```
=== Trading Bot Demo ===

Strategies added:
- MA(5,20)
- RSI(14)

Starting backtest...

=== Backtest Results ===
Initial Cash: $100,000.00
Final Portfolio Value: $102,450.75
Total Return: 2.45%
Total P&L: $1,250.30
Total Trades: 15
Remaining Cash: $85,200.45

Final Positions:
- AAPL: 25.50 shares @ $152.30 (Avg: $149.80, P&L: $63.75)
- GOOGL: 2.10 shares @ $2,510.00 (Avg: $2,485.50, P&L: $51.45)
```

## Extending the Bot

### Adding New Strategies
```python
class MyCustomStrategy(TradingStrategy):
    def __init__(self):
        super().__init__("MyStrategy")
    
    def generate_signal(self, symbol, market_data, historical_data):
        # Your strategy logic here
        # Return OrderType.BUY, OrderType.SELL, or None
        pass

# Add to bot
bot.add_strategy(MyCustomStrategy())
```

### Real Market Data Integration
To use real market data, replace `MarketDataProvider` with actual API calls:

```python
# Example with yfinance (install: pip install yfinance)
import yfinance as yf

def get_real_market_data(symbol):
    ticker = yf.Ticker(symbol)
    data = ticker.history(period="1d", interval="1m")
    return MarketData(
        symbol=symbol,
        price=data['Close'].iloc[-1],
        volume=data['Volume'].iloc[-1],
        timestamp=datetime.now()
    )
```

## Performance Notes

- The bot uses Python's built-in libraries for maximum compatibility
- Market data simulation provides realistic price movements
- Backtesting is efficient and can handle hundreds of iterations
- Results are saved to JSON files for analysis

## Disclaimer

This is an educational implementation for learning purposes. It simulates market conditions and should not be used for actual trading without proper testing, risk assessment, and regulatory compliance.

## License

This code is part of the Practice_Code repository and is intended for educational purposes.