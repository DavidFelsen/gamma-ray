#pragma once
#include <vector>
#include "json.hpp"
#include "interfaces.h"
#include "quoting_engine.h"
#include "delta_parser.h"
#include "bitmex_gateway.h"
#include "Poco/Delegate.h"

using json = nlohmann::json;

class QuoteDispatcher
{
private:
  BitmexStore &store;
  QuotingEngine &engine;
  Interfaces::IOrderEntryGateway &oe;
  Interfaces::IPositionGateway &pg;
  Interfaces::IRateLimitMonitor &rl;
  Interfaces::IExchangeDetailsGateway &details;

  bool has_enough_margin(double bid_price, double bid_size, double ask_price, double ask_size);
  void on_new_quote(const void *, Models::TwoSidedQuote &two_sided_quote);
  void converge_orders(std::vector<Models::Quote> bids, std::vector<Models::Quote> asks, Poco::DateTime time);

public:
  QuoteDispatcher(BitmexStore &store, QuotingEngine &engine, Interfaces::IOrderEntryGateway &oe, Interfaces::IPositionGateway &pg, Interfaces::IRateLimitMonitor &rl, Interfaces::IExchangeDetailsGateway &details);
  ~QuoteDispatcher();
};