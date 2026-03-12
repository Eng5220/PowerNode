#include "hardware/FlowMeter.h"

#include <lgpio.h>
#include <iostream>

// ─────────────────────────────────────────────────────────────────────────────

FlowMeter::FlowMeter(int gpioHandle, int flowPin, double mlPerPulse)
    : handle_(gpioHandle),
      flowPin_(flowPin),
      mlPerPulse_(mlPerPulse),
      initialised_(false),
      callbackId_(-1),
      pulseCount_(0)
{
}

FlowMeter::~FlowMeter() {
    shutdown();
}

// ─────────────────────────────────────────────────────────────────────────────

bool FlowMeter::init() {
    // Claim flow pin as input
    if (lgGpioClaimInput(handle_, 0, flowPin_) != 0) {
        std::cerr << "ERROR: Failed to claim FLOW pin " << flowPin_ << "\n";
        return false;
    }

    // Register alert callback for rising edge
    // lgGpioClaimAlert takes: handle, flags, eFlags (edge), pin, -1 (no debounce)
    // eFlags: LG_RISING_EDGE = 1
    if (lgGpioClaimAlert(handle_, 0, LG_RISING_EDGE, flowPin_, -1) != 0) {
        std::cerr << "ERROR: Failed to claim alert on FLOW pin " << flowPin_ << "\n";
        return false;
    }

    // Set the callback — lgGpioSetAlertsFunc is called on every edge event
    // 'this' pointer passed as userdata so the static callback can access the instance
    callbackId_ = lgGpioSetAlertsFunc(handle_, flowPin_, FlowMeter::pulseCallback, this);
    if (callbackId_ < 0) {
        std::cerr << "ERROR: Failed to set callback on FLOW pin " << flowPin_ << "\n";
        return false;
    }

    pulseCount_ = 0;
    initialised_ = true;

    std::cout << "FlowMeter initialised (PIN=" << flowPin_
              << ", calibration=" << mlPerPulse_ << " ml/pulse)\n";
    return true;
}

void FlowMeter::shutdown() {
    if (initialised_) {
        // Remove callback and free pin
        lgGpioSetAlertsFunc(handle_, flowPin_, nullptr, nullptr);
        lgGpioFree(handle_, flowPin_);
        initialised_ = false;
        std::cout << "FlowMeter shut down.\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────────

void FlowMeter::pulseCallback(int e, lgGpioAlert_p evt, void* userdata) {
    // Called automatically by lgpio on every rising edge of the flow sensor
    // Each rising edge = one pulse = one unit of water passed through
    FlowMeter* self = static_cast<FlowMeter*>(userdata);
    if (self != nullptr) {
        self->pulseCount_.fetch_add(1, std::memory_order_relaxed);
    }
}

// ─────────────────────────────────────────────────────────────────────────────

double FlowMeter::getVolumeML() const {
    return pulseCount_.load(std::memory_order_relaxed) * mlPerPulse_;
}

int FlowMeter::getPulseCount() const {
    return pulseCount_.load(std::memory_order_relaxed);
}

void FlowMeter::resetCount() {
    pulseCount_.store(0, std::memory_order_relaxed);
    std::cout << "FlowMeter counter reset.\n";
}

bool FlowMeter::hasReachedTarget(double targetML) const {
    return getVolumeML() >= targetML;
}
