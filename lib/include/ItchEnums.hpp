#ifndef ITCHENUMS_HPP_
#define ITCHENUMS_HPP_

#include <cstdint>

namespace Itch
{
    enum class MessageType : char
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

    enum class BuySell : char
    {
        BuyOrder = 'B',
        SellOrder = 'S'
    };

    enum class Printable : char
    {
        NonPrintable = 'N',
        Printable = 'Y'
    };

    enum class EventCode : char
    {
        MessagesStart = 'O',
        SystemHoursStart = 'S',
        MarketHoursStart = 'Q',
        MarketHoursEnd = 'M',
        SystemHoursEnd = 'E',
        MessagesEnd = 'C'
    };

    enum class MarketCategory : char
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

    enum class FinancialStatusIndicator : char
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

    enum class RoundLotsOnly : char
    {
        OnlyAcceptRoundLots = 'Y',
        NoOrderSizeRestrictions = 'N'
    };

    enum class IssueClassification : char
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

    enum class IssueClarificationValues : char
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

    enum class Authenticity : char
    {
        Live = 'P',
        Test = 'T',
    };

    enum class ShortSaleThresholdIndicator : char
    {
        RestrictedIssue = 'Y',
        NotRestricitedIssue = 'N',
        NotAvailable = ' ',
    };

    enum class IPOFlag : char
    {
        IPOSecurity = 'Y',
        NotIPOSecurity = 'N',
        NotAvailable = ' ',
    };

    enum class LULDReferencePriceTier : char
    {
        Tier1 = '1',
        Tier2 = '2',
        NotAvailable = ' ',
    };

    enum class ETPFlag : char
    {
        ETP = 'Y',
        NotETP = 'N',
        NotAvailable = ' ',
    };

    enum class InverseIndicator : char
    {
        InverseETP = 'Y',
        NotInverseETP = 'N'
    };

    enum class TradingState : char
    {
        Halted = 'H',
        Paused = 'P',
        QuotationOnly = 'Q',
        TradingNasdaq = 'T'
    };
};

#endif /* !ITCHENUMS_HPP_ */