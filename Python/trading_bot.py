"""
Trading Bot Implementation
A comprehensive trading bot with multiple strategies, risk management, and backtesting capabilities.
"""

import logging
import json
import random
import time
from datetime import datetime, timedelta
from typing import Dict, List, Tuple, Optional
from dataclasses import dataclass, asdict
from enum import Enum
import statistics


class OrderType(Enum):
    BUY = "BUY"
    SELL = "SELL"


class OrderStatus(Enum):
    PENDING = "PENDING"
    EXECUTED = "EXECUTED"
    CANCELLED = "CANCELLED"


@dataclass
class Order:
    symbol: str
    order_type: OrderType
    quantity: float
    price: float
    timestamp: datetime
    status: OrderStatus = OrderStatus.PENDING
    order_id: str = None

    def __post_init__(self):
        if self.order_id is None:
            self.order_id = f"ORD_{int(time.time() * 1000000)}"


@dataclass
class Position:
    symbol: str
    quantity: float
    avg_price: float
    current_price: float = 0.0

    @property
    def market_value(self) -> float:
        return self.quantity * self.current_price

    @property
    def unrealized_pnl(self) -> float:
        return (self.current_price - self.avg_price) * self.quantity


@dataclass
class MarketData:
    symbol: str
    price: float
    volume: float
    timestamp: datetime
    high: float = None
    low: float = None
    open: float = None

    def __post_init__(self):
        if self.high is None:
            self.high = self.price * random.uniform(1.00, 1.02)
        if self.low is None:
            self.low = self.price * random.uniform(0.98, 1.00)
        if self.open is None:
            self.open = self.price * random.uniform(0.99, 1.01)


class MarketDataProvider:
    """Simulates market data for testing purposes"""
    
    def __init__(self):
        self.symbols = ["AAPL", "GOOGL", "MSFT", "TSLA", "AMZN"]
        self.base_prices = {
            "AAPL": 150.0,
            "GOOGL": 2500.0,
            "MSFT": 300.0,
            "TSLA": 800.0,
            "AMZN": 3200.0
        }
        self.price_history = {symbol: [] for symbol in self.symbols}
        
    def get_market_data(self, symbol: str) -> MarketData:
        """Simulate real-time market data"""
        if symbol not in self.base_prices:
            raise ValueError(f"Symbol {symbol} not supported")
            
        # Simulate price movement with some randomness
        base_price = self.base_prices[symbol]
        if self.price_history[symbol]:
            last_price = self.price_history[symbol][-1].price
            # Random walk with slight trend
            price_change = random.uniform(-0.02, 0.02) * last_price
            new_price = max(0.01, last_price + price_change)
        else:
            new_price = base_price
            
        market_data = MarketData(
            symbol=symbol,
            price=new_price,
            volume=random.uniform(1000, 10000),
            timestamp=datetime.now()
        )
        
        self.price_history[symbol].append(market_data)
        # Keep only last 100 data points
        if len(self.price_history[symbol]) > 100:
            self.price_history[symbol] = self.price_history[symbol][-100:]
            
        return market_data
    
    def get_historical_data(self, symbol: str, periods: int = 20) -> List[MarketData]:
        """Get historical market data for analysis"""
        if symbol not in self.price_history or len(self.price_history[symbol]) == 0:
            # Generate some initial data
            for _ in range(periods):
                self.get_market_data(symbol)
                
        return self.price_history[symbol][-periods:]


class TradingStrategy:
    """Base class for trading strategies"""
    
    def __init__(self, name: str):
        self.name = name
        
    def generate_signal(self, symbol: str, market_data: MarketData, 
                       historical_data: List[MarketData]) -> Optional[OrderType]:
        """Generate trading signal based on market data"""
        raise NotImplementedError


class MovingAverageStrategy(TradingStrategy):
    """Simple Moving Average Crossover Strategy"""
    
    def __init__(self, short_period: int = 5, long_period: int = 20):
        super().__init__(f"MA({short_period},{long_period})")
        self.short_period = short_period
        self.long_period = long_period
        
    def generate_signal(self, symbol: str, market_data: MarketData, 
                       historical_data: List[MarketData]) -> Optional[OrderType]:
        if len(historical_data) < self.long_period:
            return None
            
        prices = [data.price for data in historical_data]
        
        short_ma = statistics.mean(prices[-self.short_period:])
        long_ma = statistics.mean(prices[-self.long_period:])
        prev_short_ma = statistics.mean(prices[-self.short_period-1:-1])
        prev_long_ma = statistics.mean(prices[-self.long_period-1:-1])
        
        # Buy signal: short MA crosses above long MA
        if short_ma > long_ma and prev_short_ma <= prev_long_ma:
            return OrderType.BUY
        # Sell signal: short MA crosses below long MA
        elif short_ma < long_ma and prev_short_ma >= prev_long_ma:
            return OrderType.SELL
            
        return None


class RSIStrategy(TradingStrategy):
    """Relative Strength Index Strategy"""
    
    def __init__(self, period: int = 14, oversold: float = 30, overbought: float = 70):
        super().__init__(f"RSI({period})")
        self.period = period
        self.oversold = oversold
        self.overbought = overbought
        
    def calculate_rsi(self, prices: List[float]) -> float:
        if len(prices) < self.period + 1:
            return 50.0  # Neutral RSI
            
        deltas = [prices[i] - prices[i-1] for i in range(1, len(prices))]
        gains = [delta if delta > 0 else 0 for delta in deltas]
        losses = [-delta if delta < 0 else 0 for delta in deltas]
        
        avg_gain = statistics.mean(gains[-self.period:])
        avg_loss = statistics.mean(losses[-self.period:])
        
        if avg_loss == 0:
            return 100.0
            
        rs = avg_gain / avg_loss
        rsi = 100 - (100 / (1 + rs))
        return rsi
        
    def generate_signal(self, symbol: str, market_data: MarketData, 
                       historical_data: List[MarketData]) -> Optional[OrderType]:
        if len(historical_data) < self.period + 1:
            return None
            
        prices = [data.price for data in historical_data]
        rsi = self.calculate_rsi(prices)
        
        if rsi <= self.oversold:
            return OrderType.BUY
        elif rsi >= self.overbought:
            return OrderType.SELL
            
        return None


class Portfolio:
    """Portfolio management class"""
    
    def __init__(self, initial_cash: float = 100000.0):
        self.cash = initial_cash
        self.initial_cash = initial_cash
        self.positions: Dict[str, Position] = {}
        self.orders: List[Order] = []
        self.trade_history: List[Order] = []
        
    def add_position(self, symbol: str, quantity: float, price: float):
        """Add or update position"""
        if symbol in self.positions:
            # Update existing position
            position = self.positions[symbol]
            total_quantity = position.quantity + quantity
            if total_quantity == 0:
                del self.positions[symbol]
            else:
                total_cost = (position.quantity * position.avg_price) + (quantity * price)
                position.avg_price = total_cost / total_quantity
                position.quantity = total_quantity
        else:
            # Create new position
            if quantity != 0:
                self.positions[symbol] = Position(symbol, quantity, price)
                
    def update_positions(self, market_data: Dict[str, MarketData]):
        """Update current prices for all positions"""
        for symbol, position in self.positions.items():
            if symbol in market_data:
                position.current_price = market_data[symbol].price
                
    def get_portfolio_value(self) -> float:
        """Calculate total portfolio value"""
        total_value = self.cash
        for position in self.positions.values():
            total_value += position.market_value
        return total_value
    
    def get_total_pnl(self) -> float:
        """Calculate total unrealized P&L"""
        return sum(position.unrealized_pnl for position in self.positions.values())
    
    def get_portfolio_summary(self) -> Dict:
        """Get portfolio summary"""
        return {
            "cash": self.cash,
            "portfolio_value": self.get_portfolio_value(),
            "total_pnl": self.get_total_pnl(),
            "return_pct": ((self.get_portfolio_value() - self.initial_cash) / self.initial_cash) * 100,
            "positions": {symbol: asdict(position) for symbol, position in self.positions.items()},
            "total_trades": len(self.trade_history)
        }


class RiskManager:
    """Risk management system"""
    
    def __init__(self, max_position_size: float = 0.1, stop_loss_pct: float = 0.05, 
                 max_daily_loss: float = 0.02):
        self.max_position_size = max_position_size  # Max 10% of portfolio per position
        self.stop_loss_pct = stop_loss_pct  # 5% stop loss
        self.max_daily_loss = max_daily_loss  # Max 2% daily loss
        
    def validate_order(self, order: Order, portfolio: Portfolio) -> bool:
        """Validate if order meets risk criteria"""
        portfolio_value = portfolio.get_portfolio_value()
        order_value = order.quantity * order.price
        
        # Check position size limit
        if order.order_type == OrderType.BUY:
            if order_value > portfolio_value * self.max_position_size:
                logging.warning(f"Order {order.order_id} exceeds max position size")
                return False
                
            # Check if we have enough cash
            if order_value > portfolio.cash:
                logging.warning(f"Order {order.order_id} exceeds available cash")
                return False
                
        return True
    
    def check_stop_loss(self, portfolio: Portfolio) -> List[Order]:
        """Check for stop loss conditions and generate sell orders"""
        stop_loss_orders = []
        
        for symbol, position in portfolio.positions.items():
            if position.quantity > 0:  # Long position
                loss_pct = (position.avg_price - position.current_price) / position.avg_price
                if loss_pct >= self.stop_loss_pct:
                    # Create stop loss sell order
                    order = Order(
                        symbol=symbol,
                        order_type=OrderType.SELL,
                        quantity=position.quantity,
                        price=position.current_price,
                        timestamp=datetime.now()
                    )
                    stop_loss_orders.append(order)
                    logging.info(f"Stop loss triggered for {symbol}")
                    
        return stop_loss_orders


class TradingBot:
    """Main trading bot class"""
    
    def __init__(self, initial_cash: float = 100000.0):
        self.portfolio = Portfolio(initial_cash)
        self.market_data_provider = MarketDataProvider()
        self.strategies: List[TradingStrategy] = []
        self.risk_manager = RiskManager()
        self.is_running = False
        
        # Setup logging
        logging.basicConfig(
            level=logging.INFO,
            format='%(asctime)s - %(levelname)s - %(message)s'
        )
        self.logger = logging.getLogger(__name__)
        
    def add_strategy(self, strategy: TradingStrategy):
        """Add a trading strategy"""
        self.strategies.append(strategy)
        self.logger.info(f"Added strategy: {strategy.name}")
        
    def execute_order(self, order: Order) -> bool:
        """Execute a trading order"""
        if not self.risk_manager.validate_order(order, self.portfolio):
            order.status = OrderStatus.CANCELLED
            return False
            
        try:
            if order.order_type == OrderType.BUY:
                cost = order.quantity * order.price
                self.portfolio.cash -= cost
                self.portfolio.add_position(order.symbol, order.quantity, order.price)
            else:  # SELL
                if order.symbol in self.portfolio.positions:
                    position = self.portfolio.positions[order.symbol]
                    if position.quantity >= order.quantity:
                        proceeds = order.quantity * order.price
                        self.portfolio.cash += proceeds
                        self.portfolio.add_position(order.symbol, -order.quantity, order.price)
                    else:
                        self.logger.warning(f"Insufficient position to sell {order.symbol}")
                        return False
                else:
                    self.logger.warning(f"No position to sell in {order.symbol}")
                    return False
                    
            order.status = OrderStatus.EXECUTED
            self.portfolio.trade_history.append(order)
            self.logger.info(f"Executed order: {order.order_type.value} {order.quantity} {order.symbol} @ {order.price}")
            return True
            
        except Exception as e:
            self.logger.error(f"Error executing order: {e}")
            order.status = OrderStatus.CANCELLED
            return False
    
    def run_single_iteration(self) -> Dict:
        """Run a single trading iteration"""
        current_market_data = {}
        signals = {}
        
        # Get market data for all symbols
        for symbol in self.market_data_provider.symbols:
            market_data = self.market_data_provider.get_market_data(symbol)
            current_market_data[symbol] = market_data
            
            # Get signals from all strategies
            historical_data = self.market_data_provider.get_historical_data(symbol)
            for strategy in self.strategies:
                signal = strategy.generate_signal(symbol, market_data, historical_data)
                if signal:
                    if symbol not in signals:
                        signals[symbol] = []
                    signals[symbol].append((strategy.name, signal))
        
        # Update portfolio with current prices
        self.portfolio.update_positions(current_market_data)
        
        # Check for stop losses
        stop_loss_orders = self.risk_manager.check_stop_loss(self.portfolio)
        for order in stop_loss_orders:
            self.execute_order(order)
        
        # Execute trades based on signals
        orders_executed = []
        for symbol, symbol_signals in signals.items():
            # Simple consensus: if majority of strategies agree
            buy_signals = sum(1 for _, signal in symbol_signals if signal == OrderType.BUY)
            sell_signals = sum(1 for _, signal in symbol_signals if signal == OrderType.SELL)
            
            if buy_signals > sell_signals and buy_signals > 0:
                # Calculate position size (simple: 5% of portfolio)
                portfolio_value = self.portfolio.get_portfolio_value()
                position_value = portfolio_value * 0.05
                quantity = position_value / current_market_data[symbol].price
                
                order = Order(
                    symbol=symbol,
                    order_type=OrderType.BUY,
                    quantity=quantity,
                    price=current_market_data[symbol].price,
                    timestamp=datetime.now()
                )
                
                if self.execute_order(order):
                    orders_executed.append(order)
                    
            elif sell_signals > buy_signals and sell_signals > 0:
                # Sell existing position if we have one
                if symbol in self.portfolio.positions:
                    position = self.portfolio.positions[symbol]
                    order = Order(
                        symbol=symbol,
                        order_type=OrderType.SELL,
                        quantity=position.quantity,
                        price=current_market_data[symbol].price,
                        timestamp=datetime.now()
                    )
                    
                    if self.execute_order(order):
                        orders_executed.append(order)
        
        return {
            "timestamp": datetime.now(),
            "market_data": {symbol: asdict(data) for symbol, data in current_market_data.items()},
            "signals": signals,
            "orders_executed": [asdict(order) for order in orders_executed],
            "portfolio": self.portfolio.get_portfolio_summary()
        }
    
    def run_backtest(self, iterations: int = 100) -> Dict:
        """Run backtest simulation"""
        self.logger.info(f"Starting backtest with {iterations} iterations")
        
        results = []
        for i in range(iterations):
            iteration_result = self.run_single_iteration()
            results.append(iteration_result)
            
            if i % 20 == 0:
                portfolio_summary = self.portfolio.get_portfolio_summary()
                self.logger.info(f"Iteration {i}: Portfolio Value: ${portfolio_summary['portfolio_value']:.2f}, "
                               f"Return: {portfolio_summary['return_pct']:.2f}%")
        
        final_summary = self.portfolio.get_portfolio_summary()
        self.logger.info(f"Backtest completed. Final Portfolio Value: ${final_summary['portfolio_value']:.2f}, "
                        f"Total Return: {final_summary['return_pct']:.2f}%")
        
        return {
            "iterations": results,
            "final_summary": final_summary,
            "total_iterations": iterations
        }
    
    def start(self):
        """Start the trading bot"""
        self.is_running = True
        self.logger.info("Trading bot started")
        
    def stop(self):
        """Stop the trading bot"""
        self.is_running = False
        self.logger.info("Trading bot stopped")


def main():
    """Example usage of the trading bot"""
    print("=== Trading Bot Demo ===")
    
    # Create trading bot
    bot = TradingBot(initial_cash=100000.0)
    
    # Add strategies
    bot.add_strategy(MovingAverageStrategy(short_period=5, long_period=20))
    bot.add_strategy(RSIStrategy(period=14, oversold=30, overbought=70))
    
    print("\nStrategies added:")
    for strategy in bot.strategies:
        print(f"- {strategy.name}")
    
    # Run backtest
    print(f"\nStarting backtest...")
    backtest_results = bot.run_backtest(iterations=50)
    
    # Print results
    final_summary = backtest_results["final_summary"]
    print("\n=== Backtest Results ===")
    print(f"Initial Cash: ${bot.portfolio.initial_cash:,.2f}")
    print(f"Final Portfolio Value: ${final_summary['portfolio_value']:,.2f}")
    print(f"Total Return: {final_summary['return_pct']:.2f}%")
    print(f"Total P&L: ${final_summary['total_pnl']:,.2f}")
    print(f"Total Trades: {final_summary['total_trades']}")
    print(f"Remaining Cash: ${final_summary['cash']:,.2f}")
    
    if final_summary['positions']:
        print("\nFinal Positions:")
        for symbol, position in final_summary['positions'].items():
            print(f"- {symbol}: {position['quantity']:.2f} shares @ ${position['current_price']:.2f} "
                  f"(Avg: ${position['avg_price']:.2f}, P&L: ${position['quantity'] * (position['current_price'] - position['avg_price']):.2f})")
    
    # Save results to file
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    filename = f"/tmp/trading_bot_results_{timestamp}.json"
    
    # Convert datetime objects and enums to strings for JSON serialization
    def json_serial(obj):
        if isinstance(obj, datetime):
            return obj.isoformat()
        elif isinstance(obj, (OrderType, OrderStatus)):
            return obj.value
        raise TypeError(f"Type {type(obj)} not serializable")
    
    with open(filename, 'w') as f:
        json.dump(backtest_results, f, indent=2, default=json_serial)
    
    print(f"\nResults saved to: {filename}")


if __name__ == "__main__":
    main()