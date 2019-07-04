#pragma once

#include <csignal>
#include <stdexcept>

struct signal_stopper_t {
    sigset_t m_orig_set;
    bool m_signals_masked;
    signal_stopper_t() : m_orig_set(), m_signals_masked(true) {
        sigset_t set;
        sigfillset(&set);
        sigemptyset(&m_orig_set);
        if (pthread_sigmask(SIG_SETMASK, &set, &m_orig_set)) {
            throw std::runtime_error("Couldn't mask out Signals during server init");
        }
    }
    void restore_signals() {
        if (pthread_sigmask(SIG_SETMASK, &m_orig_set, NULL)) {
            throw std::runtime_error("Couldn't unmask out Signals during server shutdown");
        }
        m_signals_masked = false;
    }
    ~signal_stopper_t() {
        if (m_signals_masked) {
            restore_signals();
        }
    }
};

