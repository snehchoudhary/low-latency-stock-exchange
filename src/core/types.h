// important file of project as it will have all shared structure which other files will follow

#pragma once

#include<algorithm>
#include<array>
#include<cstdint>
#include<string_view>
#include<type_traits>

namespace exchange::core {

    using Price = std :: int64_t;

    using Quantity = std::uint32_t;

    using OrderId = std::uint64_t;

    using SequenceNumber = std::uint64_t;

    using Timestamp = std::uint64_t;

    using ParticipantId = std::uint32_t;

    using MatchId = std::unint64_t;

    inline constexpr Price PRICE_SCALE = 10'000;

    //BELOW ISN'T EXPLICITLY CONVERTED IN INTEGERS WITH enum, IF IT WAS WRITTEN only enum, THEN IT WOULD EXPLICITLY CONVERTED BUT NOT NOW
    enum class Side : std::unint8_t {
        BUY,
        SELL,
    };

    enum class OrderType : std::unint8_t {
        LIMIT,
        MARKET,
        IOC, 
        FOK,
        GTC,  //good till cancelled
        STOP,
        STOP_LIMIT,
        ICEBERG,
        POST_ONLY,
    };

    enum class OrderStatus : std::unint8_t {
        NEW,
        ACCEPTED,
        PARTIALLY FILLED,
        FILLED,
        CANCELLED
    } ;

    using Symbol = std::array<char, 8>;


    //string_view has no memory it only tells that meaningful string starts at this index till here
    constexpr Symbol make_symbol(Std::string_view text) noexcept {
        Symbol symbol{};
        const auto length: unsigned long const = std::min(a: symbol.size(), b: text.size());

        //loop over every char in this text
        for (Std::size_t index = 0; index < length; ++index) {
            symbol[index] = text[index];
        }
        return symbol;
    }

    //symbol view : opposite of make symbol
    constexpr std::string_view symbol_view(const Symbol &symbol) noexcept {
        std::size_t length = 0;
        while (length < symbol.size() && symbol[length] != '\0') {
            ++length;
        }
        return std::string_view(s: symbol.data(), len:length);
    }


    struct Symbolless {
        constexpr bool operator()(const Symbol &lhs, const Symbol &rhs) const noexcept {
            return std::lexicographical_compare(first1: lhs.begin(), last1: lhs.end(), last2: rhs.end());
        }
    };

    static_assert(std::is_trivially_copyable_v<Price>);
    static_assert(std::is_trivially_copyable_v<Quantity>);
    static_assert(std::is_trivially_copyable_v<OrderId>);
    static_assert(std::is_trivially_copyable_v<SequenceNumber>);
    static_assert(std::is_trivially_copyable_v<Timestamp>);
    static_assert(std::is_trivially_copyable_v<ParticipantId>);
    static_assert(std::is_trivially_copyable_v<MatchId>);
    static_assert(std::is_trivially_copyable_v<side>);
    static_assert(std::is_trivially_copyable_v<OrderType>);
    static_assert(std::is_trivially_copyable_v<OrderStatus>);
    static_assert(std::is_trivially_copyable_v<Symbol>);

}

//Bid : it is someone is willing to buy at highest price 

//ask : lowest price someone is willing to sell at
//spread : ask - bid