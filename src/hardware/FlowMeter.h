#ifndef FLOWMETER_H
#define FLOWMETER_H

#include "IHardwareDevice.h"
#include <atomic>
#include <functional>

/**
 * @brief YF-S401 Flow Meter driver.
 *
 * The YF-S401 is a hall-effect flow sensor that outputs electrical pulses
 * as water passes through it. Each pulse represents a fixed volume of water.
 *
 * This class:
 *   - Registers a GPIO callback (interrupt) to count pulses automatically
 *   - Converts pulse count to millilitres using a calibration constant
 *   - Uses std::atomic for thread-safe pulse counting (ISR → main thread)
 *
 * Calibration: ML_PER_PULSE is defined in PinConfig.h (default 2.25 ml)
 */
class FlowMeter : public IHardwareDevice {
public:
    /**
     * @param gpioHandle   Handle returned by lgGpiochipOpen().
     * @param flowPin      BCM pin number for pulse input.
     * @param mlPerPulse   Millilitres of water per pulse (calibration constant).
     */
    FlowMeter(int gpioHandle, int flowPin, double mlPerPulse);
    ~FlowMeter() override;

    bool init() override;
    void shutdown() override;

    /** @brief Get total volume dispensed since last reset (in ml). */
    double getVolumeML() const;

    /** @brief Get the raw pulse count since last reset. */
    int getPulseCount() const;

    /** @brief Reset the pulse counter to zero (for next bottle). */
    void resetCount();

    /**
     * @brief Check if the target volume has been reached.
     * @param targetML  Target volume in millilitres.
     * @return true if dispensed volume >= targetML.
     */
    bool hasReachedTarget(double targetML) const;

    /**
     * @brief Static callback function for lgpio alert.
     *
     * lgpio calls this on every rising edge of the flow sensor pin.
     * The userdata pointer points to this FlowMeter instance.
     */
    static void pulseCallback(int e, lgGpioAlert_p evt, void* userdata);

private:
    int handle_;
    int flowPin_;
    double mlPerPulse_;
    bool initialised_;
    int callbackId_;

    /** Atomic pulse counter — safe to increment from ISR/callback thread. */
    std::atomic<int> pulseCount_;
};

#endif // FLOWMETER_H
