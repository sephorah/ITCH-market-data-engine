#ifndef BYTESWAP_HPP_
#define BYTESWAP_HPP_

#include <cstdint>
#include <bit>
#include "ItchMessages.hpp"

namespace Itch
{
    template <typename T>
    void networkToHost(T &) = delete;

    uint64_t parseTimestamp(const uint8_t *a)
    {
        return (
            (static_cast<uint64_t>(__builtin_bswap16(*(reinterpret_cast<const uint16_t *>(a)))) << 32) |
            static_cast<uint64_t>(__builtin_bswap32(*(reinterpret_cast<const uint32_t *>(a + 2)))));
    }

    template <>
    inline void networkToHost<AddOrderMessage>(AddOrderMessage &msg)
    {
        msg.stockLocate = __builtin_bswap16(msg.stockLocate);
        msg.trackingNumber = __builtin_bswap16(msg.trackingNumber);
        msg.orderRefNum = __builtin_bswap64(msg.orderRefNum);
        msg.shares = __builtin_bswap32(msg.shares);
        msg.price = __builtin_bswap32(msg.price);
    }

    template <>
    inline void networkToHost<AddOrderMPIDMessage>(AddOrderMPIDMessage &msg)
    {
        msg.stockLocate = __builtin_bswap16(msg.stockLocate);
        msg.trackingNumber = __builtin_bswap16(msg.trackingNumber);
        msg.orderRefNum = __builtin_bswap64(msg.orderRefNum);
        msg.shares = __builtin_bswap32(msg.shares);
        msg.price = __builtin_bswap32(msg.price);
    }

    template <>
    inline void networkToHost<OrderExecutedMessage>(OrderExecutedMessage &msg)
    {
        msg.stockLocate = __builtin_bswap16(msg.stockLocate);
        msg.trackingNumber = __builtin_bswap16(msg.trackingNumber);
        msg.orderRefNum = __builtin_bswap64(msg.orderRefNum);
        msg.executedShares = __builtin_bswap32(msg.executedShares);
        msg.matchNumber = __builtin_bswap64(msg.matchNumber);
    }

    template <>
    inline void networkToHost<OrderExecutedWithPriceMessage>(OrderExecutedWithPriceMessage &msg)
    {
        uint32_t price = std::bit_cast<uint32_t>(msg.price);

        msg.stockLocate = __builtin_bswap16(msg.stockLocate);
        msg.trackingNumber = __builtin_bswap16(msg.trackingNumber);
        msg.orderRefNum = __builtin_bswap64(msg.orderRefNum);
        msg.executedShares = __builtin_bswap32(msg.executedShares);
        msg.matchNumber = __builtin_bswap64(msg.matchNumber);
        msg.price = __builtin_bswap32(price);
    }

    template <>
    inline void networkToHost<OrderCancelMessage>(OrderCancelMessage &msg)
    {
        msg.stockLocate = __builtin_bswap16(msg.stockLocate);
        msg.trackingNumber = __builtin_bswap16(msg.trackingNumber);
        msg.orderRefNum = __builtin_bswap64(msg.orderRefNum);
        msg.cancelledShares = __builtin_bswap32(msg.cancelledShares);
    }

    template <>
    inline void networkToHost<OrderDeleteMessage>(OrderDeleteMessage &msg)
    {
        msg.stockLocate = __builtin_bswap16(msg.stockLocate);
        msg.trackingNumber = __builtin_bswap16(msg.trackingNumber);
        msg.orderRefNum = __builtin_bswap64(msg.orderRefNum);
    }

    template <>
    inline void networkToHost<OrderReplaceMessage>(OrderReplaceMessage &msg)
    {
        uint32_t price = std::bit_cast<uint32_t>(msg.price);

        msg.stockLocate = __builtin_bswap16(msg.stockLocate);
        msg.trackingNumber = __builtin_bswap16(msg.trackingNumber);
        msg.originalOrderRefNum = __builtin_bswap64(msg.originalOrderRefNum);
        msg.newOrderRefNum = __builtin_bswap64(msg.newOrderRefNum);
        msg.shares = __builtin_bswap32(msg.shares);
        msg.price = __builtin_bswap32(price);
    }

    template <>
    inline void networkToHost<SystemEventMessage>(SystemEventMessage &msg)
    {
        msg.stockLocate = __builtin_bswap16(msg.stockLocate);
        msg.trackingNumber = __builtin_bswap16(msg.trackingNumber);
    }

    template <>
    inline void networkToHost<StockDirectoryMessage>(StockDirectoryMessage &msg)
    {
        msg.stockLocate = __builtin_bswap16(msg.stockLocate);
        msg.trackingNumber = __builtin_bswap16(msg.trackingNumber);
        msg.roundLotSize = __builtin_bswap32(msg.roundLotSize);
        msg.ETPLeverageFactor = __builtin_bswap32(msg.ETPLeverageFactor);
    }

    template <>
    inline void networkToHost<StockTradingActionMessage>(StockTradingActionMessage &msg)
    {
        msg.stockLocate = __builtin_bswap16(msg.stockLocate);
        msg.trackingNumber = __builtin_bswap16(msg.trackingNumber);
    }
}

#endif /* !BYTESWAP_HPP_ */