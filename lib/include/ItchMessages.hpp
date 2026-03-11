#ifndef ITCHMESSAGES_HPP_
#define ITCHMESSAGES_HPP_

#include "ItchEnums.hpp"

// Disable padding
#pragma pack(push, 1)
namespace Itch
{
    struct TimeStamp
    {
        uint8_t data[6];
    };

    struct IssueSubType
    {
        char data[2];
    };

    struct AddOrderMessage
    {
        MessageType messageType;
        uint16_t stockLocate;
        uint16_t trackingNumber;
        TimeStamp timeStamp;
        uint64_t orderRefNum;
        BuySell buySell;
        uint32_t shares;
        char stock[8];
        uint32_t price;
    };

    struct AddOrderMPIDMessage
    {
        MessageType messageType;
        uint16_t stockLocate;
        uint16_t trackingNumber;
        TimeStamp timeStamp;
        uint64_t orderRefNum;
        BuySell buySell;
        uint32_t shares;
        char stock[8];
        uint32_t price;
        char attribution[4];
    };

    struct OrderExecutedMessage
    {
        MessageType messageType;
        uint16_t stockLocate;
        uint16_t trackingNumber;
        TimeStamp timeStamp;
        uint64_t orderRefNum;
        uint32_t executedShares;
        uint64_t matchNumber;
    };

    struct OrderExecutedWithPriceMessage
    {
        MessageType messageType;
        uint16_t stockLocate;
        uint16_t trackingNumber;
        TimeStamp timeStamp;
        uint64_t orderRefNum;
        uint32_t executedShares;
        uint64_t matchNumber;
        Printable printable;
        uint32_t price;
    };

    struct OrderCancelMessage
    {
        MessageType messageType;
        uint16_t stockLocate;
        uint16_t trackingNumber;
        TimeStamp timeStamp;
        uint64_t orderRefNum;
        uint32_t cancelledShares;
    };

    struct OrderDeleteMessage
    {
        MessageType messageType;
        uint16_t stockLocate;
        uint16_t trackingNumber;
        TimeStamp timeStamp;
        uint64_t orderRefNum;
    };

    struct OrderReplaceMessage
    {
        MessageType messageType;
        uint16_t stockLocate;
        uint16_t trackingNumber;
        TimeStamp timeStamp;
        uint64_t originalOrderRefNum;
        uint64_t newOrderRefNum;
        uint32_t shares;
        uint32_t price;
    };

    struct SystemEventMessage
    {
        MessageType messageType;
        uint16_t stockLocate;
        uint16_t trackingNumber;
        TimeStamp timeStamp;
        EventCode eventCode;
    };

    struct StockDirectoryMessage
    {
        MessageType messageType;
        uint16_t stockLocate;
        uint16_t trackingNumber;
        TimeStamp timeStamp;
        char stock[8];
        MarketCategory marketCategory;
        FinancialStatusIndicator financialStatusIndicator;
        uint32_t roundLotSize;
        RoundLotsOnly roundLotsOnly;
        IssueClassification issueClassification;
        IssueSubType issueSubType;
        Authenticity authenticity;
        ShortSaleThresholdIndicator shortSaleThresholdIndicator;
        enum IPOFlag IPOFlag;
        enum LULDReferencePriceTier LULDReferencePriceTier;
        enum ETPFlag ETPFlag;
        uint32_t ETPLeverageFactor;
        InverseIndicator inverseIndicator;
    };

    struct StockTradingActionMessage
    {
        MessageType messageType;
        uint16_t stockLocate;
        uint16_t trackingNumber;
        TimeStamp timeStamp;
        char stock[8];
        TradingState tradingState;
        char reserved;
        char reason[4];
    };
};
// Restore padding
#pragma pack(pop)

#endif /* !ITCHMESSAGES_HPP_ */