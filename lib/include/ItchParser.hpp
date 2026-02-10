#ifndef ITCHPARSER_HPP_
#define ITCHPARSER_HPP_

#include <iostream>

namespace Itch
{
    enum class ParseStatus
    {
        OK,
        UnknownMessageType,
        Truncated,
    };

    template <typename MsgType, typename Handler>
    ParseStatus parseAs(const char *buffer, std::size_t length, Handler &&handler)
    {
        if (length < sizeof(MsgType))
        {
            return ParseStatus::Truncated;
        }
        MsgType message{*reinterpret_cast<const MsgType *>(buffer)};
        networkToHost(message);
        handler(message);
        return ParseStatus::OK;
    }

    template <typename Handler>
    ParseStatus parse(const char *message, size_t length, Handler &&handler)
    {
        if (length < 1)
        {
            return ParseStatus::Truncated;
        }
        switch (MessageType(message[0]))
        {
        case MessageType::AddOrder:
            return parseAs<AddOrder>(message, length, std::forward<Handler>(handler));
        case MessageType::AddOrderMPID:
            return parseAs<AddOrderMPID>(message, length, std::forward<Handler>(handler));
            return parseAs<OrderExecuted>(message, length, std::forward<Handler>(handler));
        case MessageType::OrderExecutedWithPrice:
            return parseAs<OrderExecutedWithPrice>(message, length, std::forward<Handler>(handler));
        case MessageType::OrderCancel:
            return parseAs<OrderCancel>(message, length, std::forward<Handler>(handler));
        case MessageType::OrderDelete:
            return parseAs<OrderDelete>(message, length, std::forward<Handler>(handler));
        case MessageType::OrderReplace:
            return parseAs<OrderReplace>(message, length, std::forward<Handler>(handler));
        case MessageType::SystemEvent:
            return parseAs<SystemEvent>(message, length, std::forward<Handler>(handler));
        case MessageType::StockDirectory:
            return parseAs<StockDirectory>(message, length, std::forward<Handler>(handler));
        case MessageType::StockTradingAction:
            return parseAs<StockTradingAction>(message, length, std::forward<Handler>(handler));
        default:
            return ParseStatus::UnknownMessageType;
        }
    }
}

#endif /* !ITCHPARSER_HPP_ */