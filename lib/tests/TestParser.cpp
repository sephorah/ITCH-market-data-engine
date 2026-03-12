#include <gtest/gtest.h>
#include <string>
#include "ItchParser.hpp"
#include "CaptureMessage.hpp"

TEST(ItchParser, ParseSystemEventMessage)
{
    const char systemEvent[] = {
        'S',                                            // Message Type: SystemEvent
        '\x04', '\xD2',                                 // Stock Locate: 1234
        '\x05', '\x39',                                 // Tracking Number: 1337
        '\x1F', '\x1A', '\xCE', '\xD9', '\xF0', '\x00', // Timestamp: 34,200,000,000,000 ns
        'O'                                             // Event Code: 'O' (Start of Messages)
    };

    CaptureMessage captureMessage;
    Itch::ParseResult result = Itch::parse(systemEvent, sizeof(systemEvent), captureMessage);

    ASSERT_EQ(result.status, Itch::ParseStatus::OK);
    ASSERT_EQ(static_cast<char>(captureMessage.systemEvent.messageType), 'S');
    ASSERT_EQ(captureMessage.systemEvent.stockLocate, 1234);
    ASSERT_EQ(captureMessage.systemEvent.trackingNumber, 1337);
    ASSERT_EQ(Itch::parseTimestamp(captureMessage.systemEvent.timeStamp.data), 34200000000000);
    ASSERT_EQ(static_cast<char>(captureMessage.systemEvent.eventCode), 'O');
}

TEST(ItchParser, ParseStockDirectoryMessage)
{
    const char stockDirectory[] = {
        'R',                                            // Message Type: StockDirectory
        '\x04', '\xD2',                                 // Stock Locate: 1234
        '\x05', '\x39',                                 // Tracking Number: 1337
        '\x1F', '\x1A', '\xCE', '\xD9', '\xF0', '\x00', // Timestamp: 34,200,000,000,000 ns
        'A', 'A', 'P', 'L', ' ', ' ', ' ', ' ',         // Stock: "AAPL    "
        'Q',                                            // Market Category: 'Q' (Nasdaq)
        'N',                                            // Financial Status: 'N' (Normal)
        '\x00', '\x00', '\x00', '\x64',                 // Round Lot Size: 100
        'N',                                            // Round Lots Only: 'N'
        'C',                                            // Issue Classification: 'C'
        'Z', ' ',                                       // Issue Sub-Type: "Z "
        'P',                                            // Authenticity: 'P' (Production)
        'N',                                            // Short Sale Threshold: 'N'
        ' ',                                            // IPO Flag: ' '
        '1',                                            // LULD Reference Price Tier: '1'
        'N',                                            // ETP Flag: 'N'
        '\x00', '\x00', '\x00', '\x00',                 // ETP Leverage Factor: 0
        'N'                                             // Inverse Indicator: 'N'
    };

    CaptureMessage captureMessage;
    Itch::ParseResult result = Itch::parse(stockDirectory, sizeof(stockDirectory), captureMessage);

    ASSERT_EQ(result.status, Itch::ParseStatus::OK);
    ASSERT_EQ(static_cast<char>(captureMessage.stockDirectory.messageType), 'R');
    ASSERT_EQ(captureMessage.stockDirectory.stockLocate, 1234);
    ASSERT_EQ(captureMessage.stockDirectory.trackingNumber, 1337);
    ASSERT_EQ(Itch::parseTimestamp(captureMessage.stockDirectory.timeStamp.data), 34200000000000);
    ASSERT_EQ(std::string(captureMessage.stockDirectory.stock, 8), "AAPL    ");
    ASSERT_EQ(static_cast<char>(captureMessage.stockDirectory.marketCategory), 'Q');
    ASSERT_EQ(static_cast<char>(captureMessage.stockDirectory.financialStatusIndicator), 'N');
    ASSERT_EQ(captureMessage.stockDirectory.roundLotSize, 100);
    ASSERT_EQ(static_cast<char>(captureMessage.stockDirectory.roundLotsOnly), 'N');
    ASSERT_EQ(static_cast<char>(captureMessage.stockDirectory.issueClassification), 'C');
    ASSERT_EQ(std::string(captureMessage.stockDirectory.issueSubType.data, 2), "Z ");
    ASSERT_EQ(static_cast<char>(captureMessage.stockDirectory.authenticity), 'P');
    ASSERT_EQ(static_cast<char>(captureMessage.stockDirectory.shortSaleThresholdIndicator), 'N');
    ASSERT_EQ(static_cast<char>(captureMessage.stockDirectory.IPOFlag), ' ');
    ASSERT_EQ(static_cast<char>(captureMessage.stockDirectory.LULDReferencePriceTier), '1');
    ASSERT_EQ(static_cast<char>(captureMessage.stockDirectory.ETPFlag), 'N');
    ASSERT_EQ(captureMessage.stockDirectory.ETPLeverageFactor, 0);
    ASSERT_EQ(static_cast<char>(captureMessage.stockDirectory.inverseIndicator), 'N');
}

TEST(ItchParser, ParseStockTradingActionMessage)
{
    const char stockTradingAction[] = {
        'H',                                            // Message Type: StockTradingAction
        '\x04', '\xD2',                                 // Stock Locate: 1234
        '\x05', '\x39',                                 // Tracking Number: 1337
        '\x1F', '\x1A', '\xCE', '\xD9', '\xF0', '\x00', // Timestamp: 34,200,000,000,000 ns
        'A', 'A', 'P', 'L', ' ', ' ', ' ', ' ',         // Stock: "AAPL    "
        'T',                                            // Trading State: 'T' (Trading)
        ' ',                                            // Reserved
        ' ', ' ', ' ', ' '                              // Reason: "    "
    };

    CaptureMessage captureMessage;
    Itch::ParseResult result = Itch::parse(stockTradingAction, sizeof(stockTradingAction), captureMessage);

    ASSERT_EQ(result.status, Itch::ParseStatus::OK);
    ASSERT_EQ(static_cast<char>(captureMessage.stockTradingAction.messageType), 'H');
    ASSERT_EQ(captureMessage.stockTradingAction.stockLocate, 1234);
    ASSERT_EQ(captureMessage.stockTradingAction.trackingNumber, 1337);
    ASSERT_EQ(Itch::parseTimestamp(captureMessage.stockTradingAction.timeStamp.data), 34200000000000);
    ASSERT_EQ(std::string(captureMessage.stockTradingAction.stock, 8), "AAPL    ");
    ASSERT_EQ(static_cast<char>(captureMessage.stockTradingAction.tradingState), 'T');
    ASSERT_EQ(captureMessage.stockTradingAction.reserved, ' ');
    ASSERT_EQ(std::string(captureMessage.stockTradingAction.reason, 4), "    ");
}

TEST(ItchParser, ParseAddOrderMessage)
{
    const char addOrder[] = {
        'A',                                                            // Message Type: AddOrder
        '\x04', '\xD2',                                                 // Stock Locate: 1234
        '\x05', '\x39',                                                 // Tracking Number: 1337
        '\x1F', '\x1A', '\xCE', '\xD9', '\xF0', '\x00',                 // Timestamp: 34,200,000,000,000 ns
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x04', '\xD2', // Order Reference: 1234
        'B',                                                            // Buy/Sell: 'B' (Buy)
        '\x00', '\x00', '\x00', '\x64',                                 // Shares: 100
        'A', 'A', 'P', 'L', ' ', ' ', ' ', ' ',                         // Stock: "AAPL    "
        '\x00', '\x16', '\xE3', '\x60'                                  // Price: 1,500,000 ($150.00)
    };

    CaptureMessage captureMessage;
    Itch::ParseResult result = Itch::parse(addOrder, sizeof(addOrder), captureMessage);

    ASSERT_EQ(result.status, Itch::ParseStatus::OK);
    ASSERT_EQ(static_cast<char>(captureMessage.addOrder.messageType), 'A');
    ASSERT_EQ(captureMessage.addOrder.stockLocate, 1234);
    ASSERT_EQ(captureMessage.addOrder.trackingNumber, 1337);
    ASSERT_EQ(Itch::parseTimestamp(captureMessage.addOrder.timeStamp.data), 34200000000000);
    ASSERT_EQ(captureMessage.addOrder.orderRefNum, 1234);
    ASSERT_EQ(static_cast<char>(captureMessage.addOrder.buySell), 'B');
    ASSERT_EQ(captureMessage.addOrder.shares, 100);
    ASSERT_EQ(std::string(captureMessage.addOrder.stock, 8), "AAPL    ");
    ASSERT_EQ(captureMessage.addOrder.price, 1500000);
}

TEST(ItchParser, ParseAddOrderMPIDMessage)
{
    const char addOrderMpid[] = {
        'F',                                                            // Message Type: AddOrderMPID
        '\x04', '\xD2',                                                 // Stock Locate: 1234
        '\x05', '\x39',                                                 // Tracking Number: 1337
        '\x1F', '\x1A', '\xCE', '\xD9', '\xF0', '\x00',                 // Timestamp: 34,200,000,000,000 ns
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x02', // Order Reference: 2
        'S',                                                            // Buy/Sell: 'S' (Sell)
        '\x00', '\x00', '\x01', '\xF4',                                 // Shares: 500
        'A', 'A', 'P', 'L', ' ', ' ', ' ', ' ',                         // Stock: "AAPL    "
        '\x00', '\x17', '\x70', '\x00',                                 // Price: 1,536,000 ($153.60)
        'G', 'S', ' ', ' '                                              // Attribution: "GS  "
    };

    CaptureMessage captureMessage;
    Itch::ParseResult result = Itch::parse(addOrderMpid, sizeof(addOrderMpid), captureMessage);

    ASSERT_EQ(result.status, Itch::ParseStatus::OK);
    ASSERT_EQ(static_cast<char>(captureMessage.addOrderMPID.messageType), 'F');
    ASSERT_EQ(captureMessage.addOrderMPID.stockLocate, 1234);
    ASSERT_EQ(captureMessage.addOrderMPID.trackingNumber, 1337);
    ASSERT_EQ(Itch::parseTimestamp(captureMessage.addOrderMPID.timeStamp.data), 34200000000000);
    ASSERT_EQ(captureMessage.addOrderMPID.orderRefNum, 2);
    ASSERT_EQ(static_cast<char>(captureMessage.addOrderMPID.buySell), 'S');
    ASSERT_EQ(captureMessage.addOrderMPID.shares, 500);
    ASSERT_EQ(std::string(captureMessage.addOrderMPID.stock, 8), "AAPL    ");
    ASSERT_EQ(captureMessage.addOrderMPID.price, 1536000);
    ASSERT_EQ(std::string(captureMessage.addOrderMPID.attribution, 4), "GS  ");
}

TEST(ItchParser, ParseOrderExecutedMessage)
{
    const char orderExecuted[] = {
        'E',                                                            // Message Type: OrderExecuted
        '\x04', '\xD2',                                                 // Stock Locate: 1234
        '\x05', '\x39',                                                 // Tracking Number: 1337
        '\x1F', '\x1A', '\xCE', '\xD9', '\xF0', '\x00',                 // Timestamp: 34,200,000,000,000 ns
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x01', '\x1E', '\xCD', // Order Reference: 73421
        '\x00', '\x00', '\x00', '\x32',                                 // Executed Shares: 50
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x08', '\x64', '\xEB'  // Match Number: 550123
    };

    CaptureMessage captureMessage;
    Itch::ParseResult result = Itch::parse(orderExecuted, sizeof(orderExecuted), captureMessage);

    ASSERT_EQ(result.status, Itch::ParseStatus::OK);
    ASSERT_EQ(static_cast<char>(captureMessage.orderExecuted.messageType), 'E');
    ASSERT_EQ(captureMessage.orderExecuted.stockLocate, 1234);
    ASSERT_EQ(captureMessage.orderExecuted.trackingNumber, 1337);
    ASSERT_EQ(Itch::parseTimestamp(captureMessage.orderExecuted.timeStamp.data), 34200000000000);
    ASSERT_EQ(captureMessage.orderExecuted.orderRefNum, 73421);
    ASSERT_EQ(captureMessage.orderExecuted.executedShares, 50);
    ASSERT_EQ(captureMessage.orderExecuted.matchNumber, 550123);
}

TEST(ItchParser, ParseOrderExecutedWithPriceMessage)
{
    const char orderExecutedWithPrice[] = {
        'C',                                                            // Message Type: OrderExecutedWithPrice
        '\x04', '\xD2',                                                 // Stock Locate: 1234
        '\x05', '\x39',                                                 // Tracking Number: 1337
        '\x1F', '\x1A', '\xCE', '\xD9', '\xF0', '\x00',                 // Timestamp: 34,200,000,000,000 ns
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x01', '\x1E', '\xCD', // Order Reference: 73421
        '\x00', '\x00', '\x00', '\x32',                                 // Executed Shares: 50
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x08', '\x64', '\xEB', // Match Number: 550123
        'Y',                                                            // Printable: 'Y'
        '\x00', '\x16', '\xE3', '\x60'                                  // Execution Price: 1,500,000 ($150.00)
    };

    CaptureMessage captureMessage;
    Itch::ParseResult result = Itch::parse(orderExecutedWithPrice, sizeof(orderExecutedWithPrice), captureMessage);

    ASSERT_EQ(result.status, Itch::ParseStatus::OK);
    ASSERT_EQ(static_cast<char>(captureMessage.orderExecutedWithPrice.messageType), 'C');
    ASSERT_EQ(captureMessage.orderExecutedWithPrice.stockLocate, 1234);
    ASSERT_EQ(captureMessage.orderExecutedWithPrice.trackingNumber, 1337);
    ASSERT_EQ(Itch::parseTimestamp(captureMessage.orderExecutedWithPrice.timeStamp.data), 34200000000000);
    ASSERT_EQ(captureMessage.orderExecutedWithPrice.orderRefNum, 73421);
    ASSERT_EQ(captureMessage.orderExecutedWithPrice.executedShares, 50);
    ASSERT_EQ(captureMessage.orderExecutedWithPrice.matchNumber, 550123);
    ASSERT_EQ(static_cast<char>(captureMessage.orderExecutedWithPrice.printable), 'Y');
    ASSERT_EQ(captureMessage.orderExecutedWithPrice.price, 1500000);
}

TEST(ItchParser, ParseOrderCancelMessage)
{
    const char orderCancel[] = {
        'X',                                                            // Message Type: OrderCancel
        '\x04', '\xD2',                                                 // Stock Locate: 1234
        '\x00', '\x00',                                                 // Tracking Number: 0
        '\x1F', '\x1A', '\xCE', '\xD9', '\xF0', '\x00',                 // Timestamp: 34,200,000,000,000 ns
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x04', '\xD2', // Order Reference: 1234
        '\x00', '\x00', '\x00', '\x32'                                  // Cancelled Shares: 50
    };

    CaptureMessage captureMessage;
    Itch::ParseResult result = Itch::parse(orderCancel, sizeof(orderCancel), captureMessage);

    ASSERT_EQ(result.status, Itch::ParseStatus::OK);
    ASSERT_EQ(static_cast<char>(captureMessage.orderCancel.messageType), 'X');
    ASSERT_EQ(captureMessage.orderCancel.stockLocate, 1234);
    ASSERT_EQ(captureMessage.orderCancel.trackingNumber, 0);
    ASSERT_EQ(Itch::parseTimestamp(captureMessage.orderCancel.timeStamp.data), 34200000000000);
    ASSERT_EQ(captureMessage.orderCancel.orderRefNum, 1234);
    ASSERT_EQ(captureMessage.orderCancel.cancelledShares, 50);
}

TEST(ItchParser, ParseOrderDeleteMessage)
{
    const char orderDelete[] = {
        'D',                                                           // Message Type: OrderDelete
        '\x04', '\xD2',                                                // Stock Locate: 1234
        '\x05', '\x39',                                                // Tracking Number: 1337
        '\x1F', '\x1A', '\xCE', '\xD9', '\xF0', '\x00',                // Timestamp: 34,200,000,000,000 ns
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x04', '\xD2' // Order Reference: 1234
    };

    CaptureMessage captureMessage;
    Itch::ParseResult result = Itch::parse(orderDelete, sizeof(orderDelete), captureMessage);

    ASSERT_EQ(result.status, Itch::ParseStatus::OK);
    ASSERT_EQ(static_cast<char>(captureMessage.orderDelete.messageType), 'D');
    ASSERT_EQ(captureMessage.orderDelete.stockLocate, 1234);
    ASSERT_EQ(captureMessage.orderDelete.trackingNumber, 1337);
    ASSERT_EQ(Itch::parseTimestamp(captureMessage.orderDelete.timeStamp.data), 34200000000000);
    ASSERT_EQ(captureMessage.orderDelete.orderRefNum, 1234);
}

TEST(ItchParser, ParseOrderReplaceMessage)
{
    const char orderReplace[] = {
        'U',                                                            // Message Type: OrderReplace
        '\x04', '\xD2',                                                 // Stock Locate: 1234
        '\x05', '\x39',                                                 // Tracking Number: 1337
        '\x1F', '\x1A', '\xCE', '\xD9', '\xF0', '\x00',                 // Timestamp: 34,200,000,000,000 ns
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x04', '\xD2', // Original Order Reference: 1234
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x03', // New Order Reference: 3
        '\x00', '\x00', '\x00', '\x64',                                 // Shares: 100
        '\x00', '\x17', '\x70', '\x00'                                  // Price: 1,536,000 ($153.60)
    };

    CaptureMessage captureMessage;
    Itch::ParseResult result = Itch::parse(orderReplace, sizeof(orderReplace), captureMessage);

    ASSERT_EQ(result.status, Itch::ParseStatus::OK);
    ASSERT_EQ(static_cast<char>(captureMessage.orderReplace.messageType), 'U');
    ASSERT_EQ(captureMessage.orderReplace.stockLocate, 1234);
    ASSERT_EQ(captureMessage.orderReplace.trackingNumber, 1337);
    ASSERT_EQ(Itch::parseTimestamp(captureMessage.orderReplace.timeStamp.data), 34200000000000);
    ASSERT_EQ(captureMessage.orderReplace.originalOrderRefNum, 1234);
    ASSERT_EQ(captureMessage.orderReplace.newOrderRefNum, 3);
    ASSERT_EQ(captureMessage.orderReplace.shares, 100);
    ASSERT_EQ(captureMessage.orderReplace.price, 1536000);
}

TEST(ItchParser, ParseUnknownMessageType)
{
    const char unknown[] = {'?', '\x00', '\x00'};

    CaptureMessage captureMessage;
    Itch::ParseResult result = Itch::parse(unknown, sizeof(unknown), captureMessage);

    ASSERT_EQ(result.status, Itch::ParseStatus::UnknownMessageType);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}