#!/usr/bin/env python3
"""
Trading Bot Examples
Demonstrates various ways to use the trading bot
"""

from trading_bot import (
    TradingBot, MovingAverageStrategy, RSIStrategy, 
    MarketData, OrderType, Portfolio
)
import json


def example_basic_usage():
    """Basic usage example"""
    print("=== Basic Usage Example ===")
    
    # Create bot with custom initial cash
    bot = TradingBot(initial_cash=50000.0)
    
    # Add strategies
    bot.add_strategy(MovingAverageStrategy(short_period=3, long_period=10))
    bot.add_strategy(RSIStrategy(period=10, oversold=25, overbought=75))
    
    # Run short backtest
    results = bot.run_backtest(iterations=25)
    
    # Print summary
    summary = results["final_summary"]
    print(f"Portfolio Value: ${summary['portfolio_value']:,.2f}")
    print(f"Return: {summary['return_pct']:.2f}%")
    print(f"Total Trades: {summary['total_trades']}")
    print()


def example_single_strategy():
    """Example using only one strategy"""
    print("=== Single Strategy Example (RSI Only) ===")
    
    bot = TradingBot(initial_cash=75000.0)
    bot.add_strategy(RSIStrategy(period=14, oversold=20, overbought=80))
    
    results = bot.run_backtest(iterations=30)
    summary = results["final_summary"]
    
    print(f"RSI-only Portfolio Value: ${summary['portfolio_value']:,.2f}")
    print(f"Return: {summary['return_pct']:.2f}%")
    print()


def example_custom_parameters():
    """Example with custom risk management parameters"""
    print("=== Custom Parameters Example ===")
    
    bot = TradingBot(initial_cash=200000.0)
    
    # Modify risk management settings
    bot.risk_manager.max_position_size = 0.15  # 15% max position
    bot.risk_manager.stop_loss_pct = 0.03      # 3% stop loss
    
    # Add conservative strategies
    bot.add_strategy(MovingAverageStrategy(short_period=10, long_period=30))
    bot.add_strategy(RSIStrategy(period=21, oversold=35, overbought=65))
    
    results = bot.run_backtest(iterations=40)
    summary = results["final_summary"]
    
    print(f"Conservative Portfolio Value: ${summary['portfolio_value']:,.2f}")
    print(f"Return: {summary['return_pct']:.2f}%")
    print()


def example_manual_iteration():
    """Example of manual step-by-step execution"""
    print("=== Manual Iteration Example ===")
    
    bot = TradingBot(initial_cash=25000.0)
    bot.add_strategy(MovingAverageStrategy(short_period=5, long_period=15))
    
    print("Running 5 manual iterations:")
    for i in range(5):
        result = bot.run_single_iteration()
        portfolio = result["portfolio"]
        orders = result["orders_executed"]
        
        print(f"Iteration {i+1}:")
        print(f"  Portfolio Value: ${portfolio['portfolio_value']:,.2f}")
        print(f"  Orders Executed: {len(orders)}")
        if orders:
            for order in orders:
                print(f"    {order['order_type']} {order['quantity']:.2f} {order['symbol']} @ ${order['price']:.2f}")
        print()


def example_analyze_results():
    """Example of analyzing backtest results"""
    print("=== Results Analysis Example ===")
    
    bot = TradingBot(initial_cash=100000.0)
    bot.add_strategy(MovingAverageStrategy())
    bot.add_strategy(RSIStrategy())
    
    results = bot.run_backtest(iterations=50)
    
    # Analyze performance over time
    portfolio_values = []
    trade_counts = []
    
    for iteration in results["iterations"]:
        portfolio_values.append(iteration["portfolio"]["portfolio_value"])
        trade_counts.append(len(iteration["orders_executed"]))
    
    # Calculate some statistics
    max_value = max(portfolio_values)
    min_value = min(portfolio_values)
    total_trades = sum(trade_counts)
    avg_trades_per_iteration = total_trades / len(results["iterations"])
    
    print(f"Performance Analysis:")
    print(f"  Initial Value: ${portfolio_values[0]:,.2f}")
    print(f"  Final Value: ${portfolio_values[-1]:,.2f}")
    print(f"  Maximum Value: ${max_value:,.2f}")
    print(f"  Minimum Value: ${min_value:,.2f}")
    print(f"  Total Trades: {total_trades}")
    print(f"  Avg Trades/Iteration: {avg_trades_per_iteration:.2f}")
    print()


def example_portfolio_inspection():
    """Example of inspecting portfolio state"""
    print("=== Portfolio Inspection Example ===")
    
    bot = TradingBot(initial_cash=80000.0)
    bot.add_strategy(MovingAverageStrategy(short_period=3, long_period=8))
    
    # Run a few iterations
    for _ in range(10):
        bot.run_single_iteration()
    
    # Inspect portfolio
    portfolio = bot.portfolio
    summary = portfolio.get_portfolio_summary()
    
    print(f"Portfolio Status:")
    print(f"  Cash: ${summary['cash']:,.2f}")
    print(f"  Total Value: ${summary['portfolio_value']:,.2f}")
    print(f"  Total P&L: ${summary['total_pnl']:,.2f}")
    print(f"  Return: {summary['return_pct']:.2f}%")
    
    if summary['positions']:
        print(f"  Active Positions:")
        for symbol, position in summary['positions'].items():
            pnl = position['quantity'] * (position['current_price'] - position['avg_price'])
            print(f"    {symbol}: {position['quantity']:.2f} shares @ ${position['current_price']:.2f} "
                  f"(P&L: ${pnl:.2f})")
    
    print(f"  Recent Trades: {len(portfolio.trade_history)} total")
    if portfolio.trade_history:
        print("  Last 3 trades:")
        for trade in portfolio.trade_history[-3:]:
            print(f"    {trade.order_type.value} {trade.quantity:.2f} {trade.symbol} @ ${trade.price:.2f}")
    
    print()


def main():
    """Run all examples"""
    print("Trading Bot Examples\n")
    print("=" * 50)
    
    example_basic_usage()
    example_single_strategy()
    example_custom_parameters()
    example_manual_iteration()
    example_analyze_results()
    example_portfolio_inspection()
    
    print("All examples completed!")


if __name__ == "__main__":
    main()