#ifndef ITCHPARSER_HPP_
#define ITCHPARSER_HPP_

#include <iostream>
#include <string>
#include <type_traits>
#include "ItchMessages.hpp"
#include "Byteswap.hpp"

namespace Itch
{
    enum class ParseStatus
    {
        OK,
        UnknownMessageType,
    };

    struct ParseResult
    {
        ParseStatus status;
        std::size_t bytes;
    };

    template <typename MsgType, typename Handler>
    ParseResult parseAs(const char *buffer, std::size_t length, Handler &&handler)
    {
        MsgType message{*reinterpret_cast<const MsgType *>(buffer)};
        networkToHost(message);
        handler(message);
        ParseResult result{
            .status = ParseStatus::OK,
            .bytes = sizeof(MsgType),
        };
        return result;
    }

    template <typename Handler>
    ParseResult parse(const char *message, size_t length, Handler &&handler)
    {
        switch (MessageType(message[0]))
        {
        case MessageType::AddOrder:
            return parseAs<Itch::AddOrderMessage>(message, length, std::forward<Handler>(handler));
        case MessageType::AddOrderMPID:
            return parseAs<Itch::AddOrderMPIDMessage>(message, length, std::forward<Handler>(handler));
        case MessageType::OrderExecuted:
            return parseAs<Itch::OrderExecutedMessage>(message, length, std::forward<Handler>(handler));
        case MessageType::OrderExecutedWithPrice:
            return parseAs<Itch::OrderExecutedWithPriceMessage>(message, length, std::forward<Handler>(handler));
        case MessageType::OrderCancel:
            return parseAs<Itch::OrderCancelMessage>(message, length, std::forward<Handler>(handler));
        case MessageType::OrderDelete:
            return parseAs<Itch::OrderDeleteMessage>(message, length, std::forward<Handler>(handler));
        case MessageType::OrderReplace:
            return parseAs<Itch::OrderReplaceMessage>(message, length, std::forward<Handler>(handler));
        case MessageType::SystemEvent:
            return parseAs<Itch::SystemEventMessage>(message, length, std::forward<Handler>(handler));
        case MessageType::StockDirectory:
            return parseAs<Itch::StockDirectoryMessage>(message, length, std::forward<Handler>(handler));
        case MessageType::StockTradingAction:
            return parseAs<Itch::StockTradingActionMessage>(message, length, std::forward<Handler>(handler));
        default:
        {
            ParseResult result{
                .status = ParseStatus::UnknownMessageType,
                .bytes = length};
            return result;
        }
        }
    }
}

#endif /* !ITCHPARSER_HPP_ */