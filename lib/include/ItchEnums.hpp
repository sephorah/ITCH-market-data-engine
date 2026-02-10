#ifndef ITCHENUMS_HPP_
#define ITCHENUMS_HPP_

#include <cstdint>

namespace Itch
{
    enum class MessageType : uint8_t
    {
        AddOrder = 'A',
        AddOrderMPID = 'F',
        OrderExecuted = 'E',
        OrderExecutedWithPrice = 'C',
        OrderCancel = 'X',
        OrderDelete = 'D',
        OrderReplace = 'U',
        SystemEvent = 'S',
        StockDirectory = 'R',
        StockTradingAction = 'H'
    };

    enum class BuySell : uint8_t
    {
        BuyOrder = 'B',
        SellOrder = 'S'
    };

    enum class Printable : uint8_t
    {
        NonPrintable = 'N',
        Printable = 'Y'
    };

    enum class EventCode : uint8_t
    {
        MessagesStart = 'O',
        SystemHoursStart = 'S',
        MarketHoursStart = 'Q',
        MarketHoursEnd = 'M',
        SystemHoursEnd = 'E',
        MessagesEnd = 'C'
    };

    enum class MarketCategory : uint8_t
    {
        NasdaqGlobalSelectMarket = 'Q',
        NasdaqGlobalMarket = 'G',
        NasdaqCapitalMarket = 'S',
        NYSE = 'N',
        NYSEAmerican = 'A',
        NYSEArca = 'P',
        BATSZExchange = 'Z',
        InvestorsExchange = 'V',
        NotAvailable = ' '
    };

    enum class FinancialStatusIndicator : uint8_t
    {
        Deficient = 'D',
        Delinquent = 'E',
        Bankrupt = 'Q',
        Suspended = 'S',
        DeficientBankrupt = 'G',
        DeficientDelinquent = 'H',
        DelinquentBankrupt = 'J',
        DeficientDelinquentBankrupt = 'K',
        ETFSuspended = 'C', // Creations/Redemptions suspended for ETPs
        Normal = 'N',
        NotAvailable = ' ',
    };

    enum class RoundLotsOnly : uint8_t
    {
        OnlyAcceptRoundLots = 'Y',
        NoOrderSizeRestrictions = 'N'
    };

    enum class IssueClarificationValues : uint8_t
    {
        AmericanDepositaryShare = 'A',
        Bond = 'B',
        CommonStock = 'C',
        DepositoryReceipt = 'F',
        I144A = 'I',
        LimitedPartnership = 'L',
        Notes = 'N',
        OrdinaryShare = 'O',
        PreferredStock = 'P',
        OtherSecurities = 'Q',
        Right = 'R',
        SharesofBeneficialInterest = 'S',
        ConvertibleDebenture = 'T',
        Unit = 'U',
        UnitsBenifInt = 'V',
        Warrant = 'W'
    };

    enum class Authenticity : uint8_t
    {
        Live = 'P',
        Test = 'T',
    };

    enum class ShortSaleThresholdIndicator : uint8_t
    {
        RestrictedIssue = 'Y',
        NotRestricitedIssue = 'N',
        NotAvailable = ' ',
    };

    enum class IPOFlag : uint8_t
    {
        IPOSecurity = 'Y',
        NotIPOSecurity = 'N',
        NotAvailable = ' ',
    };

    enum class LULDReferencePriceTier : uint8_t
    {
        Tier1 = '1',
        Tier2 = '2',
        NotAvailable = ' ',
    };

    enum class ETPFlag : uint8_t
    {
        ETP = 'Y',
        NotETP = 'N',
        NotAvailable = ' ',
    };

    enum class InverseIndicator : uint8_t
    {
        InverseETP = 'Y',
        NotInverseETP = 'N'
    };

    enum class TradingState : uint8_t
    {
        Halted = 'H',
        Paused = 'P',
        QuotationOnly = 'Q',
        TradingNasdaq = 'T'
    };
};

#endif /* !ITCHENUMS_HPP_ */