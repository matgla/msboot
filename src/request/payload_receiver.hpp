#pragma once

#include <cstdint>
#include <type_traits>

#include <gsl/span>

#include <eul/container/static_vector.hpp>
#include <eul/function.hpp>

#include <hal/common/timer/timeout_timer.hpp>
#include <hal/common/timer/timer_manager.hpp>
#include <hal/time/time.hpp>

namespace request
{

constexpr std::size_t BUFFER_SIZE = 255;

class PayloadReceiver
{
public:
    using StreamType       = gsl::span<const uint8_t>;
    using WriterCallback   = eul::function<void(const StreamType&), sizeof(void*)>;
    using TransmitCallback = eul::function<void(const StreamType&), sizeof(void*)>;
    PayloadReceiver(const WriterCallback& writer, const TransmitCallback& transmitter, hal::time::Time& time, hal::common::timer::TimerManager& timer_manager);

    void receive(const uint8_t byte);

private:
    enum class ProcessingState : uint8_t
    {
        Completed,
        NotCompleted
    };

    enum class ControlByte : uint8_t
    {
        StartFrame = 0x7e,
        EndFrame   = 0x55,
        EscapeCode = 0x7c
    };

    enum class ControlMessage : uint8_t
    {
        Ack  = 0x01,
        Nack = 0x02
    };

    enum class NackReason : uint8_t
    {
        WrongMessageType = 0x01,
        CrcMismatch      = 0x02
    };

    enum class States : uint8_t
    {
        Idle,
        StartTransmission,
        ReceivingTransactionId,
        ReceivingMessageType,
        ReceivingLength,
        ReceivingPayload,
        ReceivingCrc,
        ReceivingControlPayload,
        VerifyPayload,
        TransmissionEnd
    };

    enum class MessageType : uint8_t
    {
        Control = 1,
        Data    = 2
    };

    ProcessingState receiveControl(const ControlByte byte);

    void receiveLength(const uint8_t byte);
    void receiveMessageType(const uint8_t byte);
    void receivePayload(const uint8_t byte);
    void receiveCrc(const uint8_t byte);
    void receiveControlCallback(const uint8_t byte);
    bool verifyPayload();
    void processState(const uint8_t byte);

    void processPayload();
    void respondNack(const NackReason reason) const;
    void respondAck() const;

    WriterCallback writer_;
    TransmitCallback transmitter_;

    eul::container::static_vector<uint8_t, BUFFER_SIZE> buffer_;
    eul::container::static_vector<uint8_t, 4> crc_buffer_;

    uint8_t transaction_id_;
    uint8_t payload_length_;
    States state_;
    MessageType type_;
    bool receiving_special_character_;

    hal::common::timer::TimeoutTimer<hal::time::Time> timer_;
};

} // namespace request