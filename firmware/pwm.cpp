#include "pwm.h"

#include "hal.h"

Pwm::Pwm(PWMDriver& driver, uint8_t channel, uint32_t counterFrequency, uint32_t counterPeriod)
    : m_driver(&driver)
    , m_channel(channel)
    , m_counterFrequency(counterFrequency)
    , m_counterPeriod(counterPeriod)
{
}

void Pwm::Start()
{
    PWMConfig config = {
        m_counterFrequency,
        m_counterPeriod,
        nullptr,
        {
            {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW, nullptr},
            {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW, nullptr},
            {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW, nullptr},
            {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW, nullptr}
        },
        0,
        0,
#if STM32_PWM_USE_ADVANCED
        0
#endif
    };

    pwmStart(m_driver, &config);
}

float maxF(float i1, float i2) {
	return i1 > i2 ? i1 : i2;
}

float minF(float i1, float i2) {
	return i1 < i2 ? i1 : i2;
}

float clampF(float min, float clamp, float max) {
	return maxF(min, minF(clamp, max));
}

void Pwm::SetDuty(float duty) {
    pwmcnt_t highTime = m_counterPeriod * clampF(0, duty, 1);

    m_lastDuty = highTime;

    pwm_lld_enable_channel(m_driver, m_channel, highTime);
}

uint16_t Pwm::GetLastDuty() const
{
    return m_lastDuty;
}
