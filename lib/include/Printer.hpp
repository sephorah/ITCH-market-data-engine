#ifndef PRINTER_HPP_
#define PRINTER_HPP_

#include <iostream>
#include <string>
#include "ItchMessages.hpp"

struct Printer
{
    template <typename Msg>
    void printCommon(const Msg &msg) const
    {
        std::cout << "Message Type: " << static_cast<char>(msg.messageType) << std::endl;
        std::cout << "Stock Locate: " << msg.stockLocate << std::endl;
        std::cout << "Tracking Number: " << msg.trackingNumber << std::endl;
        std::cout << "Timestamp: " << Itch::parseTimestamp(msg.timeStamp.data) << " ns" << std::endl;
    }

    void operator()(const Itch::SystemEventMessage &msg) const
    {
        printCommon(msg);
        std::cout << "Event Code: " << static_cast<char>(msg.eventCode) << std::endl;
        std::cout << std::endl;
    }

    void operator()(const Itch::StockDirectoryMessage &msg) const
    {
        printCommon(msg);
        std::cout << "Stock: " << std::string(msg.stock, 8) << std::endl;
        std::cout << "Market Category: " << static_cast<char>(msg.marketCategory) << std::endl;
        std::cout << "Financial Status: " << static_cast<char>(msg.financialStatusIndicator) << std::endl;
        std::cout << "Round Lot Size: " << msg.roundLotSize << std::endl;
        std::cout << "Round Lots Only: " << static_cast<char>(msg.roundLotsOnly) << std::endl;
        std::cout << "Issue Classification: " << static_cast<char>(msg.issueClassification) << std::endl;
        std::cout << "Issue Sub-Type: " << std::string(msg.issueSubType.data, 2) << std::endl;
        std::cout << "Authenticity: " << static_cast<char>(msg.authenticity) << std::endl;
        std::cout << "Short Sale Threshold: " << static_cast<char>(msg.shortSaleThresholdIndicator) << std::endl;
        std::cout << "IPO Flag: " << static_cast<char>(msg.IPOFlag) << std::endl;
        std::cout << "LULD Reference Price Tier: " << static_cast<char>(msg.LULDReferencePriceTier) << std::endl;
        std::cout << "ETP Flag: " << static_cast<char>(msg.ETPFlag) << std::endl;
        std::cout << "ETP Leverage Factor: " << msg.ETPLeverageFactor << std::endl;
        std::cout << "Inverse Indicator: " << static_cast<char>(msg.inverseIndicator) << std::endl;
        std::cout << std::endl;
    }

    void operator()(const Itch::StockTradingActionMessage &msg) const
    {
        printCommon(msg);
        std::cout << "Stock: " << std::string(msg.stock, 8) << std::endl;
        std::cout << "Trading State: " << static_cast<char>(msg.tradingState) << std::endl;
        std::cout << "Reserved: " << msg.reserved << std::endl;
        std::cout << "Reason: " << msg.reason << std::endl;
        std::cout << std::endl;
    }

    void operator()(const Itch::AddOrderMessage &msg) const
    {
        printCommon(msg);
        std::cout << "Order Reference: " << msg.orderRefNum << std::endl;
        std::cout << "Buy/Sell: " << static_cast<char>(msg.buySell) << std::endl;
        std::cout << "Shares: " << msg.shares << std::endl;
        std::cout << "Stock: " << std::string(msg.stock, 8) << std::endl;
        std::cout << "Price: " << msg.price / 10000.0 << std::endl;
        std::cout << std::endl;
    }

    void operator()(const Itch::AddOrderMPIDMessage &msg) const
    {
        printCommon(msg);
        std::cout << "Order Reference: " << msg.orderRefNum << std::endl;
        std::cout << "Buy/Sell: " << static_cast<char>(msg.buySell) << std::endl;
        std::cout << "Shares: " << msg.shares << std::endl;
        std::cout << "Stock: " << std::string(msg.stock, 8) << std::endl;
        std::cout << "Price: " << msg.price / 10000.0 << std::endl;
        std::cout << "Attribution: " << std::string(msg.attribution, 4) << std::endl;
        std::cout << std::endl;
    }

    void operator()(const Itch::OrderExecutedMessage &msg) const
    {
        printCommon(msg);
        std::cout << "Order Reference: " << msg.orderRefNum << std::endl;
        std::cout << "Executed Shares: " << msg.executedShares << std::endl;
        std::cout << "Match Number: " << msg.matchNumber << std::endl;
        std::cout << std::endl;
    }

    void operator()(const Itch::OrderExecutedWithPriceMessage &msg) const
    {
        printCommon(msg);
        std::cout << "Order Reference: " << msg.orderRefNum << std::endl;
        std::cout << "Executed Shares: " << msg.executedShares << std::endl;
        std::cout << "Match Number: " << msg.matchNumber << std::endl;
        std::cout << "Printable: " << static_cast<char>(msg.printable) << std::endl;
        std::cout << "Price: " << msg.price / 10000.0 << std::endl;
        std::cout << std::endl;
    }

    void operator()(const Itch::OrderCancelMessage &msg) const
    {
        printCommon(msg);
        std::cout << "Order Reference: " << msg.orderRefNum << std::endl;
        std::cout << "Cancelled Shares: " << msg.cancelledShares << std::endl;
        std::cout << std::endl;
    }

    void operator()(const Itch::OrderDeleteMessage &msg) const
    {
        printCommon(msg);
        std::cout << "Order Reference: " << msg.orderRefNum << std::endl;
        std::cout << std::endl;
    }

    void operator()(const Itch::OrderReplaceMessage &msg) const
    {
        printCommon(msg);
        std::cout << "Original Order Reference: " << msg.originalOrderRefNum << std::endl;
        std::cout << "New Order Reference: " << msg.newOrderRefNum << std::endl;
        std::cout << "Shares: " << msg.shares << std::endl;
        std::cout << "Price: " << msg.price / 10000.0 << std::endl;
        std::cout << std::endl;
    }
};

#endif /* !PRINTER_HPP_ */