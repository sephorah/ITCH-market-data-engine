#ifndef CAPTUREMESSAGE_HPP_
#define CAPTUREMESSAGE_HPP_

#include "ItchMessages.hpp"

struct CaptureMessage
{
    Itch::SystemEventMessage systemEvent;
    Itch::StockDirectoryMessage stockDirectory;
    Itch::StockTradingActionMessage stockTradingAction;
    Itch::AddOrderMessage addOrder;
    Itch::AddOrderMPIDMessage addOrderMPID;
    Itch::OrderExecutedMessage orderExecuted;
    Itch::OrderExecutedWithPriceMessage orderExecutedWithPrice;
    Itch::OrderCancelMessage orderCancel;
    Itch::OrderDeleteMessage orderDelete;
    Itch::OrderReplaceMessage orderReplace;

    void operator()(const Itch::SystemEventMessage &msg) { systemEvent = msg; }
    void operator()(const Itch::StockDirectoryMessage &msg) { stockDirectory = msg; }
    void operator()(const Itch::StockTradingActionMessage &msg) { stockTradingAction = msg; }
    void operator()(const Itch::AddOrderMessage &msg) { addOrder = msg; }
    void operator()(const Itch::AddOrderMPIDMessage &msg) { addOrderMPID = msg; }
    void operator()(const Itch::OrderExecutedMessage &msg) { orderExecuted = msg; }
    void operator()(const Itch::OrderExecutedWithPriceMessage &msg) { orderExecutedWithPrice = msg; }
    void operator()(const Itch::OrderCancelMessage &msg) { orderCancel = msg; }
    void operator()(const Itch::OrderDeleteMessage &msg) { orderDelete = msg; }
    void operator()(const Itch::OrderReplaceMessage &msg) { orderReplace = msg; }
};

#endif /* !CAPTUREMESSAGE_HPP_ */